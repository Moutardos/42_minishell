/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dico2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcozdenm <lcozdenm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 15:10:23 by lcozdenm          #+#    #+#             */
/*   Updated: 2023/06/25 18:38:34 by lcozdenm         ###   ########.fr       */
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

void	delete_dico(t_dico *dico, char *key)
{
	t_dico	*last;

	last = NULL;
	while (dico)
	{
		if (!ft_strcmp(dico->key, key))
		{
			last->next = dico->next;
			safe_free(dico->key);
			safe_free(dico->value);
			safe_free(dico);
			return ;
		}
		last = dico;
		dico = dico->next;
	}
}
