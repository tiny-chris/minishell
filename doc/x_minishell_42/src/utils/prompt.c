/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clem </var/mail/clem>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 18:28:52 by clem              #+#    #+#             */
/*   Updated: 2022/07/13 10:33:01 by cvidon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 ** 42 prompt look.
 */

static char	*ft_prompt_prefix(t_data *data)
{
	char	*prefix;
	size_t	i;

	if (getenv ("SESSION_MANAGER"))
	{
		prefix = ft_strchr (getenv ("SESSION_MANAGER"), '/') + 1;
		i = 0;
		while (prefix[i] != '.')
			i++;
		prefix = ft_w_substr(data, prefix, 0, i);
		prefix = ft_strjoin_free_s2 ("👽", prefix);
		prefix = ft_strjoin_free_s2 (getenv("USER"), prefix);
		prefix = ft_strjoin_free_s1 (prefix, ":");
	}
	else
	{
		prefix = ft_w_strdup(data, "minishell:");
	}
	return (prefix);
}

/*
 ** Prompt look.
 */

static char	*ft_prompt_line(t_data *data)
{
	char	*prompt;
	char	*home;
	size_t	homelen;
	char	*prefix;

	prefix = ft_prompt_prefix (data);
	home = getenv("HOME");
	if (home)
		homelen = ft_strlen (home);
	if (home && ft_strncmp (data->cwd, home, homelen) == 0)
	{
		prompt = ft_w_substr (data, data->cwd,
				(unsigned int) homelen, ft_strlen (data->cwd));
		prompt = ft_strjoin_free_s2 ("~", prompt);
		prompt = ft_strjoin_free_s1 (prompt, "$ ");
		prompt = ft_strjoin_free_s2 (prefix, prompt);
	}
	else
	{
		prompt = ft_w_strdup(data, data->cwd);
		prompt = ft_strjoin_free_s1 (prompt, "$ ");
		prompt = ft_strjoin_free_s2 (prefix, prompt);
	}
	ft_free (prefix);
	return (prompt);
}

/*
 ** User input reader.
 */

static void	ft_readline(t_data *data)
{
	char	*cmdline;
	char	*prompt;

	prompt = ft_prompt_line (data);
	cmdline = readline (prompt);
	ft_free (prompt);
	if (!cmdline)
	{
		ft_putendl_fd ("exit", 1);
		ft_exitmsg (data, "");
	}
	if (*cmdline)
		add_history (cmdline);
	data->cmdline = cmdline;
}

/*
 ** Split the PATH.
 */

static char	**ft_split_path(t_data *data)
{
	char	*path;
	char	**splittedpath;

	path = ft_getenv(data, data->envlist, "PATH");
	if (!path)
		return (NULL);
	splittedpath = ft_split(path, ':');
	ft_free (path);
	if (!splittedpath)
		return (NULL);
	return (splittedpath);
}

/*
 ** Prompt.
 */

void	ft_prompt(t_data *data)
{
	while (1)
	{
		data->cmd_path = ft_split_path (data);
		data->envtab = ft_update_envtab (data);
		data->cmdid = 0;
		data->nb_pipes = 0;
		ft_readline (data);
		if (ft_strlen (data->cmdline))
		{
			ft_lexer (data);
			ft_parser (data);
			ft_exec (data);
			ft_clearlist_red (&data->redlist, ft_free);
			ft_clearlist_cmd (&data->cmdlist, ft_free);
			ft_clearlist_tok (&data->toklist, ft_free);
		}
		else
			ft_free (data->cmdline);
		ft_free_tab (data->cmd_path);
		ft_free_tab (data->envtab);
	}
	ft_exitmsg (data, "");
}
