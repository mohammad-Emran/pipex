/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malja-fa <malja-fa@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 08:06:26 by malja-fa          #+#    #+#             */
/*   Updated: 2024/12/18 08:07:10 by malja-fa         ###   ########.fr       */
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
