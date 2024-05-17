#include <iostream>
#include <WS2tcpip.h> // 包含 Winsock 头文件
#pragma comment(lib, "ws2_32.lib") // 链接 ws2_32.lib 库

int main() {
    // 初始化 Winsock
    WSADATA wsData;
    WORD ver = MAKEWORD(2, 2);
    int wsOk = WSAStartup(ver, &wsData);
    if (wsOk != 0) {
        std::cerr << "Can't initialize Winsock! Quitting" << std::endl;
        return -1;
    }

    // 创建 UDP 套接字
    SOCKET udpSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (udpSocket == INVALID_SOCKET) {
        std::cerr << "Can't create socket! Quitting" << std::endl;
        WSACleanup();
        return -1;
    }

    // 绑定客户端地址和端口
    sockaddr_in clientAddr;
    clientAddr.sin_family = AF_INET;
    clientAddr.sin_port = htons(10086); // 与服务器端端口相同
    clientAddr.sin_addr.s_addr = INADDR_ANY;
    if (bind(udpSocket, (struct sockaddr*)&clientAddr, sizeof(clientAddr)) == SOCKET_ERROR) {
        std::cerr << "Can't bind socket! Quitting" << std::endl;
        closesocket(udpSocket);
        WSACleanup();
        return -1;
    }

    while(true){
        char buf[1024];
        sockaddr_in serverAddr;
        int serverSize = sizeof(serverAddr);

        int bytesReceived = recvfrom(udpSocket, buf, sizeof(buf), 0, (struct sockaddr*)&serverAddr, &serverSize);
        if (bytesReceived == SOCKET_ERROR) {
            std::cerr << "Error in recvfrom()! Quitting" << std::endl;
            closesocket(udpSocket);
            WSACleanup();
            return -1;
        }

        std::cout << "Received from " << inet_ntoa(serverAddr.sin_addr) << ": " << std::string(buf, bytesReceived) << std::endl;
        if(std::string(buf, bytesReceived) == "exit"){
            // 关闭套接字和清理 Winsock
            closesocket(udpSocket);
            WSACleanup();
            return 0;
        }
    }
    
    return 0;
}
