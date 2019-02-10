/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmuradia <vmuradia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/06 18:39:17 by vmuradia          #+#    #+#             */
/*   Updated: 2019/02/09 19:45:04 by vmuradia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h> //delete this bitch later
#include <unistd.h>
#include "./libft/libft.h"

//
// typedef struct	s_map
// {
// 	int		pl;
// 	int		x;
// 	int		y;
// 	char	**map;
// }				t_map;
//
// typedef struct	s_pc
// {
// 	int		x;
// 	int		y;
// 	char	**pc;
// }				t_pc;

typedef struct 	s_coord
{
	int			x;
	int			y;
	char		data;
}				t_coord;

typedef struct	s_filler
{
	t_coord		coords;
	char		sign;
}				t_filler;

typedef struct s_piece
{
	t_coord		size_of_piece;
	char 		**map;
	int			number_of_stars;
}				t_piece;

typedef struct 	s_all
{
	t_filler	player;
	t_filler	my_enemy;
	char		**game_board;
	int			board_size;
	int			**heat_map;
	t_coord 	*coords;
	t_piece		piece;
	int			width;
	int			height;
}				t_all;

void read_stuff(t_all *all);
void	get_player_number(t_all *all, char *line);
void get_size(t_all *all, char *line);
void get_map(t_all *all, char *line);



void read_stuff(t_all *all)
{
	char *line;

	line = NULL;
	while (get_next_line(0, &line) == 1)
	{
		get_player_number(all, line);
		get_size(all, line);
		get_map(all, line);
	}
	free(line);
}

void	get_player_number(t_all *all, char *line)
{
	if(ft_strcmp(line, "p1") == 0)
	{
		all->player.sign = 'O';
		all->my_enemy.sign = 'X';
	}
	else
	{
		all->player.sign = 'X';
		all->player.sign = 'O';
	}
}

void get_size(t_all *all, char *line)
{
	char **info;

	if (ft_strncmp(line, "Plateau ", 8) == 0)
	{
		info = ft_strsplit(line, ' ');
		all->width = ft_atoi(info[2]);
		all->height = ft_atoi(info[1]);
		all->board_size = all->width * all->height;
	}
	all->coords = (t_coord*)malloc(sizeof(t_coord) * all->board_size);
}

void get_map(t_all *all, char *line)
{
	int i;
	int j;
	int num;
	int reading;

	num = 0;
	i = 0;
	j = 0;
	reading = 4;
	if(ft_strncmp(line, "000", 3) == 0)
	{
		while (i < all->height)
		{
			while (j < all->width)
			{
				all->coords[num].y = i;
				all->coords[num].x = j;
				all->coords[num].data = line[reading++];
				printf("%c", all->coords[num].data);
				j++;
				num++;
			}
			printf("\n");
			reading = 4;
			j = 0;
			i++;
			get_next_line(0, &line);
		}
	}
}


int main(void)
{
	t_all *all;

	all = (t_all*)malloc(sizeof(t_all));
	// while (1)
	// {
		read_stuff(all);
	// }
	free(all);
}
