/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 16:16:31 by anshovah          #+#    #+#             */
/*   Updated: 2023/10/21 12:30:17 by anshovah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* checks if a variable with the key already exists*/
static t_bool   is_var(t_minibox *minibox, char *key)
{
    t_env_var   *current;

    current = minibox->vars;
    while(current)
    {
        if(ft_strcmp_strict(key, current->key))
            return (ft_true);
        current = current->next;
    }
    return (ft_false);
}

void	increment_shlvl(t_minibox *minibox)
{
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

/*
    input a key and return the POINTER to a value or NULL if doesnt exist
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

// /*
//     input a key and a value
//     if key exists
//         -> only change value
//     if key doesnt exist
//         -> create new node in linkedlist and set value
// */
// void set_var_value(t_minibox *minibox, char *key, char *value)
// {
//     t_var *current;
    
//     if(get_var_value(minibox, key))
//     {

// 	if (arg_node)
// 		create_error_msg("nnn", "env: ‘", arg_node->content,
// 			"’: No such file or directory");
// 	else
// 	{
// 		cur = minibox->vars;
// 		while (cur)
// 		{
// 			ft_putstr_fd(cur->key, 1);
// 			ft_putchar_fd('=', 1);
// 			if (cur->value)
// 				ft_putstr_fd(cur->value, 1);
// 			ft_putchar_fd('\n', 1);
// 			cur = cur->next;
// 		}
// 	}
// }
//         current = minibox->vars;
//         while(current)
//         {
//             if(ft_strcmp_strict(key, current->key))
            
//             {
            
//                     current->value = value;
//                     break;
//             }
//             current = current->next;
//         }
//     }
//     else
//         add_var(minibox, key, value);
// }  

/* check if key exists in ll
    if yes remove the node
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

static int  env_counter(t_env_var *env_var)
{
    if (!env_var)
        return (0);
    else
        return (1 + env_counter(env_var->next));
}

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
