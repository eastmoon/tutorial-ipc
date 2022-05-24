#include <stdio.h>
#include <unistd.h>

int main()
{
  	int pid, pip[2];
  	char instring[20];

  	pipe(pip);

  	pid = fork();
  	if (pid == 0)           /* child : sends message to parent*/
  	{
        printf("printed from child process %d\n",getpid());
    		/* send 7 characters in the string, including end-of-string */
        printf( "Child sending \n");
    		write(pip[1], "Hi Mom!", 7);
  	}
  	else			/* parent : receives message from child */
  	{
        printf("printed from parent process %d\n",getpid());
    		/* read from the pipe */
    		read(pip[0], instring, 7);
        printf( "Parent got '%s'\n", instring );
  	}
}
