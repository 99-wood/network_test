#include <iostream>
#include <string>
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

    // 设置广播权限
    BOOL broadcastEnable = TRUE;
    if (setsockopt(udpSocket, SOL_SOCKET, SO_BROADCAST, (const char*)&broadcastEnable, sizeof(broadcastEnable)) == SOCKET_ERROR) {
        std::cerr << "Can't set socket option! Quitting" << std::endl;
        closesocket(udpSocket);
        WSACleanup();
        return -1;
    }

    // 设置服务器地址和端口
    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(54000); // 选择任意端口
    serverAddr.sin_addr.s_addr = INADDR_BROADCAST; // 广播地址

    // 发送广播消息
    
    while(true){
        std::string message;
        std::cin >> message;
        sendto(udpSocket, message.c_str(), message.size(), 0, (struct sockaddr*)&serverAddr, sizeof(serverAddr));

        std::cout << "Broadcast message sent." << std::endl;
        if(message == "exit"){
            // 关闭套接字和清理 Winsock
            closesocket(udpSocket);
            WSACleanup();
            return 0;
        }
    }
    

    return 0;
}
