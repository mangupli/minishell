#include "minishell.h"
#include "parseader.h"


void pars_data_init(char *line, t_par *pars)
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
	pars->next = 0; // dont forget, its next enter
	pars->locs = NULL;
	pars->prev_dest = 0; // TODO ???
}

int start_validators(char *line, t_par *pars)
{
	if (im_in_begin(line, ';') || im_in_begin(line, '|') || \
		im_in_end(line, '|', pars->len) ||
		im_alone_redirect(line, pars->len))
	{
		display_error("minishell", "syntax error", "unexpected token");
		return (-1);//TODO проверка на валидность,
	}
	if (quotes_counter(line, pars) == -1)
		return (-1); //TODO проверка на валидность
	quotes_locations(line, pars);
	counter(line, pars);
	locations(line, pars);
	if (pars->scc || pars->ppc || pars->rc || pars->rrc)
	{
		if (validations(line, pars) == -1)
			return (-1); //TODO проверка на валидность
	}
	return (0);
}

int begin(char *line, int i, t_data *data)
{
	t_par pars;
	char *str;

	if (!i)
	{
		pars_data_init(line, &data->pars);
		printf("%d\n", start_validators(line, &data->pars)); //TODO проверка на валидность
	}
	pars = data->pars;
	str = split_on_semicolon(line, i, &pars);
	printf("%s\n",str);
	if (pars.next >= pars.len)
		return (0);
	//?? pipes processors?
	return (pars.next);
}
