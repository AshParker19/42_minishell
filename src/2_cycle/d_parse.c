/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 16:16:49 by astein            #+#    #+#             */
/*   Updated: 2023/12/17 18:41:32 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "frankenshell.h"

/**
 * @brief   takes the ll of tokens abd builds an AST of it using BNF notaion:
 * 
 *			<job>          : <command> '|' <job>    
 *			               | <command>              
 *			               ;
 *
 *			<command>      : <token list>           
 *			               ;
 *
 *			<token list>   : [name]  <token list>   
 *			               | [arg]   <token list>   
 *			               | <redir> <token list>   
 *			               ;
 *
 *			<redir>        : <redir in> 
 *			               | <redir out>
 *			               ;
 *
 *			<redir in>     : '<<' [file]
 *			               | '<'  [file]
 *			               ;
 *
 *			<redir out>    : '>>' [file]
 *			               | '>'  [file]
 *			               ;
 * 			
 * 			this BNF form was taken from Gabriel Tocha
 * 										(https://github.com/portugueseTorch)
 * 			Thank you Gabriel for your help!
 * 
 * @param   mbox 
 * @return  t_bool 
 */
t_bool	parse(t_mbox *mbox)
{
	info_put_banner(mbox, "PARSER", NULL, CYAN);
	mbox->tmp_token = mbox->tokens;
	mbox->ast = job_main(mbox);
	if (mbox->tmp_token)
		create_syntax_err(mbox, mbox->tmp_token);
	info_print_parser(mbox, CYAN);
	if (mbox->error_status)
		return (ft_false);
	return (ft_true);
}
