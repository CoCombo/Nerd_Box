#include <sys/types.h>
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <signal.h>
#include <errno.h>

#include <sys/stat.h>
#include <fcntl.h>

/*
int main1(void)
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

	//process error
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

		write(fd, "parent", 6);
		close(fd);
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
			write(fd, "child", 5);
			close(fd);
		}
	
	printf("after fork..\n");
	return 0;
}
*/

/*
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
*/

/*
int main2(void)
{
	pid_t pid = vfork();
	char *const argv[] = {"ls", "-l", NULL};

	if(pid == -1)
		perror("process error:\n");
	
	if(pid > 0)
		printf("parent pid: %d\n", getpid());
	if(pid == 0)
	{
		printf("child pid: %d\nparent pid: %d\n", getpid(), getppid());
		execve("/bin/ls", argv, NULL);
		exit(0);
	}

	return 0;
}
*/

void testFunc1(void)
{
	printf("fuck you.\n");
}

void testFunc2(void)
{
	printf("shit.\n");
}

int main(void)
{
	atexit(testFunc1);
	atexit(testFunc2);
	exit(0);
}
