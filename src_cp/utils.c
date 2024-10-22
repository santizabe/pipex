/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szapata- <szapata-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 01:04:16 by szapata-          #+#    #+#             */
/*   Updated: 2024/10/09 01:44:14 by szapata-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	write_file(t_info info)
{
	char	*s;

	if ((dup2(info.fd[1], STDOUT_FILENO) == -1 && ft_error("dup2"))
		|| (close(info.fd[1]) == -1 && ft_error("close")))
		return ;
	s = get_next_line(STDIN_FILENO);
	while (s)
	{
		write(STDOUT_FILENO, s, ft_strlen(s));
		free(s);
		s = get_next_line(STDIN_FILENO);
	}
}

void	wait_close(int fd[2], pid_t pid)
{
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	waitpid(pid, NULL, 0);
}

int	parse_cmds(t_info *info)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	if (info->limit && i++)
		info->argc -= 1;
	info->cmds = (char ***)malloc((info->argc - 2) * sizeof(char **));
	if (!info->cmds)
		return (-1);
	info->cmds[info->argc - 3] = NULL;
	while (info->argc - 2 > i++)
	{
		info->cmds[j] = ft_split(info->argv[i], ' ');
		if (!info->cmds[j++] && clear_info(info))
			return (-1);
	}
	if (info->limit)
		info->argc += 1;
	return (0);
}
