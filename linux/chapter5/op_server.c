#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 1024 // 버퍼 크기를 1024로 설정
#define OPSZ 4       // 피연산자 크기를 4바이트로 설정 (int 크기)
void error_handling(char *message); // 에러 처리 함수 프로토타입
int calculate(int opnum, int opnds[], char oprator); // 계산 함수 프로토타입

int main(int argc, char *argv[])
{
	int serv_sock, clnt_sock; // 서버와 클라이언트 소켓 선언
	char opinfo[BUF_SIZE]; // 피연산자와 연산자를 저장할 배열
	int result, opnd_cnt, i;
	int recv_cnt, recv_len;	
	struct sockaddr_in serv_adr, clnt_adr; // 서버와 클라이언트 주소 구조체 선언
	socklen_t clnt_adr_sz;

	if(argc!=2) { // 포트 번호가 입력되지 않았을 경우
		printf("Usage : %s <port>\n", argv[0]); // 사용법 출력
		exit(1); // 프로그램 종료
	}
	
	serv_sock=socket(PF_INET, SOCK_STREAM, 0); // 서버 소켓 생성
	if(serv_sock==-1)
		error_handling("socket() error"); // 소켓 생성 오류 처리
	
	memset(&serv_adr, 0, sizeof(serv_adr)); // 서버 주소 구조체 초기화
	serv_adr.sin_family=AF_INET; // IPv4 설정
	serv_adr.sin_addr.s_addr=htonl(INADDR_ANY); // 모든 IP로부터 연결 허용
	serv_adr.sin_port=htons(atoi(argv[1])); // 전달된 포트 번호로 설정

	if(bind(serv_sock, (struct sockaddr*)&serv_adr, sizeof(serv_adr))==-1)
		error_handling("bind() error"); // 바인딩 오류 처리
	if(listen(serv_sock, 5)==-1)
		error_handling("listen() error"); // 연결 대기 상태로 전환 오류 처리
	
	clnt_adr_sz=sizeof(clnt_adr); // 클라이언트 주소 구조체 크기 설정

	for(i=0; i<5; i++) // 최대 5번의 클라이언트 요청을 처리
	{
		opnd_cnt=0; // 피연산자 개수를 초기화
		clnt_sock=accept(serv_sock, (struct sockaddr*)&clnt_adr, &clnt_adr_sz); // 클라이언트 연결 수락
		
		read(clnt_sock, &opnd_cnt, 1); // 첫 번째 바이트에서 피연산자 개수를 읽음
		
		recv_len=0;
		while((opnd_cnt*OPSZ+1)>recv_len) // 모든 피연산자와 연산자를 받을 때까지 반복
		{
			recv_cnt=read(clnt_sock, &opinfo[recv_len], BUF_SIZE-1); // 데이터를 버퍼에 저장
			recv_len+=recv_cnt; // 받은 데이터의 길이 누적
		}
		
		result=calculate(opnd_cnt, (int*)opinfo, opinfo[recv_len-1]); // 계산 수행
		write(clnt_sock, (char*)&result, sizeof(result)); // 결과를 클라이언트에 전송
		close(clnt_sock); // 클라이언트 소켓 닫기
	}
	
	close(serv_sock); // 서버 소켓 닫기
	return 0;
}

int calculate(int opnum, int opnds[], char op)
{
	int result=opnds[0], i; // 첫 번째 피연산자로 초기화
	
	switch(op) // 연산자에 따라 연산 수행
	{
	case '+': // 덧셈
		for(i=1; i<opnum; i++) result+=opnds[i];
		break;
	case '-': // 뺄셈
		for(i=1; i<opnum; i++) result-=opnds[i];
		break;
	case '*': // 곱셈
		for(i=1; i<opnum; i++) result*=opnds[i];
		break;
	}
	return result; // 결과 반환
}

void error_handling(char *message) // 에러 메시지 출력 후 종료 함수
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}
