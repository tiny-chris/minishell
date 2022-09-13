/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   neg_dolls.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaillag <cgaillag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 11:39:05 by cgaillag          #+#    #+#             */
/*   Updated: 2022/09/13 11:40:56 by cgaillag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*	OBJ:
	conserver les quotes et modifier les $ à ne pas expand en négatif

	Next steps:
	- expand (attention à $? mais entre ' ' donc ok)
	- tokeniser
	- nettoyer dans les token les ' et " inutiles
*/
