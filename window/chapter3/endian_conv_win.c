#include <stdio.h>          // 표준 입출력 라이브러리
#include <winsock2.h>       // Windows 소켓 관련 라이브러리

// 에러 메시지를 출력하고 프로그램을 종료하는 함수
void ErrorHandling(char* message);

int main(int argc, char *argv[])
{
    WSADATA wsaData;                        // Windows 소켓 초기화 정보 저장
    unsigned short host_port = 0x1234;      // 호스트 바이트 순서의 포트 번호
    unsigned short net_port;                // 네트워크 바이트 순서로 변환된 포트 번호
    unsigned long host_addr = 0x12345678;   // 호스트 바이트 순서의 IP 주소
    unsigned long net_addr;                 // 네트워크 바이트 순서로 변환된 IP 주소

    // Windows 소켓 라이브러리 초기화
    if(WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
        ErrorHandling("WSAStartup() error!"); 
    
    // 16비트 포트를 네트워크 바이트 순서로 변환
    net_port = htons(host_port);

    // 32비트 주소를 네트워크 바이트 순서로 변환
    net_addr = htonl(host_addr);
    
    // 변환 전후의 포트 번호와 IP 주소 출력
    printf("Host ordered port: %#x \n", host_port);         // 호스트 바이트 순서의 포트 번호 출력
    printf("Network ordered port: %#x \n", net_port);       // 네트워크 바이트 순서의 포트 번호 출력
    printf("Host ordered address: %#lx \n", host_addr);     // 호스트 바이트 순서의 IP 주소 출력
    printf("Network ordered address: %#lx \n", net_addr);   // 네트워크 바이트 순서의 IP 주소 출력
    
    WSACleanup();  // Windows 소켓 라이브러리 종료
    return 0;
}

// 에러 메시지를 출력하고 프로그램을 종료하는 함수
void ErrorHandling(char* message)
{
    fputs(message, stderr); // 표준 에러에 메시지 출력
    fputc('\n', stderr);    // 줄 바꿈 문자 출력
    exit(1);                // 프로그램 종료
}
