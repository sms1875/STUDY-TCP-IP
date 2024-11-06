#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 1024 // 버퍼 크기를 1024로 설정
void error_handling(char *message); // 에러 처리 함수 프로토타입 선언

int main(int argc, char *argv[])
{
	int sock; // 클라이언트 소켓을 위한 변수 선언
	char message[BUF_SIZE]; // 메시지를 저장할 버퍼 선언
	int str_len, recv_len, recv_cnt; // 전송 및 수신한 데이터 길이를 위한 변수 선언
	struct sockaddr_in serv_adr; // 서버 주소 정보를 담을 구조체 선언

	if(argc != 3) { // IP와 포트 번호가 전달되지 않은 경우
		printf("Usage : %s <IP> <port>\n", argv[0]); // 사용법 안내 출력
		exit(1); // 프로그램 종료
	}
	
	sock = socket(PF_INET, SOCK_STREAM, 0); // 클라이언트 소켓 생성
	if(sock == -1)
		error_handling("socket() error"); // 소켓 생성 오류 처리
	
	// 서버 주소 구조체 초기화 및 설정
	memset(&serv_adr, 0, sizeof(serv_adr));
	serv_adr.sin_family = AF_INET; // 주소 체계를 IPv4로 설정
	serv_adr.sin_addr.s_addr = inet_addr(argv[1]); // 서버 IP 주소 설정
	serv_adr.sin_port = htons(atoi(argv[2])); // 서버 포트 번호 설정
	
	// 서버에 연결 요청
	if(connect(sock, (struct sockaddr*)&serv_adr, sizeof(serv_adr)) == -1)
		error_handling("connect() error!"); // 연결 오류 처리
	else
		puts("Connected..........."); // 연결 성공 메시지 출력
	
	while(1) 
	{
		fputs("Input message(Q to quit): ", stdout); // 메시지 입력 안내 출력
		fgets(message, BUF_SIZE, stdin); // 입력된 메시지를 버퍼에 저장
		
		if(!strcmp(message, "q\n") || !strcmp(message, "Q\n")) // 'q' 또는 'Q' 입력 시 종료
			break;

		// 서버로 메시지 전송
		str_len = write(sock, message, strlen(message));
		
		// 서버로부터 메시지를 수신
		recv_len = 0;
		while(recv_len < str_len)
		{
			recv_cnt = read(sock, &message[recv_len], BUF_SIZE - 1); // 수신한 데이터를 버퍼에 저장
			if(recv_cnt == -1)
				error_handling("read() error!"); // 수신 오류 처리
			recv_len += recv_cnt; // 수신한 길이를 누적
		}
		
		message[recv_len] = 0; // 문자열 끝에 NULL 문자 추가
		printf("Message from server: %s", message); // 서버로부터 수신한 메시지 출력
	}
	
	close(sock); // 소켓 닫기
	return 0;
}

void error_handling(char *message) // 에러 메시지 출력 후 종료 함수
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}
