/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaillag <cgaillag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 16:42:34 by cgaillag          #+#    #+#             */
/*   Updated: 2022/09/23 18:16:10 by cgaillag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
equal = ft_new_strchr(envp, '=');
new->var = ft_substr(envp, 0, equal);
*/

int	ft_check_export(t_token *token, t_data *data)
{
	t_env	*env;
	char	*var_tmp;
	int		i;

	env = data->env;
	var_tmp = NULL;
	i = ft_new_strchr(token->token, '=');
	var_tmp = ft_substr(token->token, 0, i + 1);
	dprintf(2, "var_tmp = %s\n", var_tmp);
	if (!var_tmp)
		return (1);//FREE + EXIT (MALLOC)
	while (env)
	{
		if (ft_strncmp(env->var_equal, var_tmp, ft_strlen(env->var_equal)) == 0)
		{
			dprintf(2, "rentre dans if\n");
			free(env->content);
			env->content = ft_substr(token->token, i + 1, (ft_strlen(token->token) - i + 1));
			if (!env->content)
				return (1);//FREE + EXIT (MALLOC)
			free(env->envp);
			env->envp = ft_strdup(token->token);
			if (!env->envp)
				return (1);//FREE + EXIT (MALLOC)
			free(var_tmp);
			return (0);
		}
		env = env->next;
	}
	if (env == NULL)
		ft_lstadd_env(&(data->env), token->token);
	env = data->env;
	free(var_tmp);
	return (0);
}

//check si premier char = digit si ou erreur
//check si contient un =
	// si ne contient pas : on check tout les char
		//si les char ne sont pas alpha num + _ (val ASCII 95) ERRNAM;
	// si ca en contient on check tout les char avant le =
		// si les char ne sont pas alpha num + _ ERRNAM;
		// si non GROS CHECK
			//si variable (char*) dans env alors remplacer
			//si non (pas dans env) alors créer et ajouter dans env
				//si modif sur le PATH, alors mettre à jour t_env env_path
int	ft_export(t_cmd *cmd, t_data *data)
{
	t_token	*token;
	int		i;

	token = cmd->token;
	i = 0;
	if (token->next == NULL)
		return (ft_msg(EXIT_FAILURE, token->token, ": ", ERRARG));
	while (token)
	{
		if (ft_isdigit(token->token[0]))
		{
			data->val_exit = ft_msg(1, token->token, ": ", ERRNAM);
		}
		else
		{
			if (token && ft_new_strchr(token->token, '=') == 0)
			{
				while (token->token[i])
				{
					if (ft_isalnum(token->token[i]) == 0 && (token->token[i] != '_'))
					{
						data->val_exit = ft_msg(1, token->token, ": ", ERRNAM);
						break;
					}
					i++;
				}
			}
			else
			{
				dprintf(2, "entre dans le else - il y a un =\n");
				printf("token[i] = %c\n", token->token[i]);
				while (token->token[i] && token->token[i] != '=')
				{
					dprintf(2, "entre dans la boucle avant le =\n");
					if (ft_isalnum(token->token[i]) == 0)//reformuler pour qu'on ait que des alphanum ou _
					{
						printf("token[i] = %c\n", token->token[i]);
						data->val_exit = ft_msg(1, token->token, ": ", ERRNAM);
						break;
					}
					i++;
				}
				if (token->token[i] == '=')
				{
					dprintf(2, "on a un = à token->token[%d]\n", i);
					ft_check_export(token, data);
				}
			}
		}
		token = token->next;
		i = 0;
	}
	return (data->val_exit);
}
