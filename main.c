/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmuradia <vmuradia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 10:34:00 by vmuradia          #+#    #+#             */
/*   Updated: 2019/02/22 10:48:55 by vmuradia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

char* get_map_size(char* line, t_data *data)
{
  char** line_data;
  while(ft_strncmp(line, "Plateau", 7) != 0)
    get_next_line(0, &line);
  if(ft_strncmp(line, "Plateau", 7) == 0)
  {
    line_data = ft_strsplit(line, ' ');
    data->height = ft_atoi(line_data[1]);
    data->width = ft_atoi(line_data[2]);
    data->total_dots = data->height * data->width;
  }
  return(line);
}

char* get_map(char* line, t_data *data)
{
  int i = 0;
  int j = 0;
  int row = 0;
  int num = 0;
  int read_point = 4;
  char** map;

  while(ft_strncmp(line, "000", 3) != 0)
    get_next_line(0, &line);

  data->map=(char**)malloc(data->height * sizeof(char*));
  for(int i=0;i<data->height;i++)
    data->map[i]=(char*)malloc(data->width*sizeof(char));

  while(i < data->height)
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
  return(line);
}

char* get_piece_size(char* line, t_data *data)
{
  char** line_data;
    while(ft_strncmp(line, "Piece", 5) != 0)
      get_next_line(0, &line);

    if(ft_strncmp(line, "Piece", 5) == 0)
    {
      //  printf("\n%s\n", line); // выводим строку, чтоб убедиться, что это нужная строка
      line_data = ft_strsplit(line, ' ');
      data->piece_h = ft_atoi(line_data[1]);
      data->piece_w = ft_atoi(line_data[2]);
      data->total_piece_dots = data->piece_h * data->piece_w;
      //  printf("piece x = %d  piece y = %d\n",data->piece_w, data->piece_h);// выводим данные куска
    }

      return(line);
}

char* get_piece(char* line, t_data *data)
{
  int i = 0;
  int j = 0;
  int num = 0;
  int read_point = 0;

  data->piece=(char**)malloc(data->piece_h * sizeof(char*));
  for(int i=0;i<data->piece_h;i++)
    data->piece[i]=(char*)malloc(data->piece_w*sizeof(char));

  while(i < data->piece_h)
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

char* get_player(char* line, t_data *data)
{
  while(ft_strncmp(line, "$$$ exec p", 9) != 0)
    get_next_line(0, &line);
  if (ft_strstr(line, "vmuradia"))
	{
		data->my_sign = 'O';
		data->enemy_sign = 'X';
	}
	else
	{
	  data->my_sign = 'X';
		data->enemy_sign = 'O';
	}
  return (line);
}

void read_each_line(char* line, t_data *data)
{
  if(data->player_done == 0)
    line = get_player(line, data);
  data->player_done = 1;
  line = get_map_size(line, data);
  line = get_map(line, data);
  line = get_piece_size(line, data);
  line = get_piece(line, data);
}

int main(void)
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
    find_target(data);
  }
  free(line);
  return 0;
}

void find_target(t_data *data)
{
  int x = 0;
  int y = 0;
  int k = 0;

  while(y < data->height)
  {
    while(x < data->width)
    {
      k = check_piece(data, x, y);
     // printf("%d\n", k);
      if(k == 1)
        break;
      x++;
    }
    if(k == 1)
      break;
    x = 0;
    y++;
  }
  print_cords(y, x);
}

void	print_cords(int y, int x)
{
	ft_putnbr(y);
	ft_putchar(' ');
	ft_putnbr(x);
	ft_putchar('\n');
}

int check_piece(t_data *data, int x, int y)
{
  int i = 0;
  int j = 0;
  int k = 0;

  while(i < data->piece_h)
  {
    while(j < data->piece_w)
    {
      if(data->piece[i][j]== '*' && (data->map[y+i][x+j] == data->my_sign || data->map[y+i][x+j] == ft_tolower(data->my_sign)))
      {
        k++;
        //printf("k = %d\n",k);
      }
      j++;
    }
    j = 0;
    i++;
  }
  return (k);
}

int find_my_y_piece(t_data *data)
{
  int x = 0;
  int y = 0;

  while(y < data->height)
  {
    while(x < data->width)
    {
      if(data->map[y][x] == data->my_sign)
        {
          //printf("%c\n", data->map[y][x]);
          return (y);
        }
      x++;
    }
    x = 0;
    y++;
  }
  return(-1);
}

int find_my_x_piece(t_data *data)
{
  int x = 0;
  int y = 0;

  while(y < data->height)
  {
    while(x< data->width)
    {
      if(data->map[y][x] == data->my_sign)
        {
          return (x);
        }
      x++;
    }
    x = 0;
    y++;
  }
  return(-1);
}

int find_enemy_x(t_data *data)
{
  int x1 = 0;
  int y1 = 0;

  while(y1 < data->height)
  {
    while(x1< data->width)
    {
      if(data->map[y1][x1] == data->enemy_sign)
        {
          return (x1);
        }
      x1++;
    }
    x1 = 0;
    y1++;
  }
  return(-1);
}

int find_enemy_y(t_data *data)
{
  int x1 = 0;
  int y1 = 0;

  while(y1 < data->height)
  {
    while(x1< data->width)
    {
      if(data->map[y1][x1] == data->enemy_sign)
        {
          return (y1);
        }
      x1++;
    }
    x1 = 0;
    y1++;
  }
  return(-1);
}

void where_am_i(t_data *data)
{
  int my_x = find_my_x_piece(data);
  int my_y = find_my_y_piece(data);
  int enemy_x = find_enemy_x(data);
  int enemy_y = find_enemy_y(data);
}

