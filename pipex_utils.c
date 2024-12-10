/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malja-fa <malja-fa@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 09:44:15 by malja-fa          #+#    #+#             */
/*   Updated: 2024/12/10 10:41:59 by malja-fa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error(char *str)
{
	perror(str);
	exit(EXIT_FAILURE);
}

void	ft_free(char **paths)
{
	int	i;

	i = 0;
	while (paths[i])
		free(paths[i++]);
	free(paths);
}

void	init_pipe(t_pipe *pipes)
{
	int	i;

	i = -1;
	while (++i < pipes->total_cmds - 1)
	{
		if (pipe(pipes->pipefd + i * 2) == -1)
		{
			free(pipes->pipefd);
			error("pipe error");
		}
	}
}

char	*find_path(char *command, char **envp)
{
	char	**paths;
	char	*valid_path;
	int		i;

	i = 0;
	while (envp[i] && ft_strnstr(envp[i], "PATH", 4) == 0)
		i++;
	if (!envp[i])
		return (NULL);
	paths = ft_split(envp[i] + 5, ':');
	if (!paths)
		return (NULL);
	valid_path = find_valid_path(paths, command);
	ft_free(paths);
	return (valid_path);
}

void	ft_excute(char **envp, char *argv, t_pipe *pipes)
{
	char	**command;
	char	*path;
	int		i;

	command = ft_split(argv, ' ');
	path = find_path(command[0], envp);
	i = -1;
	if (!path)
	{
		while (command[++i])
			free(command[i]);
		free(pipes->pipefd);
		free(command);
		close_fds(pipes->infile, pipes->outfile);
		close_pipes(pipes->pipefd, pipes->total_cmds);
		error("path error");
	}
	if (execve(path, command, envp) == -1)
	{
		free(path);
		free(pipes->pipefd);
		error("exec error");
	}
}
