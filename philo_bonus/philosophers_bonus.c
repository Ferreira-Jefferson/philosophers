/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtertuli <jtertuli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 15:27:09 by jtertuli          #+#    #+#             */
/*   Updated: 2025/10/09 14:16:18 by jtertuli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

static int	ft_error_message(int argc, char *argv[])
{
	if (ft_atoi(argv[1]) < 0 || ft_atoi(argv[2]) < 0 || ft_atoi(argv[3]) < 0 \
		|| ft_atoi(argv[4]) < 0 || (argc == 6 && ft_atoi(argv[5]) < 0))
	{
		printf("%sInvalid args: %s%sthe values should be positive %s", \
			RED_BOLD, END_COLOR, YELLOW, END_COLOR);
		printf("%s\">= 0\"%s\n", RED_BOLD, END_COLOR);
		return (1);
	}
	if (ft_is_only_number(argv[1]) && ft_atoi(argv[1]) == 0)
	{
		printf("%sInvalid args: %s%snumber_of_philosophers should be %s", \
			RED_BOLD, END_COLOR, YELLOW, END_COLOR);
		printf("%s\"> 0\"%s\n", RED_BOLD, END_COLOR);
		return (1);
	}
	printf("%sInvalid args:%s ", RED_BOLD, END_COLOR);
	printf("%snumber_of_philosophers time_to_die ", YELLOW);
	printf("time_to_eat time_to_sleep %s", END_COLOR);
	printf("%s[number_of_times_each_philosopher_must_eat]", BLUE);
	printf("%s\n", END_COLOR);
	return (1);
}

static int	ft_validation(int argc, char *argv[])
{
	int	i;

	if (argc == 1)
		return (1);
	if (argc < 5 || argc > 6)
		return (ft_error_message(argc, argv));
	if (ft_atoi(argv[1]) == 0)
		return (ft_error_message(argc, argv));
	i = 1;
	while (i < argc)
	{
		if (!ft_is_only_number(argv[i]))
			return (ft_error_message(argc, argv));
		if (ft_atoi(argv[i]) < 0)
			return (ft_error_message(argc, argv));
		i++;
	}
	return (0);
}

int	main(int argc, char *argv[])
{
	t_common	*common;

	if (ft_validation(argc, argv))
		return (0);
	if (ft_atoi(argv[1]) == 1)
	{
		printf("%d %d %s\n", 0, 1, "has taken a fork");
		printf("%s %d %s\n", argv[2], 1, "died");
		return (0);
	}
	common = (t_common *)malloc(sizeof(t_common));
	if (common == NULL)
		return (1);
	if (ft_init_common(argc, argv, &common))
	{
		free(common);
		return (1);
	}
	ft_start(common);
	free(common);
	return (0);
}
