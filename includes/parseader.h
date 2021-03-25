/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseader.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstoneho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/21 19:21:59 by mstoneho          #+#    #+#             */
/*   Updated: 2021/03/21 19:22:00 by mstoneho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSEADER_H
# define PARSEADER_H

# include <stdlib.h>
#include "minishell.h"

typedef struct	s_agrs
{
	char	**args;
	struct s_args *next;
}				t_args;

typedef struct 	s_env
{
	char		*name;
	char		*content;
	char		has_equal;
}				t_env;

t_env	*env_parser(char *env[]);
int		env_count(char *env[]);
int		env_len(char *env, int offset);
void	env_filler(char *env, char *dest_env, int offset);
char	**path_parser(t_env *envs);
int		env_is_empty(char *env, t_env *envs);
void	set_null(t_env *envs, int i);
t_env	*find_pwd(t_env *envs, char *name);
int		find_env(t_env *envs, char *name);
t_env	*add_env(t_env *envs, char *name, char *content);
int 	envs_count(t_env *envs);
int		twinks_validator(char *line);
int		quotes_validator(char *line);


#endif
