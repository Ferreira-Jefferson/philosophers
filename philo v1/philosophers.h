/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtertuli <jtertuli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 09:59:52 by jtertuli          #+#    #+#             */
/*   Updated: 2025/09/27 16:19:22 by jtertuli         ###   ########.fr       */
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

# define MAX  10

typedef struct s_forks {
	pthread_mutex_t	*vet;
	int left;
	int right;
} t_forks;

typedef struct s_philos {
	int				number_of_philosophers;
	int				id_philo;
	struct timeval	last_meal;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			number_of_times_must_eat;
	t_forks 		forks;
	pthread_mutex_t	action_mutex;
} t_philos;

int		ft_validation(int argc, char *argv[]);
void	ft_init_philos(int argc, char *argv[], t_philos **philos);
int		ft_init_forks(int qtd_forks, pthread_mutex_t *forks);
void	ft_assign_forks(t_philos **philos, pthread_mutex_t *forks);
void	ft_threads_join(int qtd_forks, pthread_t *philos);
void	ft_destroy_forks(int qtd_forks, pthread_mutex_t *forks);

int		ft_start(t_philos **philos);
void	*ft_core(void *args);
long ft_get_time_ms(const struct timeval *time);
long ft_get_diff_ms(const struct timeval *start, const struct timeval *end);

#endif