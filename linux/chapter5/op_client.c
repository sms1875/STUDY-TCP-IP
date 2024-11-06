#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 1024 // 버퍼 크기를 1024로 설정
#define RLT_SIZE 4    // 결과 크기를 4바이트로 설정 (int 크기)
#define OPSZ 4        // 피연산자 크기를 4바이트로 설정 (int 크기)
void error_handling(char *message); // 에러 처리 함수 프로토타입

int main(int argc, char *argv[])
{
	int sock; // 클라이언트 소켓을 위한 변수 선언
	char opmsg[BUF_SIZE]; // 서버에 전송할 피연산자와 연산자 정보를 담을 배열
	int result, opnd_cnt, i; // 계산 결과, 피연산자 개수, 반복 변수 선언
	struct sockaddr_in serv_adr; // 서버 주소 정보를 담을 구조체

	if(argc!=3) { // IP와 포트가 입력되지 않았을 경우
		printf("Usage : %s <IP> <port>\n", argv[0]); // 사용법 출력
		exit(1); // 프로그램 종료
	}
	
	sock=socket(PF_INET, SOCK_STREAM, 0); // 소켓 생성
	if(sock==-1)
		error_handling("socket() error"); // 소켓 생성 오류 처리
	
	memset(&serv_adr, 0, sizeof(serv_adr)); // 서버 주소 구조체 초기화
	serv_adr.sin_family=AF_INET; // IPv4 설정
	serv_adr.sin_addr.s_addr=inet_addr(argv[1]); // 서버 IP 주소 설정
	serv_adr.sin_port=htons(atoi(argv[2])); // 서버 포트 번호 설정
	
	if(connect(sock, (struct sockaddr*)&serv_adr, sizeof(serv_adr))==-1) // 서버에 연결 요청
		error_handling("connect() error!"); // 연결 오류 처리
	else
		puts("Connected..........."); // 연결 성공 메시지 출력

	// 피연산자 개수를 입력받음
	fputs("Operand count: ", stdout);
	scanf("%d", &opnd_cnt);
	opmsg[0] = (char)opnd_cnt; // 피연산자 개수를 첫 번째 바이트에 저장
	
	// 피연산자 입력 및 저장
	for(i=0; i<opnd_cnt; i++)
	{
		printf("Operand %d: ", i+1);
		scanf("%d", (int*)&opmsg[i*OPSZ+1]); // 입력된 피연산자를 배열에 저장
	}
	fgetc(stdin); // 버퍼에 남은 개행 문자 제거

	// 연산자 입력
	fputs("Operator: ", stdout);
	scanf("%c", &opmsg[opnd_cnt*OPSZ+1]); // 연산자를 마지막 위치에 저장
	write(sock, opmsg, opnd_cnt*OPSZ+2); // 서버로 피연산자와 연산자 전송

	// 서버로부터 결과를 수신
	read(sock, &result, RLT_SIZE); // 계산 결과 수신
	printf("Operation result: %d \n", result); // 결과 출력

	close(sock); // 소켓 닫기
	return 0;
}

void error_handling(char *message) // 에러 메시지 출력 후 프로그램 종료 함수
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}
