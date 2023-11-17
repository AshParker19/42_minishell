/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 16:16:49 by astein            #+#    #+#             */
/*   Updated: 2023/11/17 19:50:56 by anshovah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief   takes the ll of tokens abd builds an AST of it
 * 
 * @param   mbox 
 * @return  t_bool 
 */
t_bool	parse(t_mbox *mbox)
{
	print_parser_output(mbox, ft_true);
	mbox->tmp_token = mbox->tokens;
	mbox->root = job_main(mbox);
	if (mbox->tmp_token)
		create_syntax_err(mbox, mbox->tmp_token);
	print_parser_output(mbox, ft_false);
	if (mbox->error_status)
		return (ft_false);
	return (ft_true);
}
