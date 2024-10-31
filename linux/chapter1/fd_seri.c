#include <stdio.h>         // 표준 입출력 라이브러리
#include <fcntl.h>         // 파일 제어 옵션을 위한 헤더 파일
#include <unistd.h>        // 유닉스 표준 시스템 호출을 위한 헤더 파일
#include <sys/socket.h>    // 소켓 관련 함수와 데이터 구조체를 위한 헤더 파일

int main(void)
{	
    int fd1, fd2, fd3;

    // 소켓 생성 - PF_INET: IPv4 프로토콜, SOCK_STREAM: TCP 소켓
    fd1 = socket(PF_INET, SOCK_STREAM, 0);

    // 파일 생성 및 열기 - O_CREAT: 파일이 없으면 생성, O_WRONLY: 쓰기 전용, O_TRUNC: 파일이 이미 있으면 내용 삭제
    fd2 = open("test.dat", O_CREAT | O_WRONLY | O_TRUNC);

    // 소켓 생성 - PF_INET: IPv4 프로토콜, SOCK_DGRAM: UDP 소켓
    fd3 = socket(PF_INET, SOCK_DGRAM, 0);

    // 각 파일 디스크립터 출력
    printf("file descriptor 1: %d\n", fd1);  // TCP 소켓의 파일 디스크립터 출력
    printf("file descriptor 2: %d\n", fd2);  // 파일 "test.dat"의 파일 디스크립터 출력
    printf("file descriptor 3: %d\n", fd3);  // UDP 소켓의 파일 디스크립터 출력

    // 파일 디스크립터 닫기
    close(fd1);  // TCP 소켓 닫기
    close(fd2);  // 파일 닫기
    close(fd3);  // UDP 소켓 닫기
    
    return 0;
}
