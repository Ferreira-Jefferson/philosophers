/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtertuli <jtertuli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 08:26:19 by jtertuli          #+#    #+#             */
/*   Updated: 2025/09/29 11:39:11 by jtertuli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char *argv[])
{
	t_common	*common;
	int			error;

	if (ft_validation(argc, argv))
	{
		printf("%sInvalid args:%s ", RED_BOLD, END_COLOR);
		printf("%snumber_of_philosophers time_to_die ", YELLOW);
		printf("time_to_eat time_to_sleep %s", END_COLOR);
		printf("%s[number_of_times_each_philosopher_must_eat]", BLUE);
		printf("%s\n", END_COLOR);
		return (0);
	}
	error = ft_init_common(argc, argv, &common);
	if (!error)
		ft_start(&common);
	ft_free_common(&common);
	return (0);
}

void ft_start(t_common **common)
{
	int			quantity;
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
	ft_create(thr_philos, philos, *common);
	ft_join(quantity, thr_philos);
	ft_destroy_mutex(*common);
	ft_to_free((void **) &philos);
	ft_to_free((void **) &thr_philos);
}

void	ft_create(pthread_t	*thr_philos, t_philo *philos, t_common *common)
{
	int	i;
	int	quantity;

	quantity = common->number_of_philosophers;
	i = 0;
	while (i < quantity)
	{
		philos[i].id_philo = i;
		philos[i].common = common;
		gettimeofday(&philos[i].last_meal, NULL);
		pthread_create(&thr_philos[i], NULL, &ft_core, &philos[i]);
		i++;
	}
}
long ft_get_time_ms(const struct timeval *time)
{
	return ((time->tv_sec * 1000) + (time->tv_usec / 1000));
}

void	*ft_core(void *args)
{
	t_philo 		*philo;
	int				id;
	int				left_fork;
	int				right_fork;
	int				number_of_times_must_eat;
	struct timeval	now;

	philo = (t_philo *) args;
	id = philo->id_philo;
	left_fork = id;
	right_fork = (id + 1) % philo->common->number_of_philosophers;
	if (left_fork > right_fork)
	{
		right_fork = left_fork ^ right_fork;
		left_fork = left_fork ^ right_fork;
		right_fork = left_fork ^ right_fork;
	}
	pthread_mutex_lock(&philo->common->shutdown_mutex);
		number_of_times_must_eat = philo->common->number_of_times_must_eat;
	pthread_mutex_unlock(&philo->common->shutdown_mutex);
	while (number_of_times_must_eat)
	{
		pthread_mutex_lock(&philo->common->shutdown_mutex);
			if (philo->common->shutdown == 1)
			{
				pthread_mutex_unlock(&philo->common->shutdown_mutex);
				break ;
			}		
		pthread_mutex_unlock(&philo->common->shutdown_mutex);
	
		gettimeofday(&now, NULL);
		pthread_mutex_lock(&philo->common->shutdown_mutex);		
			if (ft_get_time_ms(&now) > ft_get_time_ms(&philo->last_meal) + philo->common->time_to_die)
			{			
				pthread_mutex_lock(&philo->common->printf_mutex);
					printf("%ld %d is died\n", ft_get_time_ms(&now), philo->id_philo);
				pthread_mutex_unlock(&philo->common->printf_mutex);
				philo->common->shutdown = 1;
				pthread_mutex_unlock(&philo->common->shutdown_mutex);
				break ;
			}
		pthread_mutex_unlock(&philo->common->shutdown_mutex);
		
		
		pthread_mutex_lock(&philo->common->forks_mutex[left_fork]);
			gettimeofday(&now, NULL);
			pthread_mutex_lock(&philo->common->printf_mutex);
				printf("%ld %d has taken a fork\n", ft_get_time_ms(&now), philo->id_philo);
			pthread_mutex_unlock(&philo->common->printf_mutex);
		pthread_mutex_lock(&philo->common->forks_mutex[right_fork]);
			gettimeofday(&now, NULL);
			pthread_mutex_lock(&philo->common->printf_mutex);
				printf("%ld %d has taken a fork\n", ft_get_time_ms(&now), philo->id_philo);
			pthread_mutex_unlock(&philo->common->printf_mutex);
			gettimeofday(&now, NULL);
			
			pthread_mutex_lock(&philo->common->last_meal_mutex);
				philo->last_meal = now;
			pthread_mutex_unlock(&philo->common->last_meal_mutex);
			
			pthread_mutex_lock(&philo->common->printf_mutex);
				printf("%ld %d is eating\n", ft_get_time_ms(&now), philo->id_philo);
			pthread_mutex_unlock(&philo->common->printf_mutex);
			pthread_mutex_unlock(&philo->common->forks_mutex[right_fork]);
		pthread_mutex_unlock(&philo->common->forks_mutex[left_fork]);		
			usleep(philo->common->time_to_eat * 1000);
		
		gettimeofday(&now, NULL);
		pthread_mutex_lock(&philo->common->printf_mutex);
			printf("%ld %d is sleeping\n", ft_get_time_ms(&now), philo->id_philo);
		pthread_mutex_unlock(&philo->common->printf_mutex);
		usleep(philo->common->time_to_sleep * 1000);
		
		gettimeofday(&now, NULL);
		pthread_mutex_lock(&philo->common->printf_mutex);
			printf("%ld %d is thinking\n", ft_get_time_ms(&now), philo->id_philo);
		pthread_mutex_unlock(&philo->common->printf_mutex);

		if (number_of_times_must_eat > 0)
		{
			number_of_times_must_eat -= 1;
			pthread_mutex_lock(&philo->common->shutdown_mutex);
				philo->common->shutdown = 1;
			pthread_mutex_unlock(&philo->common->shutdown_mutex);
		}
	}
	return (NULL);
}
