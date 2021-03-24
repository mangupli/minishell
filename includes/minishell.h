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

typedef struct 	s_env
{
	char		*name;
	char		*content;
	char		has_equal;
}				t_env;

typedef struct 			s_list_env
{
	char				*name;
	char				*content;
	char				has_equal;
	struct s_list_env 	*next;
}						t_list_env;

typedef struct	s_func
{
	int 		echo_n;
}				t_func;

typedef struct	s_data
{
	t_hist		hist;
	const char	*prompt;
	t_env		*env;
	char		**args;
	t_func		func;
	char		*echo;
	t_list_env  *envlist;
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
	ESC = 27,           /* Escape */
	BACKSPACE =  127    /* Backspace */
};

# define HISTORY_MAX_LEN 100
# define MAX_LINE 4096

struct termios orig_termios; /* In order to restore at exit.*/

/*
 * Logic functions
 */

void 		display_error(char *commandname, char *errname, char *str);
int 		execution(t_data *data);
int			shell_echo(t_data *data);
int			shell_pwd(t_data *data);
void		shell_cd(t_data *data);
void		shell_export(t_data *data);
void		shell_env(t_data *data);
void		shell_unset(t_data *data);
void		ft_exit(int errcode);
char		*find_env_content(t_env *envs, char *name);
t_env		*find_env_pointer(t_env *envs, char *name);

/*
 * Parser functions
 */

t_list_env	*get_envlist(char **env);
t_list_env	*ft_mylstnew(char *content);
void		ft_mylstadd_back(t_list_env **lst, t_list_env *new);


/*
 * Readline functions
 */

char		*ft_readline(t_data *data);
int			add_history(char *line, t_hist *h);
void		refresh_line(t_state *a);
int			get_cols(int ifd, int ofd);
void		refresh_line(t_state *a);
int			get_cursor_pos(int ifd, int ofd);
void		save_history(char *file);
void		edit_history_next(t_state *a, t_data *data, int dir);

#endif