#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>

// 에러가 발생했을 때 메시지를 출력하고 프로그램을 종료하는 함수 선언
void ErrorHandling(char* message);

int main(int argc, char* argv[])
{
    WSADATA wsaData;                // 윈속 초기화 정보를 저장하는 구조체
    SOCKET hServSock, hClntSock;    // 서버와 클라이언트를 위한 소켓 핸들
    SOCKADDR_IN servAddr, clntAddr; // 서버와 클라이언트의 주소 정보를 저장할 구조체

    int szClntAddr;                 // 클라이언트 주소 구조체의 크기
    char message[] = "Hello World!"; // 클라이언트에게 보낼 메시지

    // 명령줄 인수로 포트 번호가 입력되지 않으면 사용법 안내 후 종료
    if(argc != 2) 
    {
        printf("Usage : %s <port>\n", argv[0]);
        exit(1);
    }
  
    // 윈속 라이브러리 초기화, 실패 시 에러 메시지 출력 후 프로그램 종료
    if(WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
        ErrorHandling("WSAStartup() error!"); 
    
    // TCP 소켓 생성, 실패 시 에러 메시지 출력 후 프로그램 종료
    hServSock = socket(PF_INET, SOCK_STREAM, 0);
    if(hServSock == INVALID_SOCKET)
        ErrorHandling("socket() error");
  
    // 서버 주소 정보 초기화 및 설정
    memset(&servAddr, 0, sizeof(servAddr));             // 구조체 초기화
    servAddr.sin_family = AF_INET;                      // IPv4 주소 체계
    servAddr.sin_addr.s_addr = htonl(INADDR_ANY);       // 모든 IP 주소에서의 연결을 허용
    servAddr.sin_port = htons(atoi(argv[1]));           // 포트 번호 설정 (명령줄 인수로 받음)
    
    // 소켓과 서버 주소를 바인딩, 실패 시 에러 메시지 출력 후 프로그램 종료
    if(bind(hServSock, (SOCKADDR*)&servAddr, sizeof(servAddr)) == SOCKET_ERROR)
        ErrorHandling("bind() error");  
    
    // 연결 요청 대기, 최대 대기 큐 크기는 5로 설정, 실패 시 에러 메시지 출력 후 프로그램 종료
    if(listen(hServSock, 5) == SOCKET_ERROR)
        ErrorHandling("listen() error");

    // 클라이언트의 연결 요청 수락
    szClntAddr = sizeof(clntAddr); // 클라이언트 주소 구조체의 크기 설정
    hClntSock = accept(hServSock, (SOCKADDR*)&clntAddr, &szClntAddr); // 연결 수락
    if(hClntSock == INVALID_SOCKET)
        ErrorHandling("accept() error");  
    
    // 클라이언트에게 메시지 전송
    send(hClntSock, message, sizeof(message), 0);

    // 연결 종료: 클라이언트 소켓 및 서버 소켓 닫기
    closesocket(hClntSock);
    closesocket(hServSock);

    // 윈속 라이브러리 해제
    WSACleanup();
    return 0;
}

// 에러 발생 시 메시지를 출력하고 프로그램을 종료하는 함수 정의
void ErrorHandling(char* message)
{
    fputs(message, stderr);  // 표준 에러 출력에 메시지 출력
    fputc('\n', stderr);     // 줄바꿈 추가
    exit(1);                 // 프로그램 종료
}
