/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_tester.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 18:13:31 by astein            #+#    #+#             */
/*   Updated: 2023/10/11 18:59:21 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void test_builtins(t_minibox *minibox)
{
    char *s;
    
    put_header("X", "TEST ECHO");
    
    s = "HELLO WORLD";
    printf("\nTEST: >%s<\n", s);
    builtin_echo(s);
    
    s = "HELLO\nWORLD";
    printf("\nTEST: >%s<\n", s);
    builtin_echo(s);

    s = "NEXT ONE IS EMPTY";
    printf("\nTEST: >%s<\n", s);
    builtin_echo(s);

    s = NULL;
    printf("\nTEST: >%s<\n", s);
    builtin_echo(s);

    s = "ECHO DONE!";
    printf("\nTEST: >%s<\n", s);
    builtin_echo(s);
    
    
    
    put_header("X", "TEST CD\n---\n\n");
    
    s = "/nfs/homes/";
    printf("\nTEST: >%s<\n", s);
    builtin_cd(minibox, s);
    printf("PDW\t=%s\n",get_var(minibox, "PWD"));
    printf("OLDPDW\t=%s\n",get_var(minibox, "OLDPWD"));
    
    s = ".";
    printf("\nTEST: >%s<\n", s);
    builtin_cd(minibox, s);
    printf("PDW\t=%s\n",get_var(minibox, "PWD"));
    printf("OLDPDW\t=%s\n",get_var(minibox, "OLDPWD"));

    s = "..";
    printf("\nTEST: >%s<\n", s);
    builtin_cd(minibox, s);
    printf("PDW\t=%s\n",get_var(minibox, "PWD"));
    printf("OLDPDW\t=%s\n",get_var(minibox, "OLDPWD"));

    s = NULL;
    printf("\nTEST: >%s<\n", s);
    builtin_cd(minibox, s);
    printf("PDW\t=%s\n",get_var(minibox, "PWD"));
    printf("OLDPDW\t=%s\n",get_var(minibox, "OLDPWD"));
    
    s = "Downloads";
    printf("\nTEST: >%s<\n", s);
    builtin_cd(minibox, s);
    printf("PDW\t=%s\n",get_var(minibox, "PWD"));
    printf("OLDPDW\t=%s\n",get_var(minibox, "OLDPWD"));

    
    s = "~";
    printf("\nTEST: >%s<\n", s);
    builtin_cd(minibox, s);
    printf("PDW\t=%s\n",get_var(minibox, "PWD"));
    printf("OLDPDW\t=%s\n",get_var(minibox, "OLDPWD"));

    s = "..";
    printf("\nTEST: >%s<\n", s);
    builtin_cd(minibox, s);
    printf("PDW\t=%s\n",get_var(minibox, "PWD"));
    printf("OLDPDW\t=%s\n",get_var(minibox, "OLDPWD"));


    // put_header("X", "TEST EXPORT\n---\n\n");
    // builtin_export(minibox, "AleX=AnatoliI");

    // put_header("X", "TEST ENV\n---\n\n");
    // builtin_env(minibox, NULL);
    // builtin_env(minibox, "NULL");

    // put_header("X", "TEST PWD\n---\n\n");
    // builtin_pwd(NULL);
    // builtin_pwd("NULL");

    // put_header("X", "TEST UNSET\n---\n\n");
    // builtin_unset(minibox, "AleX");
    // builtin_unset(minibox, "PAGER");
    // builtin_unset(minibox, "GJS_DEBUG_TOPICS=JS");   //FIXME: DELETE FIRST NODE DOESNT WORK YET!
    // builtin_unset(minibox, "askjdkasdasdkasdkasdkasdmas");
    
    // put_header("X", "TEST ENV\n---\n\n");
    // builtin_env(minibox, NULL);

    // put_header("X", "TEST EXIT\n---\n\n");
    // put_header("X", "NO TEST MADE YET!\n");
}
