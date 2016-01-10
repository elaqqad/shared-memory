#include <sys/wait.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
 
int main()
{
	int p[2], p2[2];
 
	if (pipe(p) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	if (pipe(p2) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
 
	int cpid = fork();
	if (cpid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
 
	if (cpid == 0)
	{
		printf("child\n");
		char buffer[100];
		close(p[0]);
		while (read(p2[0], buffer, 100) > 0)
		{
			printf("read from p2[0]\n");
			int a,b;
			sscanf(buffer, "%d%d", &a, &b);
			sprintf(buffer, "%d\n", a+b);
			int size = write(p[1], buffer, strlen(buffer));
			printf("%d bytes written on p[1]\n", size);
			if (size == -1)
				perror("write()");
		}
		printf("child end\n");
		close(p2[0]);
		close(p2[1]);
	}
	else
	{
		int a,b;
		close(p2[0]);
 
		fd_set rfds;
		struct timeval tv;
		int retval;
 
		while (1)
		{
			FD_ZERO(&rfds);
	                FD_SET(0, &rfds);
	                FD_SET(p[0], &rfds);
 
			retval = select(p[0]+1, &rfds, NULL, NULL, NULL);
 
			if (retval == -1)
				perror("select()");
			else
			{
				if (FD_ISSET(0, &rfds))
				{
					printf("read from stdin\n");
					char buffer[100];
					scanf("%d %d", &a, &b);
					sprintf(buffer, "%d %d\n", a, b);
					int size = write(p2[1], buffer, strlen(buffer));
					printf("%d bytes written on p2[1]\n", size);
					if (size == -1)
						perror("write()");
				}
				else if (FD_ISSET(p[0], &rfds))
				{
					printf("read from p[0]\n");
					char buffer[100];
					read(p[0], buffer, 100);
					int c;
					sscanf(buffer, "%d", &c);
					printf("sum is %d\n", c);
				}
			}
		}
	}
 
	return 0;
}