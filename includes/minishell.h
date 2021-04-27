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
#include	<signal.h>

extern int	g_status;
extern char	g_echo_n;
extern pid_t pid[500];
extern int g_countpid;

typedef struct s_glob
{
	int			status;
	int			lastpid;
	char		echo_n;
}				t_glob;

typedef struct s_par
{
	int		dqc; //double quotes count
	int		sqc; // single quotes count
	int		*dql; // double quotes locations
	int 	*sql; // single quotes locations
	int		ppc; // pipes count
	int		*ppl; // pipes locations
	int		scc; // semicolon count
	int		*sccl; // semicolon locations
	int		rc; // redirects count
	int 	*rl; // redirects locations
	int 	rrc; // reverse redirects count
	int 	*rrl; // reverse redirects locations
	int		*locs; // all symbols
	int     sc; // spaces count
	int     *sl; // spaces locations

	//helpers
	int		dqi; //double quotes location index
	int		sqi; //single quotes location index
	int		tmpdq; //double quotes temp count
	int 	tmpsq; //single quotes temp count
	int		tmpi; //temp location index
	int		len; // string length
	int		tmpp; // temp pipes index locations
	int		tmps; // temp semicolon index locations
	int		tmpr; // temp redirects index locations
	int		tmprr; // temp reverse redirects index locations
	int 	sci; // temp space index locations

	int 	next; // next iteration
	 //
}				t_par;


typedef struct		s_args
{
	char			**args;
	char			type;
	int				file[2];
	struct s_args	*next;
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
	int ifd;
	int ofd;
	char *buf;
	size_t buflen;
	const char *prompt;
	size_t plen;
	size_t pos;
	size_t len;
	size_t cols;
	int index;
}				t_state;

typedef struct	s_hist
{
	char		**list;
	int			len;
	int 		maxlen;
}				t_hist;

typedef struct 			s_list_env
{
	char				*name;
	char				*content;
	char				has_equal;
	struct s_list_env 	*next;
}						t_list_env;

typedef struct	s_data
{
	t_hist		hist;
	const char	*prompt;
	t_args		*ar;
	t_list_env  *envlist;
	char		**envp;
	int			orig_fd[2];
	int 		pipe_fd[2];
	int 		fd[2];
	t_par		pars;
	char		*add_to_prompt;
}				t_data;

/*
** It is an "append buffer" structure. It helps
** write all the escape sequences in a buffer and flush them to the standard
** output in one call.
*/

typedef struct	s_apbuf
{
	char *b;
	int len;
}				t_apbuf;

enum KEY_ACTION{
	KEY_NULL = 0,	    /* NULL */
	CTRL_A = 1,         /* Ctrl+a */
	CTRL_B = 2,         /* Ctrl-b */
	CTRL_C = 3,         /* Ctrl-c */
	CTRL_D = 4,         /* Ctrl-d */
	CTRL_E = 5,         /* Ctrl-e */
	CTRL_F = 6,         /* Ctrl-f */
	CTRL_H = 8,         /* Ctrl-h */
	TAB = 9,            /* Tab */
	CTRL_K = 11,        /* Ctrl+k */
	CTRL_L = 12,        /* Ctrl+l */
	ENTER = 13,         /* Enter */
	CTRL_N = 14,        /* Ctrl-n */
	CTRL_P = 16,        /* Ctrl-p */
	CTRL_T = 20,        /* Ctrl-t */
	CTRL_U = 21,        /* Ctrl+u */
	CTRL_W = 23,        /* Ctrl+w */
	ESC = 27,
	CTRL_BACKSLASH = 28,/* Escape */
	BACKSPACE =  127    /* Backspace */
};

# define HISTORY_MAX_LEN 500
# define MAX_LINE 4096

struct termios orig_termios; /* In order to restore at exit.*/ // TODO: make it a part of a global stucture

/*
 * Logic functions
 */

void 		display_error(char *commandname, char *errname, char *str);
int 		execution(t_data *data);
void		shell_echo(t_data *data, char **args);
void		shell_pwd(t_data *data, char **args);
void		shell_cd(t_data *data, char **args);
void		shell_export(t_data *data, char **args);
void		shell_env(t_data *data, char **args);
void		shell_unset(t_data *data, char **args);
void		ft_exit(int errcode, t_data *data, char hist);
int 		shell_exit(char **args, int errcode, t_data *data);
char		*find_env_content(t_list_env *envs, char *name);
t_list_env	*find_env_pointer(t_list_env *envs, char *name);
int			find_envvar(t_list_env **envs, char *name);
int			check_symbols(char *name);
void		add_export_var(t_data *data, char **args);
t_list_env *sort_list(t_list_env *src);
void		change_content(t_list_env **envs, t_list_env *new);
int			find_fdin(t_data *data, t_args *ar);
int			find_fdout(t_data *data, t_args *ar);
void		free_2d_array(char **array, int start);
void 		envlist_to_array(t_data *data); // TODO: no need ? also what about char **envp in t_data? is it needed?
void		reset_fd(t_data *data, int *file_fd);
void		ft_free(void **ptr);
void		close_all_redir_fd(t_data *data);
void		minishell(t_data *data);
void 		set_signals(t_data *data);
void		close_2_fd(int *fd);

/*
 * Parser functions
 */

t_args		*arglstnew(char **args, char type);
void		args_lstadd_back(t_args **lst, t_args *new);
void		args_clearlist(t_args **ar);
int			argslstsize(t_args *lst);
t_list_env	*get_envlist(char **env);
int			envlstsize(t_list_env *lst);
t_list_env	*envlstnew(char *string);
t_list_env	*envlistnew1(char *name, char *content, char has_equal);
void		env_lst_addback(t_list_env **lst, t_list_env *new);
void 		add_var_to_list(t_list_env **envs, char *str);
int			find_function_path(t_args *ar, t_list_env *envs);

/*
 * for test|debug functions
 */

int		test_parser(char *line, int count, t_data *data);
void	print_arguments(char **args, char type);

/*
 * Readline functions
 */

char		*ft_readline(t_data *data);
int			add_history(char *line, t_hist *h);
void		refresh_line(t_state *a);
int			get_cols(int ifd, int ofd);
void		refresh_line(t_state *a);
int			get_cursor_pos(int ifd, int ofd);
void		save_history(t_data *data);
void		load_history(t_data *data);
void		edit_history_next(t_state *a, t_data *data, int dir);

#endif