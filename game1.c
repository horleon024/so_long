/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhorefto <lhorefto@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/04 12:09:21 by lhorefto          #+#    #+#             */
/*   Updated: 2021/07/13 14:58:23 by lhorefto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

static void	ft_load_image(t_game *game, t_img *img, void *mlx, char *path)
{
	img->img_ptr = mlx_xpm_file_to_image(mlx, path, &img->width, &img->height);
	if (!img->img_ptr)
	{
		ft_putstr_fd("Error\nWhile loading images\n", 2);
		ft_free_exit(game);
	}
	img->addr = mlx_get_data_addr(img->img_ptr, &img->bits_per_pixel,
			&img->linelength, &img->endian);
}

static void	ft_draw_map(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (game->map2d[i])
	{
		j = 0;
		while (game->map2d[i][j])
		{
			if (game->map2d[i][j] == '1')
				ft_draw_on_img(game->img, game->wall, j * PIX, i * PIX);
			else
				ft_draw_on_img(game->img, game->floor, j * PIX, i * PIX);
			j++;
		}
		i++;
	}
}

static void	ft_draw_elements(t_game *game)
{
	int		i;
	int		j;
	t_elem	*elem;

	i = 0;
	while (game->map2d[i])
	{
		j = 0;
		while (game->map2d[i][j])
		{
			if (game->map2d[i][j] == 'C')
			{
				elem = ft_get_collectible(game, i, j);
				if (elem && elem->visited == false)
					ft_draw_on_img(game->img, &game->coll->img,
						j * PIX, i * PIX);
			}
			else if (game->map2d[i][j] == 'E')
				ft_draw_on_img(game->img, &game->exit->img,
					j * PIX, i * PIX);
			j++;
		}
		i++;
	}	
}

int	ft_render_next_frame(t_game *game)
{
	mlx_put_image_to_window(game->ptrs->mlx, game->ptrs->win,
		game->img->img_ptr, 0, 0);
	ft_draw_map(game);
	ft_draw_elements(game);
	ft_draw_player(game);
	return (1);
}

void	ft_start_game(t_game *game)
{
	game->ptrs->mlx = mlx_init();
	game->ptrs->win = mlx_new_window(game->ptrs->mlx,
			game->map->linelength * PIX, game->map->lines * PIX, "So_long");
	game->img->img_ptr = mlx_new_image(game->ptrs->mlx,
			game->map->linelength * PIX, game->map->lines * PIX);
	game->img->addr = mlx_get_data_addr(game->img->img_ptr,
			&game->img->bits_per_pixel,
			&game->img->linelength, &game->img->endian);
	ft_load_image(game, &game->player->img, game->ptrs->mlx, PLAYERPATH);
	ft_load_image(game, game->wall, game->ptrs->mlx, WALLPATH);
	ft_load_image(game, game->floor, game->ptrs->mlx, FLOORPATH);
	ft_load_image(game, &game->coll->img, game->ptrs->mlx, COLLPATH);
	ft_load_image(game, &game->exit->img, game->ptrs->mlx, EXITPATH);
	mlx_loop_hook(game->ptrs->mlx, ft_render_next_frame, game);
	mlx_hook(game->ptrs->win, 2, 1, ft_key_hook, game);
	mlx_hook(game->ptrs->win, 33, 32, ft_close_clean, game);
	mlx_loop(game->ptrs->mlx);
}
