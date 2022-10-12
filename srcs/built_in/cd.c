/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaillag <cgaillag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 16:32:11 by cgaillag          #+#    #+#             */
/*   Updated: 2022/10/12 04:50:24 by cgaillag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	mettre à jour OLDPWD et PWD et data->cwd

	1 - nb arg: syntax
	2 - access
	3 - opendir :
		int et si ok close
	4 - chdir
*/

void	ft_update_cwd(t_data *data, int flag)
{
	if (data->oldpwd)
		ft_handle_malloc(DELONE, data->oldpwd, 0, 0);
	// {
	// 	free(data->oldpwd);
	// 	data->oldpwd = NULL;
	// }
	data->oldpwd = ft_strdup(data->cwd);
	ft_handle_malloc(flag, data->oldpwd, TAB_STR1, 0);
	// if (!data->oldpwd)
	// 	return ;//free malloc !!
	ft_handle_malloc(DELONE, data->cwd, 0, 0);
	// free(data->cwd);
	// data->cwd = NULL;
	data->cwd = getcwd(NULL, 0);
	ft_handle_malloc(flag, data->cwd, TAB_STR1, 0);
	// if (!data->cwd)
	// 	return ;//free malloc !!
	dprintf(2, "updated: data->cwd = %s et data->oldpwd = %s\n", data->cwd, data->oldpwd);//
}

/*	t_env *env et env = data->env
	char *oldpwd = NULL
	int	pwd_null = 0

	- mise à jour des variables dans data : data->cwd et data->oldpwd
	puis
	1. mise à jour PWD
	  si PWD existe
		a)	si (env->content) existe
				--> var oldpwd = ft_strdup(env->content); avec protection malloc
			sinon
				--> var oldpwd == NULL
		b) mise à jour de PWD env->content :
			si (env->content) existe / n'est pas NULL
				--> on nettoie env->content : free(env->content)
					+ on alimente env->content : env->content = getcwd(NULL, 0)
			sinon
				--> on alimente env->content : env->content = getcwd(NULL, 0)
		c) mise à jour de PWD env->envp :
			si (env->envp) existe / n'est pas NULL
				--> on nettoie env->envp : free(env->envp)
					+ on alimente env->envp : env->envp = ft_strjoin(env->var_equal, env->content) avec malloc check
			sinon
				--> on alimente env->envp : env->envp = ft_strjoin(env->var_equal, env->content) avec malloc check
	  sinon (si PWD n'existe pas, i.e. unset)
		--> mettre var oldpwd == NULL (laisser à NULL)
			mettre var pwd = 1
			+ ne rien faire d'autre, i.e. le maillon est supprimé via unset PWD

	2. mise à jour OLDPWD
	  si OLDPWD existe
	  	si PWD existe
			a) mise à jour de OLPDWD env->content
				si (env->content) existe / n'est pas NULL
					--> on nettoie env->content : free(env->content)
						+ on alimente env->content : env->content = var oldpwd (NULL ou non)
				sinon
					--> on alimente env->content : env->content = var oldpwd (NULL ou non)
			b) mise à jour de OLDPWD env->envp
				i (env->envp) existe / n'est pas NULL
					--> on nettoie env->envp : free(env->envp)
						+ on alimente env->envp : env->envp = ft_strjoin(env->var_equal, env->content) avec malloc check
				sinon
					--> on alimente env->envp : env->envp = ft_strjoin(env->var_equal, env->content) avec malloc check
		sinon (si PWD n'existe pas, i.e. unset) : si var pwd_null = 1
			si OLDPWD == NULL et var pwd_null = 1
				--> on alimente env->content avec data->oldpwd : env->content = ft_strdup(data->oldpwd)
			sinon (si OLDPWD != NULL et pwd_null = 1)
				--> on nettoie env->content : free(env->content)
					mise à jour de OLDPWD env->content à NULL (vide)
	  sinon (OLDPWD n'existe pas = unset)
	  	si PWD existe
			--> on ne fait rien car le maillon est supprimé via unset PWD
		sinon (si PWD n'existe pas, i.e. unset) : si var pwd_null = 1
			--> on ne fait rien car le maillon est supprimé via unset PWD

*/
void	ft_update_pwd(t_cmd *cmd, t_data *data, int flag)
{
	t_env	*env;
	char	*oldpwd;
	int		pwd_null;

	(void) cmd;// voir si on enlève le paramètre
	env = data->env;
	oldpwd = NULL;
	pwd_null = 0;
	ft_update_cwd(data, flag);
	//mise à jour PWD
	while (env)
	{
		if (ft_strncmp(env->var_equal, "PWD=", ft_strlen(env->var_equal)) == 0)
		{
			if (env->content)
			{
				oldpwd = ft_strdup(env->content);
				ft_handle_malloc(flag, oldpwd, TAB_STR1, 0);
				// if (!oldpwd)
				// 	return ; //free malloc!!
				ft_handle_malloc(DELONE, env->content, 0, 0);
				// free(env->content);
				// env->content = NULL;
			}
			// else
			// 	oldpwd = NULL;
			env->content = getcwd(NULL, 0);
			ft_handle_malloc(flag, env->content, TAB_STR1, 0);
			// if (!env->content)
			// 	return ; //free malloc!!
			if (env->envp)
				ft_handle_malloc(DELONE, env->envp, 0, 0);
			// {
			// 	free(env->envp);
			// 	env->envp = NULL;
			// }
			env->envp = ft_strjoin(env->var_equal, env->content);
			ft_handle_malloc(flag, env->envp, TAB_STR1, 0);
			// if (!env->envp)
			// 	return ;//free malloc !!
			break ;
		}
		env = env->next;
	}
	if (env == NULL)//on ne trouve pas PWD --> unset
	{
		oldpwd = NULL;
		pwd_null = 1;
	}
	//mise à jour OLDPWD
	env = data->env;
	while (env)
	{
		if (ft_strncmp(env->var_equal, "OLDPWD=", ft_strlen(env->var_equal)) == 0)
		{
			if (pwd_null == 1)//si PWD n'existe pas
			{
				if (env->content)// i.e. 'OLDPWD=content' dans env
				{
					ft_handle_malloc(DELONE, env->content, 0, 0);
					// free(env->content);
					// env->content = NULL;
					if (env->envp)
						ft_handle_malloc(DELONE, env->envp, 0, 0);
						// free(env->envp);
					env->envp = ft_strdup("OLDPWD=");//ft_strdup(env->var_equal);
					ft_handle_malloc(flag, env->envp, TAB_STR1, 0);
					// if (!env->envp)
					// 	return ; //free malloc !!
				}
				else// (!env->content), si OLDPWD est vide 'OLDPWD=' dans env
				{
					dprintf(2, "on est dans le cas PWD unset et OLDPWD=\n");
					env->content = ft_strdup(data->oldpwd);
					ft_handle_malloc(flag, env->content, TAB_STR1, 0);
					// if (!env->content)
					// 	return ; //free malloc!!
					if (env->envp)
						ft_handle_malloc(DELONE, env->envp, 0, 0);
						// free(env->envp);
					env->envp = ft_strjoin(env->var_equal, env->content);
					ft_handle_malloc(flag, env->envp, TAB_STR1, 0);
					// if (!env->envp)
					// 	return ; //free malloc !!
				}
			}
			else// (pwd_null == 0) i.e. si PWD existe
			{
				if (!oldpwd)//si PWD est vide i.e. 'PWD=' dans env
				{
					ft_handle_malloc(DELONE, env->content, 0, 0);
					// if (env->content)
					// 	free(env->content);
					// env->content = NULL;
					if (env->envp)
						ft_handle_malloc(DELONE, env->envp, 0, 0);
						// free(env->envp);
					env->envp = ft_strdup("OLDPWD=");//ft_strdup(env->var_equal);
					ft_handle_malloc(flag, env->envp, TAB_STR1, 0);
					// if (!env->envp)
					// 	return ; //free malloc !!
				}
				else//if (oldpwd)
				{
					ft_handle_malloc(DELONE, env->content, 0, 0);
					// if (env->content)
					// 	free(env->content);
					env->content = ft_strdup(oldpwd);
					ft_handle_malloc(flag, env->content, TAB_STR1, 0);
					// if (!env->content)
					// 	return ; //free malloc!!
					//free(oldpwd);
					if (env->envp)
						ft_handle_malloc(DELONE, env->envp, 0, 0);
						// free(env->envp);
					env->envp = ft_strjoin(env->var_equal, env->content);
					ft_handle_malloc(flag, env->envp, TAB_STR1, 0);
					// if (!env->envp)
					// 	return ; //free malloc !!
				}
			}
			break ;
		}
		env = env->next;
	}
	if (oldpwd)
		ft_handle_malloc(DELONE, oldpwd, 0, 0);
	return ;
	// //***mise à jour de data->cwd et data->oldpwd --> mis au tout début***
	// if (data->oldpwd)
	// 	free(data->oldpwd);
	// data->oldpwd = ft_strdup(data->cwd);
	// if (!data->oldpwd)
	// 	return ;//free malloc !!
	// free(data->cwd);
	// data->cwd = getcwd(NULL, 0);
	// if (!data->cwd)
	// 	return ;//free malloc !!
}

int	ft_cd(t_cmd *cmd, t_data *data, int flag)
{
	t_token	*token;
	DIR		*directory;

	directory = NULL;
	token = cmd->token;
	token = token->next;
	if (token == NULL)
	{
		dprintf(2, "cd --> rentre dans token == NULL\n");
		ft_get_home(data, flag);
		dprintf(2, "data->home == %p\n", data->home);
		if (data->home == NULL)
		{
			dprintf(2, "data->home == NULL\n");
			return (ft_msg(1, cmd->token->token, ": ", ERRHOM));
		}
		else if (data->home[0] == '\0')
		{
			dprintf(2, "data->home[0] = 0\n");
			return (0);
		}
		if (chdir(data->home) == -1)
			return (ft_msg(errno, data->home, ": ", strerror(errno)));
		printf("cd tout seul\n");
		ft_update_pwd(cmd, data, flag);
		return (0);
	}
	if (token->next)
		return (ft_msg(1, cmd->token->token, ": ", ERRARG));
	if (access(token->token, F_OK) == 0)
	{
		directory = opendir(token->token);
		if (directory == NULL)
			return (ft_msg(1, token->token, ": ", ERRNDR));
		closedir(directory);
		if (chdir(token->token) == -1)
			return (ft_msg(errno, ERRMSG, "", strerror(errno)));
		ft_update_pwd(cmd, data, flag);
		return (0);
	}
	else
		return (ft_msg(errno, token->token, ": ", strerror(errno)));
}
