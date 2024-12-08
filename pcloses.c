/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pcloses.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malja-fa <malja-fa@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 08:48:33 by malja-fa          #+#    #+#             */
/*   Updated: 2024/12/08 15:06:58 by malja-fa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	close_fds(int infile, int outfile)
{
	if (close(infile) == -1)
		error("close infile error");
	if (close(outfile) == -1)
		error("close outfile error");
}

void	close_pipes(int *pipefd, int total_cmds)
{
	int	i;

	i = 0;
	while (i < 2 * (total_cmds - 1))
		if (close(pipefd[i++]))
			error("close pipe error");
}

void	fd_errors(t_pipe *pipes)
{
	free(pipes->pipefd);
	close(pipes->infile);
	error("Failed to open /dev/null for outfile");
}
