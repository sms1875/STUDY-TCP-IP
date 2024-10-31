#include <stdio.h>          // 표준 입출력 라이브러리
#include <string.h>         // 문자열 처리 라이브러리
#include <arpa/inet.h>      // IP 주소 변환을 위한 라이브러리

int main(int argc, char *argv[])
{
    struct sockaddr_in addr1, addr2;   // IP 주소 정보를 저장할 구조체
    char *str_ptr;                     // IP 주소를 문자열로 변환한 결과를 저장할 포인터
    char str_arr[20];                  // 첫 번째 IP 주소 문자열을 복사할 배열
    
    // 네트워크 바이트 순서로 IP 주소 설정
    addr1.sin_addr.s_addr = htonl(0x1020304);  // 1.2.3.4에 해당하는 네트워크 바이트 순서의 정수
    addr2.sin_addr.s_addr = htonl(0x1010101);  // 1.1.1.1에 해당하는 네트워크 바이트 순서의 정수
    
    // addr1의 IP 주소를 점-십진수 표기법으로 변환
    str_ptr = inet_ntoa(addr1.sin_addr);
    strcpy(str_arr, str_ptr);  // 변환된 IP 주소 문자열을 str_arr에 복사
    printf("Dotted-Decimal notation1: %s \n", str_ptr);
    
    // addr2의 IP 주소를 점-십진수 표기법으로 변환
    inet_ntoa(addr2.sin_addr);
    printf("Dotted-Decimal notation2: %s \n", str_ptr);  // str_ptr은 addr2의 IP 주소로 변경됨
    printf("Dotted-Decimal notation3: %s \n", str_arr);  // str_arr은 addr1의 IP 주소로 유지됨

    return 0;
}
