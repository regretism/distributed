#include <stdio.h>
#include <winsock2.h>
#include <WS2tcpip.h>

#pragma comment(lib, "ws2_32.lib") // Для линковки с библиотекой ws2_32.lib

int main() {
    WSADATA wsaData;
    SOCKET clientSocket;
    struct sockaddr_in serverAddr;
    char buffer[1024];

    // Инициализация Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        printf("Failed to initialize Winsock\n");
        return 1;
    }

    // Создание сокета
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == INVALID_SOCKET) {
        printf("Failed to create socket\n");
        WSACleanup();
        return 1;
    }

    // Настройка параметров сервера
    serverAddr.sin_family = AF_INET;
    InetPton(AF_INET, "127.0.0.1", &(serverAddr.sin_addr)); // Используем InetPton вместо inet_pton
    serverAddr.sin_port = htons(12345);

    // Подключение к серверу
    if (connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        printf("Connection failed: %d\n", WSAGetLastError());
        closesocket(clientSocket);
        WSACleanup();
        return 1;
    }

    printf("Connected to server\n");

    // Отправка данных на сервер
    strcpy_s(buffer, sizeof(buffer), "Hello from client");
    if (send(clientSocket, buffer, strlen(buffer), 0) == SOCKET_ERROR) {
        printf("Send failed: %d\n", WSAGetLastError());
        closesocket(clientSocket);
        WSACleanup();
        return 1;
    }

    // Получение ответа от сервера
    memset(buffer, 0, sizeof(buffer));
    int bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);
    if (bytesReceived == SOCKET_ERROR) {
        printf("Receive failed: %d\n", WSAGetLastError());
    }
    else if (bytesReceived == 0) {
        printf("Connection closed by server\n");
    }
    else {
        printf("Received from server: %s\n", buffer);
    }

    // Закрытие сокета и выход
    closesocket(clientSocket);
    WSACleanup();

    return 0;
}
