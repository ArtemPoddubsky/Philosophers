/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lholdo <lholdo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 21:51:23 by lholdo            #+#    #+#             */
/*   Updated: 2021/12/09 22:08:46 by lholdo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	init_shared_sems(t_all *all)
{
	sem_unlink("forks");
	sem_unlink("write");
	sem_unlink("main");
	sem_unlink("num_eats");
	all->shared.forks = sem_open("forks", O_CREAT | O_EXCL,
			0644, all->args->num_philos);
	all->shared.write = sem_open("write", O_CREAT | O_EXCL, 0644, 1);
	all->shared.main = sem_open("main", O_CREAT | O_EXCL, 0644, 0);
	all->shared.num_eats = sem_open("num_eats", O_CREAT | O_EXCL,
			0644, 0);
	if (all->shared.forks == SEM_FAILED || all->shared.write == SEM_FAILED
		|| all->shared.main == SEM_FAILED || all->shared.num_eats == SEM_FAILED)
	{
		free(all->shared.t_last_meal);
		free(all->args);
		return (ERROR);
	}
	return (0);
}

void	init_const(t_all *all, int i)
{
	all->philos[i].shared = &all->shared;
	all->philos[i].num_of_philos = all->args->num_philos;
	all->philos[i].number = i + 1;
	all->philos[i].time_to_die = all->args->time_to_die;
	all->philos[i].time_to_eat = all->args->time_to_eat;
	all->philos[i].time_to_sleep = all->args->time_to_sleep;
	all->philos[i].num_of_eats = all->args->num_of_eats;
	all->philos[i].actual_eats = 0;
	all->philos[i].forks = all->shared.forks;
}
