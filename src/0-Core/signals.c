/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 19:30:56 by anshovah          #+#    #+#             */
/*   Updated: 2023/10/20 21:08:13 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void signal_handler(int signal, siginfo_t *info, void *context)
{
    (void)context;
    if (signal == SIGINT)
    {
        // PRINT NEW PROMT
        write(STDIN_FILENO, "\n", 1);
        write(1, PROMT, ft_strlen(PROMT));
        rl_replace_line("", 1);
    }
    else if (signal == SIGQUIT)
        exit(0);//TODO:
}

void initialize_signals()
{
    struct sigaction sa;

    sa.sa_handler = 0;
    sa.sa_flags = SA_SIGINFO | SA_NODEFER;;
    sa.sa_sigaction = signal_handler;
    sigaction(SIGQUIT, &sa, NULL);
    sigaction(SIGINT, &sa, NULL);
    if (sigaction(SIGINT, &sa, NULL) == -1) {
        perror("Error setting up signal handler");
        // return 1;
    }

}

