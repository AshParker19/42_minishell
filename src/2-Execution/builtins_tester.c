/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_tester.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 18:13:31 by astein            #+#    #+#             */
/*   Updated: 2023/09/29 18:56:27 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void test_builtins(t_minibox *minibox)
{
    printf("TEST ECHO\n---\n\n");
    bultin_echo("");
    bultin_echo("Hello World");
    bultin_echo("Hello 42");

    printf("TEST CD\n---\n\n");
    printf("NO TEST MADE YET!\n");

    printf("TEST EXPORT\n---\n\n");
    bultin_export(minibox, "AleX=AnatoliI");

    printf("TEST ENV\n---\n\n");
    bultin_env(minibox);

    printf("TEST PWD\n---\n\n");
    builtin_pwd();

    printf("TEST UNSET\n---\n\n");
    bultin_unset(minibox, "AleX");
    bultin_unset(minibox, "PAGER");
    bultin_unset(minibox, "GJS_DEBUG_TOPICS=JS");   //FIXME: DELETE FIRST NODE DOESNT WORK YET!
    bultin_unset(minibox, "askjdkasdasdkasdkasdkasdmas");
    
    printf("TEST ENV\n---\n\n");
    bultin_env(minibox);

    printf("TEST EXIT\n---\n\n");
    printf("NO TEST MADE YET!\n");
}
