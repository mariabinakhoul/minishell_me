/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabi-nak <mabi-nak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 23:24:32 by nhaber            #+#    #+#             */
/*   Updated: 2025/04/01 11:51:06 by mabi-nak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"
#include <stdlib.h>

void ft_pwd()
{
    char cwd[1024];

    if (getcwd(cwd, sizeof(cwd)))
        printf("%s\n", cwd);
    else
        perror("getcwd failed");
}

char *ft_get_oldpwd(void)
{
    return getenv("OLDPWD");
}
