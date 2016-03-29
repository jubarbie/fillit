/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/26 10:24:32 by jubarbie          #+#    #+#             */
/*   Updated: 2016/03/11 15:47:09 by jubarbie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

static unsigned int	**init_tetri_tab(void)
{
	unsigned int **tetri_tab;

	tetri_tab = ft_memalloc(sizeof(int *) * 2);
	if (tetri_tab == NULL)
		exit(EXIT_FAILURE);
	*tetri_tab = ft_memalloc(sizeof(int) * 6);
	if (*tetri_tab == NULL)
		exit(EXIT_FAILURE);
	tetri_tab[0][5] = 0;
	return (tetri_tab);
}

static void			free_tetri_tab(unsigned int **tab, int size)
{
	int i;

	i = -1;
	while (++i < size)
		free(tab[i]);
	free(tab);
}

unsigned int		**add_tetri_tab(unsigned int **tab, int size)
{
	unsigned int	**new;
	int				i;

	new = ft_memalloc(sizeof(int *) * size + 1);
	new[size] = ft_memalloc(sizeof(int) * 6);
	while (--size >= 0)
	{
		i = -1;
		new[size] = ft_memalloc(sizeof(int) * 6);
		while (++i < 4)
			new[size][i] = tab[size][i];
		new[size][5] = 0;
	}
	free_tetri_tab(tab, size);
	return (new);
}

t_meta				*init_meta(void)
{
	t_meta	*meta;
	int		i;

	meta = (t_meta *)ft_memalloc(sizeof(t_meta));
	if (meta == NULL)
		exit(EXIT_FAILURE);
	i = -1;
	while (++i < 32)
		MAP[i] = 4294967295;
	TETRI = init_tetri_tab();
	SIZE = 0;
	NB_TETRI = 1;
	return (meta);
}

void				free_meta(t_meta *meta)
{
	free_tetri_tab(TETRI, NB_TETRI);
	free(meta);
}
