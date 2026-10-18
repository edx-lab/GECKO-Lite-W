from pathlib import Path
import re
import zipfile

root = Path(__file__).resolve().parents[1]
issues = []
sources = [p for base in ('src', 'include') for p in (root / base).rglob('*') if p.suffix in ('.h', '.hpp', '.cpp', '.c')]
for p in sources:
    s = p.read_text(encoding='utf-8')
    # All project-root includes should resolve without removed modules.
    for inc in re.findall(r'^\s*#include\s*[<"]((?:modules|core)/[^">]+)[">]', s, re.M):
        if not (root / 'src' / inc).is_file(): issues.append(f'{p.relative_to(root)}: missing {inc}')
    # Verify directive nesting after selecting the software-clock branches.
    stack = []
    for n, line in enumerate(s.splitlines(), 1):
        m = re.match(r'^\s*#(if|ifdef|ifndef|else|elif|endif)\b', line)
        if not m: continue
        op = m.group(1)
        if op in ('if', 'ifdef', 'ifndef'): stack.append(n)
        elif not stack: issues.append(f'{p.relative_to(root)}:{n}: unmatched {op}')
        elif op == 'endif': stack.pop()
    if stack: issues.append(f'{p.relative_to(root)}: unclosed directives {stack}')

archive = root / '.gecko-backup/before-wifi-ble.zip'
if archive.is_file():
    z = zipfile.ZipFile(archive)
    for name in ('src/core/settings.h', 'src/core/config.h', 'src/core/configPins.h'):
        before = z.read(name).decode('utf-8')
        after = (root / name).read_text(encoding='utf-8')
        pattern = r'\b(?:void|int|bool)\s+(\w+)\s*\('
        removed = set(re.findall(pattern, before)) - set(re.findall(pattern, after))
        for p in sources:
            s = p.read_text(encoding='utf-8')
            s = re.sub(r'//[^\n]*|/\*[\s\S]*?\*/', '', s)
            for symbol in removed:
                if re.search(r'\b' + symbol + r'\s*\(', s): issues.append(f'{p.relative_to(root)}: removed API {symbol}')
    removed_files = [n for n in z.namelist() if not (root / n).exists()]
    z.close()
    print(f'Archived source files no longer in working tree: {len(removed_files)} (includes relocated network files)')
else:
    removed_files = []
    print('Historical backup absent: skipping comparison with the original firmware.')

for issue in issues: print(issue)
print(f'Static reference/directive audit: {len(issues)} issues in {len(sources)} files. No compilation performed.')
raise SystemExit(bool(issues))
