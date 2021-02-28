/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mainTest.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ler-rech <ler-rech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 10:12:11 by ler-rech          #+#    #+#             */
/*   Updated: 2021/02/28 16:08:40 by ler-rech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

int	read_file(char* file_name)
{
	int fd;
    fd = open(file_name, O_RDONLY);
	if (fd < 0)
		return (-1);
	return (fd);
}

int	create_empty_file(char* file_name)
{
	int fd;
    fd = open(file_name, O_WRONLY | O_TRUNC | O_CREAT | S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR, 0644);
	if (fd < 0)
		return (-1);
	return (fd);
}



char* fitoa(int i, char b[1]){
    char const digit[] = "0123456789";
    char* p = b;
    if(i<0){
        *p++ = '-';
        i *= -1;
    }
    int shifter = i;
    do{ //Move to where representation ends
        ++p;
        shifter = shifter/10;
    }while(shifter);
    *p = '\0';
    do{ //Move back, inserting digits as u go
        *--p = digit[i%10];
        i = i/10;
    }while(i);
    return b;
}

char			*ft_strjoin(char const *s1, char const *s2)
{
	size_t		i;
	size_t		j;
	char		*temp;

	if (!s1 && !s2)
		return (NULL);
	temp = malloc((strlen(s1) + strlen(s2) + 1) * sizeof(char));
	if (temp == NULL)
		return (NULL);
	j = 0;
	i = 0;
	if (s1 != NULL)
		while (s1[i] != '\0')
			temp[j++] = s1[i++];
	i = 0;
	if (s2 != NULL)
		while (s2[i] != '\0')
			temp[j++] = s2[i++];
	temp[j] = '\0';
	return (temp);
}

typedef struct	s_fd
{
	int 		fd[2];
}				t_fd;

int main(int argc, char **argv, char **env)
{

    // int fd[2];

	
    // char **ls = (char**)calloc(2,sizeof(char*));
    // ls[0] = strdup("/bin/ls");
	
    // char **grep = (char**)calloc(3,sizeof(char*));
    // grep[0] = strdup("/usr/bin/grep");
    // grep[1] = strdup("main");



	
    // pipe(fd);
    // int i = fork();
    // if (i == 0)
    // {
    //     close(fd[0]);
    //     dup2(fd[1],1);
    //     close(fd[1]);

		
    //     // printf("hello there\n");
	// 	// exit(0);

    // 	execve(ls[0],ls,env);
	// 	exit(0);

    // }
	// else // Parent process
	// {
	// 	wait(NULL);
	// 	close(fd[1]);
	// 	dup2(fd[0],0);
	// 	close(fd[0]);
	// 	execve(grep[0],grep,env);
		
	// }









	

	// int forkId;
    // int pipe_fd[2];
	// int k;


    // char **ls = (char**)calloc(2,sizeof(char*));
    // ls[0] = strdup("/bin/ls");
	
    // char **grep = (char**)calloc(3,sizeof(char*));
    // grep[0] = strdup("/usr/bin/grep");
    // grep[1] = strdup("main");



	// char **echo = (char**)calloc(3,sizeof(char*));
    // echo[0] = strdup("/bin/echo");
    // echo[1] = strdup("hhhhhh");


	
    // pipe(pipe_fd);
	// k = 0;
	// while (k < 2)
	// {
	// 	forkId = fork();
	// 	if (forkId == 0)
	// 	{
	// 		if(k == 0)
	// 		{				
	// 			execve(echo[0],echo,env);
	// 			exit(0);
	// 		}
	// 		else
	// 		{
	// 			// execve(grep[0],grep,env);
	// 			execve(echo[0],echo,env);
	// 			exit(0);
	// 		}
	// 	}
	// 	else
	// 	{
	// 		wait(NULL);
	// 		// exit(0);
	// 	}
	// 	k++;
	// }
	


	










/*

	int forkId;
    int pipe_fd[2];
	int k;
	char bb[2];

	char **echo = (char**)calloc(3,sizeof(char*));
    echo[0] = strdup("/bin/echo");
    echo[1] = strdup("hhhhhh");


	
    pipe(pipe_fd);
	k = 0;
	while (k < 5)
	{
		forkId = fork();
		if (forkId == 0)
		{
			close(pipe_fd[0]);
			dup2(pipe_fd[1],1);
			close(pipe_fd[1]);

	
			// echo[1] = ft_strjoin(echo[1], fitoa(k, bb));
			// execve(echo[0],echo,env);
			printf("hello %d \n", k);
			printf("-------------------\n");
			exit(0);
		}
		else
		{
			wait(NULL);
			// exit(0);
			close(pipe_fd[1]);
			dup2(pipe_fd[0],0);
			close(pipe_fd[0]);
		}
		k++;
	}
	*/
	







/*


	int forkId;
    int pipe_fd[2];
    int pipe_fd2[2];
	int k;


    char **ls = (char**)calloc(2,sizeof(char*));
    ls[0] = strdup("/bin/ls");
	
    char **grep = (char**)calloc(3,sizeof(char*));
    grep[0] = strdup("/usr/bin/grep");
    // grep[1] = strdup("ma");



	// int std[2];

	// std[0] = dup(0);
	// std[1] = dup(1);
		
    pipe(pipe_fd);
    pipe(pipe_fd2);
	k = 0;
	while (k < 2)
	{
		forkId = fork();
		if (forkId == 0)
		{
			if(k == 0)
			{
				
				dup2(pipe_fd[1],1);
				
				close(pipe_fd[0]);
				close(pipe_fd[1]);
				close(pipe_fd2[0]);
				close(pipe_fd2[1]);
				
				execve(ls[0],ls,env);
				// exit(0);
			}
			else if (k == 1)
			{
				dup2(pipe_fd[0],0);

				dup2(pipe_fd2[1],1);

				close(pipe_fd[0]);
				close(pipe_fd[1]);
				close(pipe_fd2[0]);
				close(pipe_fd2[1]);
				
				grep[1] = strdup("main");
				execve(grep[0],grep,env);
				// exit(0);
			}
			else if (k == 2)
			{
				
				dup2(pipe_fd2[0],0);
				
				close(pipe_fd[0]);
				close(pipe_fd[1]);
				close(pipe_fd2[0]);
				close(pipe_fd2[1]);

				
				grep[1] = strdup("main2");
				execve(grep[0],grep,env);
				// exit(0);
			}
		}
		else
		{
			wait(NULL);
		}
		k++;
	}
	*/















/*


// working

	int fd[2];
	if (pipe(fd) == -1)
	{
		return (1);
	}
	int fd2[2];
	if (pipe(fd2) == -1)
	{
		return (1);
	}







	int pid1 = fork();
	if (pid1 < 0)
	{
		return (2);
	}
	if (pid1 == 0)
	{
		// Child process 1
		dup2(fd[1], 1);
		close(fd[0]);
		close(fd[1]);
		close(fd2[0]);
		close(fd2[1]);
		execlp("ls", "ls", NULL);
		exit(0);
	}
	

	int pid2 = fork();
	if (pid2 < 0)
	{
		return (2);
	}
	if (pid2 == 0)
	{
		// Child process 1
		dup2(fd[0], 0);
		dup2(fd2[1], 1);
		close(fd[0]);
		close(fd[1]);
		close(fd2[0]);
		close(fd2[1]);
		execlp("grep", "grep", "main", NULL);
		exit(0);
	}



	int pid3 = fork();
	if (pid3 < 0)
	{
		return (2);
	}
	if (pid3 == 0)
	{
		// Child process 1
		dup2(fd2[0], 0);
		
		close(fd[0]);
		close(fd[1]);
		close(fd2[0]);
		close(fd2[1]);
		execlp("grep", "grep", "main2", NULL);
		exit(0);
	}
	


	
	close(fd[0]);
	close(fd[1]);
	close(fd2[0]);
	close(fd2[1]);
		
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	waitpid(pid3, NULL, 0);

	// wait(NULL);
	*/



/*
	char **ls = (char**)calloc(2,sizeof(char*));
    ls[0] = strdup("/bin/ls");
	
    char **grep = (char**)calloc(3,sizeof(char*));
    grep[0] = strdup("/usr/bin/grep");



	int **pipes_fd;


	pipes_fd = malloc(2 * (sizeof(int*)));

	int j = 0;
	while (j < 2)
	{
		pipes_fd[j] = malloc(2 * sizeof(int));
		
		if (pipe(pipes_fd[j]) == -1)
		{
			return (1);
		}
		j++;
	}
	
	int forks[3];

		

	int l = 0;
	while (l < 3)
	{
		
		forks[l] = fork();
		if (forks[l] < 0)
		{
			return (2);
		}
		if (forks[l] == 0)
		{
			// Child process 1
			if (l == 0) // first element
			{
				dup2(pipes_fd[l][1], 1);
			}
			else if (l == 2)
			{
				dup2(pipes_fd[l][0], 0); // last element
			}
			else
			{
				dup2(pipes_fd[l - 1][0], 0);
				dup2(pipes_fd[l][1], 1);
			}
			
			// close all pipes
			close(pipes_fd[0][0]);
			close(pipes_fd[0][1]);
			close(pipes_fd[1][0]);
			close(pipes_fd[1][1]);
			
			if(l == 0)
				execlp("ls", "ls", NULL);
			else if (l == 1)
			{
				execlp("grep", "grep", "main", NULL);
			}
			else if (l == 2)
			{
				execlp("grep", "grep", "main", NULL);
			}
			exit(0);
		}

		l++;
	}

	// close all pipes
	close(pipes_fd[0][0]);
	close(pipes_fd[0][1]);
	close(pipes_fd[1][0]);
	close(pipes_fd[1][1]);

	waitpid(forks[0], NULL, 0);
	waitpid(forks[1], NULL, 0);
	waitpid(forks[2], NULL, 0);
*/


// pipes = commands_len - 1;


	int commands_len = 4;
	int **pipes_fd;
	int *forks;
	
	forks = malloc(commands_len * (sizeof(int*)));
	pipes_fd = malloc((commands_len - 1) * (sizeof(int*)));

	int j = 0;
	while (j < commands_len)
	{
		pipes_fd[j] = malloc(2 * sizeof(int));
		
		if (pipe(pipes_fd[j]) == -1)
		{
			return (1);
		}
		j++;
	}

	int i = 0;
	while (i < commands_len)
	{
		forks[i] = fork();
		if (forks[i] < 0)
		{
			return (2);
		}
		if (forks[i] == 0)
		{
			// Child process 
			if (i == 0) // first fork
			{
				dup2(pipes_fd[0][1], 1);
			}
			else if (i == (commands_len - 1)) // last fork
			{
				dup2(pipes_fd[i - 1][0], 0);
			}
			else
			{
				dup2(pipes_fd[i - 1][0], 0);
				dup2(pipes_fd[i][1], 1);
			}
			
			
			
			
			close(pipes_fd[0][0]);
			close(pipes_fd[0][1]);
			close(pipes_fd[1][0]);
			close(pipes_fd[1][1]);
			close(pipes_fd[2][0]);
			close(pipes_fd[2][1]);
			
			
			if (i == 0)
			{
				execlp("ls", "ls", NULL);
			}
			else if (i == 1)
			{
				execlp("grep", "grep", "main", NULL);
			}
			else if (i == 2)
			{
				execlp("grep", "grep", "main2", NULL);
			}
			else if (i == 3)
			{
				execlp("grep", "grep", "main2.k", NULL);
			}

			
			exit(0);
		}
		i++;
	}
	


	
	close(pipes_fd[0][0]);
	close(pipes_fd[0][1]);
	close(pipes_fd[1][0]);
	close(pipes_fd[1][1]);
	close(pipes_fd[2][0]);
	close(pipes_fd[2][1]);
		
	waitpid(forks[0], NULL, 0);
	waitpid(forks[1], NULL, 0);
	waitpid(forks[2], NULL, 0);
	waitpid(forks[3], NULL, 0);

	// wait(NULL);
	return (EXIT_SUCCESS);
}
