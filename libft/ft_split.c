/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtertuli <jtertuli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 09:30:12 by jtertuli          #+#    #+#             */
/*   Updated: 2025/09/04 14:09:51 by jtertuli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	free_matrix(char **matrix)
{
	char	**aux;

	aux = matrix;
	while (matrix && *aux)
	{
		free(*aux);
		aux++;
	}
	free(matrix);
}

static char	**create_matrix(char const *s, char c)
{
	int		word_count;
	char	**matrix;
	int		started;

	word_count = 0;
	started = 0;
	while (*s)
	{
		if (*s != c)
			started = 1;
		if (started && *s == c)
		{
			word_count++;
			started = 0;
		}
		s++;
	}
	word_count += started;
	matrix = (char **) ft_calloc(word_count + 1, sizeof(char *));
	if (!matrix)
		return (NULL);
	return (matrix);
}

static char	*fill_matrix(char const *s, char c)
{
	size_t	size;
	char	*aux_s;

	aux_s = (char *) s;
	size = 0;
	while (*aux_s && *aux_s != c)
	{
		size++;
		aux_s++;
	}
	return (ft_substr(s, 0, size));
}

static int	populate_matrix(char **matrix, char const *s, char c)
{
	size_t	i;

	i = 0;
	while (*s)
	{
		if (*s != c)
		{
			matrix[i] = fill_matrix(s, c);
			if (!matrix[i])
			{
				free_matrix(matrix);
				return (0);
			}
			s += ft_strlen(matrix[i]);
			i++;
		}
		else
			s++;
	}
	return (1);
}

char	**ft_split(char const *s, char c)
{
	char	**matrix;

	if (!s)
		return (NULL);
	matrix = create_matrix(s, c);
	if (!matrix)
		return (NULL);
	if (!populate_matrix(matrix, s, c))
		return (NULL);
	return (matrix);
}
