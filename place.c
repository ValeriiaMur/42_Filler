/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   place.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmuradia <vmuradia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/24 18:03:26 by vmuradia          #+#    #+#             */
/*   Updated: 2019/02/25 17:24:36 by vmuradia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void    find_target(t_data *data)
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
      {
        find_dest(data, x, y);
      }
      x++;
    }
    x = 0;
    y++;
  }
  print_cords(data->final_y, data->final_x);
}

void    find_dest(t_data *data, int x, int y)
{
  int j = 0;
  int i = 0;
  int dest = 0;
  int right = 0;
  int left = 0;

  while (i < data->height)
  {
    while (j < data->width)
    {
      if (data->map[i][j] == data->enemy)
      {
        right = i < y ? y - i : i - y;
        left = j < x ? x - j : j - x;
        dest = right + left;
        if (data->min == -1 || data->min > dest)
        {
            data->min = dest;
            data->final_x = x;
            data->final_y = y;
        }
      }
      j++;
    }
    j = 0;
    i++;
  }
}

int   check_piece(t_data *data, int x, int y)
{
  int i;
  int j;
  int k;

  i = 0;
  j = 0;
  k = 0;
  while (i < data->piece_h && y + i < data->height)
  {
    while (j < data->piece_w && x + j < data->width)
    {
      if (data->piece[i][j]== '*' && 
        (data->map[y+i][x+j] == data->my_sign || data->map[y+i][x+j] == ft_tolower(data->my_sign)))
      {
        k++;
      }
      else if (data->piece[i][j] == '*' && data->map[y+i][x+j] != '.')
        return (0);
      j++;
    }
    if (!check_row(data,i, j))
      return (0);
    j = 0;
    i++;
  }
  return (k == 1 && check_column(data, i) ? 1 : 0);
}

int   check_column(t_data *data, int i)
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

int   check_row(t_data *data, int i, int j)
{
	while (j < data->piece_w)
	{
		if (data->piece[i][j] == '*')
			return (0);
		j++;
	}
	return (1);
}
