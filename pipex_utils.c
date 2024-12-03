/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malja-fa <malja-fa@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 09:44:15 by malja-fa          #+#    #+#             */
/*   Updated: 2024/12/03 14:29:34 by malja-fa         ###   ########.fr       */
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
	int		i;
	char	*test_path;
	char	*join;

	i = 0;
	while (ft_strnstr(envp[i], "PATH", 4) == 0)
		i++;
	paths = ft_split(envp[i] + 5, ':');
	i = 0;
	while (paths[i])
	{
		join = ft_strjoin(paths[i], "/");
		test_path = ft_strjoin(join, command);
		free(join);
		if (access(test_path, F_OK) == 0)
		{
			ft_free(paths);
			return (test_path);
		}
		free(test_path);
		i++;
	}
	ft_free(paths);
	return (NULL);
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
		error("path error");
	}
	if (execve(path, command, envp) == -1)
	{
		free(path);
		free(pipes->pipefd);
		error("exec error");
	}
}
