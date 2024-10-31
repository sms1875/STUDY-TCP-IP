#include <stdio.h>          // 표준 입출력 라이브러리
#include <arpa/inet.h>      // IP 주소 변환을 위한 라이브러리

int main(int argc, char *argv[])
{
    char *addr1 = "127.212.124.78";   // 올바른 형식의 IP 주소 문자열
    char *addr2 = "127.212.124.256";  // 잘못된 형식의 IP 주소 문자열 (256은 유효하지 않은 옥텟 값)

    unsigned long conv_addr = inet_addr(addr1);  // addr1 문자열을 네트워크 바이트 순서의 정수로 변환
    if(conv_addr == INADDR_NONE)
        printf("Error occurred! \n");  // 변환 실패 시 오류 메시지 출력
    else
        printf("Network ordered integer addr: %#lx \n", conv_addr);  // 변환된 정수 값을 16진수로 출력
    
    // 두 번째 IP 주소 문자열을 네트워크 바이트 순서의 정수로 변환
    conv_addr = inet_addr(addr2);
    if(conv_addr == INADDR_NONE)
        printf("Error occurred! \n");  // 변환 실패 시 오류 메시지 출력
    else
        printf("Network ordered integer addr: %#lx \n", conv_addr);  // 변환된 정수 값을 16진수로 출력
    
    return 0;
}
