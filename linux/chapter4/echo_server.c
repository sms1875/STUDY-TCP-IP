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
	int serv_sock, clnt_sock; // 서버 소켓과 클라이언트 소켓을 위한 변수 선언
	char message[BUF_SIZE]; // 메시지를 저장할 버퍼 선언
	int str_len, i;
	
	struct sockaddr_in serv_adr; // 서버 주소 정보를 담을 구조체
	struct sockaddr_in clnt_adr; // 클라이언트 주소 정보를 담을 구조체
	socklen_t clnt_adr_sz; // 클라이언트 주소 크기를 저장할 변수
	
	if(argc!=2) { // 프로그램 실행 시 포트 번호가 전달되지 않으면
		printf("Usage : %s <port>\n", argv[0]); // 사용법 안내 출력
		exit(1); // 프로그램 종료
	}
	
	serv_sock=socket(PF_INET, SOCK_STREAM, 0); // 서버 소켓 생성
	if(serv_sock==-1)
		error_handling("socket() error"); // 소켓 생성 오류 처리
	
	memset(&serv_adr, 0, sizeof(serv_adr)); // 서버 주소 구조체 초기화
	serv_adr.sin_family=AF_INET; // 주소 체계를 IPv4로 설정
	serv_adr.sin_addr.s_addr=htonl(INADDR_ANY); // 모든 IP로부터 연결 허용
	serv_adr.sin_port=htons(atoi(argv[1])); // 전달된 포트 번호 설정

	if(bind(serv_sock, (struct sockaddr*)&serv_adr, sizeof(serv_adr))==-1) // 소켓에 IP와 포트 연결
		error_handling("bind() error"); // 바인딩 오류 처리
	
	if(listen(serv_sock, 5)==-1) // 연결 요청 대기 상태로 전환
		error_handling("listen() error"); // 리슨 오류 처리
	
	clnt_adr_sz=sizeof(clnt_adr); // 클라이언트 주소 크기 설정

	for(i=0; i<5; i++) // 최대 5개의 클라이언트 연결을 처리
	{
		clnt_sock=accept(serv_sock, (struct sockaddr*)&clnt_adr, &clnt_adr_sz); // 클라이언트 연결 수락
		if(clnt_sock==-1)
			error_handling("accept() error"); // 연결 수락 오류 처리
		else
			printf("Connected client %d \n", i+1); // 연결된 클라이언트 번호 출력
	
		while((str_len=read(clnt_sock, message, BUF_SIZE))!=0) // 클라이언트로부터 메시지 수신
			write(clnt_sock, message, str_len); // 받은 메시지를 그대로 클라이언트에게 전송

		close(clnt_sock); // 클라이언트 소켓 닫기
	}

	close(serv_sock); // 서버 소켓 닫기
	return 0;
}

void error_handling(char *message) // 에러 메시지 출력 후 프로그램 종료 함수
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}
