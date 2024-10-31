#undef UNICODE               // UNICODE 비활성화
#undef _UNICODE              // _UNICODE 비활성화
#include <stdio.h>           // 표준 입출력 라이브러리
#include <winsock2.h>        // Windows 소켓 관련 라이브러리

int main(int argc, char *argv[])
{
    char *strAddr = "203.211.218.102:9190";   // 문자열 형식의 IP 주소와 포트 번호
    char strAddrBuf[50];                      // 변환된 IP 주소와 포트를 다시 문자열로 저장할 배열
    SOCKADDR_IN servAddr;                     // IP 주소와 포트 정보를 담을 구조체
    int size;

    WSADATA wsaData;                          // Windows 소켓 초기화 정보 저장
    WSAStartup(MAKEWORD(2, 2), &wsaData);     // Windows 소켓 라이브러리 초기화
    
    // 문자열 주소 -> 네트워크 바이트 순서의 주소 구조체로 변환
    size = sizeof(servAddr);                  // `servAddr` 구조체 크기를 전달
    WSAStringToAddress(
        strAddr,                              // 문자열 형식의 IP 주소와 포트
        AF_INET,                              // IPv4 주소 체계
        NULL,                                 // 프로토콜 정보는 기본값으로 사용
        (SOCKADDR*)&servAddr,                 // 변환된 주소가 저장될 구조체
        &size                                 // 변환된 구조체 크기 반환
    );

    // 주소 구조체 -> 다시 문자열 형식으로 변환
    size = sizeof(strAddrBuf);                // `strAddrBuf` 배열 크기를 전달
    WSAAddressToString(
        (SOCKADDR*)&servAddr,                 // 변환할 주소 구조체
        sizeof(servAddr),                     // 구조체 크기
        NULL,                                 // 프로토콜 정보는 기본값으로 사용
        strAddrBuf,                           // 변환된 문자열이 저장될 배열
        &size                                 // 변환된 문자열 크기 반환
    );

    // 변환 결과 출력
    printf("Second conv result: %s \n", strAddrBuf);

    WSACleanup();                             // Windows 소켓 라이브러리 종료
    return 0;
}
