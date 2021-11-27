#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;
#pragma comment(lib, "Ws2_32.lib")
#include <winsock2.h>
#include <string.h>
#include <time.h>
#include<Windows.h>
#define TIME_PORT	27015

void main()
{
	WSAData wsaData;
	if (NO_ERROR != WSAStartup(MAKEWORD(2, 2), &wsaData))
	{
		cout << "Time Server: Error at WSAStartup()\n";
		return;
	}

	SOCKET m_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (INVALID_SOCKET == m_socket)
	{
		cout << "Time Server: Error at socket(): " << WSAGetLastError() << endl;
		WSACleanup();
		return;
	}

	sockaddr_in serverService;
	serverService.sin_family = AF_INET;
	serverService.sin_addr.s_addr = INADDR_ANY;	//inet_addr("127.0.0.1");
	serverService.sin_port = htons(TIME_PORT);

	if (SOCKET_ERROR == bind(m_socket, (SOCKADDR *)&serverService, sizeof(serverService)))
	{
		cout << "Time Server: Error at bind(): " << WSAGetLastError() << endl;
		closesocket(m_socket);
		WSACleanup();
		return;
	}

	sockaddr client_addr;
	int client_addr_len = sizeof(client_addr);
	int bytesSent = 0;
	int bytesRecv = 0;
	char sendBuff[255];
	char recvBuff[255];
	time_t t13start, t13end;
	int t13flag = 0;
	cout << "Time Server: Wait for clients' requests.\n";
	long t1, t2;
	while (true)
	{

		bytesRecv = recvfrom(m_socket, recvBuff, 255, 0, &client_addr, &client_addr_len);
		if (SOCKET_ERROR == bytesRecv)
		{
			cout << "Time Server: Error at recvfrom(): " << WSAGetLastError() << endl;
			closesocket(m_socket);
			WSACleanup();
			return;
		}

		recvBuff[bytesRecv] = '\0'; 

		if (strcmp(recvBuff,"1") == 0) {
			time_t timer;
			time(&timer);

			strcpy(sendBuff, ctime(&timer));
			sendBuff[strlen(sendBuff) - 1] = '\0'; //to remove the new-line from the created string

			bytesSent = sendto(m_socket, sendBuff, (int)strlen(sendBuff), 0, (const sockaddr *)&client_addr, client_addr_len);
			if (SOCKET_ERROR == bytesSent)
			{
				cout << "Time Server: Error at sendto(): " << WSAGetLastError() << endl;
				closesocket(m_socket);
				WSACleanup();
				return;
			}
		}
		else if (strcmp(recvBuff, "2") == 0) {
			struct tm* ptr;
			time_t t;
			t = time(NULL);
			ptr = localtime(&t);
			strftime(sendBuff, 255, "%X", ptr);
			sendBuff[strlen(sendBuff)] = '\0'; //to remove the new-line from the created string

			bytesSent = sendto(m_socket, sendBuff, (int)strlen(sendBuff), 0, (const sockaddr *)&client_addr, client_addr_len);
			if (SOCKET_ERROR == bytesSent)
			{
				cout << "Time Server: Error at sendto(): " << WSAGetLastError() << endl;
				closesocket(m_socket);
				WSACleanup();
				return;
			}
		}
		else if (strcmp(recvBuff, "3") == 0) {
			time_t timer;
			timer = time(NULL);
			sprintf(sendBuff, "%d seconds since epoch time", timer);
			sendBuff[strlen(sendBuff)] = '\0'; //to remove the new-line from the created string

			bytesSent = sendto(m_socket, sendBuff, (int)strlen(sendBuff), 0, (const sockaddr *)&client_addr, client_addr_len);
			if (SOCKET_ERROR == bytesSent)
			{
				cout << "Time Server: Error at sendto(): " << WSAGetLastError() << endl;
				closesocket(m_socket);
				WSACleanup();
				return;
			}
		}
		else if (strcmp(recvBuff, "4") == 0) {
			DWORD t = GetTickCount();
			int ticket = t;
			sprintf(sendBuff, "%d", ticket);
			sendBuff[strlen(sendBuff)] = '\0'; //to remove the new-line from the created string

			bytesSent = sendto(m_socket, sendBuff, (int)strlen(sendBuff), 0, (const sockaddr *)&client_addr, client_addr_len);
			if (SOCKET_ERROR == bytesSent)
			{
				cout << "Time Server: Error at sendto(): " << WSAGetLastError() << endl;
				closesocket(m_socket);
				WSACleanup();
				return;
			}
		}
		else if (strcmp(recvBuff, "5") == 0) {
			strcpy(sendBuff, "hello there");
			sendBuff[strlen(sendBuff)] = '\0'; //to remove the new-line from the created string

			bytesSent = sendto(m_socket, sendBuff, (int)strlen(sendBuff), 0, (const sockaddr *)&client_addr, client_addr_len);
			if (SOCKET_ERROR == bytesSent)
			{
				cout << "Time Server: Error at sendto(): " << WSAGetLastError() << endl;
				closesocket(m_socket);
				WSACleanup();
				return;
			}
		}
		else if (strcmp(recvBuff, "6") == 0) {
			struct tm* ptr;
			time_t t;
			t = time(NULL);
			ptr = localtime(&t);
			strftime(sendBuff, 255, "%R", ptr);
			sendBuff[strlen(sendBuff)] = '\0'; //to remove the new-line from the created string

			bytesSent = sendto(m_socket, sendBuff, (int)strlen(sendBuff), 0, (const sockaddr *)&client_addr, client_addr_len);
			if (SOCKET_ERROR == bytesSent)
			{
				cout << "Time Server: Error at sendto(): " << WSAGetLastError() << endl;
				closesocket(m_socket);
				WSACleanup();
				return;
			}
		}
		else if (strcmp(recvBuff, "7") == 0) {
			struct tm* ptr;
			time_t t;
			t = time(NULL);
			ptr = localtime(&t);
			strftime(sendBuff, 255, "%Y", ptr);
			sendBuff[strlen(sendBuff)] = '\0'; //to remove the new-line from the created string

			bytesSent = sendto(m_socket, sendBuff, (int)strlen(sendBuff), 0, (const sockaddr *)&client_addr, client_addr_len);
			if (SOCKET_ERROR == bytesSent)
			{
				cout << "Time Server: Error at sendto(): " << WSAGetLastError() << endl;
				closesocket(m_socket);
				WSACleanup();
				return;
			}
		}
		else if (strcmp(recvBuff, "8") == 0) {
		struct tm* ptr;
		time_t t;
		t = time(NULL);
		ptr = localtime(&t);
		strftime(sendBuff, 255, "%B %A", ptr);
		sendBuff[strlen(sendBuff)] = '\0'; //to remove the new-line from the created string

		bytesSent = sendto(m_socket, sendBuff, (int)strlen(sendBuff), 0, (const sockaddr *)&client_addr, client_addr_len);
		if (SOCKET_ERROR == bytesSent)
		{
			cout << "Time Server: Error at sendto(): " << WSAGetLastError() << endl;
			closesocket(m_socket);
			WSACleanup();
			return;
		}
		}
		else if (strcmp(recvBuff, "9") == 0) {
		struct tm* ptr;
		time_t t1,t2;
		t1 = time(NULL);
		ptr = localtime(&t1);
		ptr->tm_hour = 0;
		ptr->tm_min = 0;
		ptr->tm_sec = 0;
		ptr->tm_mday=0;
		t2 = mktime(ptr);
		t1 = t1 - t2;
		sprintf(sendBuff, "%d seconds since beginning of month ", t1);
		sendBuff[strlen(sendBuff)] = '\0'; //to remove the new-line from the created string

		bytesSent = sendto(m_socket, sendBuff, (int)strlen(sendBuff), 0, (const sockaddr *)&client_addr, client_addr_len);
		if (SOCKET_ERROR == bytesSent)
		{
			cout << "Time Server: Error at sendto(): " << WSAGetLastError() << endl;
			closesocket(m_socket);
			WSACleanup();
			return;
		}
		}
		else if (strcmp(recvBuff, "10") == 0) {
		struct tm* ptr;
		time_t t;
		t = time(NULL);
		ptr = localtime(&t);
		strftime(sendBuff, 255, "%U", ptr);
		sendBuff[strlen(sendBuff)] = '\0'; //to remove the new-line from the created string

		bytesSent = sendto(m_socket, sendBuff, (int)strlen(sendBuff), 0, (const sockaddr *)&client_addr, client_addr_len);
		if (SOCKET_ERROR == bytesSent)
		{
			cout << "Time Server: Error at sendto(): " << WSAGetLastError() << endl;
			closesocket(m_socket);
			WSACleanup();
			return;
		}
		}
		else if (strcmp(recvBuff, "11") == 0) {
		struct tm* ptr;
		time_t t;
		t = time(NULL);
		ptr = localtime(&t);
		if(ptr->tm_isdst>0)
			sprintf(sendBuff, "%d  ", 1);
		else
			sprintf(sendBuff, "%d  ", 0);
		sendBuff[strlen(sendBuff)] = '\0'; //to remove the new-line from the created string

		bytesSent = sendto(m_socket, sendBuff, (int)strlen(sendBuff), 0, (const sockaddr *)&client_addr, client_addr_len);
		if (SOCKET_ERROR == bytesSent)
		{
			cout << "Time Server: Error at sendto(): " << WSAGetLastError() << endl;
			closesocket(m_socket);
			WSACleanup();
			return;
		}
		}
		else if (recvBuff[0]=='1'&&recvBuff[1]=='2') {
		struct tm* ptr;
		time_t t;
		t = time(NULL);
		ptr = gmtime(&t);
		if (strcmp(recvBuff + 2, "tokyo") == 0) {
			sprintf(sendBuff, "%d:%d:%d  ", (ptr->tm_hour+9)%24,ptr->tm_min,ptr->tm_sec);
		}
		else if (strcmp(recvBuff + 2, "melbourne") == 0) {
			sprintf(sendBuff, "%d:%d:%d  ", (ptr->tm_hour + 11) % 24, ptr->tm_min, ptr->tm_sec);
		}
		else if (strcmp(recvBuff + 2, "san francisco") == 0) {
			sprintf(sendBuff, "%d:%d:%d  ", (ptr->tm_hour - 8) % 24, ptr->tm_min, ptr->tm_sec);
		}
		else if (strcmp(recvBuff + 2, "porto") == 0) {
			sprintf(sendBuff, "%d:%d:%d  ", (ptr->tm_hour) % 24, ptr->tm_min, ptr->tm_sec);
		}
		else {
			sprintf(sendBuff, " city not in the list: returning universal time: %d:%d:%d  ", (ptr->tm_hour) % 24, ptr->tm_min, ptr->tm_sec);
		}
		sendBuff[strlen(sendBuff)] = '\0'; //to remove the new-line from the created string

		bytesSent = sendto(m_socket, sendBuff, (int)strlen(sendBuff), 0, (const sockaddr *)&client_addr, client_addr_len);
		if (SOCKET_ERROR == bytesSent)
		{
			cout << "Time Server: Error at sendto(): " << WSAGetLastError() << endl;
			closesocket(m_socket);
			WSACleanup();
			return;
		}
		}
		else if (strcmp(recvBuff, "13") == 0) {
			if (t13flag == 0){
				time(&t13start);
				t13flag = 1;
				strcpy(sendBuff, "started measuring time lap");

				sendBuff[strlen(sendBuff)] = '\0'; //to remove the new-line from the created string
				bytesSent = sendto(m_socket, sendBuff, (int)strlen(sendBuff), 0, (const sockaddr *)&client_addr, client_addr_len);
				if (SOCKET_ERROR == bytesSent)
				{
					cout << "Time Server: Error at sendto(): " << WSAGetLastError() << endl;
					closesocket(m_socket);
					WSACleanup();
					return;
				}
			}
			else if (t13flag == 1) {
				time(&t13end);
				if (t13start + 180 < t13end)
				{
					time(&t13start);
					t13flag = 1;
					strcpy(sendBuff, "started measuring time lap");

					sendBuff[strlen(sendBuff) - 1] = '\0'; //to remove the new-line from the created string
					bytesSent = sendto(m_socket, sendBuff, (int)strlen(sendBuff), 0, (const sockaddr *)&client_addr, client_addr_len);
					if (SOCKET_ERROR == bytesSent)
					{
						cout << "Time Server: Error at sendto(): " << WSAGetLastError() << endl;
						closesocket(m_socket);
						WSACleanup();
						return;
					}
				}
				else {
					t13end -= t13start;
					t13flag = 0;
					sprintf(sendBuff, "measure time lap is: %d", t13end);

					sendBuff[strlen(sendBuff)] = '\0'; //to remove the new-line from the created string
					bytesSent = sendto(m_socket, sendBuff, (int)strlen(sendBuff), 0, (const sockaddr *)&client_addr, client_addr_len);
					if (SOCKET_ERROR == bytesSent)
					{
						cout << "Time Server: Error at sendto(): " << WSAGetLastError() << endl;
						closesocket(m_socket);
						WSACleanup();
						return;
					}
				}
			}
		}
		else {
			strcpy(sendBuff, "i don't support this command\0");
			bytesSent = sendto(m_socket, sendBuff, (int)strlen(sendBuff), 0, (const sockaddr *)&client_addr, client_addr_len);
			if (SOCKET_ERROR == bytesSent)
			{
				cout << "Time Server: Error at sendto(): " << WSAGetLastError() << endl;
				closesocket(m_socket);
				WSACleanup();
				return;
			}
		}
		cout << "Time Server: Sent: " << bytesSent << "\\" << strlen(sendBuff) << " bytes of \"" << sendBuff << "\" message.\n";
	}

	// Closing connections and Winsock.
	cout << "Time Server: Closing Connection.\n";
	closesocket(m_socket);
	WSACleanup();
}