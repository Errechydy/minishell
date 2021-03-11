#include <stdio.h>

int main(int argc, char ** argv, char **env)
{


	int pid;


  
	pid = fork();
    if (pid == 0)
    {
        char *const args[] = {execter, "-c", command->full_args[0], NULL};
        if (execve(execter, command->full_args, env) == -1)
		{
			ft_putstr_fd("ERROR: \n");
		}

		exit(0);
	}
	else if (pid < 0)
	{
		printf("Shell: Fork failed to create a new process \n");
    }

	wait(NULL);

	return 0;
}
