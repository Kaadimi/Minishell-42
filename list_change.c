/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_change.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikadimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/10 11:52:50 by ikadimi           #+#    #+#             */
/*   Updated: 2019/03/10 11:54:24 by ikadimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_list(t_env *l)
{
	while (l != NULL)
	{
		ft_putstr(l->id);
		ft_putchar('=');
		ft_putendl(l->content);
		l = l->next;
	}
}

int		id_exists(t_env *l, char *id)
{
	while (l != NULL)
	{
		if (!ft_strcmp(l->id, id))
			return (1);
		l = l->next;
	}
	return (0);
}

void	swap_content(t_env **l, char *id, char *content)
{
	t_env *head;

	head = *l;
	while (*l != NULL)
	{
		if (!ft_strcmp((*l)->id, id))
		{
			free((*l)->content);
			(*l)->content = ft_strdup(content);
		}
		*l = (*l)->next;
	}
	*l = head;
}

void	node_remover_v2(t_env **l, char *id)
{
	t_env *head;
	t_env *unset;

	head = *l;
	while ((*l)->next != NULL)
	{
		if (!ft_strcmp((*l)->next->id, id))
		{
			free((*l)->next->content);
			free((*l)->next->id);
			unset = (*l)->next->next;
			(*l)->next->next = NULL;
			free((*l)->next);
			(*l)->next = unset;
		}
		if ((*l)->next != NULL)
			*l = (*l)->next;
	}
	*l = head;
}

void	node_remover(t_env **l, char *id)
{
	t_env *unset;

	if (!ft_strcmp((*l)->id, id))
	{
		unset = (*l)->next;
		free((*l)->content);
		free((*l)->id);
		(*l)->next = NULL;
		free(*l);
		*l = unset;
	}
	else
		node_remover_v2(l, id);
}
