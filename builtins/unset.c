#include "builtins.h"

int	exec_unset(char *unset_key, t_bin *bin)
{
	t_env_var	*env;

	env = bin->env;
	if (!env || !unset_key)
		return (0);
	bin->env = remove_env_var(env, unset_key);
	return (0);
}
