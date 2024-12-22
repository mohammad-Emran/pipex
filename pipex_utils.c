/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malja-fa <malja-fa@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 09:44:15 by malja-fa          #+#    #+#             */
/*   Updated: 2024/12/22 07:32:49 by malja-fa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

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
			close_fds(pipes->infile, pipes->outfile);
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
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5) != 0)
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

	command = ft_split(argv, ' ');
	if (!command)
	{
		combine(pipes, command, 2);
		error("split error");
	}
	path = find_path(command[0], envp);
	if (!path)
	{
		write(2, command[0], ft_strlen(command[0]));
		write(2, ": command not found\n", 21);
		combine(pipes, command, 1);
		exit(127);
	}
	if (execve(path, command, envp) == -1)
	{
		perror("exec error");
		combine(pipes, command, 1);
		free(path);
		exit(EXIT_FAILURE);
	}
}
