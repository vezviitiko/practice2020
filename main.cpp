#include <QCoreApplication>
#include <iostream>
#include "socket.h"
#include "string.h"

bool socket_test();

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    if (!socket_test()) {
        std::cout << "eh";
    }
    return a.exec();
}

bool socket_test() {
    SocketController test;

    unsigned short port = 30000;
    Socket socket;
    socket.open(port);

    unsigned char a = 127, b = 0, c = 0, d = 1;
    Address target(a, b, c, d, port);

    const char packet_data[] = "hello world!";
    int packet_size = 14;

    int result = socket.send(target, packet_data, packet_size);
    if ( !result ) {
        printf( "failed to send packet" );
        return false;
    }
    else
        std::cout << " all okey " << result << std::endl;

    for (int i = 0; i < 10; i++) {
        Address sender;
        char buffer[256];
        if (socket.receive( sender, buffer, 255 ) > 0) {
            char buf2[14];
            strncpy(buf2, buffer, 14);
            std::cout << buf2 << std::endl;
        }
        else
            break;
    }

    socket.close();

    return true;
}

