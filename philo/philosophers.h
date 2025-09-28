/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtertuli <jtertuli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 08:29:59 by jtertuli          #+#    #+#             */
/*   Updated: 2025/09/28 08:30:56 by jtertuli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# define _DEFAULT_SOURCE
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>

# include "../libft/libft.h"

# define RED_BOLD "\033[1;31m"
# define RED "\33[31m"
# define GREEN "\33[32m"
# define YELLOW "\33[33m"
# define BLUE "\33[36m"
# define END_COLOR "\033[0m"

// struct comum
typedef struct s_common {
	int				number_of_philosophers;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			number_of_times_must_eat;
	int				shutdown;
	pthread_mutex_t	*forks_mutex;
	pthread_mutex_t	shutdown_mutex;
	pthread_mutex_t	printf_mutex;
}	t_common;

// struct individual
typedef struct s_philo {
	int				id_philo;
	struct timeval	last_meal;
	t_common		*common;
}	t_philo;

// utils
int	ft_validation(int argc, char *argv[]);

// utils init
int	ft_init_mutex(t_common **common);
int	ft_init_common(int argc, char *argv[], t_common **common);

#endif