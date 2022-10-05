/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmelard <lmelard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 16:39:05 by cgaillag          #+#    #+#             */
/*   Updated: 2022/10/05 11:45:23 by lmelard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_val_exit;
/*	Format simplifié et fusionné des fonctions ci-dessous
	- pour unique built-in :
	nécessité d'appeler la fonction 'ft_exit_exec' dans exec.c --> déjà fait
*/

int	ft_exec_built_in(t_cmd *cmd, t_data *data)
{
	t_token	*token;

	token = cmd->token;
	if (ft_strncmp(token->token, "echo", 4) == 0)
		g_val_exit = ft_echo(cmd, data);
	else if (ft_strncmp(token->token, "cd", 2) == 0)
		g_val_exit = ft_cd(cmd, data);
	else if (ft_strncmp(token->token, "pwd", 3) == 0)
		g_val_exit = ft_pwd(data);
	else if (ft_strncmp(token->token, "export", 6) == 0)
		g_val_exit = ft_export(cmd, data);
	else if (ft_strncmp(token->token, "unset", 5) == 0)
		g_val_exit = ft_unset(cmd, data);
	else if (ft_strncmp(token->token, "env", 3) == 0)
		g_val_exit = ft_env(cmd, data);
	else if (ft_strncmp(token->token, "exit", 4) == 0)
		g_val_exit = ft_exit(cmd, data);
	else
		return (ft_msg(1, token->token, ": ", "/!\\ is not a builtin!!!!!"));//A REVOIR
	return (g_val_exit);
}

// PLUS UTILE - MERGE avec fonction exec_built_in
int	ft_exec_uniq_builtin(t_data *data)
{//
	t_token	*token;

	token = data->cmd->token;
	if (ft_strncmp(token->token, "echo", 4) == 0)
	{
		//data->val_exit = ft_echo(data->cmd, data);
		g_val_exit = ft_echo(data->cmd, data);
		ft_exit_exec(data);
		return (g_val_exit);
	}
	if (ft_strncmp(token->token, "cd", 2) == 0)
	{
		//data->val_exit = ft_cd(data->cmd, data);
		g_val_exit = ft_cd(data->cmd, data);
		ft_exit_exec(data);
		return (g_val_exit);
	}
	if (ft_strncmp(token->token, "pwd", 3) == 0)
	{
		//data->val_exit = ft_pwd(data);
		g_val_exit = ft_pwd(data);
		ft_exit_exec(data);
		return (g_val_exit);
	}
	if (ft_strncmp(token->token, "env", 3) == 0)
	{
		//data->val_exit = ft_env(data->cmd, data);
		g_val_exit = ft_env(data->cmd, data);
		ft_exit_exec(data);
		return (g_val_exit);
	}
	if (ft_strncmp(token->token, "export", 6) == 0)
	{
		//data->val_exit = ft_export(data->cmd, data);
		g_val_exit = ft_export(data->cmd, data);
		ft_exit_exec(data);
		return (g_val_exit);
	}
	if (ft_strncmp(token->token, "unset", 5) == 0)
	{
		//data->val_exit = ft_unset(data->cmd, data);
		g_val_exit = ft_unset(data->cmd, data);
		ft_exit_exec(data);
		return (g_val_exit);
	}
	// if (ft_strncmp(token->token, "exit", 4) == 0)
	// 	return (ft_exit(data->cmd, data));
	return (1);
}


// POSSIBILITE DE FUSIONNER UNIQUE BUILT IN ET PAS UNIQUE
/*	cf. Format tout en haut !!!!!!
	A SUPPRIMER
*/
// int	ft_exec_built_in(t_cmd *cmd, t_data *data)
// {
// 	t_token	*token;

// 	token = cmd->token;
// 	if (ft_strncmp(token->token, "echo", 4) == 0)
// 	{
// 		data->val_exit = ft_echo(cmd, data);
// 		return (data->val_exit);
// 	}
// 	if (ft_strncmp(token->token, "cd", 2) == 0)
// 	{
// 		data->val_exit = ft_cd(cmd, data);
// 		return (data->val_exit);
// 	}
// 	if (ft_strncmp(token->token, "pwd", 3) == 0)
// 	{
// 		data->val_exit = ft_pwd(data);
// 		return (data->val_exit);
// 	}
// 	if (ft_strncmp(token->token, "export", 6) == 0)
// 	{
// 		data->val_exit = ft_export(cmd, data);
// 		return (data->val_exit);
// 	}
// 	if (ft_strncmp(token->token, "unset", 5) == 0)
// 	{
// 		data->val_exit = ft_unset(cmd, data);
// 		return (data->val_exit);
// 	}
// 	if (ft_strncmp(token->token, "env", 3) == 0)
// 	{
// 		data->val_exit = ft_env(cmd, data);
// 		return (data->val_exit);
// 	}
// 	// if (ft_strncmp(token->token, "exit", 4) == 0)
// 	// 	return (ft_exit(data->cmd, data));
// 	return (1);
// }


