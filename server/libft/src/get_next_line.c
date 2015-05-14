/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaurer <amaurer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/28 18:49:09 by amaurer           #+#    #+#             */
/*   Updated: 2015/04/23 20:59:24 by amaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <unistd.h>
#include <fcntl.h>

static int	get_next_line_return(char **mem, char **line, int ret)
{
	char	*tmp;

	if (ret == -1)
		return (-1);
	if (!ret && ft_strlen(*mem))
	{
		*line = ft_strdup(*mem);
		tmp = *mem;
		*mem = ft_strnew(0);
		ft_strdel(&tmp);
		return (1);
	}
	return (0);
}

int			get_next_line(int fd, char **line)
{
	char		buf[BUFF_SIZE + 1];
	int			ret;
	static char	*mem;
	char		*l[2];

	bzero(buf, BUFF_SIZE + 1);
	if (!line || (mem && (l[0] = ft_strchr(mem, '\n'))
		&& (l[1] = mem)))
	{
		if (!line || (*line = ft_strsub(mem, 0, l[0] - mem)) == NULL
			|| (mem = ft_strsub(mem, l[0] - mem + 1, ft_strlen(l[0]))) == NULL)
			return (-1);
		ft_strdel(&l[1]);
		return (1);
	}
	else if ((ret = read(fd, buf, BUFF_SIZE)) > 0)
	{
		if (mem || (mem = ft_strnew(0)))
		{
			l[1] = mem;
			mem = ft_strjoin(mem, buf), ft_strdel(&l[1]);
			return (get_next_line(fd, line));
		}
	}
	return (get_next_line_return(&mem, line, ret));
}
