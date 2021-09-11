/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhorefto <lhorefto@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/03 12:48:18 by lhorefto          #+#    #+#             */
/*   Updated: 2021/07/04 16:50:23 by lhorefto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

static int	ft_getnumberoflines(char *pathofmap)
{
	int		lines;
	char	tmp[1];
	int		fd;

	fd = open(pathofmap, O_RDONLY);
	lines = 1;
	while (read(fd, tmp, 1) == 1)
	{
		if (tmp[0] == '\n')
			lines++;
	}
	close(fd);
	return (lines);
}

static void	ft_checkrectangular(char *pathofmap)
{
	int		fd;
	int		firstlength;
	int		currentlength;
	int		currentline;
	char	tmp[1];

	fd = open(pathofmap, O_RDONLY);
	firstlength = 0;
	currentline = 1;
	while (read(fd, tmp, 1) == 1)
	{
		if (currentline == 1 && tmp[0] != '\n')
			firstlength++;
		if (currentline != 1 && tmp[0] != '\n')
			currentlength++;
		else if (tmp[0] == '\n')
		{
			if (currentline != 1 && currentlength != firstlength)
				ft_printerror("Map is not rectangular\n");
			currentlength = 0;
			currentline++;
		}
	}
	close(fd);
}

static int	ft_getlinelength(char *pathofmap)
{
	int		fd;
	int		length;
	char	tmp[1];
	int		readreturn;

	length = 0;
	fd = open(pathofmap, O_RDONLY);
	while (1)
	{
		readreturn = read(fd, tmp, 1);
		if (readreturn == 1 && tmp[0] != '\n')
			length++;
		else if (tmp[0] == '\n' || readreturn == 0)
			break ;
	}
	return (length);
}

static void	ft_checkwalls(char *pathofmap)
{
	int		nboflines;
	int		line;
	char	tmp[1];
	int		fd;
	int		linelengths[2];

	linelengths[0] = ft_getlinelength(pathofmap);
	linelengths[1] = 0;
	nboflines = ft_getnumberoflines(pathofmap);
	fd = open(pathofmap, O_RDONLY);
	line = 1;
	while (read(fd, tmp, 1) == 1)
	{
		if (tmp[0] != '1' && tmp[0] != '\n' && (line == 1 || line == nboflines))
			ft_printerror("Map is not surrounded by walls\n");
		else if ((linelengths[1]++ == 0 || linelengths[1] == linelengths[0])
			&& tmp[0] != '1')
			ft_printerror("Map is not surrounded by walls\n");
		else if (tmp[0] == '\n')
		{
			line++;
			linelengths[1] = 0;
		}
	}
	close(fd);
}

void	ft_checkmap(char *pathofmap)
{
	char	tmp[1];
	int		fd;
	int		nbofstarts;
	int		nbofcollectible;
	int		nbofexit;

	nbofexit = 0;
	nbofcollectible = 0;
	nbofstarts = 0;
	ft_checkrectangular(pathofmap);
	ft_checkwalls(pathofmap);
	fd = open(pathofmap, O_RDONLY);
	while (read(fd, tmp, 1) == 1)
	{
		if (tmp[0] != '1' && tmp[0] != '\n' && tmp[0] != 'C'
			&& tmp[0] != '0' && tmp[0] != 'E' && tmp[0] != 'P')
			ft_printerror("Wrong characters used for the map\n");
		nbofexit += (tmp[0] == 'E');
		nbofcollectible += (tmp[0] == 'C');
		nbofstarts += (tmp[0] == 'P');
	}
	close(fd);
	if (nbofexit == 0 || nbofcollectible == 0 || nbofstarts != 1)
		ft_printerror("Wrong number of exits, players or collectibles\n");
}
