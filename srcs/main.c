/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llee <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/15 10:59:58 by llee              #+#    #+#             */
/*   Updated: 2019/01/15 11:00:08 by llee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

int		main(int argc, char **argv)
{
	t_file	*file;
	t_map	*map;
	t_mlx	*mlx;

	mlx = NULL;
	if (argc > 1)
	{
		if (setup_map(&file, &map, argv[1]) != -1)
			setup_mlx(map, mlx);
		else
			perror("error");
	}
	else
		perror("usage: ./fdf [input height map]\n");
	return (0);
}

int		setup_map(t_file **file, t_map **map, char *path)
{
	*file = init_file();
	*map = init_map();
	copy_argv(file, path);
	if (get_row_col(file, map) == -1)
		return (-1);
	make_map(map);
	copy_to_map(file, map);
	find_min_max(map);
	return (0);
}

int		setup_mlx(t_map *map, t_mlx *mlx)
{
	mlx = init_mlx();
	mlx->map = map;
	render(mlx);
	mlx_key_hook(mlx->win_ptr, hook_keydown, mlx);
	mlx_hook(mlx->win_ptr, 4, 0, hook_mousedown, mlx);
	mlx_hook(mlx->win_ptr, 5, 0, hook_mouseup, mlx);
	mlx_hook(mlx->win_ptr, 6, 0, hook_mousemove, mlx);
	mlx_loop(mlx->mlx_ptr);
	return (0);
}

void	copy_to_map_2(t_file **file, t_map **map, int i)
{
	(*map)->imap[0][i] = ft_atoi((*file)->cmap[i]);
	free((*file)->cmap[i]);
}
