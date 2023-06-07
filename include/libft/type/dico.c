/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dico.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcozdenm <lcozdenm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 01:32:59 by lcozdenm          #+#    #+#             */
/*   Updated: 2023/06/07 17:09:43 by lcozdenm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

t_dico	*init_dico(char *key, char *value)
{
	t_dico	*dico;

	dico = malloc(sizeof(t_dico));
	if (!dico)
		return (NULL);
	dico->next = NULL;
	dico->key = ft_strdup(key);
	dico->value = ft_strdup(value);
	if (!dico->key || !dico->value)
		return (safe_free(&dico), NULL);
	return (dico);
}

void	free_dico(t_dico **dico)
{
	t_dico	**last;

	last = dico;
	while (*dico)
	{
		safe_free((*dico)->value);
		safe_free((*dico)->key);
		last = dico;
		(*dico) = (*dico)->next;
		safe_free(*last);
	}
}

t_dico	*add_dico(t_dico *dico, char *key, char *value)
{
	t_dico	*last;

	last = dico;
	while (dico)
	{
		if (!ft_strncmp(key, dico->key, ft_strlen(key)))
			return (free(dico->value), dico->value = ft_strdup(value), dico);
		last = dico;
		dico = dico->next;
	}
	last->next = init_dico(key, value);
	return (last->next);
}

char	*get_dico(t_dico *dico, char *key)
{
	while (dico)
	{
		if (!ft_strncmp(key, dico->key, ft_strlen(key)))
			return (ft_strdup(dico->value));
		dico = dico->next;
	}
	return (ft_strdup(""));
}

char	**dico_array(t_dico *dico)
{
	unsigned int	size;
	t_dico			*current;
	char			**dico_char;
	unsigned int	i;
	char			*temp;

	size = size_dico(dico);
	dico_char = ft_calloc(sizeof(char *), size + 1);
	i = 0;
	current = dico;
	while (current)
	{
		temp = ft_strjoin(dico->key, "=");
		if (!temp)
			return (ft_free_split(dico_char), NULL);
		dico_char[i] = ft_strjoin(temp, dico->value);
		if (!dico_char[i])
			return (free(dico_char), free(temp), NULL);
		free(temp);
		current = current->next;
		i++;
	}
	return (dico_char);
}
