/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtertuli <jtertuli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 08:21:34 by jtertuli          #+#    #+#             */
/*   Updated: 2025/09/28 08:52:20 by jtertuli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_validation(int argc, char *argv[])
{
	int	i;

	if (argc == 1 || (argc < 5 || argc > 6))
		return (1);
	i = 1;
	while (i < argc)
	{
		if (!ft_is_only_number(argv[i]))
			return (1);
		i++;
	}
	return (0);
}

void	ft_threads_join(int quantity, pthread_t *thr_philos)
{
	int	i;

	i = 0;
	while (i < quantity)
	{
		pthread_join(thr_philos[i], NULL);
		i++;
	}
}

void	ft_destroy_mutex(t_common *common)
{
	int	i;

	i = 0;
	while (i < common->number_of_philosophers)
	{
		pthread_mutex_destroy(&common->forks_mutex[i]);
		i++;
	}
	pthread_mutex_destroy(&common->printf_mutex);
	pthread_mutex_destroy(&common->shutdown_mutex);
}

void	ft_free_common(t_common **common)
{
	ft_to_free((void **) &(*common)->forks_mutex);
	ft_to_free((void **) common);
}
