/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhorefto <lhorefto@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/03 12:50:26 by lhorefto          #+#    #+#             */
/*   Updated: 2021/08/12 14:32:19 by lhorefto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

static void	ft_init_img(t_img *img)
{
	game->img->img_ptr = NULL;
	game->img->addr = NULL;
	game->img->bits_per_pixel = 0;
	game->img->linelength = 0;
	game->img->endian = 0;
	game->img->width = 0;
	game->img->height = 0;
	
}

static void	ft_init_ptrs(t_game *game)
{
	game->ptrs->mlx = NULL;
	game->ptrs->win = NULL;
}

static void	ft_init_map(t_game *game)
{
	game->map->linelength = 0;
	game->map->lines = -1;
}

static void	ft_init_player(t_game *game)
{
	game->player->x = 0;
	game->player->y = 0;
	game->player->smooth_x = 0;
	game->player->smooth_y = 0;
}

t_game	*ft_init_game(void)
{
	t_game	*game;

	game = (t_game *)malloc(sizeof(t_game));
	game->player = (t_player *)malloc(sizeof(t_player));
	ft_init_player(game);
	game->coll = (t_list *)malloc(sizeof(t_list));
	game->coll->first = NULL;
	game->exit = (t_list *)malloc(sizeof(t_list));
	game->exit->first = NULL;
	game->map = (t_map *)malloc(sizeof(t_map));
	ft_init_map(game);
	game->map2d = NULL;
	game->img = (t_img *)malloc(sizeof(t_img));
	ft_init_img(game);
	game->ptrs = (t_ptrs *)malloc(sizeof(t_ptrs));
	ft_init_ptrs(game);
	game->floor = (t_img *)malloc(sizeof(t_img));
	game->wall = (t_img *)malloc(sizeof(t_img));
	game->moves = 0;
	if (!game || !game->player || !game->coll || !game->exit || !game->map
		|| !game->img || !game->ptrs || !game->wall || !game->floor)
		ft_free_exit(game);
	return (game);
}
