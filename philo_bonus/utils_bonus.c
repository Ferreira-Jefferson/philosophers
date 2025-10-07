#include "philosophers_bonus.h"

void	ft_generate_sem_name(const char *base, int id, char *buffer, int i, int j)
{
	char nbr[11];
	int k;

	i = 0;
	while (base[i])
	{
		buffer[i] = base[i];
		i++;
	}
	if (id == 0)
	{
		buffer[i++] = '0';
		buffer[i] = '\0';
		return ;
	}
	j = 0;
	k = id;
	while (k > 0)
	{
		nbr[j++] = (k % 10) + '0';
		k /= 10;
	}
	while (j > 0)
		buffer[i++] = nbr[--j];
	buffer[i] = '\0';
}

void	ft_print_message(t_philo *philo, char *message)
{
	long	timestamp;

	sem_wait(philo->common->sem_print);
	timestamp = ft_get_time_ms() - philo->common->start_time;
	printf("%ld %d %s\n", timestamp, philo->id_philo + 1, message);
	sem_post(philo->common->sem_print);
}

long	ft_get_time_ms(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}