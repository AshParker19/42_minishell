/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 16:16:31 by anshovah          #+#    #+#             */
/*   Updated: 2023/10/23 19:02:44 by anshovah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief   THS FILE DEALS WITH ALL ENVIROMENT VARIABLE RELATED TOPICS
 * 
 * 	The head of the linked list (ll) is stored in minibox->vars
 * 	The ll nodes data structure is 't_env_var'
 * 	...a classic key value pair
 *	 key and value are both ALLOCATED MEMMORY and need to be freed on exit
 * 
 *  MANAGEMENT
 *  'load_vars'			creates the ll on startup
 * 	'free_vars'			iterates the ll (minibox->vars) and frees all nodes
 * 	'free_var'			called by 'free_vars' to free one node of the ll
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
 * @brief	
 * 
 * @param 	minibox	minibox is a struct that stores all runtime related infos
 * @param 	key 	the variable key to look for
 * @return 	t_bool
 * 				ft_true		if the 'key' was found in linked list
 * 				ft_false	if the 'key" wasn"t found in linked list
 * 							if the 'ket' is NULL
 */
static t_bool   is_var(t_minibox *minibox, char *key)
{
    t_env_var   *current;

	if (!key)
		return (ft_false);
    current = minibox->vars;
    while(current)
    {
        if(ft_strcmp_strict(key, current->key))
            return (ft_true);
        current = current->next;
    }
    return (ft_false);
}

/**
 * @brief	Should be called if minishell is run in itself (nested)
 * 			This function tries to increase the shell level (SHLVL) in the ll
 * 			if the var 'SHLVL' doesnt exist or isnt numeric it set the value
 * 			alwaxs to 1
 * 
 * @param	minibox	minibox is a struct that stores all runtime related infos
 */
void	increment_shlvl(t_minibox *minibox)
{
	// FIXME: what happens if we unset SHLVL???
	// guess we need to reset it here
	int     cur_shlvl_int;
    char    *cur_shlvl_str;
    char    *cur_real_shlvl_str;
	
    cur_shlvl_str = get_var_value(minibox, "SHLVL");
	cur_shlvl_int = ft_atoi(cur_shlvl_str);
    cur_real_shlvl_str = getenv("SHLVL");
	if (cur_shlvl_int == 0)
        cur_shlvl_int = 1;
    else
        cur_shlvl_int++;
    set_var_value(minibox, "SHLVL", ft_itoa(cur_shlvl_int));
    cur_real_shlvl_str = ft_itoa(cur_shlvl_int);
}

/*
    this function crates a new node of t_var
        FIRST NEED TO CHEK IF ALREADY EXIST
            ->then just chanege
        new_var->key = key
        new_var->value = value
    add the new node to the end of the vars linked lis tin minibox
*/

/**
 * @brief	This function
 * 				- adds a new key value pair to the end of the ll
 * 				- changes the value of an existing key
 * 
 * @param	minibox	minibox is a struct that stores all runtime related infos
 * @param	key		key of the (new) key value pair
 * @param	value	value of the (new) key value pair
 */
void    set_var_value(t_minibox *minibox, char *key, char *value)
{
    t_env_var   *new_var;
    t_env_var   *current;
    
    // we look if already exists -> then free the old one and connect the pointer to the parameter
    current = minibox->vars;
    if(is_var(minibox, key))
    {
        while(current)
        {
            if(ft_strcmp_strict(key, current->key))
            {
                if(current->value)
                    free(current->value);
                current->value = value;
                return ;
            }
            current = current->next;
        }
    }

    // if not create...
    new_var = ft_calloc(1, sizeof(t_env_var));
    if (!new_var)
        return; //TODO: deal with malloc failure
    new_var->key = key;
    new_var->value = value;

    // add to list if new creatd
    if (!minibox->vars)
        minibox->vars = new_var;
    else
    {
        current = minibox->vars;
        while (current->next)
            current = current->next;
        current->next = new_var;    
    }
}

/*
    Transforming the env into a linked list
    -> store the linked list in minibox
*/

/**
 * @brief	This function must only be called at startup and creates a ll out
 * 			of the main param 'env' which can be accessed via miniox->env
 * 			
 * 			The head of the created ll will be stored in minibox->vars via the
 * 			function 'set_var_value'
 * 
 * @param	minibox	minibox is a struct that stores all runtime related infos
 */
void load_vars(t_minibox *minibox)
{
    int     i;
    char    *key;

    i = 0;
    while(minibox->env[i])
    {
        key = ft_strchr(minibox->env[i], '=');
        key = ft_substr(minibox->env[i], 0,
            ft_strlen(minibox->env[i]) - ft_strlen(key));
        set_var_value(minibox, key, ft_strdup(getenv(key)));
        i++;    
    }
}

/**
 * @brief	Returns a pointer to the given key. if key doesnt exists NULL
 * 
 * @param	minibox	minibox is a struct that stores all runtime related infos
 * @param	key		key of the desired key value pair
 * @return	char*	POINTER to the value of the param 'key'
 * 					NULL if key doesnt exist
 */
char *get_var_value(t_minibox *minibox, char *key)
{
    t_env_var *current;
    char *value;

    current = minibox->vars;
    value = NULL;
    while(current)
    {
        if(ft_strcmp_strict(key, current->key))
        {
            value = current->value;
            break;
        }
        current = current->next;
    }
    return(value);
}

/* check if key exists in ll
    if yes remove the node
*/

/**
 * @brief	This function checks if the 'key' exists in the ll and delets the
 * 			node from the ll using the function 'free_var'
 * 
 * @param	minibox	minibox is a struct that stores all runtime related infos
 * @param	key		key of the node which should be deleted
 */
void delete_var(t_minibox *minibox, char *key)
{
    t_env_var   *current;
    t_env_var   *temp;
    
    if(!minibox->vars)
        return ;
    // first check if key actually exists in ll
    if(!is_var(minibox, key))
        return ;

    // delete head
    if(ft_strcmp_strict(key, minibox->vars->key))
    {
        temp = minibox->vars;
        minibox->vars = minibox->vars->next;
        free_var(temp);
        return ;
    }
    
    // delete node in list
    current = minibox->vars;
    while(current->next)
    {
        if(ft_strcmp_strict(key, current->next->key))
        {
            temp = current->next;
            current->next = current->next->next;
            free_var(temp);
            break ;
        }
        current = current->next;
   }
}

/**
 * @brief	frees the 'key', the 'value' and the given node itself
 * 			//TODO: Maybe return NULL to set the pointer from the calling function to null
 * @param	temp	var node to be freed
 */
void free_var(t_env_var *temp)
{
    if (temp->key)
        free(temp->key);
    if(temp->value)
        free(temp->value);
    free(temp);
}

/*
    Go through the linked list of t_var and free each node
*/

/**
 * @brief	
 * 
 * @param	minibox minibox is a struct that stores all runtime related infos
 */
void free_vars(t_minibox *minibox)
{
    t_env_var *current;
    t_env_var *temp;

    current = minibox->vars;
    while(current)
    {
        temp = current;
        current = current->next;
        free_var(temp);
    }
}

/**
 * @brief	
 * 
 * @param	env_var	
 * @return	int 	
 */
static int  env_counter(t_env_var *env_var)
{
    if (!env_var)
        return (0);
    else
        return (1 + env_counter(env_var->next));
}

/**
 * @brief	
 * 
 * @param	minibox	minibox is a struct that stores all runtime related infos
 * @return char**	
 */
char **env_to_matrix(t_minibox *minibox)
{
    char    **env_matrix;
    t_env_var   *current_var;
    int     count_vars;
    int     i;

    i = -1;
    count_vars = env_counter(minibox->vars);
    current_var = minibox->vars;
    env_matrix = ft_calloc(count_vars + 1, sizeof(char *));
    if (!env_matrix)
        return (NULL);
    while (++i < count_vars)
    {
        env_matrix[i] = ft_strcat_multi(3, current_var->key, "=" , current_var->value);
        current_var = current_var->next;
    }
    return (env_matrix);
}
