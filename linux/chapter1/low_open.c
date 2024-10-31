#include <stdio.h>          // 표준 입출력 라이브러리
#include <stdlib.h>         // 표준 라이브러리, 특히 exit() 함수 사용
#include <fcntl.h>          // 파일 제어 옵션을 위한 헤더 파일
#include <unistd.h>         // 유닉스 표준 시스템 호출 (예: open, write, close)

// 에러 메시지를 출력하고 프로그램을 종료하는 함수
void error_handling(char* message);

int main(void)
{
    int fd;                 // 파일 디스크립터
    char buf[] = "Let's go!\n";  // 파일에 기록할 문자열
    
    // 파일 열기 - "data.txt"를 생성하고, 쓰기 전용으로 연다.
    // O_CREAT: 파일이 없으면 생성, O_WRONLY: 쓰기 전용, O_TRUNC: 기존 파일 내용 삭제
    fd = open("data.txt", O_CREAT | O_WRONLY | O_TRUNC);
    if(fd == -1)
        error_handling("open() error!");  // 파일 열기 실패 시 에러 처리
    
    printf("file descriptor: %d \n", fd); // 파일 디스크립터 번호 출력

    // 파일에 문자열 기록
    if(write(fd, buf, sizeof(buf)) == -1)
        error_handling("write() error!");  // 쓰기 실패 시 에러 처리

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
