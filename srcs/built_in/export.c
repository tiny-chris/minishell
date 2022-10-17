/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmelard <lmelard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 16:42:34 by cgaillag          #+#    #+#             */
/*   Updated: 2022/10/17 18:36:16 by lmelard          ###   ########.fr       */
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
	var_tmp = ft_substr(token->token, 0, i + 1);
	ft_handle_malloc(flag + TAB_STR1, var_tmp, 0, data);
	while (env)
	{
		if (ft_strncmp(env->var_equal, var_tmp, ft_strlen(env->var_equal)) == 0)
		{
			ft_handle_malloc(DELONE, env->content, 0, NULL);
			env->content = ft_substr(token->token, i + 1, (ft_strlen(token->token) - i + 1));
			ft_handle_malloc(flag + TAB_STR1, env->content, 0, data);
			ft_handle_malloc(DELONE, env->envp, 0, NULL);
			env->envp = ft_strdup(token->token);
			ft_handle_malloc(flag + TAB_STR1, env->envp, 0, data);
			ft_handle_malloc(DELONE, var_tmp, 0, NULL);
			if (ft_strncmp(env->var_equal, "PATH=", ft_strlen(env->var_equal)) == 0)
				ft_get_env_path(data, flag);
			else if (ft_strncmp(env->var_equal, "HOME=", ft_strlen(env->var_equal)) == 0)
				ft_get_home(data, flag);
			return (0);
		}
		env = env->next;
	}
	if (env == NULL)
		ft_lstadd_env(&(data->env), token->token, data, flag);
	env = data->env;
	ft_handle_malloc(DELONE, var_tmp, 0, NULL);
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
