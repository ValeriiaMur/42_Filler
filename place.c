/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   place.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmuradia <vmuradia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/24 18:03:26 by vmuradia          #+#    #+#             */
/*   Updated: 2019/02/26 16:11:20 by vmuradia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void	find_target(t_data *data)
{
	int k;
	int x;
	int y;

	k = 0;
	x = 0;
	y = 0;
	while (y < data->height)
	{
		while (x < data->width)
		{
			k = check_piece(data, x, y);
			if (k == 1)
				find_dest(data, x, y);
			x++;
		}
		x = 0;
		y++;
	}
	print_cords(data->final_y, data->final_x);
}

void	find_dest(t_data *data, int x, int y)
{
	data->i = 0;
	data->j = 0;
	data->right = 0;
	data->left = 0;
	while (data->i++ < data->height)
	{
		while (data->j++ < data->width)
		{
			if (data->map[data->i][data->j] == data->enemy)
			{
				data->right = data->i < y ? y - data->i : data->i - y;
				data->left = data->j < x ? x - data->j : data->j - x;
				data->dest = data->right + data->left;
				if (data->min == -1 || data->min > data->dest)
				{
					data->min = data->dest;
					data->final_x = x;
					data->final_y = y;
				}
			}
		}
		data->j = 0;
	}
}

int		check_piece(t_data *data, int x, int y)
{
	int k;

	data->i = 0;
	data->j = 0;
	k = 0;
	while (data->i < data->piece_h && y + data->i < data->height)
	{
		while (data->j < data->piece_w && x + data->j < data->width)
		{
			if (data->piece[data->i][data->j] == '*' &&
			(data->map[y + data->i][x + data->j] == data->my_sign ||
			data->map[y + data->i][x + data->j] == ft_tolower(data->my_sign)))
				k++;
			else if (data->piece[data->i][data->j] == '*' &&
				data->map[y + data->i][x + data->j] != '.')
				return (0);
			data->j++;
		}
		if (!check_row(data, data->i, data->j))
			return (0);
		data->j = 0;
		data->i++;
	}
	return (k == 1 && check_column(data, data->i) ? 1 : 0);
}

int		check_column(t_data *data, int i)
{
	int j;

	j = 0;
	while (i < data->piece_h)
	{
		while (j < data->piece_w)
		{
			if (data->piece[i][j] == '*')
				return (0);
			j++;
		}
		j = 0;
		i++;
	}
	return (1);
}

int		check_row(t_data *data, int i, int j)
{
	while (j < data->piece_w)
	{
		if (data->piece[i][j] == '*')
			return (0);
		j++;
	}
	return (1);
}
