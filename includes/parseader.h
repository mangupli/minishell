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

# include <stdbool.h>
# include <stdlib.h>
# include <stdio.h>
# include "minishell.h"
# include	"../libft/includes/libft.h"
# define True true
# define False false
# define ascii "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_"


typedef struct 	s_env
{
	char		*name;
	char		*content;
	char		has_equal;
}				t_env;

char	**path_parser(t_list_env *envs); // ITS YOUR FUNCS
int		get_curr_location(t_args *ar, t_list_env *envs);


int		begin_parser(char *line, int i, t_data *data);
void	pars_data_init(t_par *par);
void	pars_data_init2(char *line, t_par *pars, t_data *data);
int		start_validators(char *line, t_par *pars, t_data *data);
int		quotes_counter(char *line, t_par *pars);
void	quotes_locations(char *line, t_par *pars, t_data *data);
void	counter(char *line, t_par *pars);

void	locations(char *line, t_par *pars);
void	allocate_locations(t_par *pars);
void	semicolon_locations(int i, t_par *pars);
void	pipes_locations(int i, t_par *pars);
void	redirects_locations(int i, t_par *pars);
void	reverse_redirects_locations(int i, t_par *pars);
void	spaces_locations(int i, t_par *pars);

int		validations(char *line, t_par *pars);
void	locations_compile(t_par *pars);
int		fill_locs_array(t_par *pars, int *src, int i, int stop);
void	sorted_array(t_par *pars);
bool	between_only_spaces_or_twinks(char *line, int start, int stop, int len);
bool	has_twinks_redirects(t_par *pars);


void	spaces_worker(t_par *pars, char *line, t_data *data);
void	delete_excess_spaces(t_par *pars, int false_space);
void	separation_trash(t_par *pars);
void	back_separation_trash(char *line, t_par *pars);
void	new_spaces_array(t_par *pars, int count, t_data *data);


char	*split_on_semicolon(char *line, int i, t_par *pars); //  TODO скорее всего это не понадобится
int		get_end(int i, t_par *pars);

char	**splitter(t_data *data, int i, int location);
int		get_str(t_data *data, char *splits, int ind, int next);

bool		opener_begin(t_data *data);
int		file_opener(char *string_with_file, t_data *data, t_args *ar);
int		redirect_type(char *text, char *red_type, int i);
int		get_filename(char *text, char **filename, int i, t_data *data);
int		set_redir_fd(char *red_type, char *filename, t_args *ar);
int		reverse_redirect_open(char *filename, t_args *ar);
int		double_redirect_open(char *filename, t_args *ar);
int		redirect_open(char *filename, t_args *ar);
void	redirects_extractor(char **splits, int i);

int		splits_count(int *array, int array_el_count, int i, int next);
int		i_inside_array(int *array, int count, int i, int next);
int		get_args(t_data *data, t_par *pars, int i);
void 	args_normalizer(char **splits, t_data *data);

char	*begin_env_replace(char *string, t_list_env *envs, t_data *data);
char	type_quotes(char *string, int i);
char	*env_worker(char *string, int i, t_list_env *envs, t_data *data);
char	*get_env_key(char *key_begin, t_data *data);
void	env_replacer(char *string, char *value, char *new_string, int key_len);

char	*slash_replacer(char *string, t_data *data);
char	*trash_replacer(char *string, t_data *data);

char	*quotes_worker(char *string, t_data *data);
char	get_dominator_quotes(char *string);
int		len_without_quotes(char *string, char q);
char	*del_quotes(char *string, char quotes, t_data *data);
void	freedom(t_par *pars);

// redirlist utils
void		redir_lst_addback(t_list_redir **lst, t_list_redir *new);
void		redirslst_clear(t_list_redir **lst);
int			redirlstsize(t_list_redir *lst);
t_list_redir	*redirlstnew(char *filename, char *red_type);





// helpers
bool behind_has_backslash(char *line, char current, char *set, int i);
bool im_in_quotes(int i, int count, int *locations);
bool im_in_end(char *line, char needed, int len);
bool im_in_begin(char *line, char needed);
bool im_alone_redirect(char *line, int len);
int get_location(t_par *pars, int i);

//порядок
//проверка на пустую строку или из одного элемента, но если это ; то что-то сделать
//если первая итерация
	//SOLVED проверка на |     |  и тд
	// pars_data_init(t_par *pars);
	//start_validators(char *line, t_par *pars)
	//quotes_counter(char *line, t_par *pars);
	//quotes_locations(char *line, t_par *pars);
	//counter(char *line, t_par *pars);
	//
	//locations(char *line, t_par *pars); --> allocate_locations(t_par *pars);
	//validations(char *line, t_par *pars)
	// SOLVED перед вызовом сделать проверку, что хотя бы какие-то локации символов есть
	//прежде чем сплитить до первого ; и узнавать их положение нужно проверить,
	// если она вообще, если нет, то пропускать
	// SOLVED нужна проверка на наличие аргументов после редиректов типа >>EOF    <EOF +++
	// SOLVED плюс нужна проверка на дубли ;; || >>> <<
	// SOLVED кейс на "                     |                      "
	//spaces_worker(t_par *pars);

//char **split_by_semicolon(char *line, t_par *pars)
//char	**space_splitter(t_par *pars, char *new_str, int i);
//void	get_args(t_data *data, t_par *pars, int i, char *str);


#endif
