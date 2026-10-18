#!/usr/bin/env bash
set -euo pipefail

cd /work

# Match .github/workflows/PR_All_envs.yml matrix envs
DEFAULT_ENVS=(esp32-s3-n16r8)

if [[ -n "${PIO_ENVS:-}" ]]; then
  # Space-separated list
  read -r -a ENVS <<<"${PIO_ENVS}"
else
  ENVS=("${DEFAULT_ENVS[@]}")
fi

# Ensure platformio sees all needed platforms/packages
platformio --version

JOBS="${PIO_JOBS:-5}"

failed=()

for ((i = 0; i < ${#ENVS[@]}; i += JOBS)); do
  batch=("${ENVS[@]:i:JOBS}")

  pids=()
  pid_envs=()
  for e in "${batch[@]}"; do
    echo "===== platformio run -e ${e} ====="
    platformio run -e "${e}" &
    pids+=("$!")
    pid_envs+=("${e}")
  done

  for idx in "${!pids[@]}"; do
    pid="${pids[$idx]}"
    e="${pid_envs[$idx]}"
    if ! wait "${pid}"; then
      failed+=("${e}")
    fi
  done
done

if ((${#failed[@]} > 0)); then
  echo "Build failures: ${failed[*]}" >&2
  exit 1
fi

exit 0
