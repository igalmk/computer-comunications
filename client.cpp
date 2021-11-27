#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <iostream>
using namespace std;
#pragma comment(lib, "Ws2_32.lib")
#include <winsock2.h> 
#include <string.h>
#include<Windows.h>

#define TIME_PORT	27015

void main()
{
	WSAData wsaData;
	if (NO_ERROR != WSAStartup(MAKEWORD(2, 2), &wsaData))
	{
		cout << "Time Client: Error at WSAStartup()\n";
		return;
	}
	SOCKET connSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (INVALID_SOCKET == connSocket)
	{
		cout << "Time Client: Error at socket(): " << WSAGetLastError() << endl;
		WSACleanup();
		return;
	}

	sockaddr_in server;
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = inet_addr("127.0.0.1");
	server.sin_port = htons(TIME_PORT);
	int bytesSent = 0;
	int bytesRecv = 0;
	char sendBuff[255];
	char recvBuff[255];
	bool cont = TRUE;

	while (cont) {
		cout << "press 1 to get time" << endl;
		cout << "press 2 to get time without date " << endl;
		cout << "press 3 to get time since epoch" << endl;
		cout << "press 4 to get client to server delay estimation" << endl;
		cout << "press 5 to measure RTT" << endl;
		cout << "press 6 to get time without date or seconds" << endl;
		cout << "press 7 to get year" << endl;
		cout << "press 8 to get month and day" << endl;
		cout << "press 9 to get seconds since beginning of month" << endl;
		cout << "press 10 to get week of year" << endl;
		cout << "press 11 to get day light savings" << endl;
		cout << "press 12 to get time without delay in city" << endl;
		cout << "press 13 to measure time lap" << endl;
		cout << "press 14 for exit" << endl;
		cin >> sendBuff;
		if (strcmp(sendBuff,"14")==0)
			cont = FALSE;
		else if (strcmp(sendBuff, "4") == 0) {
			int i,sum = 0,t1=0,t2=0;
			for (i = 0; i < 100; i++)
			{
				bytesSent = sendto(connSocket, sendBuff, (int)strlen(sendBuff), 0, (const sockaddr *)&server, sizeof(server));
				if (SOCKET_ERROR == bytesSent)
				{
					cout << "Time Client: Error at sendto(): " << WSAGetLastError() << endl;
					closesocket(connSocket);
					WSACleanup();
					return;
				}
				cout << "Time Client: Sent: " << bytesSent << "/" << strlen(sendBuff) << " bytes of \"" << sendBuff << "\" message.\n";
			}
			bytesRecv = recv(connSocket, recvBuff, 255, 0);
			if (SOCKET_ERROR == bytesRecv)
			{
				cout << "Time Client: Error at recv(): " << WSAGetLastError() << endl;
				closesocket(connSocket);
				WSACleanup();
				return;
			}
			recvBuff[bytesRecv] = '\0'; //add the null-terminating to make it a string
			t2 = atoi(recvBuff);
			for (i = 0; i < 99; i++)
			{
				bytesRecv = recv(connSocket, recvBuff, 255, 0);
				if (SOCKET_ERROR == bytesRecv)
				{
					cout << "Time Client: Error at recv(): " << WSAGetLastError() << endl;
					closesocket(connSocket);
					WSACleanup();
					return;
				}
				recvBuff[bytesRecv] = '\0'; //add the null-terminating to make it a string
				t1 = t2;
				t2 = atoi(recvBuff);
				sum += (t2-t1);
			}
			sum /= 100;
			cout << "client to server delay estimation is:" << sum << " milseconds" << endl;
		}
		else if (strcmp(sendBuff, "5") == 0) {
			int i,sum = 0,t1=0,t2=0;
			DWORD tick;
			for (i = 0; i < 100; i++)
			{
				tick = GetTickCount();
				t1 = tick;
				bytesSent = sendto(connSocket, sendBuff, (int)strlen(sendBuff), 0, (const sockaddr *)&server, sizeof(server));
				if (SOCKET_ERROR == bytesSent)
				{
					cout << "Time Client: Error at sendto(): " << WSAGetLastError() << endl;
					closesocket(connSocket);
					WSACleanup();
					return;
				}
				cout << "Time Client: Sent: " << bytesSent << "/" << strlen(sendBuff) << " bytes of \"" << sendBuff << "\" message.\n";

				bytesRecv = recv(connSocket, recvBuff, 255, 0);
				if (SOCKET_ERROR == bytesRecv)
				{
					cout << "Time Client: Error at recv(): " << WSAGetLastError() << endl;
					closesocket(connSocket);
					WSACleanup();
					return;
				}

				recvBuff[bytesRecv] = '\0'; //add the null-terminating to make it a string
				tick = GetTickCount();
				t2 = tick;
				sum += (t2 - t1);
			}
			sum /= 100;
			cout << "RTT is:" << sum << " milseconds" << endl;
		}
		else if (strcmp(sendBuff, "12") == 0) {
			char city[255];
			cout << "enter the city name,all lower case " << endl;
			cin >> city;
			strcat_s(sendBuff, city);
			bytesSent = sendto(connSocket, sendBuff, (int)strlen(sendBuff), 0, (const sockaddr *)&server, sizeof(server));
			if (SOCKET_ERROR == bytesSent)
			{
				cout << "Time Client: Error at sendto(): " << WSAGetLastError() << endl;
				closesocket(connSocket);
				WSACleanup();
				return;
			}
			cout << "Time Client: Sent: " << bytesSent << "/" << strlen(sendBuff) << " bytes of \"" << sendBuff << "\" message.\n";

			bytesRecv = recv(connSocket, recvBuff, 255, 0);
			if (SOCKET_ERROR == bytesRecv)
			{
				cout << "Time Client: Error at recv(): " << WSAGetLastError() << endl;
				closesocket(connSocket);
				WSACleanup();
				return;
			}

			recvBuff[bytesRecv] = '\0'; //add the null-terminating to make it a string
			cout << "Time Client: Recieved: " << bytesRecv << " bytes of \"" << recvBuff << "\" message.\n";
		}
		else {
			bytesSent = sendto(connSocket, sendBuff, (int)strlen(sendBuff), 0, (const sockaddr *)&server, sizeof(server));
			if (SOCKET_ERROR == bytesSent)
			{
				cout << "Time Client: Error at sendto(): " << WSAGetLastError() << endl;
				closesocket(connSocket);
				WSACleanup();
				return;
			}
			cout << "Time Client: Sent: " << bytesSent << "/" << strlen(sendBuff) << " bytes of \"" << sendBuff << "\" message.\n";

			bytesRecv = recv(connSocket, recvBuff, 255, 0);
			if (SOCKET_ERROR == bytesRecv)
			{
				cout << "Time Client: Error at recv(): " << WSAGetLastError() << endl;
				closesocket(connSocket);
				WSACleanup();
				return;
			}

			recvBuff[bytesRecv] = '\0'; //add the null-terminating to make it a string
			cout << "Time Client: Recieved: " << bytesRecv << " bytes of \"" << recvBuff << "\" message.\n";
		}
	}

	cout << "Time Client: Closing Connection.\n";
	closesocket(connSocket);

	system("pause");
}