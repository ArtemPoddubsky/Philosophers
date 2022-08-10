/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lholdo <lholdo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 14:25:39 by lholdo            #+#    #+#             */
/*   Updated: 2022/07/01 16:09:08 by lholdo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_overflow(const char *str, int *nb)
{
	int	pn;

	*nb = 0;
	pn = 1;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			pn = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		*nb = *nb * 10 + (*str - 48) * pn;
		if ((pn == -1 && *nb > 0) || (pn == 1 && *nb < 0))
			return (ERROR);
		str++;
	}
	return (0);
}

int	check_args(int argc, char **argv)
{
	int	i;
	int	tmp;

	if (argc != 5 && argc != 6)
	{
		ft_putstr_fd("Invalid arguments\n", 2);
		return (ERROR);
	}
	i = 1;
	while (argv[i])
	{
		if (ft_isdigit(argv[i]) || check_overflow(argv[i], &tmp) || tmp == 0)
		{
			ft_putstr_fd("Invalid arguments\n", 2);
			return (ERROR);
		}
		i++;
	}
	return (0);
}

int	get_index(int tmp, int index)
{
	while (tmp > 9)
	{
		tmp /= 10;
		index++;
	}
	return (index);
}

int	init_protect_sem(t_philo *philo, char *name)
{
	sem_unlink(name);
	philo->protect = sem_open(name, O_CREAT | O_EXCL, 0644, 1);
	if (philo->protect == SEM_FAILED)
	{
		free(name);
		return (ERROR);
	}
	return (0);
}

int	get_protect(t_philo *philo)
{
	int		index;
	int		tmp;
	char	*name;

	index = 2;
	tmp = philo->number;
	index = get_index(tmp, index);
	name = (char *)malloc(sizeof(char) * index);
	if (!name)
		return (ERROR);
	name[0] = 'p';
	name[index--] = '\0';
	tmp = philo->number;
	while (tmp > 9)
	{
		name[index] = tmp % 10 + '0';
		tmp /= 10;
		index--;
	}
	name[index] = tmp % 10 + '0';
	if (init_protect_sem(philo, name))
		return (ERROR);
	free(name);
	return (0);
}
