#include "philosophers.h"


void ft_init_philos(int argc, char *argv[], t_philos **philos)
{
	int qtd_philos;

	qtd_philos = ft_atoi(argv[1]);
	*philos = (t_philos *) malloc(qtd_philos * sizeof(t_philos));
	(*philos)[0].number_of_philosophers = qtd_philos;
	while (--qtd_philos >= 0)
	{
		(*philos)[qtd_philos].id_philo = qtd_philos;
		(*philos)[qtd_philos].number_of_philosophers = (*philos)[0].number_of_philosophers;
		(*philos)[qtd_philos].time_to_die = ft_atoi(argv[2]);
		(*philos)[qtd_philos].time_to_eat = ft_atoi(argv[3]);
		(*philos)[qtd_philos].time_to_sleep = ft_atoi(argv[4]);
		if (argc == 6)
			(*philos)[qtd_philos].number_of_times_must_eat = ft_atoi(argv[5]);
	}
}

int	main(int argc, char *argv[])
{
	t_philos *philos;

	if (ft_validation(argc, argv))
	{
		printf("%sInvalid args:%s ", RED_BOLD, END_COLOR);
		printf("%snumber_of_philosophers time_to_die time_to_eat time_to_sleep %s", YELLOW, END_COLOR);
		printf("%s[number_of_times_each_philosopher_must_eat]%s\n", BLUE, END_COLOR);		
		return (0);
	}
	ft_init_philos(argc, argv, &philos);
	ft_start(&philos);
	return (0);
}

void *ft_core(void *args)
{
	t_philos *philos;

	philos = (t_philos *) args;
	pthread_mutex_t *forks;
	forks = philos->forks.vet;
	int i = 0;
	while (i < 2)
	{
		pthread_mutex_lock(&forks[philos->forks.left]);
		pthread_mutex_lock(&forks[philos->forks.right]);
				printf("timestamp_in_ms %d has taken a fork\n", philos->id_philo);
				printf("timestamp_in_ms %d is eating\n", philos->id_philo);
				usleep(philos->time_to_eat * 1000);
		pthread_mutex_unlock(&forks[philos->forks.left]);
		pthread_mutex_unlock(&forks[philos->forks.right]);
				printf("timestamp_in_ms %d is sleeping\n", philos->id_philo);
				usleep(philos->time_to_sleep * 1000);
				printf("timestamp_in_ms %d is thinking\n", philos->id_philo);
				usleep(philos->time_to_die * 1000);
		i++;
	}
	return (NULL);
}

void ft_assign_forks(t_philos **philos, pthread_mutex_t *forks)
{
	int qtd_philo;

	qtd_philo = philos[0]->number_of_philosophers;
	while (--qtd_philo >= 0)
	{
		if ((*philos)[qtd_philo].id_philo == 0)
		{
			(*philos)[qtd_philo].forks.left = (*philos)[qtd_philo].id_philo;
			(*philos)[qtd_philo].forks.right = qtd_philo - 1;
		}
		else
		{
			(*philos)[qtd_philo].forks.left = (*philos)[qtd_philo].id_philo;
			(*philos)[qtd_philo].forks.right = (*philos)[qtd_philo].id_philo - 1;
		}
		(*philos)[qtd_philo].forks.vet = forks;
	}
}

int ft_init_forks(int qtd_forks, pthread_mutex_t *forks)
{
	while (--qtd_forks >= 0)
	{
		if (pthread_mutex_init(&forks[qtd_forks], NULL) != 0)
		{
			perror("Error: pthread_mutex_init failed");
			return (1);
		}
	}
	return (0);
}

void ft_threads_join(int qtd_forks, pthread_t *philos)
{
	while (--qtd_forks >= 0)
		pthread_join(philos[qtd_forks], NULL);
}

void ft_destroy_forks(int qtd_forks, pthread_mutex_t *forks)
{
	while (--qtd_forks >= 0)
		pthread_mutex_destroy(&forks[qtd_forks]);
}

int	ft_start(t_philos **philos)
{
	int i;
	int size = (*philos)[0].number_of_philosophers;
	pthread_t		thr_philos[size];
	pthread_mutex_t	forks[size];

	ft_init_forks(size, forks);
	ft_assign_forks(philos, forks);
	i = 0;
	while (i < size)
	{
		pthread_create(&thr_philos[i], NULL, &ft_core, &(*philos)[i]);
		i++;
	}
	ft_threads_join(size, thr_philos);	
	ft_destroy_forks(size, forks);
	return (0);
}
