/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaillag <cgaillag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 15:47:25 by lmelard           #+#    #+#             */
/*   Updated: 2022/10/17 13:22:31 by cgaillag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_val_exit;

static void	ft_init_data_0(t_data *data)
{
	extern char	**environ;

	data->line = NULL;
	data->prompt = NULL;
	data->environ = environ;
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
	//TO CHECK : que toutes les variables de t_data sont init_0
}

void	ft_get_home(t_data *data, int flag)
{
	(void) data;
	t_env	*env;

	env = data->env;
	// dprintf(2, "data->home == %p\n", data->home);
	if (data->home)
	{
		// dprintf(2, "data->home == %s\n", data->home);
		ft_handle_malloc(DELONE, data->home, 0, NULL);
	}
	// if (data->home)
	// 	free(data->home);
	// data->home = NULL;
	if (env != NULL)
	{
		while (env)
		{
			// dprintf(2, "env->var_equal = %s et len 'HOME=' = 5\n", env->var_equal);
			// dprintf (2, "strlen = %lu\n", ft_strlen(env->var_equal));
			if (ft_strncmp(env->var_equal, "HOME=", 5) == 0 && (ft_strlen(env->var_equal) == 5))
				break ;
			env = env->next;
		}
	}
	if (env == NULL)
	{
		// dprintf(2, "pas trouve HOME donc return\n");

		return ;
	}
	// {
	// 	data->home = NULL;
		// return ;
	// }
	if (env->var_equal != NULL && env->content)
	{
		data->home = ft_strdup(env->content);
		// dprintf(2, "new data home = %s\n", data->home);//
		// printf("flag data home = %d\n", flag);
		ft_handle_malloc(flag + TAB_STR1, data->home, 0, data);
		// if (!data->home)
		// 	return ;//malloc free
	}
	return ;
}

// int	ft_init_data_1(t_data *data, char **envp)
// {
// 	ft_init_data_0(data);
// 	printf("test ici 0\n");
// 	data->env = ft_get_env(envp);
// 	printf("test là 0\n");
// 	data->prompt = ft_strdup("--minishell> ");//à ajuster
// 	if (data->prompt == NULL)
// 	{
// 		ft_free_env(&(data->env));
// 		free(data->prompt);
// 		return (1);//on peut mettre un message de pb de malloc car strdup/ could not initialise minishell
// 	}
// 	data->built_in = ft_built_in();
// 	if (data->built_in == NULL)
// 	{
// 		ft_free_env(&(data->env));
// 		free(data->prompt);
// 		ft_free_tabstr(data->built_in);
// 		return (1);//on peut mettre un message de pb de malloc car strdup/ could not initialise minishell
// 	}
// 	data->cwd = getcwd(NULL, 0);// sera mise à jour dans cd
// 	if (!data->cwd)
// 	{
// 		ft_free_env(&(data->env));
// 		free(data->prompt);
// 		ft_free_tabstr(data->built_in);
// 		return (1);//could not initialise minishell
// 	}
// 	ft_get_home(data);
// 	dprintf(2, "val data home = %s\n", data->home);
// 	ft_get_env_path(data);
// 	return (0);
// }


int	ft_init_data_1(t_data *data)
{
	ft_init_data_0(data);
	data->env = ft_get_env(data);
		//TEST1 :
		ft_free_data_process(1, NULL);
		// ft_handle_malloc(0, NULL, 0, 0);//test1
		exit (1);//test1
	data->prompt = ft_strdup("--minishell> ");//à ajuster
		// // TEST2 :
		// free(data->prompt);//test2
		// data->prompt = NULL;//test2
	ft_handle_malloc(ADD_M + TAB_STR1, data->prompt, 0, data);// !!!!!!!!!!!!!!!!!! A REMETTRE
	// if (data->prompt == NULL)
	// {
	// 	ft_free_env(&(data->env));
	// 	free(data->prompt);
	// 	return (1);//on peut mettre un message de pb de malloc car strdup/ could not initialise minishell
	// }
	data->built_in = ft_built_in();
	// if (data->built_in == NULL)
	// {
	// 	ft_free_env(&(data->env));
	// 	free(data->prompt);
	// 	ft_free_tabstr(data->built_in);
	// 	return (1);//on peut mettre un message de pb de malloc car strdup/ could not initialise minishell
	// }
	data->cwd = getcwd(NULL, 0);
	// //TEST6
	// if (data->cwd)//TEST6
	// 	free(data->cwd);//TEST6
	// data->cwd = NULL;//TEST6
	// printf("data->cwd = NULL\n");//TEST6
	if (!data->cwd)
	{
		g_val_exit = ft_msg(1, ERRMSG, "minishell : ", "could not initialise minishell");
		ft_handle_malloc(0, NULL, 0, NULL);
		exit (g_val_exit);
	}
	ft_handle_malloc(ADD_M + TAB_STR1, data->cwd, 0, data);
	// sera mise à jour dans cd
	//http://manpagesfr.free.fr/man/man3/getcwd.3.html : ok pour buf NULL et size 0 (POSIX)
	// {
	// 	g_val_exit();
	// 			ft_free_env(&(data->env));
	// 	free(data->prompt);
	// 	ft_free_tabstr(data->built_in);
	// 	return (1);//could not initialise minishell
	// }
	ft_get_home(data, ADD_M);
	// //TEST7 :
	// ft_handle_malloc(0, NULL, 0, 0);//TEST7
	// exit (1);////TEST7
	// dprintf(2, "val data home = %s\n", data->home);
	ft_get_env_path(data, ADD_M);
	return (0);
}


void	ft_minishell(t_data *data)
{
	if (ft_lexer(data->line))
		g_val_exit = ft_msg(2, "", "", ERRSTX);
	else
	{
		ft_parser(data);
		ft_exec(data);
		ft_free_cmd(&(data->cmd)); // A AJUSTER
	}
	if (data != NULL)
	{
		if (data->line)
			ft_handle_malloc(DELONE, data->line, 0, NULL);
		if (data->str_exit)
			ft_handle_malloc(DELONE, data->str_exit, 0, NULL);
	}
}

/*	Clean data->cmd
// */
// int	ft_clean_cmdline(t_data *data)
// {
// 	if (data != NULL)
// 	{
// 		if (data->line)
// 			ft_handle_malloc(DELONE, data->line, 0, NULL);
// 		// {
// 		// 	free(data->line);
// 		// 	data->line = NULL;
// 		// }
// 		if (data->str_exit)
// 			ft_handle_malloc(DELONE, data->str_exit, 0, NULL);
// 		// {
// 		// 	free(data->str_exit);
// 		// 	data->str_exit = NULL;
// 		// }
// 	}
// 	return (0);
// }

void	ft_exit_ctrl_d(t_data *data)
{
	write(2, "exit\n", 5);
	(void) data;
	rl_clear_history();
	ft_handle_malloc(0, NULL, 0, NULL);
	// ft_free_cmd(&(data->cmd)); // A AJUSTER
	// ft_clean_cmdline(data);
	// ft_clean_cmdline(data);
	// ft_clean_loop(data);
	exit(0);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc == 1 && !argv[1])
	{
		if (ft_init_data_1(&data))
			return (1);
		while (1)
		{
			ft_init_signals(&data);
			data.line = readline(data.prompt);
			if (!data.line)
				ft_exit_ctrl_d(&data);
			if (data.line && ft_strlen(data.line) != 0)
			{
				add_history(data.line);
				ft_minishell(&data);
			}
		}
		rl_clear_history();
		ft_handle_malloc(0, NULL, 0, NULL);
		return (0);
	}
	ft_msg(1, "minishell", ": ", ERRARC);
	return (1);
}

// int	main(void)
// {
// 	char	*str;
// 	char	*str2;
// 	char	*s_malloc;
// 	int		i;
// 	int		*t_int;


// 	i = 0;
// 	str = ft_strdup("coucou");
// 	printf("val str = %s\n", str);
// 	printf("str = %p\n", str);
// 	ft_handle_malloc(ADD_M, str, TAB_STR1, 6);

// 	str2 = ft_substr(str, 0, 4);
// 	ft_handle_malloc(ADD_M, str2, TAB_STR1, (4 + 1));

// 	s_malloc = ft_handle_malloc(MALLOC_C, NULL, TAB_STR1, (6 + 1));
// 	while (i < 6)
// 	{
// 		s_malloc[i] = 'c';
// 		i++;
// 	}
// 	s_malloc[i] = '\0';
// 	printf("s_malloc = %s\n", s_malloc);

// 	ft_handle_malloc(DELONE, str, 0, 0);

// 	t_int = ft_handle_malloc(MALLOC_M, NULL, TAB_INT1, 5);
// 	i = 0;
// 	while (i < 5)
// 	{
// 		t_int[i] = i;
// 		i++;
// 	}

// 	ft_handle_malloc(DELONE, s_malloc, 0, 0);
// 	ft_handle_malloc(0, NULL, 0, 0);

// 	printf("val exit %d\n", g_val_exit);

// 	return (1);
// }
