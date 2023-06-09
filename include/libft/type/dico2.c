/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dico2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcozdenm <lcozdenm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 15:10:23 by lcozdenm          #+#    #+#             */
/*   Updated: 2023/06/28 15:50:40 by lcozdenm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

t_dico	*array_dico(char **array)
{
	unsigned int	i;
	t_dico			*dico;
	char			*key;
	char			*value;
	int				len;

	dico = NULL;
	i = -1;
	while (array && array[++i] != NULL)
	{
		len = ft_strchr(array[i], '=') - array[i];
		key = ft_substr(array[i], 0, len);
		value = ft_strdup(array[i] + len + 1);
		if (!key || !value)
			return (safe_free(key), safe_free(value), free_dico(&dico), NULL);
		if (!dico)
			dico = init_dico(key, value);
		if (!dico || !add_dico(dico, key, value))
			return (safe_free(key), safe_free(value), free_dico(&dico), NULL);
		safe_free(key);
		safe_free(value);
	}
	return (dico);
}

void	display_dico(t_dico *dico)
{	
	while (dico)
	{
		if (dico->key[0] != '\0')
			ft_printf("%s=%s\n", dico->key, dico->value);
		dico = dico->next;
	}
}

int	size_dico(t_dico *dico)
{
	int	size;

	size = 0;
	while (dico)
	{
		size++;
		dico = dico->next;
	}
	return (size);
}

void	delete_dico(t_dico **dico, char *key)
{
	t_dico	*last;
	t_dico	*current;

	last = NULL;
	current = *dico;
	while (current)
	{
		if (!ft_strcmp(current->key, key))
		{
			if (last == NULL)
				*dico = current->next;
			else
				last->next = current->next;
			safe_free(current->key);
			safe_free(current->value);
			safe_free(current);
			return ;
		}
		last = current;
		current = current->next;
	}
}
