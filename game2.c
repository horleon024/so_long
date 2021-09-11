/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhorefto <lhorefto@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/04 13:26:26 by lhorefto          #+#    #+#             */
/*   Updated: 2021/07/07 12:29:12 by lhorefto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

static int	ft_get_pixel(t_img *img, int x, int y)
{
	return (*(int *)(img->addr + y * img->linelength + x
		* img->bits_per_pixel / 8));
}

static void	ft_set_pixel(t_img *img, int x, int y, int color)
{
	*(unsigned int *)(img->addr + y * img->linelength + x
			* img->bits_per_pixel / 8) = color;
}

void	ft_draw_on_img(t_img *img, t_img *upp_img, int startx, int starty)
{
	t_draw	draw;

	draw.x = 0;
	while (draw.x < PIX)
	{
		draw.y = 0;
		while (draw.y < PIX)
		{
			draw.r_x = (float)draw.x / (float)PIX;
			draw.r_y = (float)draw.y / (float)PIX;
			draw.pos_x = draw.r_x * upp_img->width;
			draw.pos_y = draw.r_y * upp_img->height;
			draw.color = ft_get_pixel(upp_img, draw.pos_x, draw.pos_y);
			draw.p_data_x = startx + draw.x;
			draw.p_data_y = starty + draw.y;
			if (draw.color != (int)BLACK)
				ft_set_pixel(img, draw.p_data_x, draw.p_data_y, draw.color);
			draw.y++;
		}
		draw.x++;
	}
}

void	ft_draw_player(t_game *game)
{
	game->player->smooth_x += (game->player->x - game->player->smooth_x) * 0.5;
	game->player->smooth_y += (game->player->y - game->player->smooth_y) * 0.5;
	ft_draw_on_img(game->img, &game->player->img,
		(int)(game->player->smooth_y * PIX),
		(int)(game->player->smooth_x * PIX));
}
