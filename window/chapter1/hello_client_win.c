#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>

// 에러가 발생했을 때 메시지를 출력하고 프로그램을 종료하는 함수 선언
void ErrorHandling(char* message);

int main(int argc, char* argv[])
{
    WSADATA wsaData;              // 윈속 초기화 정보를 저장하는 구조체
    SOCKET hSocket;               // 클라이언트 소켓을 위한 소켓 핸들
    SOCKADDR_IN servAddr;         // 서버 주소 정보를 저장할 구조체

    char message[30];             // 서버로부터 수신할 메시지를 저장할 버퍼
    int strLen;                   // 수신한 메시지의 길이

    // 프로그램이 실행될 때 IP와 포트 번호가 제공되지 않으면 사용법을 출력하고 종료
    if(argc != 3)
    {
        printf("Usage : %s <IP> <port>\n", argv[0]);
        exit(1);
    }

    // 윈속 라이브러리 초기화, 실패 시 에러 메시지 출력 후 프로그램 종료
    if(WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
        ErrorHandling("WSAStartup() error!");  
    
    // TCP 소켓 생성, 실패 시 에러 메시지 출력 후 프로그램 종료
    hSocket = socket(PF_INET, SOCK_STREAM, 0);
    if(hSocket == INVALID_SOCKET)
        ErrorHandling("socket() error");
    
    // 서버 주소 정보 초기화 및 설정
    memset(&servAddr, 0, sizeof(servAddr));           // 구조체 메모리 초기화
    servAddr.sin_family = AF_INET;                    // IPv4 주소 체계
    servAddr.sin_addr.s_addr = inet_addr(argv[1]);    // 서버 IP 주소 설정 (명령줄 인수로 받음)
    servAddr.sin_port = htons(atoi(argv[2]));         // 서버 포트 번호 설정 (명령줄 인수로 받음)
    
    // 서버에 연결 요청, 실패 시 에러 메시지 출력 후 프로그램 종료
    if(connect(hSocket, (SOCKADDR*)&servAddr, sizeof(servAddr)) == SOCKET_ERROR)
        ErrorHandling("connect() error!");
    
    // 서버로부터 메시지를 수신, 실패 시 에러 메시지 출력 후 프로그램 종료
    strLen = recv(hSocket, message, sizeof(message) - 1, 0);
    if(strLen == -1)
        ErrorHandling("read() error!");
    
    // 수신한 메시지 출력
    printf("Message from server: %s \n", message);  

    // 소켓 닫기 및 윈속 라이브러리 해제
    closesocket(hSocket);
    WSACleanup();
    return 0;
}

// 에러 발생 시 메시지를 출력하고 프로그램을 종료하는 함수 정의
void ErrorHandling(char* message)
{
    fputs(message, stderr);  // 표준 에러 출력으로 메시지 출력
    fputc('\n', stderr);     // 줄바꿈 추가
    exit(1);                 // 프로그램 종료
}
