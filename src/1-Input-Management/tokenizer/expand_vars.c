/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_vars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 12:58:49 by anshovah          #+#    #+#             */
/*   Updated: 2023/10/28 14:50:22 by astein           ###   ########.fr       */
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



/**
 * @brief	this function loops trough a string and sets all characters
 * 			which are whitespaces to NO_SPACE
 * 
 * 			the parameter 'str' will be freed!
 * 
 * @param	str		
 * @return	char*	the string with all spaces marked as NO_SPACE
 */
static	char *mark_ws(char *str)
{
	int		i;
	char	*temp;

	temp = NULL;
	i = -1;

	while (str[++i])
	{
		if (ft_isspace(str[i]))
			temp = append_str(temp, ft_chr2str(NO_SPACE), ft_true);
		else
			temp = append_str(temp, ft_chr2str(str[i]), ft_true);
	}
	free(str);
	return(temp);
}

//TODO: make it less hard code so we can use it in herdoc
static void found_key(t_mbox *mbox, int quote_s, int *k)
{
    int     end_of_key;
    char    *temp_key;
	char	*temp_value;
    
    end_of_key = *k;
    while (mbox->inp_shift[end_of_key]
            && (ft_isalnum(mbox->inp_shift[end_of_key])
            || mbox->inp_shift[end_of_key] == '_'))
                end_of_key++;
    temp_key = ft_substr(mbox->inp_shift, *k, end_of_key - *k);
	// A="ls    -l"
	// IF THE KEY IS INSIDE OF QOUTES WE DONT CHANGE WHITESPACES
	// 			echo "HI $A LOL"	-> HI ls     -l LOL
	// IF THE KEY IS OUTSIDE OF QQOUTES WE REMOVE WS
	// 			$A | wc				-> ls -l | wc	-> 42 0 0
	temp_value = ft_strdup(get_var_value(mbox, temp_key));
	if (quote_s == OUT_Q)
		temp_value = mark_ws(temp_value);
	mbox->inp_expand = append_str(mbox->inp_expand, temp_value , ft_true);
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
        else if (cur_c == '?')
            mbox->inp_expand = append_str(mbox->inp_expand, get_var_value(mbox, "?"), ft_false);
        else if (cur_c == NO_SPACE || ft_isspace(cur_c))
            mbox->inp_expand = append_str(mbox->inp_expand, "$", ft_false);
        else if (ft_isalnum(cur_c) || cur_c == ' ')
            found_key(mbox, quote_s, k);
        else if(cur_c == '\'' || cur_c == '"')
        {
            mbox->inp_expand = append_str(mbox->inp_expand, "$", ft_false);
            mbox->inp_expand = append_str(mbox->inp_expand, ft_chr2str(cur_c), ft_true);
        }
    }
    else
        mbox->inp_expand = append_str(mbox->inp_expand, ft_chr2str('$'), ft_true);
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
        }
        else
        {
            if (quote_state != add_offset('\'') && cur_char == '$') 
                found_dollar(mbox, quote_state, &k, cur_char);
            else
            mbox->inp_expand = append_str(mbox->inp_expand, ft_chr2str(cur_char), ft_true);
        }
        k++;
    }
}
