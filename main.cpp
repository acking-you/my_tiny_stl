#include <iostream>
#include "TCP_SOCKET_CLIENT.h"

using namespace std;

int main() {
    TCP_SOCKET_CLIENT a;
    const char *URL = "github.com";
    a.Gethostbyname(URL);

}