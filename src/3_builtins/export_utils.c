/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 14:44:15 by anshovah          #+#    #+#             */
/*   Updated: 2023/12/15 14:16:57 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "frankenshell.h"

// check if first char is alpha or _
// check if all other chars are alphanum including _
/**
 * @brief   checks if the 'key' is valid
 *          - can't be NULL
 *          - the first char has to be alpha or '_'
 *          - the rest has to alphanum or '_'
 * 
 * @param   key 
 * @return  t_bool 
 */
static t_bool	validate_key(char *key)
{
	if (!key)
		return (ft_false);
	if (key[0] != '_' && !ft_isalpha(key[0]))
		return (ft_false);
	key++;
	while (*key)
	{
		if (*key != '_' && !ft_isalnum(*key))
			return (ft_false);
		key++;
	}
	return (ft_true);
}

void	case_equal_sign(t_mbox *mbox, t_ast *arg_node,
	t_bool *fnd_err, char *equal_sign)
{
	char	*key;
	char	*value;

	key = ft_substr(arg_node->content, 0,
			ft_strlen(arg_node->content) - ft_strlen(equal_sign));
	value = ft_substr(equal_sign, 1, ft_strlen(equal_sign) - 1);
	if (validate_key(key))
		set_var_value(mbox, key, value);
	else
	{
		err_msg(mbox, NO_EXIT_STATUS, "nnnnnn", ERR_P, "export: `",
			arg_node->content, SQ, CS, NO_VI);
		*fnd_err = ft_false;
	}
	free_whatever("pp", key, value);
}

void	case_no_equal_sign(t_mbox *mbox, t_ast *arg_node, t_bool *fnd_err)
{
	if (!validate_key(arg_node->content))
	{
		err_msg(mbox, NO_EXIT_STATUS, "nnnnnn", ERR_P, "export: `",
			arg_node->content, SQ, CS, NO_VI);
		*fnd_err = ft_false;
	}
}
