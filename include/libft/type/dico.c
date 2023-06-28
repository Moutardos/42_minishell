/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dico.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcozdenm <lcozdenm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 01:32:59 by lcozdenm          #+#    #+#             */
/*   Updated: 2023/06/28 15:09:24 by lcozdenm         ###   ########.fr       */
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
	if (key == NULL || value == NULL)
	{
		dico->key = ft_strdup("");
		dico->value = ft_strdup("");
	}
	else
	{
		dico->key = ft_strdup(key);
		dico->value = ft_strdup(value);
	}
	if (!dico->key || !dico->value)
		return (safe_free(&dico), NULL);
	return (dico);
}

void	free_dico(t_dico **dico)
{
	t_dico	*last;

	if (!dico)
		return ;
	while (*dico)
	{
		safe_free((*dico)->value);
		safe_free((*dico)->key);
		last = *dico;
		(*dico) = (*dico)->next;
		safe_free(last);
	}
	*dico = NULL;
}

t_dico	*add_dico(t_dico *dico, char *key, char *value)
{
	t_dico	*last;
	char	*new_value;

	last = dico;
	while (dico)
	{
		if (!ft_strcmp(key, dico->key))
		{
			safe_free(dico->value);
			new_value = ft_strdup(value);
			if (!new_value)
				return (NULL);
			dico->value = new_value;
			return (dico);
		}
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
		if (ft_strcmp(key, dico->key) == 0)
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
	dico_char = ft_calloc(size + 1, sizeof(char *));
	if (!dico_char)
		return (NULL);
	i = 0;
	current = dico;
	while (current)
	{
		temp = ft_strjoin(current->key, "=");
		if (!temp)
			return (ft_free_split(dico_char), NULL);
		dico_char[i] = ft_strjoin(temp, current->value);
		if (!dico_char[i])
			return (ft_free_split(dico_char), safe_free(temp), NULL);
		safe_free(temp);
		current = current->next;
		i++;
	}
	return (dico_char);
}
