/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtertuli <jtertuli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 09:59:52 by jtertuli          #+#    #+#             */
/*   Updated: 2025/09/25 11:49:07 by jtertuli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

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

# define MAX  

typedef struct s_forks {
	pthread_mutex_t	*vet;
	int left;
	int right;
} t_forks;

typedef struct s_philos {
	int		number_of_philosophers;
	int		id_philo;
	int		ate;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	long	number_of_times_must_eat;
	t_forks forks;
} t_philos;

int		ft_validation(int argc, char *argv[]);
int	ft_start(t_philos **philos);
void	x(int qtd_philo, t_philos *philo_info, pthread_mutex_t *forks);

#endif