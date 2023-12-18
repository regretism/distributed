#include <stdio.h>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib") // Для линковки с библиотекой ws2_32.lib

int main() {
    WSADATA wsaData;
    SOCKET serverSocket, clientSocket;
    struct sockaddr_in serverAddr, clientAddr;
    int clientAddrLen = sizeof(clientAddr);
    char buffer[1024];

    // Инициализация Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        printf("Failed to initialize Winsock\n");
        return 1;
    }

    // Создание сокета
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == INVALID_SOCKET) {
        printf("Failed to create socket\n");
        WSACleanup();
        return 1;
    }

    // Настройка параметров сервера
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(12345);

    // Привязка сокета к адресу
    if (bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        printf("Bind failed\n");
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }

    // Ожидание подключения клиента
    listen(serverSocket, 1);
    printf("Waiting for a client to connect...\n");

    // Принятие подключения
    clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddr, &clientAddrLen);
    if (clientSocket == INVALID_SOCKET) {
        printf("Accept failed\n");
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }

    printf("Client connected\n");

    // Обмен данными с клиентом
    while (1) {
        memset(buffer, 0, sizeof(buffer));
        int bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);
        if (bytesReceived == SOCKET_ERROR) {
            printf("Receive failed: %d\n", WSAGetLastError());
            break;
        }
        else if (bytesReceived == 0) {
            printf("Connection closed by client\n");
            break;
        }

        printf("Received from client: %s\n", buffer);

        // Отправка ответа клиенту
        strcpy_s(buffer, sizeof(buffer), "Hello from server");
        if (send(clientSocket, buffer, strlen(buffer), 0) == SOCKET_ERROR) {
            printf("Send failed: %d\n", WSAGetLastError());
            break;
        }
    }

    // Закрытие сокетов и выход
    closesocket(clientSocket);
    closesocket(serverSocket);
    WSACleanup();

    return 0;
}
