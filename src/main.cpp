#include <string>

#include "server.h"


int main() {
    Server server("127.0.0.1", 9090);
    if (server.Init()) server.Listen();

    return 0;
}