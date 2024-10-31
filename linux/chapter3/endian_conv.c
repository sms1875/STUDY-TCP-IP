#include <stdio.h>          // 표준 입출력 라이브러리
#include <arpa/inet.h>      // 네트워크 바이트 순서 변환을 위한 라이브러리

int main(int argc, char *argv[])
{
    unsigned short host_port = 0x1234;   // 호스트 바이트 순서로 지정된 포트 번호 (16비트)
    unsigned short net_port;             // 네트워크 바이트 순서로 변환된 포트 번호 저장
    unsigned long host_addr = 0x12345678; // 호스트 바이트 순서로 지정된 IP 주소 (32비트)
    unsigned long net_addr;              // 네트워크 바이트 순서로 변환된 IP 주소 저장

    // htons() 함수를 사용하여 호스트 바이트 순서의 포트 번호를 네트워크 바이트 순서로 변환
    net_port = htons(host_port);

    // htonl() 함수를 사용하여 호스트 바이트 순서의 IP 주소를 네트워크 바이트 순서로 변환
    net_addr = htonl(host_addr);

    // 변환 전후의 포트 번호와 IP 주소를 출력
    printf("Host ordered port: %#x \n", host_port);       // 호스트 바이트 순서의 포트 번호 출력
    printf("Network ordered port: %#x \n", net_port);     // 네트워크 바이트 순서의 포트 번호 출력
    printf("Host ordered address: %#lx \n", host_addr);   // 호스트 바이트 순서의 IP 주소 출력
    printf("Network ordered address: %#lx \n", net_addr); // 네트워크 바이트 순서의 IP 주소 출력
    
    return 0;
}
