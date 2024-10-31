#include <stdio.h>          // 표준 입출력 라이브러리
#include <stdlib.h>         // 표준 라이브러리, 특히 exit() 함수 사용
#include <winsock2.h>       // Windows 소켓 관련 라이브러리

// 에러 메시지를 출력하고 프로그램을 종료하는 함수
void ErrorHandling(char* message);

int main(int argc, char* argv[])
{
    WSADATA wsaData;                   // Windows 소켓 초기화 정보 저장
    SOCKET hSocket;                    // 클라이언트 소켓 파일 디스크립터
    SOCKADDR_IN servAddr;              // 서버 주소 정보를 담을 구조체

    char message[30];                  // 서버로부터 수신할 메시지 저장용 배열
    int strLen = 0;                    // 총 수신한 바이트 수를 저장할 변수
    int idx = 0, readLen = 0;          // 인덱스와 읽은 바이트 수를 저장할 변수

    // 명령행 인자가 올바른지 확인 (IP와 포트 번호를 입력받아야 함)
    if(argc != 3)
    {
        printf("Usage : %s <IP> <port>\n", argv[0]);
        exit(1);
    }

    // Windows 소켓 라이브러리 초기화
    if(WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
        ErrorHandling("WSAStartup() error!");  

    // TCP 소켓 생성 - PF_INET: IPv4, SOCK_STREAM: TCP 소켓
    hSocket = socket(PF_INET, SOCK_STREAM, 0);
    if(hSocket == INVALID_SOCKET)
        ErrorHandling("socket() error");
    
    // 서버 주소 정보 초기화
    memset(&servAddr, 0, sizeof(servAddr));         // 구조체 초기화
    servAddr.sin_family = AF_INET;                  // 주소 체계: IPv4
    servAddr.sin_addr.s_addr = inet_addr(argv[1]);  // 문자열 IP 주소를 네트워크 바이트 순서로 변환하여 설정
    servAddr.sin_port = htons(atoi(argv[2]));       // 포트 번호를 네트워크 바이트 순서로 변환하여 설정
    
    // 서버에 연결 요청
    if(connect(hSocket, (SOCKADDR*)&servAddr, sizeof(servAddr)) == SOCKET_ERROR)
        ErrorHandling("connect() error!");
 
    // 서버로부터 데이터를 한 바이트씩 읽음
    while((readLen = recv(hSocket, &message[idx++], 1, 0)) > 0)
    {
        if(readLen == SOCKET_ERROR)
            ErrorHandling("recv() error!");
        
        strLen += readLen;  // 읽은 바이트 수를 누적하여 총 길이를 계산
    }

    // 서버로부터 수신한 메시지 출력
    printf("Message from server: %s \n", message);  
    printf("Function read call count: %d \n", strLen);

    // 소켓 종료 및 Windows 소켓 라이브러리 해제
    closesocket(hSocket);
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
