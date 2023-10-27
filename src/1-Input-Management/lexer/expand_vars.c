/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_vars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 12:58:49 by anshovah          #+#    #+#             */
/*   Updated: 2023/10/27 15:13:16 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

//TODO: RESTURCTURE IT AND MOVE IT INTO LIBFT
// LOOK AT HERDOC FILE THERE IS A BETTER VERSION
// static void appppppend_str(t_mbox *mbox, char *add_str)
// {
//     char    *temp;

//     temp =  ft_strcat_multi(2, mbox->input_expanded, add_str);
//     free(mbox->input_expanded);
//     mbox->input_expanded = temp;
// }

//TODO: make it less hard code so we can use it in herdoc
static void found_key(t_mbox *mbox, int *k)
{
    int     end_of_key;
    char    *temp_key;
    
    end_of_key = *k;
    while (mbox->inp_shift[end_of_key]
            && (ft_isalnum(mbox->inp_shift[end_of_key])
            || mbox->inp_shift[end_of_key] == '_'))
                end_of_key++;
    temp_key = ft_substr(mbox->inp_shift, *k, end_of_key - *k);
    mbox->inp_expand = append_str(mbox->inp_expand, get_var_value(mbox, temp_key), ft_false);
    // appppppend_str(mbox, get_var_value(mbox, temp_key));
    free(temp_key);
    *k = end_of_key - 1;
}

static void found_dollar(t_mbox *mbox, int quote_s, int *k, char cur_c)
{
    int     old_qoute_s;
    
    old_qoute_s = quote_s;
    (*k)++;
    cur_c = mbox->inp_shift[*k];
    if (cur_c != '\0')
    {
        update_qoute_state(&quote_s, cur_c);
        if (quote_s != old_qoute_s)
            mbox->inp_expand = append_str(mbox->inp_expand, ft_chr2str(cur_c), ft_true);
            // appppppend_str(mbox, ft_chr2str(cur_c));
        else if (cur_c == '?')
            mbox->inp_expand = append_str(mbox->inp_expand, ft_itoa(mbox->executor.exit_status), ft_true);
            // appppppend_str(mbox, ft_itoa(mbox->executor.exit_status));
        else if (cur_c == NO_SPACE || ft_isspace(cur_c))
            mbox->inp_expand = append_str(mbox->inp_expand, "$", ft_false);
            // appppppend_str(mbox, "$ ");//TODO: we this fixes the "echo      $    ?" double space issue; we need to chek again why we had it there before removeing it!!!
        else if (ft_isalnum(cur_c) || cur_c == ' ')
            found_key(mbox, k);
        else if(cur_c == '\'' || cur_c == '"')
        {
            mbox->inp_expand = append_str(mbox->inp_expand, "$", ft_false);
            mbox->inp_expand = append_str(mbox->inp_expand, ft_chr2str(cur_c), ft_true);
            // appppppend_str(mbox, ft_strjoin(ft_chr2str('$'), ft_chr2str(cur_c))); //FIXME: this shit is gonna leak as fuck
        }
    }
    else
        mbox->inp_expand = append_str(mbox->inp_expand, ft_chr2str('$'), ft_true);
        // appppppend_str(mbox, ft_chr2str('$'));
}

/*
	traverses through the input string, locates all the variable
	names checking for a dollar sign, then replaces all the variable names
    by their values which are received from the environment
*/
void	expand_variables(t_mbox *mbox, int k, int k_end, int quote_state)
{
    char    cur_char;
    int     consecutive_lt;

    consecutive_lt = 0;
    
    mbox->inp_expand = NULL;
    while (mbox->inp_shift[k])
    {
        cur_char = mbox->inp_shift[k];
        update_qoute_state(&quote_state, cur_char);
        if (quote_state == OUT_Q)
        {
            if (remove_offset(cur_char) == '<')
                consecutive_lt ++;
            else
                consecutive_lt = 0;
        }
        if (consecutive_lt == 2)
        {
            mbox->inp_expand = append_str(mbox->inp_expand, ft_chr2str(cur_char), ft_true);
            mbox->inp_expand = append_str(mbox->inp_expand, extract_limiter(mbox, &k, &quote_state), ft_true);
            // appppppend_str(mbox, ft_chr2str(cur_char));
            // appppppend_str(mbox, extract_limiter(mbox, &k, &quote_state));
        }
        else
        {
            if (quote_state != add_offset('\'') && cur_char == '$') 
                found_dollar(mbox, quote_state, &k, cur_char);
            else
            mbox->inp_expand = append_str(mbox->inp_expand, ft_chr2str(cur_char), ft_true);
            // appppppend_str(mbox, ft_chr2str(cur_char));    
        }
        k++;
    }
}
