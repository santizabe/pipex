#include "pipex.h"
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

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
		str = ft_strjoin(tmp, argv[0]);
		if (!tmp && ft_free(tmp))
			return (NULL);
		free(tmp);
		if (!access(str, F_OK))
			return (str);
		free(str);
		i++;
	}
	return (NULL);
}

void	exec_cmd(t_info info, char **argv)
{
	char	*s;

	s = get_path(info);
	if (!s && clear_info(info))
		perror("Access");
	else
		if (execve(s, argv, info.envp) == -1)
			perror("Exec");
	free(s);
}

int	set_info(t_info *info, char **argv, char **envp)
{
	ft_memset(info, 0, sizeof(t_info));
	info->envp = envp;
	info->argv = argv;
	info->argc = argc;
	if (!ft_strncmp("here_doc", argv[1], 7))
		info->limit = argv[2];
	while (*envp++)
		if (!ft_strncmp("PATH", *envp, 4))
			break ;
	info->path = ft_split(&envp[5], ':');
	if (!info->path)
		return (-1);
	if (pipe(info->end) && clear_info(info))
	{
		perror("Pipe");
		return (-1);
	}
	if (parse_cmds(info) && clear_info(info))
		return (-1);
	return (0);
}

void	child_proc(t_info info, char flags, char **argv)
{
	if (flags == 1)
	{
		dup2(info.fd[0], STDIN_FILENO);
		close(info.fd[0]);
	}
	else
	{
		dup2(info.end[0], STDIN_FILENO);
		close(info.end[0]);
	}
	if (flags == 2)
	{
		dup2(info.end[0], STDIN_FILENO);
		dup2(info.fd[1], STDOUT_FILENO);
		close(info.end[1]);
		close(info.fd[1]);
	}
	else
	{
		dup2(info.end[1], STDOUT_FILENO);
		close(info.end[0]);
	}
	exec_cmd(info, argv);
}

int	main(int argc, char **argv, char **envp)
{
	t_info	info;
	pid_t	pid;

	pid = 0;
	if (argc < 5 || set_info(&info, argv, envp))
		return (-1);
	if (check_files(argv) && clear_info(info))
		return (-1);
	while (info.cmds[i])
	{
		if (!i)
			child_proc(info, 1, )
	}
	pid = fork();
	if (pid == -1 && clear_info(info))
		return (-1);
	if (!pid)
		child_proc(info, 1, info.cmds[0]);
	wait(NULL);
}
