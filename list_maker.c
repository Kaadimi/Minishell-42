/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_maker.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikadimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/09 13:57:01 by ikadimi           #+#    #+#             */
/*   Updated: 2019/03/10 14:53:26 by ikadimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*ft_lnew(char *content)
{
	t_env *l;

	if (!(l = (t_env *)malloc(sizeof(t_env))))
		return (NULL);
	l->next = NULL;
	if (content == NULL)
	{
		l->content = NULL;
		l->id = 0;
	}
	else
	{
		l->content = ft_strdup(ft_new_strchr(content, '='));
		if (l->content == NULL)
		{
			free(l);
			return (NULL);
		}
		l->id = ft_getid(content);
	}
	return (l);
}

t_env	*ft_env(char **content)
{
	int		i;
	t_env	*l;
	t_env	*new;

	i = 0;
	l = ft_lnew(content[i]);
	while (content[++i])
	{
		new = ft_lnew(content[i]);
		ft_endof_list(&l, new);
	}
	return (l);
}

void	ft_setenv(t_env **l, char *content, char *id)
{
	t_env	*add;
	char	*full_content;

	full_content = ft_patchup(id, content);
	add = ft_lnew(full_content);
	ft_endof_list(l, add);
	free(full_content);
}

void	env_bundle_v2(char **tmp, t_env **l, struct stat mystat, int i)
{
	if ((ft_strstr(tmp[0], "unsetenv") && !lstat(tmp[0], &mystat))
			|| !ft_strcmp(tmp[0], "unsetenv"))
	{
		if (i > 1)
		{
			i = 0;
			while (tmp[++i])
				node_remover(l, tmp[i]);
		}
		if (i == 1)
			ft_putendl("unsetenv: Too few arguments.");
	}
	else if ((ft_strstr(tmp[0], "env") && !lstat(tmp[0], &mystat))
			|| !ft_strcmp(tmp[0], "env") ||
			(ft_strstr(tmp[0], "ENV") && !lstat(tmp[0], &mystat)))
		print_list(*l);
	else
	{
		ft_putstr(tmp[0]);
		ft_putendl(": Command not found.");
	}
}

void	env_bundle(char **tmp, t_env **l)
{
	int			i;
	struct stat	mystat;

	i = 0;
	while (tmp[i])
		i++;
	if ((ft_strstr(tmp[0], "setenv") && !lstat(tmp[0], &mystat))
			|| !ft_strcmp(tmp[0], "setenv"))
	{
		if (i > 3)
			ft_putendl("setenv: Too many arguments.");
		else if (i == 1)
			print_list(*l);
		else if (!id_exists(*l, tmp[1]) && i == 3)
			ft_setenv(l, tmp[2], tmp[1]);
		else if (i == 3)
			swap_content(l, tmp[1], tmp[2]);
	}
	else
		env_bundle_v2(tmp, l, mystat, i);
}
