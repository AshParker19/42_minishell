/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 22:47:09 by anshovah          #+#    #+#             */
/*   Updated: 2023/12/15 14:16:57 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "frankenshell.h"

static void	tmp_add_back(t_mbox *mbox, t_env *new_var)
{
	t_env	*cur;

	if (!mbox->env)
		mbox->env = new_var;
	else
	{
		cur = mbox->env;
		while (cur->next)
			cur = cur->next;
		cur->next = new_var;
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
void	set_var_value(t_mbox *mbox, const char *key, const char *value)
{
	t_env	*new_var;
	t_env	*cur;

	cur = mbox->env;
	if (is_var(mbox, key))
	{
		while (cur)
		{
			if (str_cmp_strct(key, cur->key))
			{
				if (cur->value)
					free(cur->value);
				cur->value = ft_strdup(value);
				return ;
			}
			cur = cur->next;
		}
	}
	new_var = ft_calloc(1, sizeof(t_env));
	if (!new_var)
		return ;
	new_var->key = ft_strdup(key); 
	new_var->value = ft_strdup(value);
	tmp_add_back(mbox, new_var);
}

/**
 * @brief   
 * 
 * @param   mbox 
 * @param   key 
 * @param   int_value 
 */
void	set_var_value_int(t_mbox *mbox, const char *key, int int_value)
{
	char	*char_value;

	char_value = ft_itoa(int_value);
	set_var_value(mbox, key, char_value);
	if (char_value)
		free (char_value);
}
