/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_vertical.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhuisman <fhuisman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/03 17:30:39 by fhuisman      #+#    #+#                 */
/*   Updated: 2023/10/03 17:30:42 by fhuisman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static uint32_t	get_colour_from_texture(mlx_texture_t *texture, int *tex)
{
	int	r;
	int	g;
	int	b;
	int	a;

	r = texture->pixels[tex[Y] * texture->width * 4 + (tex[X] * 4)];
	g = texture->pixels[tex[Y] * texture->width * 4 + (tex[X] * 4) + 1];
	b = texture->pixels[tex[Y] * texture->width * 4 + (tex[X] * 4) + 2];
	a = texture->pixels[tex[Y] * texture->width * 4 + (tex[X] * 4) + 3];
	return (rgba_to_colour(r, g, b, a));
}

static int	get_tex_x(t_ray ray, t_player *player, mlx_texture_t *texture)
{
	int		tex_x;
	double	wall_x;

	if (texture == NULL)
		return (-1);
	if (ray.side == 0)
		wall_x = player->pos_y + ray.perp_wall_dist * ray.dir_y;
	else
		wall_x = player->pos_x + ray.perp_wall_dist * ray.dir_x;
	wall_x -= floor(wall_x);
	tex_x = (int)((wall_x * (double) texture->width));
	if (ray.side == 0 && ray.dir_x > 0)
		tex_x = texture->width - tex_x - 1;
	if (ray.side == 1 && ray.dir_y < 0)
		tex_x = texture->width - tex_x - 1;
	return (tex_x);
}

static mlx_texture_t	*get_texture(t_ray ray, t_cub3d *cub3d)
{
	if (ray.side == 0)
	{
		if (ray.step_x > 0)
			return (cub3d->e_texture);
		else
			return (cub3d->w_texture);
	}
	else
	{
		if (ray.step_y > 0)
			return (cub3d->s_texture);
		else
			return (cub3d->n_texture);
	}
}

static void	get_line_start_and_end(int x, t_cub3d *cub3d, t_ray *ray)
{
	int	line_height;

	line_height = get_line_height(x, cub3d, cub3d->player, ray);
	ray->line_start = -line_height / 2 + SCREEN_HEIGHT / 2;
	if (ray->line_start < 0)
		ray->line_start = 0;
	ray->line_end = line_height / 2 + SCREEN_HEIGHT / 2;
	if (ray->line_end >= SCREEN_HEIGHT)
		ray->line_end = SCREEN_HEIGHT - 1;
}

void	draw_vertical(int x, t_cub3d *cub3d, t_player *player)
{
	t_ray			ray;
	int				tex[2];
	mlx_texture_t	*texture;
	double			step;
	double			tex_pos;

	get_line_start_and_end(x, cub3d, &ray);
	texture = get_texture(ray, cub3d);
	tex[X] = get_tex_x(ray, player, texture);
	step = 1.0 * texture->height / (ray.line_end - ray.line_start);
	tex_pos = (ray.line_start - SCREEN_HEIGHT / 2
			+ (ray.line_end - ray.line_start) / 2) * step;
	while (ray.line_start <= ray.line_end)
	{
		tex[Y] = (int) tex_pos & (texture->height - 1);
		tex_pos += step;
		mlx_put_pixel(player->img, x, ray.line_start,
			get_colour_from_texture(texture, tex));
		ray.line_start++;
	}
}
