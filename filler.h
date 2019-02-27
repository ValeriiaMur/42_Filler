/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmuradia <vmuradia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 10:13:47 by vmuradia          #+#    #+#             */
/*   Updated: 2019/02/25 20:37:55 by vmuradia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_H
# define FILLER_H

# include "./libft/libft.h"
# include "stdio.h"
# include "stdlib.h"

typedef struct			s_data
{
	int					piece_h;
	int					piece_w;
	int					height;
	int					width;
	char				my_sign;
	int					player_done;
	char				**map;
	char				**piece;
	int					final_x;
	int					final_y;
	int					min;
	char				enemy;
	int					i;
	int					j;
	int					dest;
	int					right;
	int					left;
	int					read_point;
}						t_data;

void					read_each_line(char *line, t_data *data);
char					*get_player(char *line, t_data *data);
char					*get_map_size(char *line, t_data *data);
char					*get_map(char *line, t_data *data);
char					*get_piece_size(char *line, t_data *data);
char					*get_piece(char *line, t_data *data);
void					print_cords(int y, int x);
void					find_target(t_data *data);
int						check_piece(t_data *data, int x, int y);
void					find_dest(t_data *data, int x, int y);
int						check_column(t_data *data, int i);
int						check_row(t_data *data, int i, int j);
void					*make_a_map(t_data *data);
void					*make_piece(t_data *data);

#endif
