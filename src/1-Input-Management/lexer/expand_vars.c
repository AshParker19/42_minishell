/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_vars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 12:58:49 by anshovah          #+#    #+#             */
/*   Updated: 2023/10/24 19:55:46 by anshovah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

static void append_str(t_minibox *minibox, char *add_str)
{
    char    *temp;

    temp =  ft_strcat_multi(2, minibox->input_expanded, add_str);
    free(minibox->input_expanded);
    minibox->input_expanded = temp;
}

static void found_key(t_minibox *minibox, int *k)
{
    int     end_of_key;
    char    *temp_key;
    
    end_of_key = *k;
    while (minibox->input_quoted[end_of_key]
            && (ft_isalnum(minibox->input_quoted[end_of_key])
            || minibox->input_quoted[end_of_key] == '_'))
                end_of_key++;
    temp_key = ft_substr(minibox->input_quoted, *k, end_of_key - *k);
    append_str(minibox, get_var_value(minibox, temp_key));
    free(temp_key);
    *k = end_of_key - 1;
}

static void found_dollar(t_minibox *minibox, int quote_s, int *k, char cur_c)
{
    int     old_qoute_s;
    
    old_qoute_s = quote_s;
    (*k)++;
    cur_c = minibox->input_quoted[*k];
    if (cur_c != '\0')
    {
        update_qoute_state(&quote_s, cur_c);
        if (quote_s != old_qoute_s)
            append_str(minibox, ft_chr2str(cur_c));
        else if (cur_c == '?')
            append_str(minibox, ft_itoa(minibox->executor.exit_status));
        else if (cur_c == NO_SPACE || ft_isspace(cur_c))
            append_str(minibox, "$ ");//TODO: we this fixes the "echo      $    ?" double space issue; we need to chek again why we had it there before removeing it!!!
        else if (ft_isalnum(cur_c) || cur_c == ' ')
            found_key(minibox, k);
        else if(cur_c == '\'' || cur_c == '"')
            append_str(minibox, ft_strjoin(ft_chr2str('$'), ft_chr2str(cur_c))); //FIXME: this shit is gonna leak as fuck
    }
    else
        append_str(minibox, ft_chr2str('$'));
}

/*
	traverses through the input string, locates all the variable
	names checking for a dollar sign, then replaces all the variable names
    by their values which are received from the environment
*/
void	expand_variables(t_minibox *minibox, int k, int k_end, int quote_state)
{
    char    *cur_key;
    char    *cur_value;
    char    cur_char;
    int     old_qoute_state;
    int     end_of_key;
    char    *temp_key;
    
    temp_key = NULL;
    minibox->input_expanded = NULL;
    while (minibox->input_quoted[k])
    {
        cur_char = minibox->input_quoted[k];
        update_qoute_state(&quote_state, cur_char);
        if (quote_state != add_offset('\'') && cur_char == '$')
            found_dollar(minibox, quote_state, &k, cur_char);
        else
           append_str(minibox, ft_chr2str(cur_char));
        k++;
    }
}
