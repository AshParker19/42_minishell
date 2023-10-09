/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_tester.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 18:13:31 by astein            #+#    #+#             */
/*   Updated: 2023/10/09 17:24:39 by anshovah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void test_builtins(t_minibox *minibox)
{
    printf("TEST ECHO\n---\n\n");
    builtin_echo("");
    builtin_echo("Hello World");
    builtin_echo("Hello 42");

    printf("TEST CD\n---\n\n");
    printf("NO TEST MADE YET!\n");

    printf("TEST EXPORT\n---\n\n");
    builtin_export(minibox, "AleX=AnatoliI");

    printf("TEST ENV\n---\n\n");
    builtin_env(minibox);

    printf("TEST PWD\n---\n\n");
    builtin_pwd();

    printf("TEST UNSET\n---\n\n");
    builtin_unset(minibox, "AleX");
    builtin_unset(minibox, "PAGER");
    builtin_unset(minibox, "GJS_DEBUG_TOPICS=JS");   //FIXME: DELETE FIRST NODE DOESNT WORK YET!
    builtin_unset(minibox, "askjdkasdasdkasdkasdkasdmas");
    
    printf("TEST ENV\n---\n\n");
    builtin_env(minibox);

    printf("TEST EXIT\n---\n\n");
    printf("NO TEST MADE YET!\n");
}
