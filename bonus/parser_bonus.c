/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szapata- <szapata-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 14:03:42 by szapata-          #+#    #+#             */
/*   Updated: 2024/10/06 18:45:48 by szapata-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	parse_cmds(t_info *info)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	if (info.limit && i++)
		info.argc -= 1;
	info->cmds = (char ***)malloc((info.argc - 2) * sizeof(char **));
	if (!info->cmds)
		return (-1);
	info->cmds[info.argc - 3] = NULL;
	while (info.argc - 2 > i++)
	{
		info->cmds[j] = ft_split(argv[i], ' ');
		if (!info->cmds[j++] && clear_info(info))
			return (-1);
	}
	return (0);
}
