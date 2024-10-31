#include <stdio.h>          // 표준 입출력 라이브러리
#include <string.h>         // 문자열 처리 라이브러리
#include <winsock2.h>       // Windows 소켓 관련 라이브러리

// 에러 메시지를 출력하고 프로그램을 종료하는 함수
void ErrorHandling(char* message);

int main(int argc, char *argv[])
{
    WSADATA wsaData;  // Windows 소켓 초기화 정보 저장
    
    // Windows 소켓 라이브러리 초기화
    if(WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
        ErrorHandling("WSAStartup() error!"); 

    /* inet_addr 함수 사용 예 */
    {
        char *addr = "127.212.124.78";            // 문자열 형식의 IP 주소
        unsigned long conv_addr = inet_addr(addr); // 문자열 IP 주소를 네트워크 바이트 순서의 정수로 변환

        if(conv_addr == INADDR_NONE)              // 변환 실패 시
            printf("Error occurred! \n");
        else                                      // 변환 성공 시
            printf("Network ordered integer addr: %#lx \n", conv_addr);
    }

    /* inet_ntoa 함수 사용 예 */
    {
        struct sockaddr_in addr;       // IP 주소 정보를 담을 구조체
        char *strPtr;                  // 점-십진수 표기법으로 변환된 주소 문자열을 가리킬 포인터
        char strArr[20];               // 문자열을 복사할 배열
        
        addr.sin_addr.s_addr = htonl(0x1020304);  // 1.2.3.4에 해당하는 네트워크 바이트 순서의 정수로 변환 후 설정
        strPtr = inet_ntoa(addr.sin_addr);        // 네트워크 바이트 순서의 주소를 점-십진수 문자열로 변환
        strcpy(strArr, strPtr);                   // 변환된 문자열을 strArr에 복사

        printf("Dotted-Decimal notation: %s \n", strArr);
    }

    WSACleanup();  // Windows 소켓 라이브러리 종료
    return 0;
}

// 에러 메시지를 출력하고 프로그램을 종료하는 함수
void ErrorHandling(char* message)
{
    fputs(message, stderr);  // 표준 에러에 메시지 출력
    fputc('\n', stderr);     // 줄 바꿈 문자 출력
    exit(1);                 // 프로그램 종료
}
