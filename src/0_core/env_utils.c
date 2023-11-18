/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 21:35:50 by astein            #+#    #+#             */
/*   Updated: 2023/11/18 15:44:02 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief	
 * 
 * @param 	mbox	mbox is a struct that stores all runtime related infos
 * @param 	key 	the variable key to look for
 * @return 	t_bool
 * 				ft_true		if the 'key' was found in linked list
 * 				ft_false	if the 'key" wasn"t found in linked list
 * 							if the 'ket' is NULL
 */
t_bool   is_var(const t_mbox *mbox, const char *key)
{
    t_env_var   *cur;

	if (!key)
		return (ft_false);
    cur = mbox->env;
    while(cur)
    {
        if(str_cmp_strct(key, cur->key))
            return (ft_true);
        cur = cur->next;
    }
    return (ft_false);
}

/**
 * @brief	Should be called if minishell is run in itself (nested)
 * 			This function tries to increase the shell level (SHLVL) in the ll.
 * 			if the var 'SHLVL' doesnt exist or isnt numeric it set the value
 * 			always to 1.
 * 
 * @param	mbox	mbox is a struct that stores all runtime related infos
 */
void	increment_shlvl(t_mbox *mbox)
{
	int     cur_shlvl_int;
	
	if(is_var(mbox, "SHLVL"))
	{
		cur_shlvl_int = ft_atoi(get_var_value(mbox, "SHLVL"));
		if (cur_shlvl_int == 0)
			cur_shlvl_int = 1;
		else
			cur_shlvl_int++;
		set_var_value_int(mbox, "SHLVL", cur_shlvl_int);
	}
	else
		set_var_value(mbox, "SHLVL", "1");
}

/**
 * @brief	
 * 
 * @param	env_var	
 * @return	int 	
 */
static int  env_counter(const t_env_var *env_var)
{
    if (!env_var)
        return (0);
    else
        return (1 + env_counter(env_var->next));
}

/**
 * @brief			matrix_size is the amount of variables in the matrix
 * 					-1 because of the key '?' which is not exported
 * 					+1 because of the NULL pointer at the end
 * 
 * @param	mbox	mbox is a struct that stores all runtime related infos
 * @return char**	
 */
char **env_to_matrix(const t_mbox *mbox, const char *put_quotes)
{
    char        **env_matrix;
    t_env_var   *cur_var;
    int         matrix_size;
    int         i;

    cur_var = mbox->env;
    matrix_size = env_counter(mbox->env);
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
			env_matrix[i] = ft_strcat_multi(5, cur_var->key, "=",put_quotes ,
				cur_var->value, put_quotes);
			i++;
			cur_var = cur_var->next;
		}
    }
    return (env_matrix);
}


/**
 * @brief	frees the 'key', the 'value' and the given node itself
 * 
 *          NOTE: function should only be called by 'free_vars_v2'
 * 
 * @param	temp	var node to be freed
 */
void    *free_var_v2(t_env_var *temp)
{
    if  (!temp)
        return (NULL);    
    if (temp->key)
        free(temp->key);
    if(temp->value)
        free(temp->value);
    free(temp);
    return (NULL);
}
