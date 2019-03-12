/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikadimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/03 17:36:42 by ikadimi           #+#    #+#             */
/*   Updated: 2019/03/11 14:08:48 by ikadimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	siginthandler(int signal)
{
	int		father;
	char	**cmd;
	char	cwd[255];

	if (signal == SIGINT)
	{
		cmd = (char **)malloc(sizeof(char *) * 3);
		cmd[0] = ft_strdup("/bin/stty");
		cmd[1] = ft_strdup("-echoctl");
		cmd[2] = 0;
		father = fork();
		if (father == 0)
			execve(cmd[0], cmd, NULL);
		else
			wait(NULL);
		tab_free(cmd);
		getcwd(cwd, 255);
		ft_putstr("\n\e[32m");
		ft_putstr(cwd);
		ft_putstr(" ⇢ \e[0m");
	}
}

void	ft_echo(char **av)
{
	int i;
	int j;
	int ac;

	i = 1;
	ac = 0;
	while (av[ac])
		ac++;
	if (ac > 1)
		while (av[i])
		{
			j = 0;
			while (av[i][j])
				write(1, &av[i][j++], 1);
			write(1, " ", 1);
			i++;
		}
	write(1, "\n", 1);
}

void	main_v3(t_norm *k, char **env)
{
	if (k->i > 0)
	{
		variable_swap(k->tmp, k->l);
		if (!ft_strcmp(k->tmp[0], "exit"))
		{
			if (k->i == 1)
			{
				free_factory(k);
				exit(0);
			}
			else
				ft_putendl("exit: Expression Syntax.");
		}
		built_in(k->tmp, &k->l, k->i, env);
	}
}

void	main_v2(t_norm *k, char **env)
{
	char *for_free;
	char *test_path;

	while (k->semi_colon[k->j])
	{
		k->i = 0;
		k->tmp = ft_strsplit(k->semi_colon[k->j], -1);
		while (k->tmp[k->i])
			if (ft_strstr(k->tmp[k->i++], "~"))
			{
				for_free = k->tmp[k->i - 1];
				test_path = ft_strdup("HOME");
				variable_swap_v2(&test_path, k->l);
				k->tmp[k->i - 1] = ft_find_replace(k->tmp[k->i - 1],
						"~", test_path);
				free(test_path);
				free(for_free);
			}
		main_v3(k, env);
		tab_free(k->tmp);
		k->i++;
		k->j++;
	}
}

int		main(int ac, char **av, char **env)
{
	t_norm	k;

	if (ac == 1)
	{
		login_salutation();
		k.l = ft_env(env);
		while (1337)
		{
			signal(SIGINT, siginthandler);
			if (ft_read_line(&k.line))
			{
				k.semi_colon = ft_strsplit(k.line, ';');
				k.j = 0;
				main_v2(&k, env);
				tab_free(k.semi_colon);
				free(k.line);
			}
		}
	}
	else
	{
		ft_putstr(av[0]);
		ft_putendl(": no args needed");
	}
	return (0);
}
