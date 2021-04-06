
#include "parser_head.h"


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

	if (!i)
	{
		pars_data_init(line, &data->pars);
		printf("%d\n", start_validators(line, &data->pars)); //TODO проверка на валидность
	}
	pars = data->pars;
	printf("%s",line);
	split_on_semicolon(line, i, &pars);
	if (pars.next >= pars.len)
		return (0);
	return (pars.next);
}

int main()
{
	/*char *line = "HELLO ; 'WORLD\\; IM;' ;TEAPOT \";5433 ;you ;hot \";dog ;hahahah;"
			  "takie dela; skoro buhata \"; daaaa\"; ku';'  ";
	t_data data;
	int i = 0;*//*

	printf("%s\n------------\n", line);
	i = -1;
	while (1 <= (i = begin(line, i + 1, &data)))
	{
		;
	}
	line = "<<>>< hello <>ganry'>><'ds><d john > vong <<endy > petr \">><<\" zx";

	printf("%d == 6\n", data.pars.rc);
	printf("%d == 7\n", data.pars.rrc);
	printf("%d == 10\n", data.pars.rrl[3]);*//*
	begin("hel|lo| pr|ivet < gay ; rex > sobaka >> dra>go>n", 0, &data);
	while (data.pars.locs[i] != -1)
	{
		printf("%d\n", data.pars.locs[i]);
		i++;
	}*/
	t_data data;
/*	begin("test||gth\n--------\n", 0, &data);
	begin("test|gth\n--------\n", 0, &data);
	begin("test>gth\n--------\n", 0, &data);
	begin("test>>gth\n--------\n", 0, &data);
	begin("test>>>gth\n--------\n", 0, &data);
	begin("test<gth\n--------\n", 0, &data);
	begin("test<<gth\n--------\n", 0, &data);
	begin("test;gth\n--------\n", 0, &data);
	begin("test;;gth\n--------\n", 0, &data);
	begin("test|     |gth\n--------\n", 0, &data);
	begin("test>     >gth\n--------\n", 0, &data);
	begin("test;     ;gth\n--------\n", 0, &data);
	begin("test>>gth\n--------\n", 0, &data);
	begin("test> >gth\n--------\n", 0, &data);
	begin("test<    <gth\n--------\n", 0, &data);
	begin("test gth;  ", 0, &data);
	begin("\ntest gth|  ", 0, &data);
	begin("\ntest without  \n", 0, &data);*/
	begin("a", 0, &data);
}

//TODO DELETE THIS SHIT
void		display_error(char *commandname, char *errname, char *str)
{
	printf("%s %s %s\n", commandname, errname, str);
}
