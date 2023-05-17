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
	while (line[i] && i <= index)
	{
		//printf("line[i] : %c\n", line[i]);
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

t_cmd	*new_cmd()
{
	t_cmd	*cmd;

	cmd = ft_calloc(1, sizeof(t_cmd));
	if (cmd == NULL)
		return (NULL);
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
	int hold;

	j = 0;
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
	//printf("Compared builtin : %s\n", builtin);
	if (!ft_strncmp(builtin, "echo", 4) || !ft_strncmp(builtin, "cd", 2) || \
	!ft_strncmp(builtin, "pwd", 3) || !ft_strncmp(builtin, "export", 6) || \
	!ft_strncmp(builtin, "unset", 5) || !ft_strncmp(builtin, "env", 3)  || \
	!ft_strncmp(builtin, "exit", 4) ||  !ft_strncmp(builtin, ">>", 2))
		return (builtin);
	return (NULL);
}

static int is_sep(char c)
{
	if (c == '"' || c == '\'' || c == ' ' || c == '|' || c == '\0')
		return (1);
	return (0);
}


static int is_delim(char *cmd, int i)
{
	if (!quotes(cmd, i) && (cmd[i] == '>' || cmd[i] == '<' || cmd[i] == '|'))
		return (1);
	return (0);
}

static char *str_truncate(char *str, int start)
{
	char *new;
	int i;

	i = 0;
	new = malloc(ft_strlen(str) - start + 1);
	if (!new)
		return (NULL);
	while (str[start] != '\0')
	{
		new[i] = str[start];
		i++;
		start++;
	}
	new[i] = '\0';
	free(str);
	return (new);
}


static char *str_truncate_delim(char *str, int start)
{
	char *new;
	int i;

	i = 0;
	new = malloc(ft_strlen(str) - start + 1);
	//printf("str_truncate_delim alloc : %ld\n", ft_strlen(str) - start + 1);
	//printf("str_truncate_delim start : %d\n", start);
	//printf("str_truncate_delim str[start] : %c\n", str[start]);
	if (!new)
		return (NULL);
	while (str[start] == ' ')
		start++;
	while (str[start] != '\0')
	{
		new[i] = str[start];
		i++;
		start++;
	}
	new[i] = '\0';
	//printf("str_truncate_delim new : %s\n", new);
	free(str);
	return (new);
}

static int get_post_bltn(char *str)
{
	int i;

	i = 0;
	while (str[i] == ' ')
		i++;
	while (str[i] != ' ')
		i++;
	while (str[i] == ' ')
		i++;
	return (i);
}

/*

	//printf("str[pos] %c\n", str[pos]);
		//printf("str[pos + 1] %c\n", str[pos + 1]);
		//printf("str[pos + 2] %c\n", str[pos + 2]);
		//printf("quotes(str, pos) : %d\n", quotes(str, pos));
		if (str[pos] == '"' || str[pos] == '\'')
			pos++;
		if ((!quotes(str, pos) && is_sep(str[pos])))
			return (pos);
		pos++;
		
*/

//version qui marche mais decalage d'un
/*

	while (str[pos] != '\0')
	{
		if ((str[pos] == '"' || str[pos] == '\'' ) && !quotes(str, pos + 1))
			pos++;
		if ((!quotes(str, pos) && is_sep(str[pos])))
			return (pos + 1);
		pos++;	
	}
	
	
	*/

static int next_arg_pos(char *str, int pos)
{
	while (str[pos] != '\0')
	{
		if (!quotes(str, pos))
		{
			while (!quotes(str, pos) && str[pos] != ' ' && str[pos] != '\0')
				pos++;
			return (pos);
		}
		if (quotes(str, pos))
		{
			while (quotes(str, pos))
				pos++;
			return (pos + 1);
		}
		pos++;
	}
	return (pos);
}

/// @brief Get the builtin args, before any next redirection
/// @param curr_cmd 
/// @param cmd 
/// @return 
int get_args(t_cmd *curr_cmd, char *cmd)
{
	int i;
	int j;
	int l;
	int	count;

	i = 0;
	j = 0;
	count = 0;
	//MODIF ARG AMOUNT PAR LA SUITE
	curr_cmd->av= malloc(1000 * sizeof(char *));
	if (!curr_cmd->av)
		return (1);
	cmd = str_truncate(cmd, get_post_bltn(cmd));
	while (cmd[i] != '\0' && !is_delim(cmd, i))
	{
		if (cmd[i] != ' ')
		{
			l = 0;
			i = next_arg_pos(cmd, i);
			curr_cmd->av[count] = malloc(i - j + 1);
			if (!curr_cmd->av[count])
				return (1);
			while (j < i)
			{
				curr_cmd->av[count][l] = cmd[j];
				j++;
				l++;
			}
			curr_cmd->av[count][l] = '\0';
			count++;
			continue;
		}
		i++;
		j++;
	}
	curr_cmd->av[count] = NULL;
	return (1);
}

int get_next_delim(char *str, int start)
{
	int i;

	i = start;
	while (str[i] != '\0' && str[i] != '>' && str[i] != '<')
		i++;
	return (i);
}

int get_delims_amount(char *str)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (str[i] != '\0')
	{
		if  (str[i] == '>' || str[i] == '<')
		{
			if  ((str[i] == '>' && str[i + 1] == '>') \
			|| (str[i] == '<' && str[i + 1] == '<'))
				i++;
			count++;
		}
		i++;
	}
	return (count);
}

t_delim get_curr_delim(char *str, int pos)
{
	if (str[pos] == '>')
	{
		if (str[pos + 1] == '>')
			return (OUT_APPEND);
		return (OUT);
	}
	else if (str[pos] == '<')
	{
		if (str[pos + 1] == '<')
			return (IN_NL);
		return (IN);
	}
	return (NONE);
}

/// @brief Get the cmd delims redirection, and associated files
/// @param cmd 
/// @return 
int get_delims(t_cmd *curr_cmd, char *cmd)
{
	int i;
	int j;
	int count;
	int delims;
	int l;
	int m;
	char **delims_f;

	count = 0;
	m = 0;
	if ((delims = get_delims_amount(cmd)) == 0)
		return (-1);
	curr_cmd->delim = malloc(sizeof(t_delim) * (delims + 1));
	if (!curr_cmd->delim)
		return (1);
	delims_f = malloc(1000 * sizeof(char *));
	while (count < delims)
	{
		i = 0;
		i = get_next_delim(cmd, i);
		if ((curr_cmd->delim[count] = get_curr_delim(cmd, i)) == IN_NL \
		|| (curr_cmd->delim[count] = get_curr_delim(cmd, i)) == OUT_APPEND)
			i ++;
		cmd = str_truncate_delim(cmd, i + 1);
		i = 0;
		j = 0;
		//printf("cmd[i] : %c\n", cmd[i]);
		//printf("cmd : %s\n", cmd);
		while (cmd[i] != '\0' && cmd[i] != '>' && cmd[i] != '<')
		{
			//printf("cmd[i] : %c\n", cmd[i]);
			if (cmd[i] != ' ')
			{
				l = 0;
				i = next_arg_pos(cmd, i);
				//printf("next_arg_pos : %d\n", i);
				delims_f[m] = malloc(i - j + 1);
				//printf("malloced : %d\n", i - j + 1);
				//printf("m : %d\n", m);
				if (!delims_f[m])
					return (1);
				while (j < i)
				{
					delims_f[m][l] = cmd[j];
					//printf("cmd[j]: %c\n", cmd[j]);
					j++;
					l++;
				}
				delims_f[m][l] = '\0';
				printf("delims_f : %s\n", delims_f[m]);
				m++;
				continue;
			}
			i++;
			j++;
		}
		count++;
	}
	return (0);
}

///////// REFAIRE UNE FONCTIOON TRUNCATE

t_cmd	*parse_cmd(int start, int end, char *str)
{
	int		j;
	char	*temp;
	char	**args;
	char	*builtin;
	t_cmd   *cmd;

	j = 0;
	temp = malloc(end - start + 1);
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
	//printf("Valid builtin \n");
	cmd = new_cmd();
	get_args(cmd, str_fullcpy(temp));
	get_delims(cmd,  str_fullcpy(temp));
	/*
	while (*args != NULL)
	{
		printf("arg : %s\n", *args);
		args++;
	}
	*/
	return (cmd);
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
	printf("full cmd : %s\n", str);
	while (str[i] != '\0')
	{
		next_delim = next_sep_pos(str, i);
		new_cmd = parse_cmd(i, next_delim, str);
		if (!new_cmd)
			return (clear_cmd(curr_cmd));
		cmd_add_back(&curr_cmd, new_cmd);
		i = next_delim;

	}
	//while (curr_cmd != NULL)
	//{
	//	printf("cmd builtin : %s\n", curr_cmd->av[0]);
	//	curr_cmd = curr_cmd->next;
	//}
}


int main (void) {

	char test1[] = "cat client_bonus.c | wc -l 'test |'";
	char test2[] = "echo \"salut toi |\" > test.txt append > \"test2.txt\"append << test3.txt";
	char test3[] = "cd test.txt";
	char test4[] = "echo \"salut toi | \"";
	char test5[] = "echo \"bonjour\" | >> a";
	char test6[] = "echo \"bonjour\" | cd rewrwerwe | echo rewrwerew \" | \" ";
	char test7[] = "echo \"bonjour\" | echot rewrwerwe | echo rewrwerew \" | \" ";
	char test8[] = "echo    \"bonjour\"'fdsfrtryt' rewrwerew \" | \" > test.txt << test2.txt";
	char test9[] = "echo  ee\"   bonjour test\"ee'tete'rewrwqe \"|\"    fdsfrtryt rewrwerew \" | \" ";

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
	assign_cmds(test8);
	printf("/////////////////\n");
	assign_cmds(test9);
	printf("/////////////////\n");
}