/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malja-fa <malja-fa@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 09:43:54 by malja-fa          #+#    #+#             */
/*   Updated: 2024/12/03 14:29:27 by malja-fa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	init_childs(t_pipe *pipes, int *i, char **argv, char **envp)
{
	if (pipes->flag2 == -1)
	{
		create_child(pipes, 0, argv, envp);
		close_pipes(pipes->pipefd, pipes->total_cmds);
		close_fds(pipes->infile, pipes->outfile);
		free(pipes->pipefd);
		wait (NULL);
		error("outfile error");
	}
	while (++(*i) < pipes->total_cmds)
	{
		if (pipes->flag == -1 && *i == 0)
			continue ;
		create_child(pipes, *i, argv, envp);
	}
}

void	redirect_files(t_pipe *pipex, int i)
{
	if (i == 0)
	{
		dup2(pipex->infile, STDIN_FILENO);
	}
	else
		dup2(pipex->pipefd[(i - 1) * 2], STDIN_FILENO);
	if (i < pipex->total_cmds - 1)
		dup2(pipex->pipefd[i * 2 + 1], STDOUT_FILENO);
	else
		dup2(pipex->outfile, STDOUT_FILENO);
}

void	create_child(t_pipe *pipex, int i, char **argv, char **envp)
{
	int	id;

	id = fork();
	if (id == -1)
		error("child error");
	if (id == 0)
	{
		redirect_files(pipex, i);
		close_pipes(pipex->pipefd, pipex->total_cmds);
		ft_excute(envp, argv[i + 2], pipex);
		exit(EXIT_SUCCESS);
	}
}

void	open_files(char **argv, t_pipe *pipex, int argc)
{
	pipex->flag = 0;
	pipex->flag2 = 0;
	pipex->infile = open(argv[1], O_RDONLY);
	if (pipex->infile == -1)
	{
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
		pipex->outfile = open("/dev/null", O_WRONLY);
		pipex->flag2 = -1;
		if (pipex->outfile == -1)
			fd_errors(pipex);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_pipe	pipes;
	int		i;

	if (argc < 5)
		error("wrong number of arguments");
	pipes.total_cmds = argc - 3;
	pipes.pipefd = (int *)malloc(sizeof(int) * 2 * (pipes.total_cmds - 1));
	if (!pipes.pipefd)
	{
		free(pipes.pipefd);
		error("pipefd erorr");
	}
	open_files(argv, &pipes, argc);
	i = -1;
	init_pipe(&pipes);
	init_childs(&pipes, &i, argv, envp);
	close_pipes(pipes.pipefd, pipes.total_cmds);
	close_fds(pipes.infile, pipes.outfile);
	free(pipes.pipefd);
	i = 0;
	while (i++ < pipes.total_cmds)
		wait(NULL);
	if (pipes.flag == -1)
		error("infile error");
	return (0);
}
