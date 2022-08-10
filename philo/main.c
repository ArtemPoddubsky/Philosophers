/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lholdo <lholdo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 16:13:53 by lholdo            #+#    #+#             */
/*   Updated: 2022/07/09 10:28:59 by lholdo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	cleanup(t_all *all)
{
	int	i;

	i = -1;
	while (++i < all->args->num_philos)
	{
		pthread_mutex_destroy(&all->philos[i].protection);
		pthread_mutex_destroy(&all->shared.forks[i]);
	}
	pthread_mutex_destroy(all->shared.forks);
	pthread_mutex_destroy(&all->shared.write);
	free(all->shared.forks);
	free(all->shared.t_last_meal);
	free(all->philos);
	free(all->args);
}

int	join_threads(t_all *all)
{
	int	i;

	i = -1;
	while (++i < all->args->num_philos)
	{
		if (pthread_join(all->philos[i].thread, NULL))
			return (ERROR);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_all		all;

	all.args = (t_args *)malloc(sizeof(t_args));
	if (!all.args)
		return (ERROR);
	if (parse_args(all.args, argc, argv) || init_shared(&all)
		|| (init_philos(&all)))
		return (ERROR);
	if (start_threads(&all) || join_threads(&all))
		return (ERROR);
	cleanup(&all);
	return (0);
}
