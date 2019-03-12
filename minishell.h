/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikadimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 11:41:43 by ikadimi           #+#    #+#             */
/*   Updated: 2019/03/11 13:19:04 by ikadimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "libft/libft.h"
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <unistd.h>
# include <dirent.h>
# include "libft/libft.h"
# include <sys/stat.h>
# define BUFF_SIZE 1

typedef struct		s_env
{
	char			*content;
	char			*id;
	struct s_env	*next;
}					t_env;

typedef struct		s_norm
{
	char			*line;
	char			**tmp;
	char			**semi_colon;
	t_env			*l;
	int				j;
	int				i;
}					t_norm;

void				variable_swap_v2(char **tmp, t_env *l);
int					path_exists(char *ft, t_env *l);
int					fonction_exists(char *ft, char **ret, t_env *l);
void				tab_free(char **tab);
char				*ft_freejoin(char *s1, char const *s2);
char				*path_finder(t_env *l);
t_env				*ft_lnew(char *content);
void				ft_endof_list(t_env **l, t_env *new);
t_env				*ft_env(char **content);
void				ft_setenv(t_env **l, char *content, char *id);
void				env_bundle(char **tmp, t_env **l);
void				swap_content(t_env **l, char *id, char *content);
int					id_exists(t_env *l, char *id);
void				print_list(t_env *l);
char				*ft_patchup(char *id, char *content);
int					ft_read_line(char **tmp);
char				*ft_getid(char *s1);
char				*ft_new_strchr(const char *s1, int c);
void				node_remover(t_env **l, char *id);
void				up_grade(char **line);
int					dollar_sign_exists(char **tmp);
void				variable_swap(char **tmp, t_env *l);
void				variable_swap_v2(char **tmp, t_env *l);
void				free_factory(t_norm *k);
void				built_in(char **tmp, t_env **l, int i, char **env);
char				*ft_getid(char *s1);
char				*ft_new_strchr(const char *s1, int c);
void				tab_free(char **tab);
void				siginthandler();
void				ft_pwd(int i);
void				variable_swap_v2(char **tmp, t_env *l);
int					quotes_checker(char *line);
void				login_salutation(void);

#endif
