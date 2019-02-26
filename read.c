/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmuradia <vmuradia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 09:08:56 by vmuradia          #+#    #+#             */
/*   Updated: 2019/02/25 17:20:53 by vmuradia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

char	*get_map_size(char *line, t_data *data)
{
	char **line_data;

	while (ft_strncmp(line, "Plateau", 7) != 0)
	{
		free(line);
		get_next_line(0, &line);
	}
	if (ft_strncmp(line, "Plateau", 7) == 0)
	{
		line_data = ft_strsplit(line, ' ');
		data->height = ft_atoi(line_data[1]);
		data->width = ft_atoi(line_data[2]);
		free_2d((void*)line_data, 3);
	}
	return (line);
}

char	*get_map(char *line, t_data *data)
{
	int i;
	int j;
	int read_point;

	i = 0;
	j = 0;
	read_point = 4;
	while (ft_strncmp(line, "000", 3) != 0)
		get_next_line(0, &line);
	make_a_map(data);
	while (i < data->height)
	{
		while (j < data->width)
		{
			data->map[i][j] = line[read_point++];
			j++;
		}
		i++;
		j = 0;
		get_next_line(0, &line);
		read_point = 4;
	}
	return (line);
}

char	*get_piece_size(char *line, t_data *data)
{
	char **line_data;

	while (ft_strncmp(line, "Piece", 5) != 0)
	{
		free(line);
		get_next_line(0, &line);
	}
	if (ft_strncmp(line, "Piece", 5) == 0)
	{
		line_data = ft_strsplit(line, ' ');
		data->piece_h = ft_atoi(line_data[1]);
		data->piece_w = ft_atoi(line_data[2]);
		free_2d((void*)line_data, 3);
	}
	return (line);
}

char	*get_piece(char *line, t_data *data)
{
	int i;
	int j;
	int read_point;

	i = 0;
	j = 0;
	read_point = 0;
	make_piece(data);
	while (i < data->piece_h)
	{
		get_next_line(0, &line);
		while (j < data->piece_w)
		{
			data->piece[i][j] = line[read_point++];
			j++;
		}
		i++;
		j = 0;
		read_point = 0;
	}
	return (line);
}

char	*get_player(char *line, t_data *data)
{
	while (ft_strncmp(line, "$$$ exec p1", 9) != 0)
	{
		free(line);
		get_next_line(0, &line);
	}
	if (ft_strstr(line, "vmuradia"))
	{
		data->my_sign = 'O';
		data->enemy = 'X';
	}
	else
	{
		data->my_sign = 'X';
		data->enemy = 'O';
	}
	return (line);
}
