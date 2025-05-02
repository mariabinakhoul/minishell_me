/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhaber <nhaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 19:04:45 by nhaber            #+#    #+#             */
/*   Updated: 2025/05/02 13:45:10 by nhaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void reset_sig(int signo)
{
    (void) signo;
    write(STDIN_FILENO, "\n", 1);
    rl_on_new_line();
    rl_replace_line("",1);
    rl_redisplay();
}

void set_signals()
{
    signal(SIGINT,reset_sig);
    signal(SIGQUIT,SIG_IGN);
}

void def_signals()
{
    signal(SIGQUIT,SIG_DFL);
    signal(SIGINT,SIG_DFL);
}

void ignore_signals()
{
    signal(SIGQUIT,SIG_IGN);
    signal(SIGINT,SIG_IGN);
}


void handle_signal(int sig)
{
    if (sig == SIGINT)
    {
        write(1, "\n", 1);
        exit_code = 130;
    }
    else if (sig == SIGQUIT)
    {
        write(1, "Quit (core dumped)\n", 20);
        exit_code = 131;
    }
}