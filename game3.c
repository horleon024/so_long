/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhorefto <lhorefto@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/04 13:54:00 by lhorefto          #+#    #+#             */
/*   Updated: 2021/07/04 14:18:18 by lhorefto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

static void	ft_display_moves(t_game *game)
{
	ft_putnbr(game->moves);
	ft_putstr_fd("\n", 1);
}

static void	ft_other_keys(int key, t_game *game)
{
	if (game->map2d[game->player->x][game->player->y + 1] != '1' && key == D)
	{
		game->player->y += 1;
		game->moves++;
		ft_display_moves(game);
	}
	if (key == ESC)
		ft_close_clean(game);
	if (ft_is_collectible(game, game->player->x, game->player->y))
		ft_set_to_visited(game);
	if (ft_is_exit(game, game->player->x, game->player->y)
		&& ft_all_coll_picked(game))
		ft_close_clean(game);
}

int	ft_key_hook(int key, t_game *game)
{
	if (game->map2d[game->player->x - 1][game->player->y] != '1' && key == W)
	{
		game->player->x -= 1;
		game->moves++;
		ft_display_moves(game);
	}
	if (game->map2d[game->player->x][game->player->y - 1] != '1' && key == A)
	{
		game->player->y -= 1;
		game->moves++;
		ft_display_moves(game);
	}
	if (game->map2d[game->player->x + 1][game->player->y] != '1' && key == S)
	{
		game->player->x += 1;
		game->moves++;
		ft_display_moves(game);
	}
	ft_other_keys(key, game);
	return (1);
}
