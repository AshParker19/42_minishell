/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 22:47:09 by anshovah          #+#    #+#             */
/*   Updated: 2023/11/19 17:00:41 by anshovah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

void	rewrite_var(void *content)
{
	t_env	*node;

	node = (t_env *)content;
	if (str_cmp_strct(node->key, pass_along(NULL, false)))
	{
		if (node->value)
			free (node->value);
		node->value = ft_strdup(getenv(node->key));	
	}
}

static char	*pass_along(char *save, bool set)
{
	static char	*key = NULL;
	
	if (set)
		key = save;
	return (key);
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
		pass_along(key, true); /*in a case when we need to rewrite the value of the existing variable,
		we would need to store the current key somewhere to  rewrite the exesting var, but we can't pass it the t_env
		because the we change the t_env struct and it's not a linked list anymore, now it's t_list is a used ll which has only void *content
		and we try to use the function pointer ft_lstiter so we don't iterate in set_var_value()

		AND IN GENERAL WE WOULD NEED TO CHANGE A LOT BECAUSE NOW WE CAN'T JUST GO env->next, because it's a fucking void *content only
		*/
		ft_lstiter(mbox->env_lst, rewrite_var);
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

