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


typedef struct 	s_env
{
	char		*name;
	char		*content;
	char		has_equal;
}				t_env;

char	**path_parser(t_list_env *envs); // ITS YOUR FUNCS
int		get_curr_location(t_args *ar, t_list_env *envs);


int		begin(char *line, int i, t_data *data);
void	pars_data_init(char *line, t_par *par);
int		start_validators(char *line, t_par *pars);
int		quotes_counter(char *line, t_par *pars);
void	quotes_locations(char *line, t_par *pars);
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


void	spaces_worker(t_par *pars);
void	delete_excess_spaces(t_par *pars);
void	separation_trash(t_par *pars);
void	new_spaces_array(t_par *pars, int count);


void	pipes_processors(t_data *data, char *str, int i);

char	**space_splitter(t_par *pars, char *new_str, int i);
bool	i_inside_array(int *array, int count, int i, int next);


char	*split_on_semicolon(char *line, int i, t_par *pars);
int		get_end(int i, t_par *pars);


int		str_has_pipe(t_par *pars, int ind, int start);


// helpers
bool behind_has_backslash(char *line, char current, char *set, int i);
bool im_in_quotes(int i, int count, int *locations);
bool im_in_end(char *line, char needed, int len);
bool im_in_begin(char *line, char needed);
bool im_alone_redirect(char *line, int len);


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
	//spaces_worker(t_par *pars);


//char **split_by_semicolon(char *line, t_par *pars)
//pipes_processors(t_data *data, char *str, int i);

#endif
