/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmuradia <vmuradia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 10:34:00 by vmuradia          #+#    #+#             */
/*   Updated: 2019/02/22 20:21:45 by vmuradia         ###   ########.fr       */
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
      line_data = ft_strsplit(line, ' ');
      data->piece_h = ft_atoi(line_data[1]);
      data->piece_w = ft_atoi(line_data[2]);
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
  while(ft_strncmp(line, "$$$ exec p1", 9) != 0)
    get_next_line(0, &line);
  // if (ft_strncmp(line, "vmuradia", 8) == 0)
	// {
	// 	data->my_sign = 'O';
	// 	data->enemy_sign = 'X';
  //  // printf("I'm first %c", data->my_sign);
	// }
	// else
	// {
	//   data->my_sign = 'X';
	// 	data->enemy_sign = 'O';
  //  // printf("I'm second %c", data->my_sign);
	// }
  data->my_sign = (line[10] == '1' ? 'O' : 'X');
	data->enemy_sign = (line[10] == '1' ? 'X' : 'O');
  printf("my enemy is %c", data->enemy_sign);
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
    data->min = -1;
    data->final_x = 0;
    data->final_y = 0;
    printf("my enemy is %c", data->enemy_sign);
    find_target(data);
  }
  free(line);
  return 0;
}

void find_target(t_data *data)
{
  int k = 0;
  int min_dest = 100;
  int find;
  int x = 0;
  int y = 0;

  printf("my enemy is %c", data->enemy_sign);
  while(y < data->height)
  {
    while(x < data->width)
    {
      k = check_piece(data, x, y);
      if(k == 1 && data->map[y][x] != data->enemy_sign)
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

void find_dest(t_data *data, int x, int y)
{
  int j = 0;
  int i = 0;
  int dest = 0;
  int right = 0;
  int left = 0;

printf("my enemy is %c", data->enemy_sign);
  while(i < data->height)
  {
    while (j < data->width)
    {
      if (data->map[i][j] == data->enemy_sign)
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

  while(i < data->piece_h && y + i < data->height)
  {
    while(j < data->piece_w && x + j < data->width)
    {
      if(data->piece[i][j]== '*' && (data->map[y+i][x+j] != data->enemy_sign || data->map[y+i][x+j] != ft_tolower(data->enemy_sign)) 
          && (data->map[y+i][x+j] == data->my_sign || data->map[y+i][x+j] == ft_tolower(data->my_sign)))
      {
        k++;
      }
      j++;
    }
    j = 0;
    i++;
  }
  return (k);
}


