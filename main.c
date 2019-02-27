/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmuradia <vmuradia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 10:34:00 by vmuradia          #+#    #+#             */
/*   Updated: 2019/02/26 16:05:27 by vmuradia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void	read_each_line(char *line, t_data *data)
{
	if (data->player_done == 0)
		line = get_player(line, data);
	data->player_done = 1;
	line = get_map_size(line, data);
	line = get_map(line, data);
	line = get_piece_size(line, data);
	line = get_piece(line, data);
	//free(line);
}

int		main(void)
{
	char	*line;
	t_data	*data;

	data = malloc(sizeof(t_data));
	data->height = 0;
	data->piece_h = 0;
	data->player_done = 0;
	while (get_next_line(0, &line) > 0)
	{
		read_each_line(line, data);
		data->min = -1;
		data->final_x = 0;
		data->final_y = 0;
		find_target(data);
	}
	return (0);
}

void	print_cords(int y, int x)
{
	ft_putnbr(y);
	ft_putchar(' ');
	ft_putnbr(x);
	ft_putchar('\n');
}

void	*make_a_map(t_data *data)
{
	int i;

	i = 0;
	data->map = (char **)malloc(sizeof(char*) * (data->height + 1));
	if (!data->map)
		return (NULL);
	while (i < data->height + 1)
	{
		data->map[i] = (char*)malloc(sizeof(char) * (data->width + 1));
		i++;
	}
	return (NULL);
}

void	*make_piece(t_data *data)
{
	int i;

	i = 0;
	data->piece = (char **)malloc(sizeof(char*) * (data->piece_h + 1));
	if (!data->piece)
		return (NULL);
	while (i < data->piece_h + 1)
	{
		data->piece[i] = (char*)malloc(sizeof(char) * (data->piece_w + 1));
		i++;
	}
	return (NULL);
}
