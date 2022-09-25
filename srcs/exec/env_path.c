/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaillag <cgaillag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 16:26:06 by cgaillag          #+#    #+#             */
/*   Updated: 2022/09/26 00:35:19 by cgaillag         ###   ########.fr       */
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

/*	1ERE PARTIE : A DESACTIVER pour tester les modifs opérationnelles pour export
	4 fonctions
*/
int	ft_lstadd_env2(t_env **env, char *tab_path)
{
	t_env	*new;
	t_env	*last;

	new = malloc(sizeof(t_env));
	if (!new)
	{
		ft_free_env(env);
		return (1);
	}
	//equal = ft_new_strchr(tab_path, '=');
	// si equal == NULL ?
	new->var = NULL;
	new->var_equal = NULL;
	new->content = ft_strdup(tab_path);
	new->envp = NULL;
	new->next = NULL;
	if (ft_lstlast_env(*env) == 0)
	{
		*env = new;
		return (0);
	}
	last = ft_lstlast_env(*env);
	last->next = new;
	return (0);
}

t_env	*ft_lst_env_path(char **tab_path)
{
	t_env	*env_path;
	int		i;

	i = 0;
	env_path = NULL;
	while (tab_path[i])
	{
		if (ft_lstadd_env2(&env_path, tab_path[i]))
			return (NULL);// FREE TOUT ET EXIT
		i++;
	}
	ft_free_tabstr(tab_path);
	return (env_path);
}

//MODIFIER ET UTILISER LA LISTE CHAINEE ENV AU LIEU DE **ENVP
void	ft_get_env_path(t_data *data, char **envp)
{
	char	*ptr_path;
	char	**tab_path;
	int		i;

	i = 0;
	ptr_path = NULL;
	tab_path = NULL;
	while (envp[i] != NULL && envp[i][0] != '\0')
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			ptr_path = ft_strdup(envp[i] + 5);
		//	printf("ptrpath = %s\n", ptr_path);
			break ;
		}
		i++;
	}
	if (!ptr_path)
		return ;
	tab_path = ft_split(ptr_path, ':');
	// printf("tabpath 1 = %s\n", tab_path[0]);
	// printf("tabpath 2 = %s\n", tab_path[1]);
	// printf("tabpath 3 = %s\n", tab_path[2]);
	if (!tab_path)
		return ;
	free(ptr_path);
	data->env_path = ft_lst_env_path(tab_path);
}

char	**ft_get_str_env_path(t_data *data)
{
	t_env	*env_path;
	char	**s_env_path;
	int		i;

	env_path = data->env_path;
	i = 0;
	while (env_path)
	{
		i++;
		env_path = env_path->next;
	}
	s_env_path = malloc (sizeof(char *) * (i + 1));
	if (!s_env_path)
		return (NULL);
	i = 0;
	env_path = data->env_path;
	while (env_path)
	{
		s_env_path[i] = ft_strdup(env_path->content);
		if (!s_env_path)
		{
			ft_free_tabstr(s_env_path);
			return (NULL);
		}
		i++;
		env_path = env_path->next;
	}
	//s_env_path[i] = ft_strdup("");
	s_env_path[i] = NULL;
	return (s_env_path);
}


/*	********** 2E PARTIE : A ACTIVER POUR LA MODIF EXPORT **********
*/
/*	modif du 2e paramètre du prototype uniquement */

// int	ft_lstadd_env2(t_env **env, char *s_env_path_i)
// {
// 	t_env	*new;
// 	t_env	*last;

// 	new = malloc(sizeof(t_env));
// 	if (!new)
// 	{
// 		ft_free_env(env);
// 		return (1);
// 	}
// 	new->var = NULL;
// 	new->var_equal = NULL;
// 	new->content = ft_strdup(s_env_path_i);
// 	new->envp = NULL;
// 	new->next = NULL;
// 	if (ft_lstlast_env(*env) == 0)
// 	{
// 		*env = new;
// 		return (0);
// 	}
// 	last = ft_lstlast_env(*env);
// 	last->next = new;
// 	return (0);
// }

// /*	Version modifiee pour etre utilisee aussi dans le built in export
// 	dans le cas où la variable à export est "PATH"
// */
// void	ft_get_env_path(t_data *data)
// {
// 	t_env	*env;
// 	int		i;

// 	env = data->env;
// 	i = 0;
// 	if (env == NULL || env->var[0] == '\0')
// 		return ;// on ne met pas à jour env_path donc pas de free ou autre
// 	dprintf(2, "*****fill ou update PATH*****\n");
// 	while (env != NULL && env->var[0] != '\0')
// 	{
// 		if (ft_strncmp(env->var_equal, "PATH=", ft_strlen(env->var_equal)) == 0)
// 			break;
// 		env = env->next;
// 	}
// 	if (!env->content)
// 		return ;//nettoyer : free / exit malloc
// 	if (data->env_path)
// 		ft_free_tabstr(data->s_env_path);
// 	data->s_env_path = ft_split(env->content, ':');
// 	if (!data->s_env_path)
// 		return ;//nettoyer : free / exit malloc
// 	while (data->s_env_path[i])
// 	{
// 		if (ft_lstadd_env2(&(data->env_path), data->s_env_path[i]))
// 			return ;// FREE TOUT ET EXIT
// 		i++;
// 	}
// }
