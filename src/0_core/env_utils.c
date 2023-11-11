/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 21:35:50 by astein            #+#    #+#             */
/*   Updated: 2023/11/11 10:11:44 by anshovah         ###   ########.fr       */
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
    cur = mbox->env_vars;
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
 * 			This function tries to increase the shell level (SHLVL) in the ll
 * 			if the var 'SHLVL' doesnt exist or isnt numeric it set the value
 * 			alwaxs to 1
 * 
 * @param	mbox	mbox is a struct that stores all runtime related infos
 */
void	increment_shlvl(t_mbox *mbox)
{
	// FIXME: what happens if we unset SHLVL???
	// guess we need to reset it here
	int     cur_shlvl_int;
    char    *cur_shlvl_str;
    char    *cur_real_shlvl_str;
    char    *new_value;
	
    cur_shlvl_str = get_var_value(mbox, "SHLVL");
	cur_shlvl_int = ft_atoi(cur_shlvl_str);
    cur_real_shlvl_str = getenv("SHLVL");
	if (cur_shlvl_int == 0)
        cur_shlvl_int = 1;
    else
        cur_shlvl_int++;
    new_value = ft_itoa(cur_shlvl_int);
    set_var_value(mbox, "SHLVL", new_value);
    free(new_value);
    cur_real_shlvl_str = ft_itoa(cur_shlvl_int);
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
 * @brief	
 * 
 * @param	mbox	mbox is a struct that stores all runtime related infos
 * @return char**	
 */
char **env_to_matrix(const t_mbox *mbox, const t_bool put_quotes)
{
    char        **env_matrix;
    t_env_var   *cur_var;
    int         count_vars;
    int         i;

    i = -1;
    count_vars = env_counter(mbox->env_vars);
    cur_var = mbox->env_vars;
    env_matrix = ft_calloc(count_vars + 1, sizeof(char *));
    if (!env_matrix)
        return (NULL);
    while (++i < count_vars)
    {
		if (!str_cmp_strct(cur_var->key, "?"))
		{
            if (put_quotes)
			    env_matrix[i] = ft_strcat_multi(4, cur_var->key, "=\"" ,
                    cur_var->value, "\"");
            else
			    env_matrix[i] = ft_strcat_multi(3, cur_var->key, "=" ,
                    cur_var->value);
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
