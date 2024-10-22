/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szapata- <szapata-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 17:32:44 by szapata-          #+#    #+#             */
/*   Updated: 2024/10/09 04:54:20 by szapata-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	read_infile(t_info *info)
{
	char	*b;
	pid_t	pid;
	int		fd[2];
	
	pipe(fd);
	pid = fork();
	if (!pid)
	{
		close(fd[0]);
		b = get_next_line(info->fd[0]);
		while (b)
		{
			if (info->limit &&
				!ft_strncmp(b, info->limit, ft_strlen(info->limit)))
				break ;
			write(fd[1], b, ft_strlen(b));
			free(b);
			b = get_next_line(info->fd[0]);
		}
		exit(EXIT_SUCCESS);
	}
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	wait(NULL);
}

int	check_files(t_info *info)
{
	char	*b;

	b = info->argv[info->argc - 1];
	if (!info->limit)
		info->fd[0] = open(info->argv[1], O_RDONLY);
	info->fd[1] = open(b, O_RDWR | O_CREAT | O_TRUNC, 0777);
	if (info->fd[1] == -1)
		return (-1);
	if (!info->limit)
		dup2(info->fd[0], STDIN_FILENO);
	else
		read_infile(info);
	return (0);
}

void	double_free(char **ptr)
{
	char	**tmp;

	tmp = ptr;
	while (ptr && *ptr)
		free(*ptr++);
	free(tmp);
}

int	clear_info(t_info *info)
{
	int	i;

	i = 0;
	double_free(info->path);
	while (info->cmds[i])
		double_free(info->cmds[i++]);
	free(info->cmds);
	if (info->fd[0] > 2)
		close(info->fd[0]);
	if (info->fd[1] > 2)
		close(info->fd[1]);
	ft_memset(info, 0, sizeof(t_info));
	return (1);
}

int	ft_error(char *s)
{
	perror(s);
	exit(EXIT_FAILURE);
	return (-1);
}
