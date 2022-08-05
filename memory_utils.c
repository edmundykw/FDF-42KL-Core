/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeen-wy <ekeen-wy@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 12:34:50 by ekeen-wy          #+#    #+#             */
/*   Updated: 2022/08/04 23:54:09 by ekeen-wy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	free_char(char **str)
{
	char	**temp;

	temp = str;
	while (*temp != NULL)
	{
		free(*temp);
		temp++;
	}
	free(str);
}

void	free_vector(t_map *map)
{
	t_vector	**temp;
	size_t		size;

	temp = map->vector;
	size = 0;
	while (size++ < map->x_row * map->y_column)
	{
		free(*temp);
		temp++;
	}
	free(map->vector);
}

static void	free_mem(t_map *map, double *matrix[4])
{
	size_t	index;

	index = -1;
	while (++index < map->vector_size)
		free(matrix[index]);
}

void	free_matrix(t_map *map)
{
	free_mem(map, map->matrices->matrix_x);
	free_mem(map, map->matrices->matrix_z);
	free_mem(map, map->matrices->matrix_xz);
}
