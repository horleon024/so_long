/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readmap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhorefto <lhorefto@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/03 13:22:12 by lhorefto          #+#    #+#             */
/*   Updated: 2021/07/04 12:06:25 by lhorefto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

void	ft_getmapdata(char *pathofmap, t_map *map)
{
	char	tmp[1];
	int		fd;

	fd = open(pathofmap, O_RDONLY);
	map->lines = 1;
	map->linelength = 0;
	while (read(fd, tmp, 1) == 1)
	{
		if (tmp[0] != '\n' && map->lines == 1)
			map->linelength++;
		else if (tmp[0] == '\n')
			map->lines++;
	}
	close(fd);
}

void	ft_get2dmap(char *pathofmap, t_game *game)
{
	char	tmp[1];
	int		cline;
	int		ccoll;
	int		fd;

	cline = 0;
	ccoll = 0;
	fd = open(pathofmap, O_RDONLY);
	game->map2d[cline] = (char *)malloc(game->map->linelength + 1);
	while (read(fd, tmp, 1) == 1)
	{
		if (tmp[0] == '\n')
		{
			game->map2d[cline++][ccoll] = '\0';
			game->map2d[cline] = (char *)malloc(game->map->linelength + 1);
			ccoll = 0;
		}
		else if (tmp[0] != '\n')
			game->map2d[cline][ccoll] = tmp[0];
		if (tmp[0] != '\n')
			ccoll++;
	}
	game->map2d[cline][ccoll] = '\0';
	game->map2d[cline + 1] = '\0';
	close(fd);
}

void	ft_get_positions(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < game->map->lines)
	{
		j = 0;
		while (game->map2d[i][j])
		{
			if (game->map2d[i][j] == 'C')
				ft_lst_addback(game, game->coll, i, j);
			if (game->map2d[i][j] == 'E')
				ft_lst_addback(game, game->exit, i, j);
			if (game->map2d[i][j] == 'P')
			{
				game->player->x = i;
				game->player->y = j;
				game->player->smooth_x = i;
				game->player->smooth_y = j;
			}
			j++;
		}
		i++;
	}
}
