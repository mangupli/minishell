
#include "minishell.h"
#include "parseader.h"

void	set_null(t_env *envs, int i)
{
	envs[i].name = NULL;
	envs[i].content = NULL;
}

t_env	*find_pwd(t_env *envs, char *name)
{
	int i;
	int f;

	i = 0;
	f = 0;
	while (envs[i].name != NULL)
	{
		if (!ft_strcmp(envs[i].name, name))
			f = 1;
		i++;
	}
	if (!f)
		envs = add_env(envs, name, "");
	return (envs);
}

int	find_env(t_env *envs, char *name)
{
	int i;

	i = 0;
	while (envs[i].name != NULL)
	{
		if (!ft_strcmp(envs[i].name, name))
			return (1);
		i++;
	}
	return (0);
}

t_env	*add_env(t_env *envs, char *name, char *content)
{
	int i;
	int count;
	t_env *new_envs;

	i = 0;
	count = envs_count(envs);
	printf("count %d\n", count);
	new_envs = (t_env *)malloc(sizeof(t_env) * (count + 2));
	while (envs[i].name != NULL)
	{
		new_envs[i].name = envs[i].name;
		new_envs[i].content = envs[i].content;
		new_envs[i].has_equal = envs[i].has_equal;
		//free(envs[i].name);
		//free(envs[i].content);
		//free(envs[i]); TODO возможно течет, брат. ХЗ ЧТО ПРОИСХОДИТ
		i++;
	}
	//free(envs);
	new_envs[i].name = ft_strdup(name);
	new_envs[i].content = ft_strdup(content);
	new_envs[i].has_equal = 1;
	set_null(new_envs, i + 1);
	return (new_envs);
}

int envs_count(t_env *envs)
{
	int i;

	i = 0;
	while (envs[i].name != NULL)
		i++;
	return (i);
}