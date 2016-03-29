/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/23 15:42:45 by jubarbie          #+#    #+#             */
/*   Updated: 2016/03/25 10:26:42 by jubarbie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

static void				map_error(t_meta *meta)
{
	if (meta)
		free_meta(meta);
	ft_putendl("error");
	exit(EXIT_FAILURE);
}

static unsigned int		treat_line(char *buf, t_meta *meta)
{
	int	i;

	i = -1;
	while (++i < 4)
		if (buf[i] != '.' && buf[i] != '#')
			map_error(meta);
	if (buf[i] != '\n')
		map_error(meta);
	else
		buf[i] = '\0';
	return (ft_atoi(ft_convert_base(ft_strrev(buf), BASE_TETRI, BASE_DEC)));
}

static void				verif_tetri(t_meta *meta, int i, int nblock, int ntouch)
{
	int	j;
	int	k;

	j = -1;
	while (++j < 4)
	{
		k = -1;
		while (++k < 4)
		{
			if (TETRI[i][j] & (1 << k))
			{
				nblock++;
				if (j > 0 && (TETRI[i][j - 1] & (1 << k)))
					ntouch++;
				if (k > 0 && (TETRI[i][j] & (1 << (k - 1))))
					ntouch++;
				if (j < 3 && (TETRI[i][j + 1] & (1 << k)))
					ntouch++;
				if (k < 3 && (TETRI[i][j] & (1 << (k + 1))))
					ntouch++;
			}
		}
	}
	if (nblock != 4 || ntouch < 6 || i > 25)
		map_error(meta);
}

int						open_file(char *file_name)
{
	int		fd;

	fd = open(file_name, O_RDONLY);
	if (fd == -1)
		map_error(NULL);
	return (fd);
}

void					file_to_tab(int fd, t_meta *meta)
{
	char	buf[5];
	int		i;
	int		j;
	int		ret;

	ret = 1;
	while (ret)
	{
		i = NB_TETRI - 1;
		j = -1;
		while (++j < 4)
		{
			ret = read(fd, buf, 5);
			TETRI[i][j] = treat_line(buf, meta);
		}
		verif_tetri(meta, i, 0, 0);
		stick_tetri_up_right(TETRI[i]);
		ret = read(fd, buf, 1);
		if (ret && *buf != '\n')
			map_error(meta);
		if (ret)
			TETRI = add_tetri_tab(TETRI, NB_TETRI++);
	}
	close(fd);
}
