/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmuradia <vmuradia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 10:13:47 by vmuradia          #+#    #+#             */
/*   Updated: 2019/02/22 20:19:11 by vmuradia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_H
# define FILLER_H

# include "./libft/libft.h"
# include "stdio.h"
# include <sys/stat.h>
# include <fcntl.h>
# include "stdlib.h"

typedef struct			s_data
{
	int 				piece_h;
	int 				piece_w;
	int					height;
	int					width;
	char				my_sign;
	char				enemy_sign;
	int 				player_done;
	char				**map;
	char				**piece;
	int					final_x;
	int					final_y;
	int					min;
}						t_data;

void	read_each_line(char* line, t_data *data);
char	*get_player(char* line, t_data *data);
char	*get_map_size(char* line, t_data *data);
char	*get_map(char* line, t_data *data);
char	*get_piece_size(char* line, t_data *data);
char	*get_piece(char* line, t_data *data);
void	print_cords(int y, int x);
void find_target(t_data *data);
// int		find_my_x_piece(t_data *data);
// int		find_my_y_piece(t_data *data);
int		check_piece(t_data *data, int x, int y);
int 	find_enemy_x(t_data *data);
int 	find_enemy_y(t_data *data);
void find_dest(t_data *data, int x, int y);



#endif