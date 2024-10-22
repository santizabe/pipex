#include "../includes/pipex.h"

static int	ft_free(void *ptr)
{
	free(ptr);
	return (1);
}

char	*get_path(t_info info)
{
	int	i;
	char	*str;
	char	*tmp;

	i = 0;
	while (info.path[i])
	{
		tmp = ft_strjoin(info.path[i], "/");
		if (!tmp)
			return (NULL);
		str = ft_strjoin(tmp, info.cmds[info.i - 1][0]);
		if (!str && ft_free(tmp))
			return (NULL);
		free(tmp);
		if (!access(str, X_OK))
			return (str);
		free(str);
		i++;
	}
	return (NULL);
}

void	child_proc(t_info info, char **argv)
{
	char	*s;
	int		fd[2];
	pid_t	pid;

	s = get_path(info);
	if ((!s && ft_error("PATH"))
		|| (pipe(fd) == -1 && ft_error("pipe")))
		return ;
	pid = fork();
	if (pid == -1 && ft_error("fork"))
		return ;
	else if (!pid)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		if (execve(s, argv, info.envp) == -1)
			perror(argv[0]);
		exit(EXIT_FAILURE);
	}
	else
		wait_close(fd, pid);
}

int	set_info(t_info *info, char **argv, char **envp, int argc)
{
	char	*err_msg;

	err_msg = "Usage: ./pipex here_doc LIMITER [cmds] outfile\n";
	ft_memset(info, 0, sizeof(t_info));
	info->envp = envp;
	info->argv = argv;
	info->argc = argc;
	if (!ft_strncmp("here_doc", argv[1], 8) && argc == 6)
		info->limit = argv[2];
	else if (ft_error(err_msg))
		return (-1);
	while (*envp++)
		if (!ft_strncmp("PATH", *envp, 4))
			break ;
	info->path = ft_split(*envp + 5, ':');
	if (!info->path)
		return (-1);
	if (parse_cmds(info) && clear_info(info))
		return (-1);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_info	info;

	if (argc < 5 || set_info(&info, argv, envp, argc))
		return (-1);
	if (check_files(&info) && clear_info(&info))
		return (-1);
	while (info.cmds[info.i + 1] != NULL)
		child_proc(info, info.cmds[info.i++]);
	write_file(info);
	clear_info(&info);
	return (0);
}
