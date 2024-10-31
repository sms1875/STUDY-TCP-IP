#include <stdio.h>          // 표준 입출력 라이브러리
#include <stdlib.h>         // 표준 라이브러리, 특히 exit() 함수 사용
#include <string.h>         // 문자열 처리 라이브러리
#include <unistd.h>         // 유닉스 표준 시스템 호출 (예: read, close)
#include <arpa/inet.h>      // 인터넷 주소 변환을 위한 라이브러리
#include <sys/socket.h>     // 소켓 관련 함수와 데이터 구조체

// 에러 메시지를 출력하고 프로그램을 종료하는 함수
void error_handling(char *message);

int main(int argc, char *argv[])
{
    int serv_sock;               // 서버 소켓 파일 디스크립터
    int clnt_sock;               // 클라이언트 소켓 파일 디스크립터

    struct sockaddr_in serv_addr; // 서버 주소 정보를 담을 구조체
    struct sockaddr_in clnt_addr; // 클라이언트 주소 정보를 담을 구조체
    socklen_t clnt_addr_size;     // 클라이언트 주소 구조체의 크기를 저장할 변수

    char message[] = "Hello World!"; // 클라이언트에게 전송할 메시지
    
    // 포트 번호가 전달되었는지 확인
    if(argc != 2){
        printf("Usage : %s <port>\n", argv[0]);  // 사용법 안내 메시지 출력
        exit(1);  // 프로그램 종료
    }
    
    // 서버 소켓 생성 - PF_INET: IPv4, SOCK_STREAM: TCP 소켓
    serv_sock = socket(PF_INET, SOCK_STREAM, 0);
    if(serv_sock == -1)
        error_handling("socket() error");  // 소켓 생성 실패 시 에러 처리
    
    // 서버 주소 정보 초기화
    memset(&serv_addr, 0, sizeof(serv_addr));         // 구조체 초기화
    serv_addr.sin_family = AF_INET;                   // 주소 체계: IPv4
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);    // 모든 IP에서 접속 허용
    serv_addr.sin_port = htons(atoi(argv[1]));        // 포트 번호 할당
    
    // 서버 소켓에 주소 할당
    if(bind(serv_sock, (struct sockaddr*) &serv_addr, sizeof(serv_addr)) == -1)
        error_handling("bind() error");  // 바인딩 실패 시 에러 처리
    
    // 연결 대기 - 최대 5개의 연결 요청을 대기열에 저장
    if(listen(serv_sock, 5) == -1)
        error_handling("listen() error");  // 연결 대기 실패 시 에러 처리
    
    // 클라이언트의 연결 요청 수락
    clnt_addr_size = sizeof(clnt_addr);  
    clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_addr, &clnt_addr_size);
    if(clnt_sock == -1)
        error_handling("accept() error");  // 수락 실패 시 에러 처리
    
    // 클라이언트에게 메시지 전송
    write(clnt_sock, message, sizeof(message));

    // 소켓 종료 - 클라이언트와 서버 소켓 모두 닫음
    close(clnt_sock);	
    close(serv_sock);

    return 0;
}

// 에러 메시지를 출력하고 프로그램을 종료하는 함수
void error_handling(char *message)
{
    fputs(message, stderr); // 표준 에러에 메시지 출력
    fputc('\n', stderr);    // 줄 바꿈 문자 출력
    exit(1);                // 프로그램 종료
}
