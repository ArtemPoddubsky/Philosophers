/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lholdo <lholdo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 15:11:46 by lholdo            #+#    #+#             */
/*   Updated: 2022/07/09 17:21:11 by lholdo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	death_conditions(t_philo *philo, long time)
{
	if (time - philo->shared->t_last_meal[philo->number_id - 1]
		>= philo->time_to_die)
	{
		philo->shared->dead = 1;
		pthread_mutex_lock(&philo->shared->write);
		if (philo->shared->dead)
			print_action(philo->number_id, DEATH);
		pthread_mutex_unlock(&philo->shared->write);
		return (1);
	}
	return (0);
}

int	unlock_if_locked(t_philo *philo, int amount)
{
	pthread_mutex_unlock(philo->fork_l);
	if (amount == TOOK_TWO)
		pthread_mutex_unlock(philo->fork_r);
	return (1);
}
