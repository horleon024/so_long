/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhorefto <lhorefto@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/04 14:19:31 by lhorefto          #+#    #+#             */
/*   Updated: 2021/07/04 17:39:23 by lhorefto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

int	main(int argc, char **argv)
{
	t_game	*game;

	if (argc != 2)
		ft_printerror("Wrong number of arguments\n");
	ft_checkmap(argv[1]);
	game = ft_init_game();
	ft_getmapdata(argv[1], game->map);
	game->map2d = (char **)malloc(sizeof(char *) * (game->map->lines + 1));
	if (!game->map2d)
		ft_free_exit(game);
	ft_get2dmap(argv[1], game);
	ft_get_positions(game);
	ft_start_game(game);
	return (0);
}
