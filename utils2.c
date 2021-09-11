/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhorefto <lhorefto@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/04 14:12:27 by lhorefto          #+#    #+#             */
/*   Updated: 2021/07/04 16:53:31 by lhorefto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

void	ft_lst_addback(t_game *game, t_list *list, int x, int y)
{
	t_elem	*elem;
	t_elem	*tmp;

	elem = (t_elem *)malloc(sizeof(t_elem));
	if (!elem)
		ft_free_exit(game);
	elem->x = x;
	elem->y = y;
	elem->visited = false;
	if (!list->first)
	{
		elem->next = NULL;
		list->first = elem;
		return ;
	}
	tmp = list->first;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = elem;
	elem->next = NULL;
}

bool	ft_is_exit(t_game *game, int i, int j)
{
	t_elem	*elem;

	elem = game->exit->first;
	while (elem)
	{
		if (elem->x == i && elem->y == j)
			return (true);
		elem = elem->next;
	}
	return (false);
}
