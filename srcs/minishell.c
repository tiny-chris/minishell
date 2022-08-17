/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmelard <lmelard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 15:47:25 by lmelard           #+#    #+#             */
/*   Updated: 2022/08/17 16:23:11 by lmelard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int main(int argc, char **argv, char **envp)
{
    char    *line;
    char    *prompt;
    
    (void)envp;
    if (argc == 1 && !argv[1])
    {
        prompt = ft_strdup("minishell> ");
        while (1)
        {
            line = readline(prompt);
            add_history(line);
            free(line);
        }
        rl_clear_history();
        free(prompt);
    }
    return (1);
}