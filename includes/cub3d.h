/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mverbrug <mverbrug@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/08 14:20:47 by mverbrug      #+#    #+#                 */
/*   Updated: 2023/09/21 17:20:31 by mverbrug      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

//			INCLUDES

# include <libft.h> // for libft
# include <MLX42/MLX42.h> // for MLX42
# include <memory.h> // for MLX42
# include <stdio.h> // for MLX42
# include <stdlib.h> // for malloc, free, exit
# include <unistd.h> // for write, read
# include <fcntl.h> // for open
# include <math.h> // for cos and sin

//			MACROS

# define SUCCESS 0
# define FAILURE -1

# define X 0
# define Y 1

# define SCREEN_WIDTH 640
# define SCREEN_HEIGHT 480

# define MINIMAP_WIDTH 150
# define MINIMAP_HEIGHT 150
# define MINIMAP_TILES 15
# define MINIMAP_CENTRE 8

# define MOVE_SPEED 0.07
# define ROTATE_SPEED 0.03

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 32
# endif

//			STRUCTURES

typedef struct s_player
{
	mlx_image_t	*img;
	double		pos_x;
	double		pos_y;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
}	t_player;

typedef struct s_mini_map
{
	mlx_image_t	*img;
	int			max_width_points;
	int			max_height_points;
	int			x;
	int			y;
	int			y2;
	int			x2;
	int			x_interval;
	int			y_interval;
	int			x_hold;
	int			y_hold;
}	t_mini_map;

typedef struct s_cub3d
{
	t_player		*player;
	mlx_t			*mlx;
	char			**map;
	t_mini_map		*mm;
	uint32_t		ceiling_colour;
	uint32_t		floor_colour;
	mlx_texture_t	*n_texture;
	mlx_texture_t	*e_texture;
	mlx_texture_t	*s_texture;
	mlx_texture_t	*w_texture;
	int				contrast;
	bool			ceiling_flag;
	bool			floor_flag;
	int				mouse_x;
}	t_cub3d;

typedef struct s_ray
{
	double	dir_x;
	double	dir_y;
	int		map_x;
	int		map_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	side_dist_x;
	double	side_dist_y;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
	double	perp_wall_dist;
	int		line_start;
	int		line_end;
}	t_ray;

//			FUNCTIONS

//			COLOUR.c
uint32_t	rgba_to_colour(int r, int g, int b, int a);
void		set_colour_flag(t_cub3d *cub3d, char identifier);
int			get_colour(t_cub3d *cub3d, char *sdf_str, int *i);

//			DRAW_VERTICAL
void		draw_vertical(int x, t_cub3d *cub3d, t_player *player);

//			ERROR HANDLE
int			error_mlx(void);
int			error_mlx_load_png(char *identifier);
int			error_sdf(char *msg);
int			error(char *msg);

// 			FREE
char		**free_2d_array(char **array_2d);
void		free_all(t_cub3d *cub3d);

// 			GET START POSITION
void		get_start_position_and_direction(t_cub3d *cub3d);

//			HOOKERS
void		hookers(t_cub3d *cub3d);

//			INIT
int			init_mm(t_cub3d *cub3d);
int			init_cub3d(t_cub3d *cub3d);
int			init_imgs(t_cub3d *cub3d);

//			MAP
int			validate_map(char **map);

//			MINI MAP COLOURS
uint32_t	get_colour_mm(char **map, int x, int y, t_cub3d *cub3d);

//			MINI_MAP
int			map_max_width(char **map);
int			map_max_height(char **map);
int			check_y(int y_player, t_mini_map *mm);
int			check_x(int x_player, t_mini_map *mm);
void		draw_mini_map(t_cub3d *cub3d, t_mini_map *mm);

//			MLX
void		draw(t_cub3d *cub3d);
void		end_mlx(t_cub3d *cub3d);
int			perform_mlx_stuff(t_cub3d *cub3d);

//			MOVE
void		move(mlx_key_data_t keydata, t_cub3d *cub3d, t_player *player);

//			PARSER CHECKS
bool		is_identifier(char *str);
bool		is_double_colour(t_cub3d *cub3d, char identifier);
bool		is_double_texture_identifier(t_cub3d *cub3d, char *identifier);
bool		all_elements_provided(t_cub3d *cub3d);

//			PARSER
int			parser(char **argv, t_cub3d *cub3d);

//			PLAYER_VIEW
void		draw_player_view(t_cub3d *cub3d, t_player *player);

//			RAYCASTING
int			get_line_height(int x, t_cub3d *cub3d, \
			t_player *player, t_ray *ray);

//			READ SDF
int			open_sdf(char **argv);
int			file_to_str(int fd, char **file);

//			ROTATE
void		rotate_right(t_player *player);
void		rotate_left(t_player *player);
void		rotate(mlx_key_data_t keydata, t_player *player);

// 			TESTS
void		print_sdf(t_cub3d *cub3d);

// 			UTILS
void		skip_char(char *str, int *i, char c);
bool		is_position_char(int c);

#endif
