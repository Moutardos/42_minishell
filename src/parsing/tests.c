#include <stdlib.h>
#include <stdio.h>

int is_sep(char c)
{
	if (c == '<' || c == '>' || c == '|' || c == '"' || c == '\'')
		return (1);
	return (0);
}

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

void	assign_cmds(char *str)
{
	int	i;
	int j;
	int k;
	char *current_cmd;
	
	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		k = 0;
		if ((!quotes(str, i) && is_sep(str[i])) || str[i + 1] == '\0')
		{
			printf("malloced: %d\n", i - j + 1);
			current_cmd = malloc(sizeof(char) * (i - j + 1));
			while (j < i)
			{
				current_cmd[k] = str[j];
				j++;
				k++;
			}
			current_cmd[k] = '\0';
			printf("last cmd : %s\n", current_cmd);
			free(current_cmd);
		}
		i++;
	}
}

int main (void) {
	assign_cmds("cat client_bonus.c | wc -l 'test |'");
}