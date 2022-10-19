/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmelard <lmelard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 16:26:06 by cgaillag          #+#    #+#             */
/*   Updated: 2022/10/19 21:41:24 by lmelard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* cf. version modifiée en bas (en comment) :
	Pour tester :
	1. dans le fichier export.c (dossier built-in) :
		- activer la partie de mise à jour du PATH (ligne 58 et suiv.)
	2. dans le fichier env_path.c (dossier exec - ICI)
		- commenter toute la première partie (les 4 fonctins)
		+ "dé-commenter" les fonctions réécrites tout en bas (2e partie)
			--> plus que 2 fonctions ^^
	3. dans le fichier .h :
		- mettre à jour la partie env_path (ligne 115 et suiv.)
	4. dans la fonction ft_child_process du ficher exec.c :
		- commenter la partie s_env_path (ligne 193 et suiv.)
	5. dans la fonction ft_init_data_1 du fichier minishell.c :
		- modifier le prototype ft_get_env_path(data), sans le envp (lignes 77-78)
*/

int	ft_lstadd_env2(t_env **env_path, char *s_env_path_i, t_data *data, int flag)
{
	t_env	*new;
	t_env	*last;

	new = ft_handle_malloc(flag + 1 + LST_ENV, NULL, 1, data);
	new->var = NULL;
	new->var_equal = NULL;
	new->content = ft_strdup(s_env_path_i);
	ft_handle_malloc(flag + TAB_STR1, new->content, 0, data);
	new->envp = NULL;
	new->next = NULL;
	if (ft_lstlast_env(*env_path) == 0)
	{
		*env_path = new;
		return (0);
	}
	last = ft_lstlast_env(*env_path);
	last->next = new;
	return (0);
}

/*	Version modifiee pour etre utilisee aussi dans le built in export
	dans le cas où la variable à export est "PATH"
*/

static void	ft_del_data_envpath(t_data *data)
{
	if (data->s_env_path)
	{
		ft_handle_malloc(DELONE, data->s_env_path, 0, NULL);
		data->s_env_path = NULL;
	}
	if (data->env_path)
	{
		ft_handle_malloc(DELONE, data->env_path, 0, NULL);
		data->env_path = NULL;
	}
}

void	ft_get_env_path(t_data *data, int flag)
{
	t_env	*env;
	int		i;

	env = data->env;
	i = 0;
	ft_del_data_envpath(data);
	if (env == NULL || env->var[0] == '\0')
		return ;
	while (env != NULL)
	{
		if (ft_strncmp(env->var_equal, "PATH=", 5) == 0 \
			&& (ft_strlen(env->var_equal) == 5))
			break ;
		env = env->next;
	}
	if (env == NULL || env->var_equal == NULL || env->content[0] == '\0')
		return ;
	data->s_env_path = ft_split2(env->content, ':');
	ft_handle_malloc(flag + TAB_STRS, data->s_env_path, 0, data);
	i = 0;
	while (data->s_env_path[i])
	{
		ft_lstadd_env2(&(data->env_path), data->s_env_path[i], data, flag);
		i++;
	}
}
