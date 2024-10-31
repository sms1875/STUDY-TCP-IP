#include <stdio.h>          // 표준 입출력 라이브러리
#include <stdlib.h>         // 표준 라이브러리, 특히 exit() 함수 사용
#include <fcntl.h>          // 파일 제어 옵션을 위한 헤더 파일
#include <unistd.h>         // 유닉스 표준 시스템 호출 (예: open, read, close)

#define BUF_SIZE 100        // 버퍼 크기를 100 바이트로 정의

// 에러 메시지를 출력하고 프로그램을 종료하는 함수
void error_handling(char* message);

int main(void)
{
    int fd;                         // 파일 디스크립터
    char buf[BUF_SIZE];             // 파일 데이터를 저장할 버퍼 배열
    
    // 파일 열기 - "data.txt" 파일을 읽기 전용으로 연다
    fd = open("data.txt", O_RDONLY);
    if(fd == -1)
        error_handling("open() error!");  // 파일 열기 실패 시 에러 처리
    
    printf("file descriptor: %d \n", fd); // 파일 디스크립터 번호 출력
    
    // 파일에서 데이터를 읽어서 buf에 저장
    if(read(fd, buf, sizeof(buf)) == -1)
        error_handling("read() error!");  // 읽기 실패 시 에러 처리

    // 파일에서 읽은 데이터 출력
    printf("file data: %s", buf);
    
    // 파일 닫기
    close(fd);
    return 0;
}

// 에러 메시지를 출력하고 프로그램을 종료하는 함수
void error_handling(char* message)
{
    fputs(message, stderr); // 표준 에러에 메시지 출력
    fputc('\n', stderr);    // 줄 바꿈 문자 출력
    exit(1);                // 프로그램 종료
}
