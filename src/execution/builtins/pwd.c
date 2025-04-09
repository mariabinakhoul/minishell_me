/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabi-nak <mabi-nak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 23:24:32 by nhaber            #+#    #+#             */
/*   Updated: 2025/04/09 19:03:34 by mabi-nak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"
#include <stdlib.h>

void	ft_pwd(void)
{
	char	cwd[1024];

	if (getcwd(cwd, sizeof(cwd)))
		printf("%s\n", cwd);
	else
		perror("getcwd failed");
}

static char	*ft_get_oldpwd(void)
{
	return (getenv("OLDPWD"));
}
