/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 16:38:32 by anshovah          #+#    #+#             */
/*   Updated: 2023/10/09 17:46:23 by anshovah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_parser_output(t_minibox *minibox);

// dealing with everything thats before exection
void	manage_input(t_minibox *minibox)
{
    minibox->error_status = false;
    add_history(minibox->input_original);
    // printf ("minibox->input_original:\t%s\n", minibox->input_original);
    minibox->input_trimmed = ft_strtrim(minibox->input_original, " \n\t\v");
    // printf ("minibox->input_trimmed:\t\t%s\n", minibox->input_trimmed);
    mark_seps(minibox, 0, 0);
    // printf ("minibox->input_quoted:\t\t%s\n", minibox->input_quoted);
    expand_variables(minibox, 0, 0, OUT_Q);
    printf ("minibox->input_expanded:\t%s\n", minibox->input_expanded);
    if (ft_strlen(minibox->input_expanded) != 0)
    {
        if(ft_strcmp_strict("exit", minibox->input_expanded))
        // if (ft_strlen(minibox->input_expanded) == 4 && !ft_strncmp(minibox->input_expanded, "exit", 4))
        {
            printf("Bye Bye fuckers!\n");
            // Deal with exit status!
            free_and_close_box(minibox, -1);
        }
    }
    tokenize(minibox, 0);
    parse(minibox);
    print_parser_output(minibox);
    if (minibox->error_status == false)
    {
        print_executor_output(minibox, 0); 
        execute(minibox);
        print_executor_output(minibox, 1); 
    }
    free_cycle(minibox);
}
