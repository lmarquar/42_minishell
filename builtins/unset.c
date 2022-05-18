#include "builtins.h"

int exec_unset(char *unset_key, t_bin *bin)
{
	t_env_var *env;
	t_env_var *tmp;

	env = bin->env;
	tmp = env;
	if (!unset_key)
		return (0);
	while (env && ft_strncmp(env->key, unset_key, ft_strlen(env->key) + 1))
	{
		tmp = env;
		env = env->next;
	}
	if (!env)
		return (0);
	tmp->next = env->next;
	free(env->key);
	free(env->val);
	free(env);
	return (0);
}