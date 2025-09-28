/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtertuli <jtertuli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 08:26:19 by jtertuli          #+#    #+#             */
/*   Updated: 2025/09/28 09:17:18 by jtertuli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char *argv[])
{
	t_common	*common;

	if (ft_validation(argc, argv))
	{
		printf("%sInvalid args:%s ", RED_BOLD, END_COLOR);
		printf("%snumber_of_philosophers time_to_die ", YELLOW);
		printf("time_to_eat time_to_sleep %s", END_COLOR);
		printf("%s[number_of_times_each_philosopher_must_eat]", BLUE);
		printf("%s\n", END_COLOR);
		return (0);
	}
	ft_init_common(argc, argv, &common);
	ft_start(&common);
	ft_free_common(&common);
	return (0);
}

void ft_start(t_common **common)
{
	int i;
	int quantity;
	pthread_t	*thr_philos;
	t_philo		*philos;	

	quantity = (*common)->number_of_philosophers;
	philos = (t_philo *) malloc(quantity * sizeof(t_philo));
	if (!philos)
		return ;
	thr_philos = (pthread_t *) malloc(quantity * sizeof(pthread_t));
	if (!thr_philos)
	{
		ft_to_free((void **) &philos);
		return ;
	}
	i = 0;
	while (i < quantity)
	{
		philos[i].id_philo = i;
		gettimeofday(&philos[i].last_meal, NULL);
		philos[i].common = common;
		pthread_create(&thr_philos[i], NULL, ft_core, &philos[i]);
		i++;
	}
	ft_join(quantity, thr_philos);
	ft_destroy_mutex(common);
}

void	*ft_core(void *args)
{
	return (NULL);
}
