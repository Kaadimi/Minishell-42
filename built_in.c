/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikadimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/09 14:24:13 by ikadimi           #+#    #+#             */
/*   Updated: 2019/03/11 13:07:35 by ikadimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_cd_v2(char **tmp, int i, t_env **l, char **tmp2)
{
	if (i > 2 && ft_strcmp(tmp[1], "-"))
	{
		ft_putstr("cd: string not in pwd: ");
		ft_putendl(tmp[1]);
	}
	else if (!ft_strcmp(tmp[1], "-"))
	{
		*tmp2 = ft_strdup("OLDPWD");
		variable_swap_v2(tmp2, *l);
		chdir(*tmp2);
		free(*tmp2);
	}
}

void	ft_cd(char **tmp, int i, t_env **l)
{
	char buf[255];
	char *tmp2;

	if (i == 1)
	{
		tmp2 = ft_strdup("HOME");
		variable_swap_v2(&tmp2, *l);
		chdir(tmp2);
		free(tmp2);
	}
	else if (i == 2 && ft_strcmp(tmp[1], "-"))
	{
		getcwd(buf, 255);
		if (chdir(tmp[1]) == 0)
			swap_content(l, "OLDPWD", buf);
		else if (chdir(tmp[1]) == -1)
		{
			ft_putstr("cd: no such file or directory: ");
			ft_putendl(tmp[1]);
		}
	}
	else
		ft_cd_v2(tmp, i, l, &tmp2);
}

void	built_in_v2(char **tmp, int i, char **env)
{
	pid_t		father;
	struct stat mystat;

	if (!ft_strcmp(tmp[0], "pwd"))
		ft_pwd(i);
	else if (!lstat(tmp[0], &mystat))
	{
		if (access(tmp[0], X_OK) == -1)
		{
			ft_putstr(tmp[0]);
			ft_putendl(": Permission denied.");
		}
		else
		{
			father = fork();
			if (father == 0)
				execve(tmp[0], tmp, env);
			else
				wait(NULL);
		}
	}
}

int		fonction_checker(char **tmp, t_env **l, char **env, char **path)
{
	pid_t		father;

	if (fonction_exists(tmp[0], path, *l))
	{
		if (!access(*path, X_OK))
		{
			father = fork();
			if (father == 0)
				execve(*path, tmp, env);
			else
				wait(NULL);
		}
		else
		{
			ft_putstr(tmp[0]);
			ft_putendl(": Permission denied.");
		}
		return (1);
	}
	return (0);
}

void	built_in(char **tmp, t_env **l, int i, char **env)
{
	char		*path;
	struct stat mystat;

	path = NULL;
	if (!ft_strcmp(tmp[0], "cd"))
		ft_cd(tmp, i, l);
	else if (ft_strstr(tmp[0], "setenv") || ft_strstr(tmp[0], "unsetenv")
			|| ft_strstr(tmp[0], "env") || ft_strstr(tmp[0], "ENV"))
		env_bundle(tmp, l);
	else if (!lstat(tmp[0], &mystat) || !ft_strcmp(tmp[0], "pwd"))
		built_in_v2(tmp, i, env);
	else if (fonction_checker(tmp, l, env, &path))
		;
	else
	{
		ft_putstr(tmp[0]);
		ft_putendl(": Command not found.");
	}
	free(path);
}
