#include "parser.h"

int	expand_wildcard_bonus(t_cmds *cmds, char *token)
{
	char	**arr;
	int		i;

	printf("before exp_wildcard\n");
	arr = replace_ast_bonus(token);
	printf("after exp_wildcard\n");
	if (!arr)
		return (1);
	if (!cmds->current_cmd->cmd)
	{
		cmds->current_cmd->cmd = arr[0];
		cmds->current_cmd->is_builtin = is_builtin(arr[0]);
	}
	i = 0;
	while (arr[i])
	{
		add_arg(&cmds->current_cmd, arr[i]);
		i++;
	}
	i = 0;
	free(arr);
	return (0);
}
