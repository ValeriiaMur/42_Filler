/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmuradia <vmuradia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/06 18:39:17 by vmuradia          #+#    #+#             */
/*   Updated: 2019/02/08 17:40:32 by vmuradia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h> //delete this bitch later
#include <unistd.h>
#include "./libft/libft.h"

typedef struct 	s_coord
{
	int			x;
	int			y;
}				t_coord;

typedef struct	s_filler
{
	t_coord		coords;
	char		sign;
}				t_filler;

typedef struct 	s_all
{
	t_filler	player;
	t_filler	my_enemy;
	char		**game_board;
	int			board_size;
	int			**heat_map;
	t_coord 	coords;
}				t_all;

void	get_player_number(t_all *all, char *file)
{
	char *line;
	int fd;

	line = NULL;
	printf("here2\n");
	fd = open(file, O_RDONLY);
	if ((get_next_line(fd, &line)) == -1)
	{
		ft_putendl("Error blin");
		exit(-1);
	}
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
	free(line);
	close(fd);
}

void get_info(char *file, t_all *all, int fd, char *line)
{
	int	res;
	char	**info;

	printf("here4\n");
	if ((res = get_next_line(fd, &line) == -1))
	{
			ft_putendl("Error blin");
			exit(-1);
	}
	if (!(info = ft_strsplit(line, ' ')))
	{
		ft_putendl("Error blin");
		exit(-1);
	}
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			printf("%c", info[i][j]);
		}
	}
	all->coords.x = ft_atoi(info[2]);
	all->coords.y = ft_atoi(info[1]);
	// all->board_size = (all->coords.x) * (all->coords.y);
	printf("OK x is %d and y is %d", all->coords.x, all->coords.y);
	printf("This is my board size: %d\n", all->board_size);
	free(line);
	close(fd);
}

void get_board(t_all *all, char *file)
{
	int a;
	int b;
	int fd;
	char *line;

	a = 0;
	b = 0;
	fd = open(file, O_RDONLY);
	get_info(file, all, fd, line);
	printf("here3\n");
	// while (get_next_line(fd, &line) == 1)
	// {
	// 	read_info =
	// 	while(a < all->coords.x)
	// 	{
    //
	// 	}
	// }
}


int main(int argc, char **argv)
{
	t_all *all;

	all = (t_all*)malloc(sizeof(t_all));
	printf("here1\n");
	get_player_number(all, argv[1]);
	// while (1)
	// {
    get_board(all, argv[1]);
	// }
	free(all);
}
