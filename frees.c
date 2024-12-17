#include <pipex.h>

void    combine(t_pipe *pipes, char **command, int flag)
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
