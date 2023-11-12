/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 18:00:32 by anshovah          #+#    #+#             */
/*   Updated: 2023/11/11 17:06:11 by anshovah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

void	builtin_header(t_mbox *mbox, t_ast *arg_node)
{
    printf (CYAN"\n        :::      ::::::::\n");
    printf (CYAN"      :+:      :+:    :+:\n");
    printf (CYAN"    +:+ +:+         +:+  \n");
    printf (CYAN"   +#+  +:+       +#+     \n");
    printf (CYAN"+#+#+#+#+#+   +#+        \n");
    printf (CYAN"     #+#    #+#         \n");  //FIXME: write to the correct fd
    printf (CYAN"    ###   ########.fr    \n\n");
    printf (YELLOW "astein\t\t" PURPLE " anshovah\n\n"RESET);
    set_var_value(mbox, "?", EXIT_STR_SUCCESS);
}
