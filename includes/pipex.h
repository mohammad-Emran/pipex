/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malja-fa <malja-fa@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 09:44:03 by malja-fa          #+#    #+#             */
/*   Updated: 2024/12/21 08:23:35 by malja-fa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_pipe
{
	int		outfile;
	int		infile;
	int		total_cmds;
	int		*pipefd;
	int		flag;
	int		flag2;
	pid_t	last;
}			t_pipe;

void		error(char *str);
void		close_pipes(int *pipefd, int total_cmds);
void		*redirect_files(t_pipe *pipex, int i);
void		create_child(t_pipe *pipex, int i, char **argv, char **envp);
void		open_files(char **argv, t_pipe *pipex, int argc);
char		*find_path(char *command, char **envp);
void		ft_excute(char **envp, char *argv, t_pipe *pipes);
void		init_pipe(t_pipe *pipes);
void		close_fds(int infile, int outfile);
void		init_childs(t_pipe *pipes, char **argv, char **envp);
void		fd_errors(t_pipe *pipes);
void		ft_free(char **ss);
char		*find_valid_path(char **paths, char *command);
char		*join_paths(char *path, char *command);
void		combine(t_pipe *pipes, char **command, int flag);
int			init_pipex(int argc, t_pipe *pipes, char **argv);
int			process_exit_status(int status);
int			wait_child(t_pipe *pipes, int status, int last_pid);
#endif
