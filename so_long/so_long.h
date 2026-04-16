/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgumusay <fgumusay@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 16:25:28 by fgumusay          #+#    #+#             */
/*   Updated: 2024/06/29 10:32:23 by fgumusay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# define ESC 53
# define W 13
# define A 0
# define S 1
# define D 2

typedef struct s_data
{
	char	**map;
	int		height;
	int		width;
	int		c_count;
	int		e_count;
	int		p_count;
	int		player_x;
	int		player_y;
	int		move_count;
	void	*player_img;
	void	*player_exit_img;
	void	*collectible_img;
	void	*wall_img;
	void	*exit_img;
	void	*ground_img;
	int		img_size;
	void	*mlx;
	void	*mlx_win;
}				t_data;

void	map_read(t_data *data, int i, int j, char *map);
void	fill_data(t_data *data, char *map);
void	map_wall_control(t_data *data);
void	move_control(t_data *data);
void	ft_free(t_data *data, int flag);
int		ft_exit(t_data *data);
void	free_visited(char **visited, t_data *data, int flag);
void	add_graphics(t_data *data, int i, int j);
int		ft_move(int key_code, t_data *data);
void	move_control(t_data *data);
void	mlx_control(t_data *data);
void	setup_data(t_data *data);

#endif
