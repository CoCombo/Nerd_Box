#include <sys/types.h>
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <signal.h>
#include <errno.h>

#include <sys/stat.h>
#include <fcntl.h>

int main(void)
{
	pid_t pid;
	signal(SIGCHLD, SIG_IGN);
	printf("before fork pid: %d.\n", getpid());
	
	//open file
	int fd = open("./test.txt", O_RDWR);

	if(fd == -1)
	{
		perror("open");
		exit(-1);
	}

	//create process
	int num = 10;
	pid = fork();
	//create process error
	if(pid == -1)
	{
		perror("tile");
		return -1;
	}
	//parent process
	if(pid > 0)
	{
		num++;
		printf("parent pid: %d.\n", getpid());
		printf("num: %d.\n", num);

		write(fd, "parent", )
		//sleep(30);
	}
	//child process
	else
		if(pid == 0)
		{
			num++;
			printf("child: %d. parent: %d.\n", getpid(), getppid());
			printf("num: %d.\n", num);
			//sleep(10);
			//printf("parent: %d\n", getppid());
		}
	
	printf("after fork..\n");
	return 0;
}

//multi process
void testFunc()
{
	puts("fuck you.");
}

int main0(void)
{
	int proCount = 10;
	int loopCount = 20;
	int i, j;

	pid_t pid;

	printf("enter proCount: ");
	scanf("%d", &proCount);
	printf("enter loopCount: ");
	scanf("%d", &loopCount);

	for(i = 0; i < proCount; i++)
	{
		pid = fork();
		if(pid == 0)
		{
			for(j = 0; j < loopCount; j++)
			{
				testFunc();
			}
			exit(0);
		}
	}
}
