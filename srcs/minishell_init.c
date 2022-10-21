/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_init.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaillag <cgaillag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 21:55:56 by lmelard           #+#    #+#             */
/*   Updated: 2022/10/21 10:52:42 by cgaillag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_val_exit;

static void	ft_init_data_0(t_data *data)
{
	data->line = NULL;
	data->prompt = NULL;
	data->env = NULL;
	data->cwd = NULL;
	data->oldpwd = NULL;
	data->home = NULL;
	data->val_exit = 0;
	data->str_exit = NULL;
	data->nb_pipes = -1;
	data->cmd = NULL;
	data->built_in = NULL;
	data->pid = NULL;
	data->pipe_fd = NULL;
	data->env_path = NULL;
	data->s_env_path = NULL;
	data->tmp_oldpwd = NULL;
}

void	ft_get_home(t_data *data, int flag)
{
	t_env	*env;

	(void) data;
	env = data->env;
	if (data->home)
		ft_handle_malloc(DELONE, data->home, 0, NULL);
	if (env != NULL)
	{
		while (env)
		{
			if (ft_strncmp(env->var_equal, "HOME=", 5) == 0 \
				&& (ft_strlen(env->var_equal) == 5))
				break ;
			env = env->next;
		}
	}
	if (env == NULL)
		return ;
	if (env->var_equal != NULL && env->content)
	{
		data->home = ft_strdup(env->content);
		ft_handle_malloc(flag + TAB_STR1, data->home, 0, data);
	}
	return ;
}

int	ft_init_data_1(t_data *data, char **envp)
{
	ft_init_data_0(data);
	data->env = ft_get_env(envp, data);
	data->prompt = ft_strdup("--minishell> ");
	ft_handle_malloc(ADD_M + TAB_STR1, data->prompt, 0, data);
	data->built_in = ft_built_in();
	data->cwd = getcwd(NULL, 0);
	if (!data->cwd)
	{
		g_val_exit = ft_msg(1, ERRMSG, ERRINI, "");
		ft_handle_malloc(0, NULL, 0, NULL);
		exit (g_val_exit);
	}
	ft_handle_malloc(ADD_M + TAB_STR1, data->cwd, 0, data);
	ft_get_home(data, ADD_M);
	ft_get_env_path(data, ADD_M);
	return (0);
}

int	ft_clean_cmdline(t_data *data)
{
	if (data != NULL)
	{
		if (data->line)
			ft_handle_malloc(DELONE, data->line, 0, NULL);
		if (data->str_exit)
			ft_handle_malloc(DELONE, data->str_exit, 0, NULL);
	}
	return (0);
}

void	ft_exit_ctrl_d(t_data *data)
{
	write(2, "exit\n", 5);
	ft_free_cmd(&(data->cmd));
	ft_clean_cmdline(data);
	ft_clean_cmdline(data);
	rl_clear_history();
	ft_handle_malloc(0, NULL, 0, NULL);
	exit(0);
}
