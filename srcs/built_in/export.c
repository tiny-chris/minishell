/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaillag <cgaillag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 16:42:34 by cgaillag          #+#    #+#             */
/*   Updated: 2022/10/13 17:54:07 by cgaillag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	GROS CHECK :
		si le char * de token (texte jusqu'au '=') est équiv à un des env->var
			alors : on remplace env->var, content... par les data de token
		sinon (pas dans env) on crée le maillon env contenant les infos token
			et on l'ajoute à la liste chainee t_env env
		si la modification concerne la var PATH
			alors on met t_env env_path à jour

		PROPOSITION:
			--> util de ft_strncmp
			--> si PATH= ==> free le env_path et rappeler la fonction ft_get_env_path
			/!\ pour ft_get_env_path : MODIFIER ET UTILISER LA LISTE CHAINEE ENV AU LIEU DE CHAR *ENVP
			/!\ récupérer s_env_path dans ft_get_env_path (= tab_path)
				--> cela évite une redite (fonction 'ft_get_str_env_path' inutile)
					et permet de mettre à jour en même temps s_env_path
*/
int	ft_check_export(t_token *token, t_data *data, int flag)
{
	t_env	*env;
	char	*var_tmp;
	int		i;

	env = data->env;
	var_tmp = NULL;
	i = ft_new_strchr(token->token, '=');
	// printf("val de i new strchr export = dans tokentoken : %d\n", i);
	var_tmp = ft_substr(token->token, 0, i + 1);
	ft_handle_malloc(flag + TAB_STR1, var_tmp, 0, data);
	// if (!var_tmp)
	// 	return (1);//FREE + EXIT (MALLOC)
	while (env)
	{
		if (ft_strncmp(env->var_equal, var_tmp, ft_strlen(env->var_equal)) == 0)
		{
			// dprintf(2, "rentre dans if\n");
			ft_handle_malloc(DELONE, env->content, 0, NULL);
			// free(env->content);
			env->content = ft_substr(token->token, i + 1, (ft_strlen(token->token) - i + 1));
			ft_handle_malloc(flag + TAB_STR1, env->content, 0, data);
			// if (!env->content)
			// 	return (1);//FREE + EXIT (MALLOC)
			ft_handle_malloc(DELONE, env->envp, 0, NULL);
			// free(env->envp);
			env->envp = ft_strdup(token->token);
			ft_handle_malloc(flag + TAB_STR1, env->envp, 0, data);
			// if (!env->envp)
			// 	return (1);//FREE + EXIT (MALLOC)
			ft_handle_malloc(DELONE, var_tmp, 0, NULL);
			// free(var_tmp);
			if (ft_strncmp(env->var_equal, "PATH=", ft_strlen(env->var_equal))  == 0)
				ft_get_env_path(data, flag);//ne plus prendre char **envp
			else if (ft_strncmp(env->var_equal, "HOME=", ft_strlen(env->var_equal))  == 0)
				ft_get_home(data, flag);
			return (0);
		}
		env = env->next;
	}
	if (env == NULL)
		//ft_lstadd_env(&(data->env), token->token);///OLD VERSION
		ft_lstadd_env(&(data->env), token->token, data, flag);
	env = data->env;
	ft_handle_malloc(DELONE, var_tmp, 0, NULL);
	// free(var_tmp);
	return (0);
}

/*	***** version simplifiée *****
	s'il n'y a pas de token après export
		alors : erreur --> message ERRFEW
	sinon on avance au token suivant
	boucle tant que le token existe
	1.	si 1er char n'est pas alpha ou '_' (val ASCII 95)
			alors : erreur --> message ERRNAM
	2.	sinon (1er char est un alpha ou '_')
			alors :	tant que char + 1 existe  ET  char + 1 différent de '=' (boucle)
						alors :	si char n'est pas alpha num ou '_'
									alors : erreur --> message ERRNAM
								sinon on avance (jusqu'à la fin du token)
					si le char suivant (hors boucle) est un '='
					alors : GROS CHECK
						si le char * de token (texte jusqu'au '=') est équiv à un des env->var
							alors : on remplace env->var, content... par les data de token
						sinon (pas dans env) on crée le maillon env contenant les infos token
							et on l'ajoute à la liste chainee t_env env
						si la modification concerne la var PATH
							alors on met t_env env_path à jour
	3. on met à jour val_exit
		et on change de token
*/
int	ft_export(t_cmd *cmd, t_data *data, int flag)
{
	t_token	*token;
	int		i;
	int		res;
	int		res2;

	token = cmd->token;
	i = 0;
	res = 0;
	res2 = 0;
	if (token->next == NULL)
		return (ft_msg(EXIT_FAILURE, token->token, ": ", ERRFEW));
	token = token->next;
	while (token)
	{
		if ((ft_isalpha(token->token[0]) == 0) && (token->token[0] != '_'))
			res = ft_msg(1, token->token, ": ", ERRNAM);
		else if ((token->token[0] == '_') && (token->token[1] == '='))
			res = 0;
		else
		{
			while (token->token[i] && token->token[i] != '=')
			{
				// printf("token->token[%d] = %c\n", i, token->token[i]);
				if ((ft_isalnum(token->token[i]) == 0))
				{
					res = ft_msg(1, token->token, ": ", ERRNAM);
					break ;
				}
				else
				{
					i++;
					res = 0;
				}
			}
			if (token->token[i] == '=')
				res = ft_check_export(token, data, flag);
		}
		if (res == 0 && res2 == 0)
			res2 = 0;
		else
			res2 = 1;
		token = token->next;
		i = 0;
	}
	return (res2);
}



/*	ANCIENNE VERSION - modification ci-dessus */

// //check si premier char = digit si ou erreur
// //check si contient un =
// 	// si ne contient pas : on check tout les char
// 		//si les char ne sont pas alpha num + _ (val ASCII 95) ERRNAM;
// 	// si ca en contient on check tout les char avant le =
// 		// si les char ne sont pas alpha num + _ ERRNAM;
// 		// si non GROS CHECK
// 			//si variable (char*) dans env alors remplacer
// 			//si non (pas dans env) alors créer et ajouter dans env
// 				//si modif sur le PATH, alors mettre à jour t_env env_path
// int	ft_export(t_cmd *cmd, t_data *data)
// {
// 	t_token	*token;
// 	int		i;
// 	int 	res;
// 	int		res2;

// 	token = cmd->token;
// 	i = 0;
// 	res = 0;
// 	res2 = 0;
// 	if (token->next == NULL)
// 		return (ft_msg(EXIT_FAILURE, token->token, ": ", ERRFEW));
// 	token = token->next;//
// 	while (token)
// 	{
// 		printf("0 token->token[0] = %c\n", token->token[0]);
// 		printf("0 res ft alpha token[0] = %d\n", ft_isalpha(token->token[0]));
// 		printf("0 res token->token[0] == '_' = %d\n", token->token[0] == '_');
// 		//if (ft_isdigit(token->token[0]))
// 		if ((ft_isalpha(token->token[0]) == 0) && (token->token[0] != '_'))
// 			res = ft_msg(1, token->token, ": (1st char)", ERRNAM);
// 		else
// 		{
// 			i = 1;
// 			if (ft_new_strchr(token->token, '=') == 0)
// 			{
// 				printf("res ft_new_strchr(token->token, '=') = %d\n", ft_new_strchr(token->token, '='));
// 				//i++;
// 				printf("token->token[%d] = %c\n", i, token->token[i]);
// 				while (token->token[i])
// 				{
// 					printf("token->token[%d] = %c\n", i, token->token[i]);
// 					printf("res token->token[%d] == '_' = %d\n", i, token->token[i] == '_');
// 					printf("res token->token[%d] == %c = %d\n", i, 95, token->token[i] == 95);
// 					printf("res ft alnum token[%d] = %d\n", i, ft_isalnum(token->token[i]));
// 					if ((ft_isalnum(token->token[i]) == 0) && (token->token[i] != '_'))
// 					{
// 						res = ft_msg(1, token->token, ": (other char)", ERRNAM);
// 						dprintf(2, "erreur de nom (!isalnum et !_)\n");
// 						break;
// 					}
// 					else
// 					{
// 						i++;
// 						res = 0;
// 					}
// 				}
// 			}
// 			else
// 			{
// 				dprintf(2, "entre dans le else - il y a un =\n");
// 				printf("token[i] = %c\n", token->token[i]);
// 				while (token->token[i] && token->token[i] != '=')
// 				{
// 					dprintf(2, "entre dans la boucle avant le =\n");
// 					if ((ft_isalnum(token->token[i]) == 0) && (token->token[i] != '_'))
// 					{
// 						printf("token[i] = %c\n", token->token[i]);
// 						res = ft_msg(1, token->token, ": ", ERRNAM);
// 						break;
// 					}
// 					else
// 					{
// 						i++;
// 						res = 0;
// 					}
// 				}
// 				if (token->token[i] == '=')
// 				{
// 					dprintf(2, "on a un = à token->token[%d]\n", i);
// 					res = ft_check_export(token, data);
// 				}
// 			}
// 		}
// 		if (res == 0 && res2 == 0)
// 			res2 = 0;
// 		else
// 			res2 = 1;
// 		token = token->next;
// 		//i = 0;
// 	}
// 	return (res2);
// }
