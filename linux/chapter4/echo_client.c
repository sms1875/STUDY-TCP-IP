#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 1024 // 버퍼 크기를 1024 바이트로 정의
void error_handling(char *message); // 에러 처리 함수 프로토타입 선언

int main(int argc, char *argv[])
{
	int sock; // 클라이언트 소켓을 위한 변수 선언
	char message[BUF_SIZE]; // 메시지를 저장할 버퍼 선언
	int str_len;
	struct sockaddr_in serv_adr; // 서버 주소 정보를 담을 구조체
	
	if(argc!=3) { // 프로그램 실행 시 IP 주소와 포트 번호가 전달되지 않으면
		printf("Usage : %s <IP> <port>\n", argv[0]); // 사용법 안내 출력
		exit(1); // 프로그램 종료
	}
	
	sock=socket(PF_INET, SOCK_STREAM, 0); // 클라이언트 소켓 생성
	if(sock==-1)
		error_handling("socket() error"); // 소켓 생성 오류 처리
	
	memset(&serv_adr, 0, sizeof(serv_adr)); // 서버 주소 구조체 초기화
	serv_adr.sin_family=AF_INET; // 주소 체계를 IPv4로 설정
	serv_adr.sin_addr.s_addr=inet_addr(argv[1]); // 서버 IP 주소 설정
	serv_adr.sin_port=htons(atoi(argv[2])); // 서버 포트 번호 설정
	
	if(connect(sock, (struct sockaddr*)&serv_adr, sizeof(serv_adr))==-1) // 서버에 연결 요청
		error_handling("connect() error!"); // 연결 오류 처리
	else
		puts("Connected..........."); // 연결 성공 메시지 출력
	
	while(1) 
	{
		fputs("Input message(Q to quit): ", stdout); // 사용자에게 메시지 입력 요청
		fgets(message, BUF_SIZE, stdin); // 입력된 메시지를 버퍼에 저장
		
		if(!strcmp(message,"q\n") || !strcmp(message,"Q\n")) // 'q' 또는 'Q' 입력 시 종료
			break;

		write(sock, message, strlen(message)); // 서버로 메시지 전송
		str_len=read(sock, message, BUF_SIZE-1); // 서버로부터 메시지 수신
		message[str_len]=0; // 문자열 끝에 NULL 문자 추가
		printf("Message from server: %s", message); // 서버로부터 수신한 메시지 출력
	}
	
	close(sock); // 클라이언트 소켓 닫기
	return 0;
}

void error_handling(char *message) // 에러 메시지 출력 후 프로그램 종료 함수
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}
