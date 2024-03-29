/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeen-wy <ekeen-wy@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 15:03:43 by ekeen-wy          #+#    #+#             */
/*   Updated: 2022/08/18 19:28:21 by ekeen-wy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/fdf.h"

/* Scales each coordinate based on the distance between each coordinate. */

static void	scale_coord(t_map *map)
{
	size_t	index;
	double	**coord;
	size_t	row;

	index = 0;
	row = 0;
	coord = map->vector;
	while (++index < map->x_column * map->y_row)
	{
		(coord[index][xi]) = (coord[index][xi]) * map->unit_vector_size;
		if ((index + 1) % map->x_column == 0)
			row = 1;
		if (row)
			(coord[index][yi]) = (coord[index][yi]) * map->unit_vector_size;
		if (coord[index][zi] != 0)
		{
			(coord[index][zi]) = (coord[index][zi])
				* map->unit_vector_size * 1.4;
		}
	}
}

/* Stores the converted string in each column in a linked list 
for later retrieval and processing.
 */

static void	store_input(t_map *map, double *line_read, size_t x_size)
{
	t_list	*new;

	if (map->temp_map != NULL)
		is_valid_dimension(map, x_size);
	new = ft_lstnew(line_read);
	ft_lstadd_back(&map->temp_map, new);
}

/* Convert each string in a row to an integer. */

static void	convert_line(t_map *map, char *line)
{
	size_t	x_size;
	size_t	index;
	double	*line_read;
	char	**split;
	char	*temp_line;

	index = -1;
	x_size = 0;
	temp_line = ft_strtrim(line, " \n");
	split = ft_split(temp_line, ' ');
	while (split[++index] != NULL)
		x_size++;
	if (map->x_column == 0)
		map->x_column = x_size;
	line_read = (double *)malloc(sizeof(*line_read) * x_size);
	check_mem(line_read);
	index = -1;
	while (split[++index] != NULL)
		line_read[index] = (double)ft_atoi(split[index]);
	free_char(split);
	free(temp_line);
	store_input(map, line_read, x_size);
}

/* Reads each row in the file until the last row. */

static void	read_file(t_map *map, int fd)
{
	char	*line;
	size_t	y_size;

	line = get_next_line(fd);
	if (line == NULL)
		p_error("Error: File is empty\n");
	y_size = 0;
	while (line != NULL)
	{
		convert_line(map, line);
		free(line);
		line = get_next_line(fd);
		y_size++;
	}
	map->y_row = y_size;
}

void	process_input(t_map *map, char *file)
{
	int		fd;

	fd = check_file_status(file);
	read_file(map, fd);
	build_map(map);
	set_unit_vector(map);
	scale_coord(map);
	ft_lstclear(&map->temp_map, free);
}
