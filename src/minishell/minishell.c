/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coltcivers <coltcivers@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 19:37:11 by coltcivers        #+#    #+#             */
/*   Updated: 2023/06/13 21:29:25 by coltcivers       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"
#include "exec.h"

/// @brief Minishell struct and fields init
/// @return Newly allocated shell entity
t_minishell *init_minishell(char **envp)
{
	t_minishell *mini;
	char		*path;
	
	path = getenv("PATH");
	if (!path)
		return (NULL);
	mini = ft_calloc(1, sizeof(t_minishell));
	if (!mini)
		return (NULL);
	if (!envp)
		mini->env = NULL;
	else
		mini->env = array_dico(envp);
	//display_dico(mini->env);
	//mini->dico = init_dico("TEST", "salut");
	//add_dico(mini->dico, "TEST2", "au revoir");
	if (getcwd(mini->pwd, BUFFER_SIZE) == NULL)
		return (perror("minishell:"), free_dico(&mini->env), safe_free(mini), NULL);
	//paths par defaut 
	mini->paths = ft_split(path, ':');
	mini->exit = -1;
	//Ajouter ici par la suite les fieds a allouer / initialiser
	return (mini);
}

void	free_cmds(t_cmd *cmds)
{
	t_cmd	*curr;
	t_cmd	*prev;

	curr = cmds;
	while (curr != NULL)
	{
		//printf("freeing cmd : %s\n", curr->av[0]);
		ft_free_split(curr->av);
		safe_free(curr->path);
		ft_free_split(curr->delim_f);
		safe_free(curr->delim);
		if (curr->next == NULL)
		{
			safe_free(curr);
			curr = NULL;
		}
		else
		{
			prev = curr;
			curr = curr->next;
			//safe_free(curr->prev);
			safe_free(prev);
		}
	}
}

void	free_dico2(t_dico *dicos)
{
	t_dico	*curr;

	curr = dicos;
	while (curr != NULL)
	{
		safe_free(curr->key);
		safe_free(curr->value);
		if (curr->next == NULL)
		{
			safe_free(curr);
			curr = NULL;
		}
		else
		{
			curr = curr->next;
			//safe_free(curr->prev);
		}
	}
}

static void	free_mini(t_minishell *mini)
{
	//free_cmds(mini->cmds);
	ft_free_split(mini->paths);
	//if (mini->env != NULL)
		//ft_lstclear( (void *) (mini->env), free);
	free(mini);
}

//echo salut"toi"$TEST'$TEST' << test.txt append > test2.txt | echo salut > redir.png | > "to"
int main(int ac, char **av, char **envp)
{
	t_minishell	*mini;

	(void)ac;
	(void)av;
	mini = init_minishell(envp);
	if (!mini)
		return (-1);
	while (mini->exit == -1)
	{
	parse_current_cmd(mini);
	if (mini->cmds)
		execute(mini);
	free_cmds(mini->cmds);
	}
	free_dico(&mini->env);
	free(mini->env);
	free_mini(mini);
	return (0);
}