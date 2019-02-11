/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   good.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmuradia <vmuradia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 15:29:58 by vmuradia          #+#    #+#             */
/*   Updated: 2019/02/11 15:46:49 by vmuradia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

char* get_map_size(char* line, t_all *all)
{
  char** info;
  while(ft_strncmp(line, "Plateau ", 8) != 0)
  		get_next_line(0, &line);
  if(ft_strncmp(line, "Plateau ", 8) == 0)
  {
      printf("\n%s\n", line);
      info = ft_strsplit(line, ' ');
      all->height = ft_atoi(info[1]);
      all->width = ft_atoi(info[2]);
      all->board_size = all->height * all->width;
   }
 	all->coords = (t_coord *)malloc(sizeof(t_coord) * all->board_size);// создаем свою карту
    return(line);
}

char* get_map(char* line, t_all *all)
{
  int i = 0;
  int j = 0;
  int row = 0;
  int num = 0;
  int read_point = 4;
  while(ft_strncmp(line, "000", 3) != 0)
    get_next_line(0, &line);
  while(i < all->height)
    {

      while(j < all->width)
      {
        all->coords[num].y = i;
        all->coords[num].x = j;
        all->coords[num].data = line[read_point++];
        printf("%c", all->coords[num].data);
        j++;
        num++;
      }
     printf("\n" );
     read_point = 4;
      j = 0;
      i++;
      get_next_line(0, &line);
    }
  return(line);
}

char* get_piece_size(t_all *all, char* line)
{
  	char** info;

    while(ft_strncmp(line, "Piece", 5) != 0)
    	get_next_line(0, &line);
    if(ft_strncmp(line, "Piece", 5) == 0)
	{
      printf("\n%s\n", line);
      info = ft_strsplit(line, ' ');
      all->piece_h = ft_atoi(info[1]);
      all->piece_w = ft_atoi(info[2]);
      all->piece_size = all->piece_h * all->piece_w;
      printf("piece x = %d  piece y = %d\n",all->piece_w, all->piece_h);// выводим данные куска
    }
    return(line);
}

char* get_piece(char* line, t_all *all)
{
  int i = 0;
  int j = 0;
  int num = 0;
  int read_point = 0;
  all->piece = (t_piece *)malloc(sizeof(t_piece) * all->piece_size);
  while(i < all->piece_h)
  {
      // get_next_line(0, &line);
	  while(j < all->piece_w)
      {
      	all->piece[num].y = i;
      	all->piece[num].x = j;
      	all->piece[num].data = line[read_point++];
      	printf("%c", all->piece[num].data);
      	j++;
      	num++;
    }
    printf("\n" );
    read_point = 0;
    j = 0;
    i++;
  }
  return (line);
}

// char* get_player(line, all)
// {
// 	if(ft_strcmp(line, "p1") == 0)
// 	{
// 		all->player.sign = 'O';
// 		all->my_enemy.sign = 'X';
// 		printf("\nHere is my sign %c\n", all->player.sign);
// 	}
// 	else
// 		{
// 			all->player.sign = 'X';
// 			all->player.sign = 'O';
// 			printf("\nHere is my sign %c\n", all->player.sign);
// 		}
// 		return(line);
// }

void read_each_line(char* line, t_all *all)
{
	// line = get_player(line, all)
	line = get_map_size(line, all);
	line = get_map(line, all);
	line = get_piece_size(all, line);
	line = get_piece(line, all);
}

int main(void)
{
	char	*line;
    t_all	*all;
    all = malloc(sizeof(t_all));

//while(1)
//{
    while (get_next_line(0, &line) == 1)
  {
      read_each_line(line, all);
  }
  //}
  	free(all->coords);
  	free(all->piece);
    free(line);
	return 0;
}
