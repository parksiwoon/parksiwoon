#include <stdio.h>   // 표준 입력 및 출력 함수를 사용하기 위해 stdio.h 헤더 파일을 포함
#include <unistd.h>  // UNIX 표준 함수인 fork(), getpid() 등을 사용하기 위해 unistd.h 헤더 파일을 포함

int fork_test() // Fork 함수 정의 시작
{
	pid_t pid;        // pid_t: 프로세스 ID를 저장하기 위한 변수 타입
	pid = fork();     // fork() 함수 호출, 현재 실행중인 프로세스를 복제하고 새로 생성된 프로세스의 ID를 반환

	if(pid > 0)       // 부모 프로세스인 경우 실행
	{
		printf("parent process %d\n", getpid());  // 부모 프로세스의 ID 출력
	}

	else if(pid == 0)  // 첫 번째 자식 프로세스인 경우 실행
	{
		printf("child process %d\n", getpid());  // 첫 번째 자식 프로세스의 ID 출력
		pid = fork();  // 다시 fork()를 호출하여 첫 번째 자식 프로세스를 복제

		if(pid > 0)    // 첫 번째 자식 프로세스 내에서 실행된 두 번째 fork()의 부모 프로세스일 경우
		{
			printf("child process %d\n", getpid());  // 첫 번째 자식 프로세스의 ID 출력
		}

		else if(pid == 0)  // 첫 번째 자식 프로세스의 자식, 즉 손자 프로세스인 경우
		{
			printf("grand child %d\n", getpid());  // 손자 프로세스의 ID 출력
		}

		else  // fork() 호출 실패 시
		{
			printf("Fork failed to create grand child.\n");  // 실패 메시지 출력
		}
	}

	else  // 첫 번째 fork() 호출 실패 시
	{
		printf("Fork failed to create child.\n");  // 실패 메시지 출력
	}
    return 0;
}
