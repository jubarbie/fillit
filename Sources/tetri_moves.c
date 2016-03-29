/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tetri_moves.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/26 10:50:03 by jubarbie          #+#    #+#             */
/*   Updated: 2016/03/25 09:22:54 by jubarbie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

static void	stick_tetri_up(unsigned int *tetri)
{
	int	i;

	i = -1;
	while (tetri[0] == 0 && ++i < 4)
	{
		tetri[0] = tetri[1];
		tetri[1] = tetri[2];
		tetri[2] = tetri[3];
		tetri[3] = 0;
	}
	tetri[4] = 0;
}

static void	stick_tetri_right(unsigned int *tetri)
{
	while (tetri[0] % 2 == 0 && tetri[1] % 2 == 0 &&
			tetri[2] % 2 == 0 && tetri[3] % 2 == 0)
	{
		tetri[0] >>= 1;
		tetri[1] >>= 1;
		tetri[2] >>= 1;
		tetri[3] >>= 1;
	}
}

void		stick_tetri_up_right(unsigned int *tetri)
{
	stick_tetri_up(tetri);
	stick_tetri_right(tetri);
}

void		erase_tetri(t_meta *meta, int i)
{
	int	j;

	j = -1;
	while (++j < 4)
		MAP[j + TETRI[i][4]] ^= TETRI[i][j];
	TETRI[i][5] = 0;
}

void		move_tetri_left(t_meta *meta, int i)
{
	int	j;
	int	out;

	j = -1;
	out = 0;
	while (++j < 4)
	{
		TETRI[i][j] <<= 1;
		if (TETRI[i][j] >= (unsigned int)ft_power_two(SIZE))
			out = 1;
	}
	if (out)
	{
		stick_tetri_right(TETRI[i]);
		TETRI[i][4]++;
	}
}
