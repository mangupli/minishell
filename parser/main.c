//
// Created by Moaning Stonehouse on 3/21/21.
//

#include <stdio.h>
#include <stdlib.h>
#include "../includes/parseader.h"
#include "../includes/minishell.h"


int main(int argc, char *argv[], char *env[])
{
	int i = 0;

	t_env *envs;
	envs = env_parser(env);

	while (envs[i].name != NULL)
	{
		printf("|%s|\n", envs[i].name);
		printf("|%s|\n", envs[i].content);
		i++;
	}
}