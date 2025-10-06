/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtertuli <jtertuli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 08:26:19 by jtertuli          #+#    #+#             */
/*   Updated: 2025/10/06 13:50:50 by jtertuli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

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
	common = (t_common *) malloc(sizeof(t_common));
	if (common == NULL)
		return (1);
	error = ft_init_common(argc, argv, &common);
	if (!error)
		ft_start(common);
	free(common);
	return (0);
}

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
