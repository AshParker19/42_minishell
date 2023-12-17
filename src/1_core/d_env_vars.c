/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 16:16:31 by anshovah          #+#    #+#             */
/*   Updated: 2023/12/17 16:55:53 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "frankenshell.h"

/**
 * @brief   THS FILE DEALS WITH ALL ENVIROMENT VARIABLE RELATED TOPICS
 * 
 * 	The head of the linked list (ll) is stored in mbox->env
 * 	The ll nodes data structure is 't_env'
 * 	...a classic key value pair
 *	 key and value are both ALLOCATED MEMMORY and need to be freed on exit
 * 
 *  MANAGEMENT
 *  'initialize_vars'			creates the ll on startup
 * 	'free_vars_v2'			iterates the ll (mbox->env) and frees all nodes
 * 	'free_var_v2'			called by 'free_vars_v2' to free one node of the ll
 * 
 *  READ FUNCTIONS
 *  'is_var'			checks if the argument 'key' is present in list
 * 	'get_var_value'		
 * 	'env_counter'
 * 	'env_to_matrix'
 * 
 *  WRITE FUNCTIONS
 * 	'set_var_value'
 * 	'increment_shlvl'
 * 	'delete_var'
 */

/**
 * @brief	This function must only be called at startup and creates a ll out
 * 			of the main param 'env' which can be accessed via 'mbox->env'
 * 			
 * 			The head of the created ll will be stored in 'mbox->env' via the
 * 			function 'set_var_value'
 * 
 *          NOTE: only called once by 'main' on startup
 *  
 *          NOTE: a special node for the exit status with key '?' will be added
 * 
 * @param	mbox	mbox is a struct that stores all runtime related infos
 */
void	initialize_vars(t_mbox *mbox, char **env)
{
	int		i;
	char	*key;

	i = 0;
	while (env[i])
	{
		key = ft_strchr(env[i], '=');
		key = ft_substr(env[i], 0,
				ft_strlen(env[i]) - ft_strlen(key));
		set_var_value(mbox, key, getenv(key));
		if (key)
			free (key);
		i++;
	}
	set_var_value_int(mbox, "?", EXIT_SUCCESS);
}

/**
 * @brief	Returns a pointer to the value of the given key.
 * 			if key doesnt exists NULL
 * 
 * @param	mbox	mbox is a struct that stores all runtime related infos
 * @param	key		key of the desired key value pair
 * @return	char*	POINTER to the value of the param 'key'
 * 					NULL if key doesnt exist
 */
char	*get_var_value(const t_mbox *mbox, const char *key)
{
	t_env	*cur;
	char	*value;

	cur = mbox->env;
	value = NULL;
	while (cur)
	{
		if (str_cmp_strct(key, cur->key))
		{
			value = cur->value;
			break ;
		}
		cur = cur->next;
	}
	return (value);
}

/**
 * @brief	This function checks if the 'key' exists in the ll and delets the
 * 			node from the ll using the function 'free_var_v2'
 * 
 * @param	mbox	mbox is a struct that stores all runtime related infos
 * @param	key		key of the node which should be deleted
 */
void	delete_var(t_mbox *mbox, const char *key)
{
	t_env	*cur;
	t_env	*temp;

	if (!mbox->env || !is_var(mbox, key))
		return ;
	if (str_cmp_strct(key, mbox->env->key))
	{
		temp = mbox->env;
		mbox->env = mbox->env->next;
		free_var_v2(temp);
		return ;
	}
	cur = mbox->env;
	while (cur->next)
	{
		if (str_cmp_strct(key, cur->next->key))
		{
			temp = cur->next;
			cur->next = cur->next->next;
			free_var_v2(temp);
			break ;
		}
		cur = cur->next;
	}
}

/**
 * @brief	traverses through the linked list of t_var and frees:
 *              - content via 'free_var_v2'
 *              - node itself
 *          
 *          NOTE: function should only be called by 'destroy_mbox'
 * 
 * @param	mbox mbox is a struct that stores all runtime related infos
 */
void	free_vars_v2(t_mbox *mbox)
{
	t_env	*cur;
	t_env	*temp;

	cur = mbox->env;
	while (cur)
	{
		temp = cur;
		cur = cur->next;
		temp = free_var_v2(temp);
	}
	mbox->env = NULL;
}
