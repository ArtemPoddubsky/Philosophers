/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lholdo <lholdo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 14:25:39 by lholdo            #+#    #+#             */
/*   Updated: 2021/12/08 18:51:38 by lholdo           ###   ########.fr       */
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
