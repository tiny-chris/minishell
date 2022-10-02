/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   explist_3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clem </var/mail/clem>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 18:20:20 by clem              #+#    #+#             */
/*   Updated: 2022/07/14 15:19:18 by cvidon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 ** Return 1 if the entry key is defined in explist.
 */

int	ft_check_exp_entry(t_dlist *explist, char *key)
{
	t_dlist	*temp;
	char	*expkey;
	size_t	keylen;
	size_t	expkeylen;

	temp = explist;
	keylen = ft_strlen(key);
	while (temp)
	{
		expkey = ((t_exp *)temp->content)->key;
		expkeylen = ft_strlen (expkey);
		if (keylen == expkeylen && !ft_strncmp (key, expkey, expkeylen))
			return (TRUE);
		temp = temp->next;
	}
	return (FALSE);
}

/*
 ** Return the 'value' attached to the given 'key' within minishel exp.
 */

char	*ft_getexp(t_data *data, t_dlist *explist, char *key)
{
	t_dlist	*temp;
	char	*expkey;
	size_t	keylen;
	size_t	expkeylen;

	temp = explist;
	keylen = ft_strlen(key);
	while (temp)
	{
		expkey = ((t_exp *)temp->content)->key;
		expkeylen = ft_strlen (expkey);
		if (keylen == expkeylen && !ft_strncmp (expkey, key, expkeylen))
		{
			if (((t_exp *)temp->content)->val)
				return (ft_w_strdup(data, ((t_exp *)temp->content)->val));
			else
				return (ft_w_strdup(data, ""));
		}
		temp = temp->next;
	}
	return (NULL);
}

/*
 ** Sort EXPLIST in alphabetical order.
 */

t_dlist	*ft_sort_exp_2(t_data *data, t_dlist *new)
{
	char	*swap;

	swap = ft_w_strdup(data, ((t_exp *) new->content)->key);
	ft_free (((t_exp *) new->content)->key);
	((t_exp *) new->content)->key
		= ft_w_strdup(data, ((t_exp *) new->next->content)->key);
	ft_free (((t_exp *) new->next->content)->key);
	((t_exp *) new->next->content)->key = ft_w_strdup(data, swap);
	ft_free (swap);
	swap = ft_strdup(((t_exp *) new->content)->val);
	ft_free (((t_exp *) new->content)->val);
	((t_exp *) new->content)->val
		= ft_strdup(((t_exp *) new->next->content)->val);
	ft_free (((t_exp *) new->next->content)->val);
	((t_exp *) new->next->content)->val = ft_strdup(swap);
	ft_free (swap);
	return (new);
}

void	ft_sort_exp(t_data *data, t_dlist *explist)
{
	t_dlist	*temp;
	t_dlist	*new;

	temp = explist;
	while (temp)
	{
		new = explist;
		while (new->next)
		{
			if (ft_strcmp (((t_exp *) new->content)->key,
					((t_exp *) new->next->content)->key) > 0)
				new = ft_sort_exp_2 (data, new);
			new = new->next;
		}
		temp = temp->next;
	}
}
