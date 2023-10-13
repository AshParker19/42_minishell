/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 16:16:31 by anshovah          #+#    #+#             */
/*   Updated: 2023/10/13 19:50:02 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
    this function crates a new node of t_var
        FIRST NEED TO CHEK IF ALREADY EXIST
            ->then just chanege
        new_var->key = key
        new_var->value
            if value=NULL
                getenv
            else
                value
    add the new node to the end of the vars linked lis tin minibox
*/
void    add_var(t_minibox *minibox, char *key, char *value)
{
    t_var   *new_var;
    t_var   *current;
    
    if(get_var(minibox, key) != NULL)
    {
        set_var(minibox, key, value);
        return ;
    }

    new_var = ft_calloc(1, sizeof(t_var));
    if(!new_var)
        return; //TODO: deal with malloc failure
    new_var->key = key;
    if(value)
        new_var->value = value;
    else
        new_var->value = ft_strdup(getenv(key));
    if(!minibox->vars)
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
        add_var(minibox, key, NULL);
        i++;    
    }
}

/*
    input a key and return the value or NULL if doesnt exist
*/
char *get_var(t_minibox *minibox, char *key)
{
    t_var *current;
    char *value;

    current = minibox->vars;
    value = NULL;

    while(current)
    {
        if(ft_strcmp_strict(key, current->key))
        // if(ft_strlen(key) == ft_strlen(current->key))
        {
            // if(!ft_strncmp(key, current->key, ft_strlen(key)))
            // {
                value = current->value;
                break;
            // }
        }
        current = current->next;
    }
    return(value);
}

/*
    input a key and a value
    if key exists
        -> only change value
    if key doesnt exist
        -> create new node in linkedlist and set value
*/
void set_var(t_minibox *minibox, char *key, char *value)
{
    t_var *current;
    
    if(get_var(minibox, key))
    {
        current = minibox->vars;
        while(current)
        {
            if(ft_strcmp_strict(key, current->key))
            // if(ft_strlen(key) == ft_strlen(current->key))   
            {
                // if(!ft_strncmp(key, current->key, ft_strlen(key)))
                // {
                    current->value = value;
                    break;
                // }
            }
            current = current->next;
        }
    }
    else
        add_var(minibox, key, value);
}  

/*
    Go through the linked list of t_var and free each node
*/
void free_vars(t_minibox *minibox)
{
    t_var *current;
    t_var *temp;

    current = minibox->vars;
    while(current)
    {
        temp = current;
        current = current->next;
        if (temp->key)
            free(temp->key);
        if(temp->value)
            free(temp->value); // FIXME: getenv no free! overwrtitten value need free!
        free(temp);
    }
}

