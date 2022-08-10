/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lholdo <lholdo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 16:14:11 by lholdo            #+#    #+#             */
/*   Updated: 2022/08/10 11:14:59 by lholdo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*check_death(void *data)
{
	t_philo	*philo;
	long	time;

	philo = (t_philo *)data;
	while (42)
	{
		pthread_mutex_lock(&philo->protection);
		time = timestamp();
		if (philo->shared->dead == 1 || (philo->shared->ate_enough
				&& philo->shared->ate_enough == philo->num_philos)
			|| death_conditions(philo, time))
		{
			philo->shared->dead = 1;
			break ;
		}
		pthread_mutex_unlock(&philo->protection);
		usleep(1000);
	}
	pthread_mutex_unlock(&philo->protection);
	return (NULL);
}

int	action(t_philo *philo, int action)
{
	if (action == EATS || action == SLEEPS)
		pthread_mutex_lock(&philo->protection);
	pthread_mutex_lock(&philo->shared->write);
	if (philo->shared->dead)
		return (death_in_action(philo, action));
	if (action == EATS)
	{
		print_action(philo->number_id, EATS);
		philo->shared->t_last_meal[philo->number_id - 1] = timestamp();
		philo->actual_eats++;
	}
	else if (action == TAKES_FORK)
		print_action(philo->number_id, TAKES_FORK);
	else if (action == SLEEPS)
	{
		print_action(philo->number_id, SLEEPS);
		if (philo->actual_eats == philo->num_of_eats)
			philo->shared->ate_enough++;
	}
	else if (action == THINKS)
		print_action(philo->number_id, THINKS);
	pthread_mutex_unlock(&philo->shared->write);
	if (action == EATS || action == SLEEPS)
		pthread_mutex_unlock(&philo->protection);
	return (0);
}

int	sequence(t_philo *philo)
{
	pthread_mutex_lock(philo->fork_l);
	if (action(philo, TAKES_FORK) || philo->fork_l == philo->fork_r)
		return (unlock_if_locked(philo, TOOK_ONE));
	pthread_mutex_lock(philo->fork_r);
	if (action(philo, TAKES_FORK) || action(philo, EATS))
		return (unlock_if_locked(philo, TOOK_TWO));
	ft_usleep(philo, philo->time_to_eat);
	if (action(philo, SLEEPS))
		return (unlock_if_locked(philo, TOOK_TWO));
	pthread_mutex_unlock(philo->fork_l);
	pthread_mutex_unlock(philo->fork_r);
	ft_usleep(philo, philo->time_to_sleep);
	if (action(philo, THINKS))
		return (1);
	return (0);
}

void	*routine(void *data)
{
	t_philo	*philo;

	philo = (t_philo *) data;
	if (pthread_create(&philo->monitor, NULL, check_death, (void *)philo))
		return (NULL);
	if ((philo->number_id & 1) == 0)
	{
		if (philo->time_to_eat == 1)
			ft_usleep(philo, 1);
		else
			ft_usleep(philo, philo->time_to_eat * 0.9);
	}
	while (!philo->shared->dead)
		if (sequence(philo))
			break ;
	pthread_join(philo->monitor, NULL);
	return (NULL);
}
