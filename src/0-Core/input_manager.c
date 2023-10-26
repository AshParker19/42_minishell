/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 16:38:32 by anshovah          #+#    #+#             */
/*   Updated: 2023/10/26 19:53:25 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_parser_output(t_minibox *minibox);

// dealing with everything thats before exection
void	manage_input(t_minibox *minibox)
{
    minibox->error_status = false;
    add_history(minibox->inp_orig);
    printf("minibox->input_original:\t(%s)\n", minibox->inp_orig);
    minibox->input_trimmed = ft_strtrim(minibox->inp_orig, " \n\t\v");
    printf("minibox->input_trimmed:\t\t(%s)\n", minibox->input_trimmed);
    mark_seps(minibox, 0, 0);
    printf("minibox->input_quoted:\t\t(%s)\n", minibox->input_quoted);
    expand_variables(minibox, 0, 0, OUT_Q);
    printf("minibox->input_expanded:\t(%s)\n", minibox->input_expanded);
    if (*minibox->input_expanded == '\0')
    {
            free_cycle(minibox);
            return ;
    }
    tokenize(minibox, 0); // TODO: we dont check if it returns error
    parse(minibox);
    if (minibox->root->type == CMD_NODE && ft_strcmp_strict(minibox->root->content, "exit"))
        builtin_exit(minibox, minibox->root->right);
    print_parser_output(minibox);
    if (minibox->error_status == false)
    {
        print_executor_output(minibox, 0);
        execute(minibox);
        print_executor_output(minibox, 1); 
    }
    free_cycle(minibox);
}
