/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstoneho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/21 19:21:28 by mstoneho          #+#    #+#             */
/*   Updated: 2021/03/21 19:21:30 by mstoneho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parseader.h"

t_env	*env_parser(char *env[])
{
	t_env	*envs;
	int		i;
	int		len;

	i = 0;
	envs = (t_env *)malloc(sizeof(t_env) * (env_count(env) + 1));
	while (env[i] != NULL)
	{
		len = env_len(env[i], 0) + 1;
		envs[i].name = (char *)malloc(len);
		env_filler(env[i], envs[i].name, 0);
		if (env_is_empty(env[i], envs[i]))
		{
			envs[i].content = (char *)malloc(1);
			envs[i].content[0] = '\0';
		}
		else
		{
			envs[i].content = (char *)malloc(env_len(env[i], len) + 1);
			env_filler(env[i], envs[i].content, len);
		}
		i++;
	}
	set_null(envs, i);
	return (find_env(envs, "OLDPWD"));
}

int	env_count(char *env[])
{
	int		i;

	i = 0;
	while (env[i] != NULL)
		i++;
	return (i);
}

int	env_len(char *env, int offset)
{
	int		i;

	i = 0;
	while (env[offset] != '\0' && env[offset] != '=')
	{
		offset++;
		i++;
	}
	return (i);
}

void	env_filler(char *env, char *dest_env, int offset)
{
	int		i;

	i = 0;
	while (env[offset] != '\0' && env[offset] != '=')
	{
		dest_env[i] = env[offset];
		offset++;
		i++;
	}
	dest_env[i] = '\0';
}

int	env_is_empty(char *env, t_env envs)
{
	int		i;

	i = 0;
	envs.has_equal = 0;
	while (env[i] != '\0')
	{
		if (env[i] == '=')
			envs.has_equal = 1;
		i++;
	}
	if ((envs.has_equal && env[i - 1] == '=' && env[i] == '\0') || \
			(!envs.has_equal))
		return (1);
	return (0);
}
