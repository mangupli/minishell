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
# include "minishell.h"

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
char	**path_parser(t_list_env *envs);
int		env_is_empty(char *env, t_env *envs);
void	set_null(t_env *envs, int i);
t_env	*find_pwd(t_env *envs, char *name);
int		find_env(t_env *envs, char *name);
t_env	*add_env(t_env *envs, char *name, char *content);
int 	envs_count(t_env *envs);
int		twinks_validator(char *line);
int		quotes_validator(char *line);
int		find_function_path(char *func, t_list_env *envs, t_data *data);
int		get_count(char *line);
int		is_end_arg(char *line, int i, int double_quotes, int single_quotes);
int		get_string(char *line, char start, char stop, t_args *args);
void	get_type(char c, t_args *args);
void	args_fill(char *line, t_args *args);
t_args	*line_parser(char *line);
int		ft_strlen_to_pipe_or_comma(char *line, int i);
int		count_args(char *str);
int		ft_strlen_to_space(char *str, int i);
int		str_fill(char *str, char *dest, int i);
char 	**new_split(char *str);


#endif
