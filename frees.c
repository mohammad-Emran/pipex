/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malja-fa <malja-fa@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 08:06:26 by malja-fa          #+#    #+#             */
/*   Updated: 2025/01/01 09:37:11 by malja-fa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

int	is_absolute_path(char *command)
{
	if (!command)
		return (0);
	if (command[0] == '/' || ft_strncmp(command, "./", 2) == 0
		|| ft_strncmp(command, "../", 3) == 0)
		return (1);
	return (0);
}

void	combine(t_pipe *pipes, char **command, int flag)
{
	if (flag == 1)
	{
		write(2, command[0], ft_strlen(command[0]));
		write(2, ": command not found\n", 21);
		ft_free(command);
		close_pipes(pipes->pipefd, pipes->total_cmds);
		close_fds(pipes->infile, pipes->outfile);
		free(pipes->pipefd);
	}
	else if (flag == 2)
	{
		close_pipes(pipes->pipefd, pipes->total_cmds);
		close_fds(pipes->infile, pipes->outfile);
		free(pipes->pipefd);
	}
}

int	init_pipex(int argc, t_pipe *pipes, char **argv)
{
	pipes->total_cmds = argc - 3;
	pipes->pipefd = (int *)malloc(sizeof(int) * 2 * (pipes->total_cmds - 1));
	if (!pipes->pipefd)
	{
		perror("pipefd error");
		return (0);
	}
	open_files(argv, pipes, argc);
	init_pipe(pipes);
	return (1);
}

int	process_exit_status(int status, t_pipe *pipes)
{
	if (WIFEXITED(status) && pipes->flag2 != -1)
		return (WEXITSTATUS(status));
	return (1);
}

int	wait_child(t_pipe *pipes, int status, int last_pid)
{
	pid_t	wpid;

	wpid = 0;
	while (pipes->total_cmds > 0)
	{
		wpid = waitpid(-1, &status, 0);
		if (wpid == -1)
		{
			if (errno == ECHILD)
				break ;
			perror("waitpid error");
			return (1);
		}
		if (wpid == pipes->last)
			last_pid = status;
		pipes->total_cmds--;
	}
	if (last_pid != -1)
		status = process_exit_status(last_pid, pipes);
	else
		status = process_exit_status(status, pipes);
	return (status);
}
