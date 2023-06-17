/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_str.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcozdenm <lcozdenm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 12:23:15 by lcozdenm          #+#    #+#             */
/*   Updated: 2023/06/17 16:03:21 by lcozdenm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// static unsigned int		get_new_size(t_dico *dico, char *str);
// static void				skip_word(char **p_s);
// static char				*ft_ext_word(char const *p_s);
// static unsigned int		len_between_words(char *str);

// char	*replace_str(t_dico *dico, char *str)
// {
// 	unsigned int	size;
// 	unsigned int	len;
// 	char			*new;
// 	char			*word;
// 	char			*newword;

// 	new = malloc(sizeof(char) * (get_new_size(dico, str) + 1));
// 	if (!new)
// 		return (NULL);
// 	len = 0;
// 	while (*str)
// 	{
// 		word = ft_ext_word(str);
// 		if (!word)
// 			return (NULL);
// 		newword = get_dico(dico, word);
// 		if (!newword)
// 			return (safe_free(word), NULL);
// 		if (newword[0] == 0)
// 		{
// 			safe_free(newword);
// 			newword = word;
// 		}
// 		size = len_between_words(str);
// 		ft_strlcpy(new + len, str, size + 1);
// 		len += size;
// 		ft_strlcpy(new + len, newword, ft_strlen(newword) + 1);
// 		len += ft_strlen(newword);
// 		skip_word(&str);
// 		safe_free(newword);
// 	}
// 	return (new);
// }

// static unsigned int	get_new_size(t_dico *dico, char *str)
// {
// 	char			*part;
// 	unsigned int	size;

// 	size = strlen(str);
// 	while (dico)
// 	{
// 		part = ft_strnstr(str, dico->key, ft_strlen(str));
// 		while (part)
// 		{
// 			size += ft_strlen(dico->value) - ft_strlen(dico->key);
// 			part += ft_strlen(dico->key);
// 			part = ft_strnstr(part , dico->key, ft_strlen(part));
// 		}
// 		dico = dico->next;
// 	}
// 	return (size);
// }

// static void	skip_word(char **p_s)
// {
// 	while (**p_s && ft_isspace(**p_s))
// 		(*p_s)++;
// 	while (**p_s && !ft_isspace(**p_s))
// 		(*p_s)++;
// }

// static char	*ft_ext_word(char const *str)
// {
// 	size_t	len;
// 	char	*word;

// 	len = 0;
// 	while (*str && ft_isspace(*str))
// 		str++;
// 	while (str[len] && !ft_isspace(str[len]))
// 		len++;
// 	if (len == SIZE_MAX)
// 		return (NULL);
// 	word = malloc(len + 1);
// 	if (word == NULL)
// 		return (NULL);
// 	ft_strlcpy(word, str, len + 1);
// 	return (word);
// }

// static	unsigned int	len_between_words(char *str)
// {
// 	unsigned int	size;

// 	size = 0;
// 	while (*str && ft_isspace(*str))
// 	{
// 		str++;
// 		size++;
// 	}
// 	return (size);
// }
