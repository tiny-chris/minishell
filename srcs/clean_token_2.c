/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_token_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaillag <cgaillag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 18:41:20 by cgaillag          #+#    #+#             */
/*   Updated: 2022/09/07 18:46:19 by cgaillag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* STEPS
	- clean 1st token
	- check built-in
		- if command --> cleaning (negative, delete quotes...)
			BEWARE: empty token
			BEWARE: $?
		- if built-in
			--> check specific situations incl. echo case (WORD_N...)
*/
