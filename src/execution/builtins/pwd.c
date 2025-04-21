/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhaber <nhaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 23:24:32 by nhaber            #+#    #+#             */
/*   Updated: 2025/04/21 18:10:58 by nhaber           ###   ########.fr       */
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
		ft_putstr_fd("pwd: usage: pwd\n", 2);
		return ;
	}
	if (getcwd(cwd, sizeof(cwd)))
		printf("%s\n", cwd);
	else
		perror("getcwd failed");
}

// static char	*ft_get_oldpwd(void)
// {
// 	return (getenv("OLDPWD"));
// }
