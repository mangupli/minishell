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
	pars->sc = 0;
	pars->sl = NULL;
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
	pars->next = 0; // don't forget, its next enter
	pars->locs = NULL;
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
	if (pars->sc)
		spaces_worker(pars, line);
	return (0);
}

int begin(char *line, int i, t_data *data)
{
	t_par pars;
	char *str;

	if (!i)
	{
		pars_data_init(line, &data->pars);
		start_validators(line, &data->pars); //TODO проверка на валидность
	}
	pars = data->pars;
	str = split_on_semicolon(line, i, &pars);
	printf("%s\n", str);
	get_args(data, &pars, i, str);

	if (pars.next >= pars.len)
		return (0);
	t_args *tmp;

	tmp = data->ar;
	while (tmp)
	{
		int x = 0;
		while(tmp->args[x])
		{
			printf("its motherfucker arg [%d %s]\n", x, tmp->args[x]);
			x++;
		}
		printf("[%c]\n", tmp->type);
		tmp = tmp->next;
	}
	return (pars.next);
}
