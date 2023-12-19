/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_env_vars.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 16:16:31 by anshovah          #+#    #+#             */
/*   Updated: 2023/12/19 00:54:13 by astein           ###   ########.fr       */
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
 * MANAGEMENT
 *  'initialize_vars'	creates the ll on startup
 * 	'free_vars'			frees the ll
 * 	'free_var'			free the given node
 * 	'var_add_back'		adds the node to the end of the ll
 * 
 * READ FUNCTIONS
 *  'is_var'			checks if the argument 'key' is present in list
 * 	'get_var_node'		returns a pointer to the node with the given key
 * 	'get_var_value'		returns a pointer to the value of the given key
 * 	'get_vars_count'	returns the amount of nodes in the ll
 * 	'get_env_as_matrix'	creates a matrix of strings from the ll
 * 
 * WRITE FUNCTIONS
 * 	'set_var_value'		updates/creates node with the given key and value
 * 	'set_var_value_int'	updates/creates node with the given key and int value
 * 	'increment_shlvl'	increases the value of the 'SHLVL' variable
 * 	'unset_var'			removes the node with the given key from the ll
 */

/**
 * @brief	frees the 'key', the 'value' and the given node itself
 * 
 * @param	temp	var node to be freed
 */
static void	*free_var(t_env *temp)
{
	if (!temp)
		return (NULL);
	if (temp->key)
		free(temp->key);
	if (temp->value)
		free(temp->value);
	free(temp);
	return (NULL);
}

/**
 * @brief   Searches the ll for the given key and returns a pointer to it if
 * 			found, else NULL
 * 
 * @param   mbox        
 * @param   key         
 * @return  t_env*      
 */
static t_env *get_var_node(const t_mbox *mbox, const char *key)
{
	t_env	*cur;
	
	if (!mbox || !key)
		return (NULL);
	cur = mbox->env;
	while (cur)
	{
		if (str_cmp_strct(key, cur->key))
			break ;
		cur = cur->next;
	}
	return (cur);
}

/**
 * @brief   Calls itself recursively until it reaches the end of the ll to count
 * 			the amount of nodes in it
 * 
 * @param   env_var     
 * @return  int         
 */
static int	get_vars_count(const t_env *env_var)
{
	if (!env_var)
		return (0);
	else
		return (1 + get_vars_count(env_var->next));
}

/**
 * @brief   Adds the given node to the end of the ll
 * 
 * @param   mbox        
 * @param   new_var     
 */
static void	var_add_back(t_mbox *mbox, t_env *new_var)
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
 * @brief   This function must only be called at startup and creates a ll out
 * 			of the main param 'env' which is provided as an argument to main and
 * 			will be passed to this function.
 * 			
 * 			The head of the created ll will be stored in 'mbox->env' via the
 * 			function 'set_var_value'
 * 
 *          NOTE: only called once by 'main' on startup
 *          NOTE: a special node for the exit status with key '?' will be added
 * 
 * @param   mbox        
 * @param   env         
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
 * @brief	Checks if a var with the parameter `key` exists in the linked list
 * 
 * @param 	mbox	mbox is a struct that stores all runtime related infos
 * @param 	key 	the variable key to look for
 * @return 	t_bool
 * 				ft_true		if the 'key' was found in linked list
 * 				ft_false	if the 'key" wasn't found in linked list
 * 							if the 'key' is NULL
 */
t_bool	is_var(const t_mbox *mbox, const char *key)
{
	t_env	*var_node;

	var_node = get_var_node(mbox, key);
	if (!var_node)
		return (ft_false);
	return (ft_true);
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
	t_env	*var_node;

	var_node = get_var_node(mbox, key);
	if (!var_node)
		return (NULL);
	return (var_node->value);
}

/**
 * @brief   Creates a matrix of strings from the 't_env' linked list
 * 
 * 			matrix_size is the amount of variables in the matrix
 * 				-1 because of the key '?' which is not exported
 * 				+1 because of the NULL pointer at the end
 * 
 * @param   mbox        
 * @param   put_quotes  this char will be put around the value of the variable
 * @return  char**      
 */
char	**get_env_as_matrix(const t_mbox *mbox, const char *put_quotes)
{
	char	**env_matrix;
	t_env	*cur_var;
	int		matrix_size;
	int		i;

	cur_var = mbox->env;
	matrix_size = get_vars_count(mbox->env);
	env_matrix = ft_calloc(matrix_size, sizeof(char *));
	if (!env_matrix)
		return (NULL);
	i = 0;
	while (cur_var)
	{
		if (str_cmp_strct(cur_var->key, "?"))
			cur_var = cur_var->next;
		else
		{
			env_matrix[i] = ft_strcat_multi(5, cur_var->key, "=", put_quotes,
					cur_var->value, put_quotes);
			i++;
			cur_var = cur_var->next;
		}
	}
	return (env_matrix);
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
	t_env	*var_node;

	if (!mbox || !key)
		return ;
	var_node = get_var_node(mbox, key);
	if (var_node)
	{
		if (var_node->value)
			free(var_node->value);
		var_node->value = ft_strdup(value);
	}
	else
	{
		var_node = ft_calloc(1, sizeof(t_env));
		if (!var_node)
			return ;
		var_node->key = ft_strdup(key); 
		var_node->value = ft_strdup(value);
		var_add_back(mbox, var_node);
	}
}

/**
 * @brief   Used to set a value of a key to an int value. Therefore the int
 * 			value will be converted to a string and then set via 'set_var_value'
 * 			Mostly used for the ? variable aka the exit status of the last cmd
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

/**
 * @brief	Should be called on start of minishell.
 * 			This function tries to increase the shell level (SHLVL) in the ll.
 * 			If the var 'SHLVL' doesnt exist or isnt numeric it set the value
 * 			always to 1.
 * 
 * @param	mbox	mbox is a struct that stores all runtime related infos
 */
void	increment_shlvl(t_mbox *mbox)
{
	int	cur_shlvl_int;

	if (is_var(mbox, "SHLVL"))
	{
		cur_shlvl_int = ft_atoi(get_var_value(mbox, "SHLVL"));
		cur_shlvl_int++;
		set_var_value_int(mbox, "SHLVL", cur_shlvl_int);
	}
	else
		set_var_value(mbox, "SHLVL", "1");
}

/**
 * @brief	This function checks if the 'key' exists in the ll and frees the
 * 			node using the function 'free_var' and removes the node from the ll 
 * 
 * @param	mbox	mbox is a struct that stores all runtime related infos
 * @param	key		key of the node which should be deleted
 */
void	unset_var(t_mbox *mbox, const char *key)
{
	t_env	*cur;
	t_env	*temp;

	if (!mbox->env || !is_var(mbox, key))
		return ;
	if (str_cmp_strct(key, mbox->env->key))
	{
		temp = mbox->env;
		mbox->env = mbox->env->next;
		free_var(temp);
		return ;
	}
	cur = mbox->env;
	while (cur->next)
	{
		if (str_cmp_strct(key, cur->next->key))
		{
			temp = cur->next;
			cur->next = cur->next->next;
			free_var(temp);
			break ;
		}
		cur = cur->next;
	}
}

/**
 * @brief	traverses through the linked list of t_var and frees:
 *              - content via 'free_var'
 *              - node itself
 *          
 *          NOTE: function should only be called by 'destroy_mbox'
 * 
 * @param	mbox mbox is a struct that stores all runtime related infos
 */
void	free_vars(t_mbox *mbox)
{
	t_env	*cur;
	t_env	*temp;

	cur = mbox->env;
	while (cur)
	{
		temp = cur;
		cur = cur->next;
		temp = free_var(temp);
	}
	mbox->env = NULL;
}
