/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malja-fa <malja-fa@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 09:43:54 by malja-fa          #+#    #+#             */
/*   Updated: 2024/12/21 08:24:15 by malja-fa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

void	init_childs(t_pipe *pipes, char **argv, char **envp)
{
	int	i;

	i = -1;
	while (++i < pipes->total_cmds)
	{
		if (pipes->flag == -1 && i == 0)
			continue ;
		else if (pipes->flag2 == -1 && i == pipes->total_cmds)
			break ;
		create_child(pipes, i, argv, envp);
	}
}

void	*redirect_files(t_pipe *pipex, int i)
{
	if (i == 0)
	{
		if (dup2(pipex->infile, STDIN_FILENO) == -1)
			return (NULL);
	}
	else
	{
		if (dup2(pipex->pipefd[(i - 1) * 2], STDIN_FILENO) == -1)
			return (NULL);
	}
	if (i < pipex->total_cmds - 1)
	{
		if (dup2(pipex->pipefd[i * 2 + 1], STDOUT_FILENO) == -1)
			return (NULL);
	}
	else
	{
		if (dup2(pipex->outfile, STDOUT_FILENO) == -1)
			return (NULL);
	}
	return ((void *)1);
}

void	create_child(t_pipe *pipex, int i, char **argv, char **envp)
{
	pid_t	id;

	id = fork();
	if (id == -1)
	{
		free(pipex->pipefd);
		close_fds(pipex->infile, pipex->outfile);
		close_pipes(pipex->pipefd, pipex->total_cmds);
		error("child error");
	}
	if (id == 0)
	{
		if (!(redirect_files(pipex, i)))
		{
			close_fds(pipex->infile, pipex->outfile);
			close_pipes(pipex->pipefd, pipex->total_cmds);
			free(pipex->pipefd);
			error("Error");
		}
		close_pipes(pipex->pipefd, pipex->total_cmds);
		ft_excute(envp, argv[i + 2], pipex);
		exit(EXIT_SUCCESS);
	}
	if (i == pipex->total_cmds - 1)
		pipex->last = id;
}

void	open_files(char **argv, t_pipe *pipex, int argc)
{
	pipex->flag = 0;
	pipex->flag2 = 0;
	pipex->infile = open(argv[1], O_RDONLY);
	if (pipex->infile == -1)
	{
		perror(argv[1]);
		pipex->infile = open("/dev/null", O_RDONLY);
		if (pipex->infile == -1)
		{
			free(pipex->pipefd);
			error("Failed to open /dev/null for outfile");
		}
		pipex->flag = -1;
	}
	pipex->outfile = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (pipex->outfile == -1)
	{
		perror(argv[argc - 1]);
		pipex->outfile = open("/dev/null", O_WRONLY);
		pipex->flag2 = -1;
		if (pipex->outfile == -1)
			fd_errors(pipex);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_pipe	pipes;
	int		status;
	int		last_pid_status;

	status = 0;
	last_pid_status = -1;
	if (argc < 5)
	{
		write(2, "wrong number of arguments\n", 27);
		return (1);
	}
	if (!init_pipex(argc, &pipes, argv))
		return (1);
	init_childs(&pipes, argv, envp);
	combine(&pipes, NULL, 2);
	status = wait_child(&pipes, status, last_pid_status);
	return (status);
}
