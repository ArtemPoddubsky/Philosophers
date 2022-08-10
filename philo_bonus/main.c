/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lholdo <lholdo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 16:31:13 by lholdo            #+#    #+#             */
/*   Updated: 2022/07/09 10:31:10 by lholdo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	cleanup(t_all *all)
{
	int	i;
	int	ret;

	ret = 0;
	i = 0;
	while (i < all->args->num_philos)
	{
		if (pthread_join(all->philos[i].monitor, NULL))
			ret = ERROR;
		if (kill(all->philos[i].pid, SIGKILL))
			ret = ERROR;
		i++;
	}
	free(all->shared.t_last_meal);
	free(all->args);
	free(all->philos);
	sem_close(all->shared.write);
	sem_close(all->shared.main);
	sem_close(all->shared.forks);
	return (ret);
}

int	main(int argc, char **argv)
{
	t_all		all;

	all.args = (t_args *)malloc(sizeof(t_args));
	if (!all.args)
		return (ERROR);
	if (parse_args(all.args, argc, argv) || init_shared(&all)
		|| init_philosophers(&all))
		return (ERROR);
	if (start_processes(&all))
	{
		free(all.args);
		free(all.shared.t_last_meal);
		free(all.philos);
		return (ERROR);
	}
	if (cleanup(&all))
		return (ERROR);
	return (0);
}
