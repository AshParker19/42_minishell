/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_mbox.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 16:49:13 by anshovah          #+#    #+#             */
/*   Updated: 2023/10/28 14:37:07 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	initialize_box(t_mbox *mbox, char **env)
{
	mbox->env = env;
	mbox->vars = NULL;
	mbox->inp_orig = NULL;
	mbox->inp_trim = NULL;
	mbox->inp_shift = NULL;
	mbox->inp_expand = NULL;
	mbox->error_status = false;
	mbox->tokens = NULL;
	mbox->root = NULL;
	mbox->tmp_token = NULL;
	mbox->tmp_node = NULL;
}
// void	free_matrix(char **matrix, int i)
// {
// 	if (matrix)
// 	{
// 		while (matrix[++i])
// 			free (matrix[i]);
// 		free (matrix);		
// 	}
// }

void free_input_strings(t_mbox *mbox)
{
	if (mbox->inp_orig)
		free(mbox->inp_orig);
	if (mbox->inp_trim)
		free(mbox->inp_trim);
	if (mbox->inp_shift)
		free (mbox->inp_shift);
	if (mbox->inp_expand)
		free(mbox->inp_expand);
}

void free_tokens(t_mbox *mbox)
{
	t_token *cur;

	while(mbox->tokens)
	{
		cur = mbox->tokens;
		mbox->tokens = mbox->tokens->next;
		free(cur->value);
		free(cur);
	}
	mbox->tokens = NULL;
}

void free_cycle(t_mbox *mbox)
{
    free_input_strings(mbox);    
    free_tokens(mbox);
    mbox->tokens = NULL;
    delete_ast(mbox->root);
    mbox->root = NULL;
	free_process(mbox);
	if (mbox->executor.pid)
	{
		free (mbox->executor.pid);
		mbox->executor.pid = NULL;
	}
	dbg_printf(no_block, "FREED CYCLE READY TO GO AGAIN!\n");
}

// TODO:
// Function should check all members of the mbox struct 
// and frees them if they are inizialised
// exits program
void free_and_close_box(t_mbox *mbox)
{
	int	exit_status;
	
	exit_status = ft_atoi(get_var_value(mbox, "?"));
	free_input_strings(mbox);
	free_tokens(mbox);
	delete_ast(mbox->root);
	free_vars(mbox);
	free_executor(mbox);
    exit(exit_status);
}
