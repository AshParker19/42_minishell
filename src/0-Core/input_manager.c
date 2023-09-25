/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 16:38:32 by anshovah          #+#    #+#             */
/*   Updated: 2023/09/25 18:48:51 by anshovah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
        1. trim readline (begin end)
        2. expand the vars (considering contexet quotes)
        3. check if stringlen = 0 (->no can do but add to history (trimmed))
        4. check for exit
        5. tokenize (look for swp
        6. parse into binary tree
        7. execv
        	- 1. pipes
        	- 2. fork
        		- 3. redirection in child
*/

// dealing with everything thats before exection
void	manage_input(t_minibox *minibox)
{
    add_history(minibox->input_original);
    printf ("minibox->input_original:%s\n", minibox->input_original);
    minibox->input_trimmed = ft_strtrim(minibox->input_original, " \n\t\v");
    printf ("minibox->input_trimmed:%s\n", minibox->input_trimmed);
    expand_variables(minibox, -1, 0);
    printf ("minibox->input_expanded:%s\n", minibox->input_expanded);
    if (ft_strlen(minibox->input_expanded) != 0)
    {
        if (ft_strlen(minibox->input_expanded) == 4 && !ft_strncmp(minibox->input_expanded, "exit", 4))
        {
            printf("Bye Bye fuckers!\n");
            //TODO: Deal with exit satus!
            free_and_close_box(minibox, -1);
        }
        tokenize(minibox);
        parse(minibox);
    }

    // somehow call something to execute everything

    // free
    //  input_original, input_trimmed, input_expanded, .....
    free_input_strings(minibox);
    free_matrix(minibox, -1);
    
}
