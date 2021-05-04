#include "minishell.h"
#include "parseader.h"

void	spaces_locations(int i, t_par *pars)
{
	pars->sl[pars->sci] = i;
	pars->sci++;
}

void	pars_data_init(char *line, t_par *pars, t_data *data)
{
	pars->dqc = 0;
	pars->sqc = 0;
	pars->dql = NULL;
	pars->sql = NULL;
	pars->ppc = 0;
	pars->ppl = NULL;
	pars->scc = 0;
	pars->sccl = NULL;
	pars->rc = 0;
	pars->rl = NULL;
	pars->rrc = 0;
	pars->rrl = NULL;
	pars->sc = 0;
	pars->sl = NULL;
	pars->locs = NULL;
	pars_data_init2(line, &data->pars, data);
}

void	pars_data_init2(char *line, t_par *pars, t_data *data)
{
	pars->sci = 0;
	pars->dqi = 0;
	pars->sqi = 0;
	pars->tmpdq = 0;
	pars->tmpsq = 0;
	pars->tmpi = 0;
	pars->len = ft_strlen(line);
	pars->tmpp = 0;
	pars->tmps = 0;
	pars->tmpr = 0;
	pars->tmprr = 0;
	pars->next = 0;
	pars->redirs = NULL;
	pars->line_copy = ft_strdup(line);
	if (pars->line_copy == NULL)
		ft_exit(-1, data, 1);
	add_history(line, &data->hist);
}

int	start_validators(char *line, t_par *pars, t_data *data)
{
	if (im_in_begin(line, ';') || im_in_begin(line, '|') || \
			im_in_end(line, '|', pars->len) || \
			im_in_end(line, '\\', pars->len) || \
			im_alone_redirect(line, pars->len))
		return (-1);
	if (quotes_counter(line, pars) == -1)
		return (-1);
	quotes_locations(line, pars, data);
	counter(line, pars);
	locations(line, pars);
	if (pars->scc || pars->ppc || pars->rc || pars->rrc)
	{
		if (validations(line, pars) == -1)
			return (-1);
	}
	if (pars->sc)
		spaces_worker(pars, line, data);
	return (0);
}

int	begin_parser(char *line, int i, t_data *data)
{
	if (!i)
	{
		pars_data_init(line, &data->pars, data);
		if (start_validators(line, &data->pars, data) == -1)
		{
			freedom(&data->pars);
			g_struct.status = 258;
			display_error("minishell", "syntax error", "unexpected token");
			return (-1);
		}
	}
	data->pars.next = get_end(i, &data->pars);
	if (get_args(data, &data->pars, i) == -2)
		return (-2);
	data->pars.hello = data->pars.next + 1;
	find_echo_n(data);
	while (line[data->pars.hello] != '\0' && data->pars.next < data->pars.len)
	{
		if (line[data->pars.hello] != ' ')
			return (data->pars.next);
		data->pars.hello++;
	}
	freedom(&data->pars);
	return (0);
}
