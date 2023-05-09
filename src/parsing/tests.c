#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include "../../include/minishell.h"

int		quotes(char *line, int index)
{
	int	i;
	int	open;

	i = 0;
	open = 0;
	while (line[i] && i < index)
	{
		if (i > 0 && line[i - 1] == '\\')
			;
		else if (open == 0 && line[i] == '"')
			open = 1;
		else if (open == 0 && line[i] == '\'')
			open = 2;
		else if (open == 1 && line[i] == '"')
			open = 0;
		else if (open == 2 && line[i] == '\'')
			open = 0;
		i++;
	}
	return (open);
}

static int next_sep_pos(char *str, int pos)
{
	while (str[pos] != '\0')
	{
		if (!quotes(str, pos) && str[pos] == '|')
			return (pos + 1);
		pos++;
	}
	return (pos);
}

t_cmd	*new_cmd(char *builtin, char **args, char **delims\
, t_delim *delims_type)
{
	t_cmd	*cmd;

	cmd = ft_calloc(1, sizeof(t_cmd));
	if (cmd == NULL)
		return (NULL);
	cmd->next = NULL;
	cmd->av = args;
	cmd->delim_f = delims;
	cmd->delim = delims_type;
	return (cmd);
}

t_cmd	*cmd_last(t_cmd *lst)
{
	if (!lst)
		return (0);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

void	cmd_add_back(t_cmd **cmd, t_cmd *new)
{
	t_cmd	*temp;

	if (new)
	{
		if (*cmd)
		{
			temp = cmd_last(*cmd);
			temp->next = new;
		}
		else
			*cmd = new;
	}
}

/// @brief Checking builtin / redir validity 
/// @param cmd 
/// @return 
char 	*validate_builtin(char *cmd)
{
	int i;
	int j;
	char *builtin;

	j = 0;
	i = 0;
	while (cmd[j] == ' ')
		j++;
	i = j;
	while (cmd[i] != ' ')
		i++;
	if (j)
		i--;
	builtin = ft_calloc(i + 1, sizeof(char));
	//printf("alloced for builtin : %d\n", i + 1);
	if (!builtin)
		return (0);
	i = 0;
	while (cmd[j] && i < 6 && cmd[j] != ' ')
	{
		builtin[i] = cmd[j];
		j++;
		i++;
	}
	builtin[i] == '\0';
	printf("Compared builtin : %s\n", builtin);
	if (!ft_strncmp(builtin, "echo", 4) || !ft_strncmp(builtin, "cd", 2) || \
	!ft_strncmp(builtin, "pwd", 3) || !ft_strncmp(builtin, "export", 6) || \
	!ft_strncmp(builtin, "unset", 5) || !ft_strncmp(builtin, "env", 3)  || \
	!ft_strncmp(builtin, "exit", 4) ||  !ft_strncmp(builtin, ">>", 2))
		return (builtin);
	return (NULL);
}

static int is_sep(char c)
{
	if (c == '"' || c == '\'' || c == ' ')
		return (1);
	return (0);
}

static int next_arg_pos(char *str, int pos)
{
	while (str[pos] != '\0')
	{
		if (!quotes(str, pos) && is_sep(str[pos]))
			return (pos + 1);
		pos++;
	}
	return (pos);
}

/// @brief Get the builtin args, before any next redirection
/// @param cmd 
/// @return 
char **get_args(char *cmd)
{
	int i;
	int j;
	char **args;

	i = 0;
	j = 0;

	args = malloc(INT_MAX * sizeof(char *));
	if (!args)
		return (NULL);
	printf("cmd : %s\n", cmd);
	while (cmd[i] != '\0')
	{
		if (cmd[i] != ' ')
		{
			i = next_arg_pos(cmd, i);
			printf("Start, end : %d | %d\n", j, i);
			j = i;
			continue;
		}
		i++;
	}
	return (NULL);
}

t_cmd	*parse_cmd(int start, int end, char *str)
{
	int		j;
	t_cmd	*curr_cmd;
	char	*temp;
	char	**args;
	char	*builtin;

	j = 0;
	temp = malloc(end - start);
	while (start < end)
	{
		temp[j] = str[start];
		start++;
		j++;
	}
	temp[j] = '\0';
	if ((builtin = validate_builtin(temp)) == NULL)
	{
		printf("Invalid builtin provided\n");
		return (NULL);
	}
	printf("Valid builtin \n");
	args = get_args(temp);
	return (new_cmd(temp, args, NULL, NULL));
}

//TODO :clear complete list
void *clear_cmd(t_cmd	*cmd)
{
	return (NULL);
}

//schedule : recup premier cmd, envoie i -> next_sep pos a parse cmd 
// qui verifie la validite du built in / construction de l'argument
t_cmd	*assign_cmds(char *str)
{
	int		i;
	int		next_delim;
	t_cmd	*curr_cmd;
	t_cmd	*new_cmd;
	
	i = 0;
	curr_cmd = NULL;
	while (str[i] != '\0')
	{
		next_delim = next_sep_pos(str, i);
		new_cmd = parse_cmd(i, next_delim, str);
		if (!new_cmd)
			return (clear_cmd(curr_cmd));
		cmd_add_back(&curr_cmd, new_cmd);
		i = next_delim;
	}
	while (curr_cmd != NULL)
	{
		printf("cmd builtin : %s\n", curr_cmd->av[0]);
		curr_cmd = curr_cmd->next;
	}
}


int main (void) {

	char test1[] = "cat client_bonus.c | wc -l 'test |'";
	char test2[] = "echo \"salut toi |\" > test.txt";
	char test3[] = "cd test.txt";
	char test4[] = "echo \"salut toi | \"";
	char test5[] = "echo \"bonjour\" | >> a";
	char test6[] = "echo \"bonjour\" | echo rewrwerwe | echo rewrwerew \" | \" ";
	char test7[] = "echo \"bonjour\" | echot rewrwerwe | echo rewrwerew \" | \" ";

	assign_cmds(test1);
	printf("/////////////////\n");
	assign_cmds(test2);
	printf("/////////////////\n");
	assign_cmds(test3);
	printf("/////////////////\n");
	assign_cmds(test4);
	printf("/////////////////\n");
	assign_cmds(test5);
	printf("/////////////////\n");
	assign_cmds(test6);
	printf("/////////////////\n");
	assign_cmds(test7);
	printf("/////////////////\n");
}