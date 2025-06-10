/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabi-nak <mabi-nak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 23:24:32 by nhaber            #+#    #+#             */
/*   Updated: 2025/06/09 13:39:06 by mabi-nak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"
#include <stdlib.h>

void	ft_pwd(char **args)
{
	char	cwd[1024];

	if (args[1] && args[1][0] == '-')
	{
		ft_putstr_fd("bash: pwd: invalid option\n", 2);
		return ;
	}
	if (getcwd(cwd, sizeof(cwd)))
		printf("%s\n", cwd);
	else
		perror("getcwd failed");
}
