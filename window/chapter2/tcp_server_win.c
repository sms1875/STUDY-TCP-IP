#include <stdio.h>          // 표준 입출력 라이브러리
#include <stdlib.h>         // 표준 라이브러리, 특히 exit() 함수 사용
#include <winsock2.h>       // Windows 소켓 관련 라이브러리

// 에러 메시지를 출력하고 프로그램을 종료하는 함수
void ErrorHandling(char* message);

int main(int argc, char* argv[])
{
    WSADATA wsaData;                        // Windows 소켓 초기화 정보 저장
    SOCKET hServSock, hClntSock;            // 서버 소켓과 클라이언트 소켓 파일 디스크립터
    SOCKADDR_IN servAddr, clntAddr;         // 서버와 클라이언트의 주소 정보를 담을 구조체

    int szClntAddr;                         // 클라이언트 주소 구조체의 크기
    char message[] = "Hello World!";        // 클라이언트에 전송할 메시지

    // 명령어 인자 확인: 포트 번호가 전달되었는지 확인
    if(argc != 2) 
    {
        printf("Usage : %s <port>\n", argv[0]);
        exit(1);
    }
  
    // Windows 소켓 라이브러리 초기화
    if(WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
        ErrorHandling("WSAStartup() error!"); 
  
    // 서버 소켓 생성 - PF_INET: IPv4, SOCK_STREAM: TCP 소켓
    hServSock = socket(PF_INET, SOCK_STREAM, 0);
    if(hServSock == INVALID_SOCKET)
        ErrorHandling("socket() error");
  
    // 서버 주소 정보 초기화
    memset(&servAddr, 0, sizeof(servAddr));         // 구조체 초기화
    servAddr.sin_family = AF_INET;                  // 주소 체계: IPv4
    servAddr.sin_addr.s_addr = htonl(INADDR_ANY);   // 모든 IP에서의 접속 허용
    servAddr.sin_port = htons(atoi(argv[1]));       // 포트 번호 할당 (문자열을 숫자로 변환)
    
    // 서버 소켓에 주소 할당
    if(bind(hServSock, (SOCKADDR*) &servAddr, sizeof(servAddr)) == SOCKET_ERROR)
        ErrorHandling("bind() error");  
  
    // 연결 대기 - 최대 5개의 연결 요청을 대기열에 저장
    if(listen(hServSock, 5) == SOCKET_ERROR)
        ErrorHandling("listen() error");

    // 클라이언트의 연결 요청 수락
    szClntAddr = sizeof(clntAddr);
    hClntSock = accept(hServSock, (SOCKADDR*)&clntAddr, &szClntAddr);
    if(hClntSock == INVALID_SOCKET)
        ErrorHandling("accept() error");  
  
    // 클라이언트에게 메시지 전송
    send(hClntSock, message, sizeof(message), 0);

    // 클라이언트 소켓과 서버 소켓 닫기
    closesocket(hClntSock);
    closesocket(hServSock);

    // Windows 소켓 라이브러리 종료
    WSACleanup();
    
    return 0;
}

// 에러 메시지를 출력하고 프로그램을 종료하는 함수
void ErrorHandling(char* message)
{
    fputs(message, stderr); // 표준 에러에 메시지 출력
    fputc('\n', stderr);    // 줄 바꿈 문자 출력
    exit(1);                // 프로그램 종료
}
