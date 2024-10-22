#ifndef PIPEX_H
# define PIPEX_H
# include <stdio.h>
# include <errno.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>
# include "../libft/libft.h"
# include "../gnl/get_next_line.h"

typedef struct s_info {
	char	**path;
	char	**envp;
	char	**argv;
	char	***cmds;
	int		argc;
	int		i;
	char	*limit;
	int		fd[2];
}	t_info;

int		parse_cmds(t_info *info);
int		clear_info(t_info *info);
void	double_free(char **ptr);
char	*get_path(t_info info);
int		set_info(t_info *info, char **argv, char **envp, int argc);
void	child_proc(t_info info, char **argv);
int		ft_error(char *s);
void	write_file();
int		check_files(t_info *info);
void	wait_close(int fd[2], pid_t pid);

#endif