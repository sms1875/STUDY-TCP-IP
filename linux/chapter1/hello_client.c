#include <stdio.h>          // 표준 입출력 라이브러리
#include <stdlib.h>         // 표준 라이브러리, 특히 exit() 함수 사용
#include <string.h>         // 문자열 처리 라이브러리
#include <unistd.h>         // 유닉스 표준 시스템 호출 (예: read, close)
#include <arpa/inet.h>      // 인터넷 주소 변환을 위한 라이브러리
#include <sys/socket.h>     // 소켓 관련 함수와 데이터 구조체

// 에러 메시지를 출력하고 프로그램을 종료하는 함수
void error_handling(char *message);

int main(int argc, char* argv[])
{
    int sock;                      // 소켓 파일 디스크립터
    struct sockaddr_in serv_addr;  // 서버 주소 정보를 담을 구조체
    char message[30];              // 서버로부터 받을 메시지 저장용 배열
    int str_len;                   // 수신한 문자열의 길이를 저장할 변수
    
    // 입력 인자 확인: IP 주소와 포트 번호가 전달되었는지 확인
    if(argc != 3){
        printf("Usage : %s <IP> <port>\n", argv[0]);  // 사용법 안내 메시지 출력
        exit(1);  // 프로그램 종료
    }
    
    // 소켓 생성: TCP 소켓 (PF_INET: IPv4, SOCK_STREAM: TCP)
    sock = socket(PF_INET, SOCK_STREAM, 0);
    if(sock == -1)
        error_handling("socket() error");  // 소켓 생성 실패 시 에러 처리
    
    // 서버 주소 정보 초기화
    memset(&serv_addr, 0, sizeof(serv_addr));       // 구조체 초기화
    serv_addr.sin_family = AF_INET;                 // 주소 체계: IPv4
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]); // IP 주소 할당
    serv_addr.sin_port = htons(atoi(argv[2]));      // 포트 번호 할당 (문자열을 숫자로 변환)
        
    // 서버에 연결 요청
    if(connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1) 
        error_handling("connect() error!");  // 연결 실패 시 에러 처리
    
    // 서버로부터 메시지 수신
    str_len = read(sock, message, sizeof(message) - 1);
    if(str_len == -1)
        error_handling("read() error!");  // 수신 실패 시 에러 처리
    
    // 수신한 메시지 출력
    message[str_len] = 0;  // 문자열 끝에 널 문자 추가
    printf("Message from server: %s \n", message);  
    
    // 소켓 닫기
    close(sock);
    return 0;
}

// 에러 메시지를 출력하고 프로그램을 종료하는 함수
void error_handling(char *message)
{
    fputs(message, stderr); // 표준 에러에 메시지 출력
    fputc('\n', stderr);    // 줄 바꿈 문자 출력
    exit(1);                // 프로그램 종료
}
