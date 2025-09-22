#ifndef PHILOSOFERS
# define PHILOSOFERS

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include "../libft/libft.h"

typedef struct s_rules {
	int number_of_philosophers;
	long time_to_die;
	long time_to_eat;
	long time_to_sleep;
	long number_of_times_each_philosopher_must_eat;
} t_rules;

int ft_validation(int argc, char *argv[]);
void ft_init_rules(int argc, char *argv[], t_rules *rules);

#endif