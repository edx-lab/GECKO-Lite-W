#if !defined(LITE_VERSION)

#ifndef GECKO_NETIF_CLIENT_H
#define GECKO_NETIF_CLIENT_H

#include "Arduino.h"

class NetifClient {
public:
    NetifClient();
    ~NetifClient();
    int connect(IPAddress ip, uint16_t port, int32_t timeout_ms);
    void client_close(int sockfd);
    bool connected(int sockfd);
};

#endif
#endif
