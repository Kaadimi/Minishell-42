/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_and_lignes.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikadimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/09 14:09:28 by ikadimi           #+#    #+#             */
/*   Updated: 2019/03/10 09:59:12 by ikadimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_factory(t_norm *k)
{
	int		i;
	t_env	*tmp2;

	tmp2 = NULL;
	i = 0;
	while (k->l != NULL)
	{
		tmp2 = k->l->next;
		free(k->l->content);
		k->l->content = NULL;
		free(k->l->id);
		k->l->id = NULL;
		k->l->next = NULL;
		free(k->l);
		k->l = tmp2;
	}
	tab_free(k->semi_colon);
	tab_free(k->tmp);
	free(k->line);
}

void	variable_swap_v2(char **tmp, t_env *l)
{
	while (l)
	{
		if (!ft_strcmp(*tmp, l->id))
		{
			free(*tmp);
			*tmp = ft_strdup(l->content);
		}
		l = l->next;
	}
}

void	variable_swap(char **tmp, t_env *l)
{
	int		i;
	int		j;
	int		k;
	char	**var;

	i = 0;
	while (tmp[i])
	{
		j = 0;
		k = 0;
		if (tmp[i][0] != '$')
			j = 1;
		var = ft_strsplit(tmp[i], '$');
		while (var[j])
			variable_swap_v2(&var[j++], l);
		free(tmp[i]);
		tmp[i] = ft_strnew(0);
		while (j > k)
			tmp[i] = ft_freejoin(tmp[i], var[k++]);
		j = 0;
		tab_free(var);
		i++;
	}
}

int		dollar_sign_exists(char **tmp)
{
	int i;
	int j;

	i = 0;
	while (tmp[i])
	{
		j = 0;
		while (tmp[i][j])
			if (tmp[i][j++] == '$')
				return (1);
		i++;
	}
	return (0);
}

void	up_grade(char **line)
{
	int i;

	i = 0;
	while (*line[i])
	{
		if (*line[i] == ' ' || *line[i] == '\t' || *line[i] == '"'
				|| *line[i] == 39)
			*line[i] = -1;
		i++;
	}
}
