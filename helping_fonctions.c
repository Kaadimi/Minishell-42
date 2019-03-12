/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helping_fonctions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikadimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/09 17:36:49 by ikadimi           #+#    #+#             */
/*   Updated: 2019/03/11 13:36:37 by ikadimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	login_salutation(void)
{
	ft_putendl("####                      ####");
	ft_putendl("#   #                    #    #");
	ft_putendl("#   #                    #    #");
	ft_putendl("#   Welcome to my Minishell   #");
	ft_putendl("#                             #");
}

void	tab_free(char **tab)
{
	int i;

	i = 0;
	while (tab[i])
		free(tab[i++]);
	free(tab);
}

char	*ft_new_strchr(const char *s1, int c)
{
	int i;
	int j;

	i = 0;
	j = ft_strlen(s1);
	while (i <= j)
	{
		if (s1[i] == (char)c)
			return ((char *)s1 + i + 1);
		i++;
	}
	return (NULL);
}

char	*ft_getid(char *s1)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	j = 0;
	while (s1[i] != '\0')
	{
		if (s1[i] == '=')
			break ;
		i++;
	}
	tmp = (char *)malloc(sizeof(char) * (i + 1));
	while (j < i)
	{
		tmp[j] = s1[j];
		j++;
	}
	tmp[j] = '\0';
	return (tmp);
}

char	*ft_patchup(char *id, char *content)
{
	char	*full_content;
	size_t	i;
	size_t	j;

	j = 0;
	i = ft_strlen(content) + ft_strlen(id);
	full_content = (char *)malloc(sizeof(char *) * i + 2);
	i = 0;
	while (id[i])
	{
		full_content[i] = id[i];
		i++;
	}
	full_content[i++] = '=';
	while (content[j])
		full_content[i++] = content[j++];
	full_content[i] = '\0';
	return (full_content);
}
