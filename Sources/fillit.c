/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/24 11:56:35 by jubarbie          #+#    #+#             */
/*   Updated: 2016/03/29 19:43:42 by jubarbie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

static void	display_map(t_meta *meta)
{
	int	i;
	int	j;
	int	k;

	j = -1;
	while (++j < SIZE)
	{
		k = -1;
		while (++k < SIZE)
		{
			i = -1;
			while (++i < NB_TETRI)
			{
				if (j >= (int)TETRI[i][4] && j < (int)TETRI[i][4] + 4 &&
						TETRI[i][5] && TETRI[i][j - TETRI[i][4]] & (1 << k))
				{
					ft_putchar('A' + i);
					i = 28;
				}
			}
			if (i != 29)
				ft_putchar('.');
		}
		ft_putchar('\n');
	}
}

static void	enlarge_map(t_meta *meta, int size)
{
	int	i;

	i = -1;
	while (++i < NB_TETRI)
	{
		erase_tetri(meta, i);
		stick_tetri_up_right(TETRI[i]);
	}
	i = -1;
	while (++i < size)
	{
		MAP[i] = 4294967295;
		MAP[i] -= ft_power_two(SIZE) - 1;
	}
	MAP[i] = 4294967295;
}

static int	tetri_fits(t_meta *meta, int i)
{
	int	j;
	int	res;

	j = -1;
	res = 0;
	if (TETRI[i][4] > (unsigned int)SIZE)
	{
		TETRI[i][4] = 0;
		return (0);
	}
	while (++j < 4)
		res += (TETRI[i][j] & MAP[j + TETRI[i][4]]);
	if (res == 0)
	{
		while (--j >= 0)
			MAP[j + TETRI[i][4]] |= TETRI[i][j];
		TETRI[i][5] = 1;
		return (1);
	}
	else
	{
		move_tetri_left(meta, i);
		return (tetri_fits(meta, i));
	}
	return (0);
}

static int	try_to_fill(t_meta *meta)
{
	int	i;
	int	res;

	i = -1;
	res = 0;
	while (++i < NB_TETRI)
		res += TETRI[i][5];
	if (res == NB_TETRI)
		return (1);
	i = -1;
	while (++i < NB_TETRI)
		if (TETRI[i][5] == 0 && res == i)
		{
			while (tetri_fits(meta, i) == 1)
				if (try_to_fill(meta) == 1)
					return (1);
				else
				{
					erase_tetri(meta, i);
					move_tetri_left(meta, i);
				}
		}
	return (0);
}

void		fillit(t_meta *meta)
{
	SIZE = ft_sqrt_up(NB_TETRI * 4);
	enlarge_map(meta, SIZE);
	while (try_to_fill(meta) == 0)
		enlarge_map(meta, ++SIZE);
	display_map(meta);
}
