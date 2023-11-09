/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 16:16:31 by anshovah          #+#    #+#             */
/*   Updated: 2023/11/09 21:41:34 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief   THS FILE DEALS WITH ALL ENVIROMENT VARIABLE RELATED TOPICS
 * 
 * 	The head of the linked list (ll) is stored in mbox->env_vars
 * 	The ll nodes data structure is 't_env_var'
 * 	...a classic key value pair
 *	 key and value are both ALLOCATED MEMMORY and need to be freed on exit
 * 
 *  MANAGEMENT
 *  'load_vars_v2'			creates the ll on startup
 * 	'free_vars_v2'			iterates the ll (mbox->env_vars) and frees all nodes
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
 * 			The head of the created ll will be stored in 'mbox->env_vars' via the
 * 			function 'set_var_value'
 * 
 *          NOTE: only called once by 'main' on startup
 *  
 *          NOTE: a special node for the exit status with key '?' will be added
 * 
 * @param	mbox	mbox is a struct that stores all runtime related infos
 */
void load_vars_v2(t_mbox *mbox)
{
    int     i;
    char    *key;

    i = 0;
    while(mbox->env[i])
    {
        key = ft_strchr(mbox->env[i], '=');
        key = ft_substr(mbox->env[i], 0,
            ft_strlen(mbox->env[i]) - ft_strlen(key));
        set_var_value(mbox, key, getenv(key));
        free (key);
        i++;    
    }
    set_var_value(mbox, "?", EXIT_STR_SUCCESS);
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
char *get_var_value(const t_mbox *mbox, const char *key)
{
    t_env_var *cur;
    char *value;

    cur = mbox->env_vars;
    value = NULL;
    while(cur)
    {
        if(str_cmp_strct(key, cur->key))
        {
            value = cur->value;
            break;
        }
        cur = cur->next;
    }
    return(value);
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
    t_env_var   *new_var;
    t_env_var   *cur;
    
    cur = mbox->env_vars;
    if(is_var(mbox, key))
    {
        while(cur)
        {
            if(str_cmp_strct(key, cur->key))
            {
                if(cur->value)
                    free(cur->value);
                cur->value = ft_strdup(value);
                return ;
            }
            cur = cur->next;
        }
    }
    new_var = ft_calloc(1, sizeof(t_env_var));
    if (!new_var)
        return; //TODO: deal with malloc failure
    new_var->key = ft_strdup(key); 
    new_var->value = ft_strdup(value);
    if (!mbox->env_vars)
        mbox->env_vars = new_var;
    else
    {
        cur = mbox->env_vars;
        while (cur->next)
            cur = cur->next;
        cur->next = new_var;    
    }
}

/**
 * @brief	This function checks if the 'key' exists in the ll and delets the
 * 			node from the ll using the function 'free_var_v2'
 * 
 * @param	mbox	mbox is a struct that stores all runtime related infos
 * @param	key		key of the node which should be deleted
 */
void delete_var(t_mbox *mbox, const char *key)
{
    t_env_var   *cur;
    t_env_var   *temp;
    
    if(!mbox->env_vars)
        return ;
    if(!is_var(mbox, key))
        return ;

    // delete head
    if(str_cmp_strct(key, mbox->env_vars->key))
    {
        temp = mbox->env_vars;
        mbox->env_vars = mbox->env_vars->next;
        free_var_v2(temp);
        return ;
    }
    
    // delete node in list
    cur = mbox->env_vars;
    while(cur->next)
    {
        if(str_cmp_strct(key, cur->next->key))
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
 *          NOTE: function should only be called by 'free_and_close_box_v2'
 * 
 * @param	mbox mbox is a struct that stores all runtime related infos
 */
void free_vars_v2(t_mbox *mbox)
{
    t_env_var *cur;
    t_env_var *temp;

    cur = mbox->env_vars;
    while (cur)
    {
        temp = cur;
        cur = cur->next;
        temp = free_var_v2(temp);
    }
    mbox->env_vars = NULL;
}




