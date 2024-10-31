#include <stdio.h>          // 표준 입출력 라이브러리
#include <stdlib.h>         // 표준 라이브러리, 특히 exit() 함수 사용
#include <arpa/inet.h>      // IP 주소 변환을 위한 라이브러리

// 에러 메시지를 출력하고 프로그램을 종료하는 함수
void error_handling(char *message);

int main(int argc, char *argv[])
{
    char *addr = "127.232.124.79";           // 변환할 IP 주소 문자열
    struct sockaddr_in addr_inet;            // IP 주소 정보를 담을 구조체
    
    // IP 주소 문자열을 네트워크 바이트 순서의 정수로 변환
    if(!inet_aton(addr, &addr_inet.sin_addr))
        error_handling("Conversion error");   // 변환 실패 시 오류 처리
    else
        printf("Network ordered integer addr: %#x \n", addr_inet.sin_addr.s_addr);  // 변환된 네트워크 바이트 순서 주소 출력

    return 0;
}

// 에러 메시지를 출력하고 프로그램을 종료하는 함수
void error_handling(char *message)
{
    fputs(message, stderr); // 표준 에러에 메시지 출력
    fputc('\n', stderr);    // 줄 바꿈 문자 출력
    exit(1);                // 프로그램 종료
}
