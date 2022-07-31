/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeen-wy <ekeen-wy@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 16:14:16 by ekeen-wy          #+#    #+#             */
/*   Updated: 2022/07/31 21:54:34 by ekeen-wy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
/*
	

	t_list	*temp;
	size_t	i;

	temp = map.temp_map;
	while (temp != NULL)
	{
		i = 0;
		while (i < map.y_column)
		{
			printf("%d ", temp->content[i]);
			i++;
		}
		temp = temp->next;
		printf("\n");
	}

	
	

	t_vector	**temp;
	size_t		i;
	size_t		j;

	temp = map.vector;
	i = 0;
	while (i < map.x_row * map.y_column)
	{
		j = 0;
		while (j++ < map.y_column)
		{
			printf("%d ", (*temp)->z);
			temp++;
			i++;
		}
		printf("\n");
	}
*/

static void	set_unit_vector(t_map *map)
{
	map->unit_vector_size[x1] = 540 / map->x_row;
	map->unit_vector_size[y1] = 1080 / map->y_column;
}

static void	init_map(t_map *map)
{
	map->y_column = 0;
	map->x_row = 0;
	map->temp_map = NULL;
	map->vector = NULL;
	map->rotation = NULL;
}

int	main(int argc, char **argv)
{
	t_data	img;
	t_map	map;
	void	*mlx;
	void	*mlx_win;

	if (argc < 2)
		p_error("Error: Map not provided\n");
	init_map(&map);
	process_input(&map, argv[1]);
	set_unit_vector(&map);
	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 1440, 720, "FDF");
	img.img = mlx_new_image(mlx, 1440, 720);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
			&img.endian);
	bresenhams(&map, &img);
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
	free_struct(&map);
}
