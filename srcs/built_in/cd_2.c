/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmelard <lmelard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 14:40:51 by lmelard           #+#    #+#             */
/*   Updated: 2022/10/18 17:48:22 by lmelard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	ft_maj_pwd(t_env *env, t_data *data, t_token *token, int flag)
{
	size_t	size_var_equal;

	size_var_equal = ft_strlen(env->var_equal);
	while (env)
	{
		if (ft_strncmp(env->var_equal, "PWD=", 4) == 0 && size_var_equal == 4)
		{
			if (env->content) // SI PWD EXISTE 
			{
				data->old_pwd = ft_strdup(env->content);
				ft_handle_malloc(flag + TAB_STR1, data->old_pwd, 0, data);
				ft_handle_malloc(DELONE, env->content, 0, NULL);
			}
			if (token && ft_strncmp(token->token, "//", 2) == 0 && ft_strlen(token->token) == 2)
				env->content = ft_strdup(token->token);
			else
			{
				env->content = getcwd(NULL, 0);
				if (!env->content)
					return (ft_msg(1, ERRCWD, "", ""));
			}
			ft_handle_malloc(flag + TAB_STR1, env->content, 0, data);
			if (env->envp)
				ft_handle_malloc(DELONE, env->envp, 0, NULL);
			env->envp = ft_strjoin(env->var_equal, env->content);
			ft_handle_malloc(flag + TAB_STR1, env->envp, 0, data);
			break ;
		}
		env = env->next;
	}
	return (0);
}

void	ft_maj_oldpwd_pwd_exists(t_env *env, t_data *data, int flag)
{
	if (env->content)
	{
		ft_handle_malloc(DELONE, env->content, 0, NULL);
		if (env->envp)
			ft_handle_malloc(DELONE, env->envp, 0, NULL);
		env->envp = ft_strdup("OLDPWD=");
		ft_handle_malloc(flag + TAB_STR1, env->envp, 0, data);
	}
	else
	{
		env->content = ft_strdup(data->oldpwd);
		ft_handle_malloc(flag + TAB_STR1, env->content, 0, data);
		if (env->envp)
			ft_handle_malloc(DELONE, env->envp, 0, NULL);
		env->envp = ft_strjoin(env->var_equal, env->content);
		ft_handle_malloc(flag + TAB_STR1, env->envp, 0, data);
	}
}

void	ft_maj_oldpwd_no_pwd(t_env *env, t_data *data, int flag)
{
	if (!data->old_pwd)
	{
		ft_handle_malloc(DELONE, env->content, 0, NULL);
		if (env->envp)
			ft_handle_malloc(DELONE, env->envp, 0, NULL);
		env->envp = ft_strdup("OLDPWD=");
		ft_handle_malloc(flag + TAB_STR1, env->envp, 0, data);
	}
	else
	{
		ft_handle_malloc(DELONE, env->content, 0, NULL);
		env->content = ft_strdup(data->old_pwd);
		ft_handle_malloc(flag + TAB_STR1, env->content, 0, data);
		if (env->envp)
			ft_handle_malloc(DELONE, env->envp, 0, NULL);
		env->envp = ft_strjoin(env->var_equal, env->content);
		ft_handle_malloc(flag + TAB_STR1, env->envp, 0, data);
	}
}

void	ft_maj_oldpwd(t_env *env, t_data *data, int flag, int pwd_null)
{
	while (env)
	{
		if (ft_strncmp(env->var_equal, "OLDPWD=", 7) == 0 \
			&& (ft_strlen(env->var_equal) == 7))
		{
			if (pwd_null == 1)
				ft_maj_oldpwd_pwd_exists(env, data, flag);
			else
				ft_maj_oldpwd_no_pwd(env, data, flag);
			break ;
		}
		env = env->next;
	}
}
