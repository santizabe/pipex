/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szapata- <szapata-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 17:32:44 by szapata-          #+#    #+#             */
/*   Updated: 2024/10/06 20:48:05 by szapata-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	read_here(t_info info)
{
	close(info.end[0]);
	while (read(0, &b, 1) > 0)
	{
		b = get_next_line(STDIN_FILENO);
		if (!ft_strncmp(b, info.limiter, ft_strlen(info.limiter)))
			break ;
		write(info.end[1], b, ft_strlen(b));
	}
}

int	check_files(t_info info)
{
	char	*b;

	b = 0;
	if (!info.limit)
		info.fd[0] = open(info.argv[1], O_RDONLY, 0777);
	else
		read_here();

	info.fd[1] = open(info.argv[info.argc - 1]);
	if (info.fd[0] == -1)
		return (-1);
	if (info.fd[1] == -1)
		return (-1);
	return (0);
}

void	double_free(char **ptr)
{
	char	**tmp;

	tmp = ptr;
	while (*ptr)
		free(ptr++);
	free(tmp);
}

int	clear_info(t_info info)
{
	int	i;

	i = 0;
	double_free(info.path);
	while (info.cmds[i])
		double_free(info.cmds[i++]);
	free(info.cmds);
}

int	ft_error(char *s)
{
	perror(s);
	exit(EXIT_FAILURE);
	return (-1);
}
