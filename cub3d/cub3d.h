/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgumusay <fgumusay@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 17:25:28 by ndogan            #+#    #+#             */
/*   Updated: 2025/01/10 15:57:31 by fgumusay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdbool.h>
# include <stdio.h>

# define W_WIDTH 1920
# define W_HEIGHT 1080

# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_LEFT 65361
# define KEY_RIGHT 65363
# define KEY_ESC 65307

typedef struct s_player
{
	double			move_speed;
	double			pos_x;
	double			pos_y;
	double			turn_angle;
	double			dir_x;
	double			dir_y;
	double			fov_x;
	double			fov_y;
}					t_player;

typedef struct s_color
{
	int				r;
	int				g;
	int				b;
	int				rgb_value;
	bool			is_defined;
}					t_color;

typedef struct s_keys
{
	bool			w;
	bool			a;
	bool			s;
	bool			d;
	bool			right;
	bool			left;
}					t_keys;

typedef struct s_image
{
	char			*image_path;
	void			*mlx_image;
	int				*pixel_data;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
	int				width;
	int				height;
}					t_image;

typedef struct s_texture
{
	double			offset;
	int				x_coord;
	int				y_coord;
	int				width;
	int				height;
}					t_texture;

typedef struct s_ray
{
	double			cam_x;
	double			ray_dir_x;
	double			ray_dir_y;
	double			s_dist_x;
	double			s_dist_y;
	double			d_dist_x;
	double			d_dist_y;
	double			p_wall_dist;
	double			step;
	int				map_x;
	int				map_y;
	int				step_x;
	int				step_y;
	int				side;
	int				line_h;
	int				draw_start;
	int				draw_end;
	double			wall_x;
	int				floor_c;
	int				ceil_c;
	t_texture		tex;
	t_texture		active_tex;
}					t_ray;

typedef struct s_wall
{
	t_image			n_tex;
	t_image			s_tex;
	t_image			w_tex;
	t_image			e_tex;
}					t_wall;

typedef struct s_vector
{
	double			x;
	double			y;
}					t_vector;

typedef struct s_mlx
{
	void			*mlx;
	void			*mlx_win;
}					t_mlx;

typedef struct s_map
{
	char			**map_2d;
	char			*no_path;
	char			*so_path;
	char			*we_path;
	char			*ea_path;
	int				map_height;
	int				map_width;
	t_wall			wall;
	t_color			floor_color;
	t_color			ceiling_color;
}					t_map;

typedef struct s_data
{
	t_image			image;
	t_player		player;
	t_mlx			mlx;
	t_map			map;
	t_keys			key;
	t_vector		vector;
}					t_data;

typedef struct s_malloc
{
	void			*ptr;
	struct s_malloc	*next;
}					t_malloc;

void				init_data(t_data *data);
void				init_graphics(t_data *data);
void				init_texture(t_data *d);
int					game_loop(t_data *data);
void				raycast(t_data *data);
void				calculate_ray(t_data *d, t_ray *ray, int x);
void				init_ray(t_data *d, t_ray *ray);
void				trace_ray(t_data *data, t_ray *ray);
void				calc_wall_bounds(t_ray *ray);
void				select_wall_texture(t_data *d, t_ray *ray);
void				add_garbage_c(void *ptr);
void				garbage_collecter(void *ptr);
void				gc_free(void);
t_malloc			*get_garbage_c(void);
void				*gc_malloc(unsigned int size);
void				safe_free(void *ptr);
void				safe_exit(char *str);
int					game_quit(t_data *data);
void				ft_exit_mlx(t_data *data);
bool				is_valid_char(char c);
void				find_player(char **map, t_data *data);
void				flood_fill(char **map, int len, int y, int x);
void				map_check(t_data *data);
const char			*parse_number(const char *str, int *s);
int					parse_rgb_values(const char *str, int *data);
void				parse_single_param(char *mappin, t_map *map, int *i,
						int *c);
void				parse_map_params(char *mappin, t_map *map, int *i);
void				parse_map(char *mappin, t_data *data);
int					ft_isspace(const char *str);
int					everything_okay(t_map map);
int					get_path(char *map, char **path);
int					parse_rgb(const char *str, t_color *color);
char				*map_line_build(int len, char *line);
void				build_control_map(t_data *data);
void				build_2d_map(t_data *data, char *mappin);
int					get_row_count(char *mappin);
char				**get_map_lines(char *mappin, int row_index, int start,
						int row_count);
bool				is_white_space(char c);
int					get_space_count(char *str, int location, char s_or_e);
int					get_file_size(int fd);
int					map_file_ctrl(char *file_name);
char				*read_map(char *file_name, int file_size, int fd);

#endif
