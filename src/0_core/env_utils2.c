/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 22:47:09 by anshovah          #+#    #+#             */
/*   Updated: 2023/11/19 23:30:48 by anshovah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

void	rewrite_var(void *content, char *key, char *value)
{
	t_env	*node;

	node = (t_env *)content;
	if (str_cmp_strct(node->key, key))
	{
		if (node->value)
			free (node->value);
		node->value = ft_strdup(value);	
	}
}

/**
 * @brief	This function
 * 				- either adds a new key value pair to the end of the ll
 * 				- or changes the value of an existing key
 * 
 *          therefore it always duplicates key and / or value!
 * 
 * @param	mbox	mbox is a struct that stores all runtime related infos
 * @param	key		key of the (new) key value pair
 * @param	value	value of the (new) key value pair
 */
void    set_var_value(t_mbox *mbox, const char *key, const char *value)
{
	t_env	*new_node;
	t_env	*cur;
	
	if (is_var(mbox, key))
	{	
		ft_lstiter_chr(mbox->env_lst, rewrite_var, key, value);
		return ;
	}
	new_node = ft_calloc(1, sizeof(t_env));
	if (!new_node)
		return ; //TODO: deal with malloc failure
	new_node->key = ft_strdup(key);
	new_node->value = ft_strdup(value);
	new_node->mbox = mbox;
   	ft_lstadd_back(&(mbox->env_lst), ft_lstnew(new_node)); // this is a big improvement but it takes a big price
}


/**
 * @brief   
 * 
 * @param   mbox 
 * @param   key 
 * @param   int_value 
 */
void    set_var_value_int(t_mbox *mbox, const char *key, int int_value)
{
	char    *char_value;

	char_value = ft_itoa(int_value);
	set_var_value(mbox, key, char_value);
	free (char_value);
}

