/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhaber <nhaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 19:04:45 by nhaber            #+#    #+#             */
/*   Updated: 2025/04/15 20:07:55 by nhaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void reset_sig(int signo)
{
    (void) signo;
    write(1, "\n", 1);
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
