/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_checker.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikadimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/09 12:59:32 by ikadimi           #+#    #+#             */
/*   Updated: 2019/03/11 13:07:32 by ikadimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd(int i)
{
	char buf[255];

	if (i == 1)
		ft_putendl(getcwd(buf, 255));
	if (i > 1)
		ft_putendl("pwd: too many arguments");
}

char	*path_finder(t_env *l)
{
	char	*tmp;

	tmp = NULL;
	while (l)
	{
		if (!ft_strcmp(l->id, "PATH"))
			tmp = l->content;
		l = l->next;
	}
	if (tmp == NULL)
		return ("12");
	return (tmp);
}

int		fonction_exists_v2(char **path, char **ret, char *ft)
{
	DIR				*mydir;
	struct dirent	*myfile;
	int				i;
	char			*tmp;

	i = 0;
	while (path[i])
	{
		mydir = opendir(path[i]);
		while ((myfile = readdir(mydir)))
			if (!ft_strcmp(myfile->d_name, ft))
			{
				tmp = ft_strjoin(path[i], "/");
				*ret = ft_freejoin(tmp, ft);
				tab_free(path);
				closedir(mydir);
				return (1);
			}
		closedir(mydir);
		i++;
	}
	return (0);
}

int		fonction_exists(char *ft, char **ret, t_env *l)
{
	char	**path;

	path = ft_strsplit(path_finder(l), ':');
	if (ft_strcmp(path[0], "12"))
		if (fonction_exists_v2(path, ret, ft))
			return (1);
	tab_free(path);
	return (0);
}
