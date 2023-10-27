// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   builtins_tester.c                                  :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: astein <astein@student.42.fr>              +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2023/09/29 18:13:31 by astein            #+#    #+#             */
// /*   Updated: 2023/10/11 18:59:21 by astein           ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "minishell.h"

// void test_builtins(t_mbox *mbox)
// {
//     char *s;
    
//     put_header("X", "TEST ECHO");
    
//     s = "HELLO WORLD";
//     printf("\nTEST: >%s<\n", s);
//     builtin_echo(s);
    
//     s = "HELLO\nWORLD";
//     printf("\nTEST: >%s<\n", s);
//     builtin_echo(s);

//     s = "NEXT ONE IS EMPTY";
//     printf("\nTEST: >%s<\n", s);
//     builtin_echo(s);

//     s = NULL;
//     printf("\nTEST: >%s<\n", s);
//     builtin_echo(s);

//     s = "ECHO DONE!";
//     printf("\nTEST: >%s<\n", s);
//     builtin_echo(s);
    
    
    
//     put_header("X", "TEST CD\n---\n\n");
    
//     s = "/nfs/homes/";
//     printf("\nTEST: >%s<\n", s);
//     builtin_cd(mbox, s);
//     printf("PDW\t=%s\n",get_var(mbox, "PWD"));
//     printf("OLDPDW\t=%s\n",get_var(mbox, "OLDPWD"));
    
//     s = ".";
//     printf("\nTEST: >%s<\n", s);
//     builtin_cd(mbox, s);
//     printf("PDW\t=%s\n",get_var(mbox, "PWD"));
//     printf("OLDPDW\t=%s\n",get_var(mbox, "OLDPWD"));

//     s = "..";
//     printf("\nTEST: >%s<\n", s);
//     builtin_cd(mbox, s);
//     printf("PDW\t=%s\n",get_var(mbox, "PWD"));
//     printf("OLDPDW\t=%s\n",get_var(mbox, "OLDPWD"));

//     s = NULL;
//     printf("\nTEST: >%s<\n", s);
//     builtin_cd(mbox, s);
//     printf("PDW\t=%s\n",get_var(mbox, "PWD"));
//     printf("OLDPDW\t=%s\n",get_var(mbox, "OLDPWD"));
    
//     s = "Downloads";
//     printf("\nTEST: >%s<\n", s);
//     builtin_cd(mbox, s);
//     printf("PDW\t=%s\n",get_var(mbox, "PWD"));
//     printf("OLDPDW\t=%s\n",get_var(mbox, "OLDPWD"));

    
//     s = "~";
//     printf("\nTEST: >%s<\n", s);
//     builtin_cd(mbox, s);
//     printf("PDW\t=%s\n",get_var(mbox, "PWD"));
//     printf("OLDPDW\t=%s\n",get_var(mbox, "OLDPWD"));

//     s = "..";
//     printf("\nTEST: >%s<\n", s);
//     builtin_cd(mbox, s);
//     printf("PDW\t=%s\n",get_var(mbox, "PWD"));
//     printf("OLDPDW\t=%s\n",get_var(mbox, "OLDPWD"));


//     // put_header("X", "TEST EXPORT\n---\n\n");
//     // builtin_export(mbox, "AleX=AnatoliI");

//     // put_header("X", "TEST ENV\n---\n\n");
//     // builtin_env(mbox, NULL);
//     // builtin_env(mbox, "NULL");

//     // put_header("X", "TEST PWD\n---\n\n");
//     // builtin_pwd(NULL);
//     // builtin_pwd("NULL");

//     // put_header("X", "TEST UNSET\n---\n\n");
//     // builtin_unset(mbox, "AleX");
//     // builtin_unset(mbox, "PAGER");
//     // builtin_unset(mbox, "GJS_DEBUG_TOPICS=JS");   //FIXME: DELETE FIRST NODE DOESNT WORK YET!
//     // builtin_unset(mbox, "askjdkasdasdkasdkasdkasdmas");
    
//     // put_header("X", "TEST ENV\n---\n\n");
//     // builtin_env(mbox, NULL);

//     // put_header("X", "TEST EXIT\n---\n\n");
//     // put_header("X", "NO TEST MADE YET!\n");
// }
