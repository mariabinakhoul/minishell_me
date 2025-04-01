/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhaber <nhaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 23:24:32 by nhaber            #+#    #+#             */
/*   Updated: 2025/04/01 23:52:06 by nhaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"
#include <stdlib.h>

void ft_pwd()
{
    char cwd[100000];

    if (getcwd(cwd, sizeof(cwd)))
        printf("%s\n", cwd);
    else
        perror("getcwd failed");
}

char *ft_get_oldpwd(void)
{
    return getenv("OLDPWD");
}
