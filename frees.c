/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malja-fa <malja-fa@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 08:06:26 by malja-fa          #+#    #+#             */
/*   Updated: 2024/12/19 12:13:53 by malja-fa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

void	combine(t_pipe *pipes, char **command, int flag)
{
	if (flag == 1)
	{
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

int	process_exit_status(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (1);
}
