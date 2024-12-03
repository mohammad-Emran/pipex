/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malja-fa <malja-fa@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 09:44:03 by malja-fa          #+#    #+#             */
/*   Updated: 2024/12/03 14:29:31 by malja-fa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "./libft/libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_pipe
{
	int	outfile;
	int	infile;
	int	total_cmds;
	int	*pipefd;
	int	flag;
	int	flag2;
}		t_pipe;

void	error(char *str);
void	close_pipes(int *pipefd, int total_cmds);
void	redirect_files(t_pipe *pipex, int i);
void	create_child(t_pipe *pipex, int i, char **argv, char **envp);
void	open_files(char **argv, t_pipe *pipex, int argc);
char	*find_path(char *command, char **envp);
void	ft_excute(char **envp, char *argv, t_pipe *pipes);
void	init_pipe(t_pipe *pipes);
void	close_fds(int infile, int outfile);
void	init_childs(t_pipe *pipes, int *i, char **argv, char **envp);
void	fd_errors(t_pipe *pipes);
#endif
