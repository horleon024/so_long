/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solong.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhorefto <lhorefto@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/03 12:29:13 by lhorefto          #+#    #+#             */
/*   Updated: 2021/07/22 17:40:57 by lhorefto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOLONG_H
# define SOLONG_H
# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include <fcntl.h>
# include <sys/types.h>
# include "mlx/mlx.h"
# define A 97
# define W 119
# define D 100
# define S 115
# define BLACK 0xFF000000
# define ESC 65307
# define PIX 256
# define WALLPATH "textures/wall.xpm"
# define FLOORPATH "textures/floor.xpm"
# define PLAYERPATH "textures/player.xpm"
# define EXITPATH "textures/exit.xpm"
# define COLLPATH "textures/donut.xpm"

typedef struct s_img
{
	void	*img_ptr;
	char	*addr;
	int		bits_per_pixel;
	int		linelength;
	int		endian;
	int		width;
	int		height;
}			t_img;

typedef struct s_ptrs
{
	void	*mlx;
	void	*win;
}			t_ptrs;

typedef struct s_map
{
	int	lines;
	int	linelength;
}		t_map;

typedef struct s_player
{
	t_img	img;
	int		x;
	int		y;
	float	smooth_x;
	float	smooth_y;
}			t_player;

typedef struct s_elem
{
	int				x;
	int				y;
	bool			visited;
	struct s_elem	*next;
}					t_elem;

typedef struct s_list
{
	t_elem	*first;
	t_img	img;
}			t_list;

typedef struct s_draw
{
	int		x;
	int		y;
	float	r_x;
	float	r_y;
	int		color;
	int		pos_x;
	int		pos_y;
	int		p_data_x;
	int		p_data_y;
}				t_draw;

typedef struct s_game
{
	t_player		*player;
	t_list			*coll;
	t_list			*exit;
	t_img			*img;
	t_img			*floor;
	t_img			*wall;
	t_ptrs			*ptrs;
	t_map			*map;
	char			**map2d;
	int				moves;
}					t_game;

void	ft_putstr_fd(const char *str, int fd);
int		ft_strlen(const char *s);
void	ft_printerror(const char *msg);
void	ft_checkmap(char *pathofmap);
t_game	*ft_init_game(void);
void	ft_free_exit(t_game *game);
void	ft_getmapdata(char *pathofmap, t_map *map);
void	ft_get2dmap(char *pathofmap, t_game *game);
void	ft_lst_addback(t_game *game, t_list *list, int x, int y);
void	ft_get_positions(t_game *game);
void	ft_putnbr(int nb);
int		ft_close_clean(t_game *game);
void	ft_draw_on_img(t_img *img, t_img *upp_img, int startx, int starty);
int		ft_render_next_frame(t_game *game);
t_elem	*ft_get_collectible(t_game *game, int i, int j);
void	ft_draw_player(t_game *game);
bool	ft_is_collectible(t_game *game, int i, int j);
void	ft_set_to_visited(t_game *game);
bool	ft_all_coll_picked(t_game *game);
bool	ft_is_exit(t_game *game, int i, int j);
int		ft_key_hook(int key, t_game *game);
void	ft_start_game(t_game *game);

#endif