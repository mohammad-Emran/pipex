/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pcloses.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malja-fa <malja-fa@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 08:48:33 by malja-fa          #+#    #+#             */
/*   Updated: 2024/12/18 10:19:54 by malja-fa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

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
	{
		if (pipefd[i] >= 0)
		{
			if (close(pipefd[i]) == -1)
				perror("close pipe error");
			pipefd[i] = -1;
		}
		i++;
	}
}

void	fd_errors(t_pipe *pipes)
{
	free(pipes->pipefd);
	close(pipes->infile);
	error("Failed to open /dev/null for outfile");
}

char	*join_paths(char *path, char *command)
{
	char	*joined_path;
	char	*full_path;

	joined_path = ft_strjoin(path, "/");
	if (!joined_path)
		return (NULL);
	full_path = ft_strjoin(joined_path, command);
	free(joined_path);
	return (full_path);
}

char	*find_valid_path(char **paths, char *command)
{
	char	*test_path;
	int		i;

	i = 0;
	while (paths[i])
	{
		test_path = join_paths(paths[i], command);
		if (!test_path)
			return (NULL);
		if (access(test_path, F_OK | X_OK) == 0)
			return (test_path);
		free(test_path);
		i++;
	}
	return (NULL);
}
