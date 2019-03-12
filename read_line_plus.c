/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line_plus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikadimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/10 11:54:35 by ikadimi           #+#    #+#             */
/*   Updated: 2019/03/11 13:56:53 by ikadimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_endof_list(t_env **l, t_env *new)
{
	t_env *head;

	head = *l;
	while ((*l)->next != NULL)
		(*l) = (*l)->next;
	(*l)->next = new;
	*l = head;
}

char	*ft_freejoin(char *s1, char const *s2)
{
	char	*fr;
	size_t	v;

	if (!s1 || !s2)
		return (NULL);
	v = ft_strlen(s1) + ft_strlen(s2);
	if (!(fr = (char *)malloc(sizeof(char) * v + 1)))
		return (NULL);
	ft_strcpy(fr, s1);
	ft_strcat(fr, s2);
	free(s1);
	return (fr);
}

void	ft_read_v2(char *tmp2, int ret, char **tmp)
{
	ret = 0;
	while (tmp2[ret])
	{
		if (tmp2[ret] == ' ' || tmp2[ret] == '\t' || tmp2[ret] == '"'
				|| tmp2[ret] == 39)
			tmp2[ret] = -1;
		ret++;
	}
	*tmp = ft_strtrim(tmp2);
}

int		ft_read_line(char **tmp)
{
	int		ret;
	char	*tmp2;
	char	buf[BUFF_SIZE + 1];
	char	cwd[255];

	getcwd(cwd, 255);
	ft_putstr("\e[32m");
	ft_putstr(cwd);
	ft_putstr(" ⇢ \e[0m");
	tmp2 = ft_strnew(0);
	while ((ret = read(0, buf, BUFF_SIZE)) > 0)
	{
		buf[ret] = '\0';
		tmp2 = ft_freejoin(tmp2, buf);
		if (ft_strchr(tmp2, '\n'))
			break ;
	}
	if (quotes_checker(tmp2))
	{
		free(tmp2);
		return (0);
	}
	ft_read_v2(tmp2, ret, tmp);
	free(tmp2);
	return (1);
}

int		quotes_checker(char *line)
{
	int i;
	int j;

	j = 0;
	i = 0;
	while (line[i])
		if (line[i++] == '"')
			j++;
	if ((j % 2) != 0)
	{
		ft_putendl("Unmatched \".");
		return (1);
	}
	i = 0;
	j = 0;
	while (line[i])
		if (line[i++] == 39)
			j++;
	if ((j % 2) != 0)
	{
		ft_putendl("Unmatched \'.");
		return (1);
	}
	return (0);
}
