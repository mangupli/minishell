#include "minishell.h"
#include "parseader.h"

char *get_env_key(char *key_begin)
{
	int i;
	char *key;

	i = 0;
	while (ft_strrchr(ascii, key_begin[i])  && key_begin[i] != '\0')
		i++;
	if (!i)
		return (NULL);
	key = (char *)malloc(i + 1); // TODO маллоки
	i = 0;
	while (ft_strrchr(ascii, key_begin[i])  && key_begin[i] != '\0')
	{
		key[i] = key_begin[i];
		i++;
	}
	key[i] = '\0';
	return (key);
}

char *env_worker(char *string, int i, t_list_env *envs)
{
	char *value;
	char *key;
	int len;
	char *new_string;

	key = get_env_key(&string[i + 1]);
	if (key == NULL)
		return (ft_strdup(string));
	value = find_env_content(envs, key);
	if (!value)
		len = ft_strlen(string) + 1;
	else
		len = ft_strlen(string) + ft_strlen(value) + 1;
	new_string = (char *)malloc(len); // TODO маллоки
	env_replacer(string, value, new_string, ft_strlen(key));
	//free(value); // TODO WHY MALLOC BUGS???
	free(key);
	return (new_string);
}

void env_replacer(char *string, char *value, char *new_string, int key_len)
{
	int i;
	int j;
	int x;

	i = 0;
	j = 0;
	x = 0;
	while (string[i] != '\0')
	{
		if (string[i] == '$' && !j)
		{
			while (value != NULL && value[j] != '\0')
			{
				new_string[x] = value[j];
				j++;
				x++;
			}
			i += key_len + 1;
		}
		new_string[x] = string[i];
		i++;
		x++;
	}
	new_string[x] = '\0';
}

char	*find_env_content(t_list_env *envs, char *name) // TODO DELETE THIS FUNC
{
	t_list_env *tmp;

	tmp = envs;
	while (tmp)
	{
		if (!ft_strcmp(tmp->name, name))
			return (tmp->content);
		tmp = tmp->next;
	}
	return (NULL);
}

char *trash_replacer(char *string)
{
	int sq;
	int dq;
	int i;
	char *tmp;

	sq = 0;
	dq = 0;
	i = 0;
	while (string[i] != '\0')
	{
		if (type_quotes(string, i) == '\'')
			sq++;
		if (type_quotes(string, i) == '"')
			dq++;
		if (string[i] == '\\' && !(sq % 2))
		{
			tmp = string;
			string = slash_replacer(string);
			free(tmp);
		}
		i++;
	}
	return (string);
}