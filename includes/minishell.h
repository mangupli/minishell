#ifndef MINISHELL_H
# define MINISHELL_H

# include	<stdio.h>
# include	<unistd.h>
# include	<unistd.h>
# include	<term.h>
# include	<string.h>
# include	<curses.h>
# include	<errno.h>
# include	<sys/ioctl.h>
# include	"../libft/includes/libft.h"
# include	<signal.h>

typedef struct s_glob
{
	int				status;
	char			echo_n;
	struct termios	orig_termios;
}					t_glob;

t_glob		g_struct;

typedef struct s_cursor
{
	int		rows;
	char	c;
	int		cols;
	int		pow;
}				t_cursor;

typedef struct s_line
{
	char		*keys;
	char		*buf;
	int			res;
	size_t		pos;
	size_t		len;
}				t_line;

/*
int		dqc -> double quotes count
int		sqc ->  single quotes count
int		*dql ->  double quotes locations
int 	*sql ->  single quotes locations
int		ppc ->  pipes count
int		*ppl ->  pipes locations
int		scc ->  semicolon count
int		*sccl ->  semicolon locations
int		rc ->  redirects count
int 	*rl ->  redirects locations
int 	rrc ->  reverse redirects count
int 	*rrl ->  reverse redirects locations
int		*locs ->  all symbols
int     sc ->  spaces count
int     *sl ->  spaces locations
char	*redirs ->  redirs
int		xr ->  when you do
int		xrr ->  not pass the norm
int		xstop ->  they come to the rescue
int		hello;
int		dqi -> double quotes location index
int		sqi -> single quotes location index
int		tmpdq -> double quotes temp count
int 	tmpsq -> single quotes temp count
int		tmpi -> temp location index
int		len ->  string length
int		tmpp ->  temp pipes index locations
int		tmps ->  temp semicolon index locations
int		tmpr ->  temp redirects index locations
int		tmprr ->  temp reverse redirects index locations
int 	sci ->  temp space index locations
int 	next ->  next iteration
*/

typedef struct s_par
{
	int		dqc;
	int		sqc;
	int		*dql;
	int		*sql;
	int		ppc;
	int		*ppl;
	int		scc;
	int		*sccl;
	int		rc;
	int		*rl;
	int		rrc;
	int		*rrl;
	int		*locs;
	int		sc;
	int		*sl;
	char	*redirs;
	int		xr;
	int		xrr;
	int		xstop;
	int		hello;
	int		dqi;
	int		sqi;
	int		tmpdq;
	int		tmpsq;
	int		tmpi;
	int		len;
	int		tmpp;
	int		tmps;
	int		tmpr;
	int		tmprr;
	int		sci;
	int		next;
	char	*line_copy;
}				t_par;

typedef struct s_args
{
	char			**args;
	char			type;
	int				file[2];
	struct s_args	*next;
	pid_t			pid;
}					t_args;

/*
** int ifd ------------> Terminal stdin file descriptor.
** int ofd ------------> Terminal stdout file descriptor.
** char *buf ----------> Edited line buffer.
** size_t buflen ------> Edited line buffer size.
** const char *prompt -> Prompt to display.
** size_t plen --------> Prompt length.
** size_t pos ---------> Current cursor position.
** size_t len ---------> Current edited line length.
** size_t cols --------> Number of columns in terminal.
** int list --------> The list index we are currently editing.
*/

typedef struct s_state
{
	int			ifd;
	int			ofd;
	char		*buf;
	size_t		buflen;
	const char	*prompt;
	size_t		plen;
	size_t		pos;
	size_t		len;
	size_t		cols;
	int			index;
}				t_state;

typedef struct s_hist
{
	char		**list;
	int			len;
	int			maxlen;
}				t_hist;

typedef struct s_list_env
{
	char				*name;
	char				*content;
	char				has_equal;
	struct s_list_env	*next;
}						t_list_env;

typedef struct s_data
{
	t_hist		hist;
	const char	*prompt;
	t_args		*ar;
	t_list_env	*envlist;
	char		**envp;
	int			orig_fd[2];
	int			pipe_fd[2];
	int			fd[2];
	t_par		pars;
	char		*add_to_prompt;
}				t_data;

/*
** It is an "append buffer" structure. It helps
** write all the escape sequences in a buffer and flush them to the standard
** output in one call.
*/

typedef struct s_apbuf
{
	char		*b;
	int			len;
}				t_apbuf;

enum e_KEY_ACTION
{
	CTRL_C = 3,
	CTRL_D = 4,
	ENTER = 13,
	ESC = 27,
	CTRL_BACKSLASH = 28,
	BACKSPACE = 127
};

# define HISTORY_MAX_LEN 500
# define MAX_LINE 4096

/*
 * Logic functions
 */

void		display_error(char *commandname, char *errname, char *str);
int			execution(t_data *data);
void		shell_echo(t_data *data, char **args);
void		shell_pwd(t_data *data, char **args);
void		shell_cd(t_data *data, char **args);
void		shell_export(t_data *data, char **args);
void		shell_env(t_data *data, char **args);
void		shell_unset(t_data *data, char **args);
void		ft_exit(int errcode, t_data *data, char hist);
int			shell_exit(char **args, int errcode, t_data *data);
char		*find_env_content(t_list_env *envs, char *name);
t_list_env	*find_env_pointer(t_list_env *envs, char *name);
int			find_envvar(t_list_env **envs, char *name);
int			check_symbols(char *name);
void		add_export_var(t_data *data, char **args);
t_list_env	*sort_list(t_list_env *src);
void		change_content(t_list_env **envs, t_list_env *new);
int			find_fdin(t_data *data, t_args *ar);
int			find_fdout(t_data *data, t_args *ar);
void		free_2d_array(char **array, int start);
void		envlist_to_array(t_data *data);
void		reset_fd(int *file_fd);
void		ft_free(void **ptr);
void		close_all_redir_fd(t_data *data);
void		minishell(t_data *data);
void		set_signals(t_data *data);
void		close_2_fd(int *fd);
void		find_echo_n(t_data *data);
void		renew_data(t_data *data);
int			first_my_function(char **args, t_data *data);
int			exec_my_function(char **args, t_data *data);
int			func_in_return(t_data *data, char **args, \
												void (*f)(t_data *, char **));
void		add_content(t_list_env **envs, t_list_env *new);

/*
 * Parser functions
 */

t_args		*arglstnew(char **args, char type);
void		args_lstadd_back(t_args **lst, t_args *new);
void		args_clearlist(t_args **ar);
int			argslstsize(t_args *lst);
t_args		*arglstlast(t_args *lst);
t_list_env	*get_envlist(char **env);
int			envlstsize(t_list_env *lst);
t_list_env	*envlstnew(char *string);
t_list_env	*envlistnew1(char *name, char *content, char has_equal);
void		env_lst_addback(t_list_env **lst, t_list_env *new);
void		envslst_clear(t_list_env **lst);
void		envsclear_node(t_list_env *env);
void		add_var_to_list(t_list_env **envs, char *str);
int			find_function_path(t_args *ar, t_list_env *envs);

/*
 * for test|debug functions
 */

void		print_arguments(char **args, char type);

/*
 * Readline functions
 */

char		*ft_readline(t_data *data);
int			add_history(char *line, t_hist *h);
void		refresh_line(t_state *a);
int			get_cols(int ofd);
void		refresh_line(t_state *a);
int			get_cursor_pos(int ofd);
void		save_history(t_data *data);
void		load_history(t_data *data);
void		edit_history_next(t_state *a, t_data *data, int dir);
int			enable_mode(int fd);
int			rawline(char *buf, t_data *data);
int			edit(int stdin_fd, int stdout_fd, char *buf, t_data *data);
void		init_struct_a(t_state *a, int stdin_fd, \
												int stdout_fd, t_data *data);
void		backspace_edit(t_state *a);
int			ft_ctrl_c(char *buf);
int			ft_esc(char *keys, t_data *data, t_state *a);

#endif