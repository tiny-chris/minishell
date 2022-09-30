/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmelard <lmelard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 15:47:25 by lmelard           #+#    #+#             */
/*   Updated: 2022/09/30 21:06:50 by lmelard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_val_exit;

int	ft_only_space(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '$' && line[i + 1] && ft_isdigit(line[i + 1]))
			i++;
		else if (line[i] != ' ')
			return (1);
		i++;
	}
	return (0);
}

static void ft_init_data_0(t_data *data)
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
	//data->bin = NULL;
	//TO CHECK : que toutes les variables de t_data sont init_0
}

void	ft_get_home(t_data *data)
{
	(void) data;
	t_env	*env;

	env = data->env;
	if (data->home)
		free(data->home);
	data->home = NULL;
	if (env != NULL)
	{
		while (env)
		{
			if (ft_strncmp(env->var_equal, "HOME=", ft_strlen(env->var_equal)) == 0)
				break ;
			env = env->next;
		}
	}
	if (env == NULL)
	{
		data->home = NULL;
		return ;
	}
	if (env->content)
	{
		data->home = ft_strdup(env->content);
		if (!data->home)
			return ;//malloc free
	}
	return ;
}

int	ft_init_data_1(t_data *data, char **envp)
{
	ft_init_data_0(data);
	data->env = ft_get_env(envp);
	data->prompt = ft_strdup("minishell> ");
	if (data->prompt == NULL)
	{
		ft_free_env(&(data->env));
		free(data->prompt);
		return (1);//on peut mettre un message de pb de malloc car strdup/ could not initialise minishell
	}
	data->built_in = ft_built_in();
	if (data->built_in == NULL)
	{
		ft_free_env(&(data->env));
		free(data->prompt);
		ft_free_tabstr(data->built_in);
		return (1);//on peut mettre un message de pb de malloc car strdup/ could not initialise minishell
	}
	data->cwd = getcwd(NULL, 0);// sera mise à jour dans cd
	if (!data->cwd)
	{
		ft_free_env(&(data->env));
		free(data->prompt);
		ft_free_tabstr(data->built_in);
		return (1);//could not initialise minishell
	}
	ft_get_home(data);
	dprintf(2, "val data home = %s\n", data->home);
	// ft_get_env_path(data, envp);// à commenter pour export - PATH
	ft_get_env_path(data);// à activer pour export - PATH
	return (0);
}

/*	Clean data->cmd
*/
int	ft_clean_cmdline(t_data *data)
{
	if (data != NULL)
	{
		if (data->line)
		{
			free(data->line);
			data->line = NULL;
		}
		if (data->str_exit)
		{
			free(data->str_exit);
			data->str_exit = NULL;
		}
	}
	return (0);
}

int	ft_clean_loop(t_data *data)
{
	if (data->built_in != NULL)
		ft_free_tabstr(data->built_in);
	if (data->cwd != NULL)
		free(data->cwd);
	if (data->oldpwd != NULL)
		free(data->oldpwd);
	if (data->home != NULL)
		free(data->home);
	free(data->prompt);
	if (data->env != NULL)
		ft_free_env(&(data->env));
	if (data->env_path)
		ft_free_env(&(data->env_path));
	if (data->s_env_path)
		ft_free_tabstr(data->s_env_path);
	return (0);
}

void	ft_minishell(t_data *data)
{
	if (ft_lexer(data->line))
	{//dprintf(2, "ft_lexer = %d\n", ft_lexer(data.line));
		//data->val_exit = ft_msg(2, "", "", ERRSTX);
		//g_val_exit = data->val_exit;
		g_val_exit = ft_msg(2, "", "", ERRSTX);
	}
	else
	{
		ft_parser(data);// peut etre faire un if == 0 ou 1
		ft_exec(data);// peut etre faire un if == 0 ou 1
		ft_free_cmd(&(data->cmd));// A AJUSTER
	}
	ft_clean_cmdline(data);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	if (argc == 1 && !argv[1])
	{
		if (ft_init_data_1(&data, envp))
			return (1);
		while (1)
		{
			signal(SIGINT, sig_int);
			signal(SIGQUIT, FTQUIT);
			data.line = readline(data.prompt);
			if (data.line && ft_strlen(data.line) != 0 && ft_only_space(data.line) == 1)
			{
				add_history(data.line);
				ft_minishell(&data);
			}
		}
		rl_clear_history();
		ft_clean_loop(&data);
		return (0);
	}
	// penser à faire un message d'erreur si nb d'arg incorrect
	return (1);
}
