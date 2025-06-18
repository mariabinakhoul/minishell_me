/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_alpha2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabi-nak <mabi-nak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 15:40:52 by mabi-nak          #+#    #+#             */
/*   Updated: 2025/06/18 16:41:46 by mabi-nak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	process_tokens(t_chain **tokens, t_ast *cmd_node,
	int *param_count, char **env)
{
	while (*tokens && (*tokens)->type != TYPE_PIPE)
	{
		if (((*tokens)->type == TYPE_INDIR) || (*tokens)->type == TYPE_OUTDIR
			|| (*tokens)->type == TYPE_APPEND
			|| (*tokens)->type == TYPE_HEREDOC)
		{	
			if (parse_redirection(tokens, cmd_node, env) == -1)
			{
				cmd_node->exit = 2;
				return ;
			}
		}
		else
		{
			if (!(cmd_node->value))
				cmd_node->value = ft_strdup((*tokens)->value);
			expand_params_and_lexer(cmd_node, *tokens, param_count);
			(*param_count)++;
			cmd_node->params[*param_count] = NULL;
			*tokens = (*tokens)->next;
		}
	}
}

void	init_cmd_node(t_ast *cmd_node, int *param_count)
{
	cmd_node->type = CMD;
	cmd_node->params = NULL;
	cmd_node->value = NULL;
	cmd_node->heredoc_delim = NULL;
	cmd_node->in_file = NULL;
	cmd_node->out_file = NULL;
	cmd_node->append = 0;
	cmd_node->right = NULL;
	cmd_node->left = NULL;
	cmd_node->tree_link = NULL;
	cmd_node->exit = 0;
	cmd_node->lexer = NULL;
	cmd_node->heredoc = 0;
	*param_count = 0;
}

t_ast	*parse_command(t_chain **tokens, char **env)
{
	t_ast	*cmd_node;
	int		param_count;

	if ((!(*tokens)) || (*tokens)->type == TYPE_PIPE)
		return (NULL);
	cmd_node = malloc(sizeof(t_ast));
	if (!cmd_node)
		return (NULL);
	init_cmd_node(cmd_node, &param_count);
	process_tokens(tokens, cmd_node, &param_count, env);
	if (!cmd_node->value)
	{
		free_ast(cmd_node);
		return (NULL);
	}
	return (cmd_node);
}

void	heredoc_handler(t_ast *cmd_node, t_chain *token, char **env)
{
	int		pipefd[2];
	pid_t	pid;
	int		status;

	(void)token;
	pipe(pipefd);
	pid = fork();
	if (pid == -1)
		exit (0);
	if (pid == 0)
	{
		ft_heredoc(cmd_node->heredoc_delim, pipefd[1], env);
		close(pipefd[1]);
		exit(0);
	}
	waitpid(pid, &status, 0);
	close(pipefd[1]);
	cmd_node->here_doc_in = pipefd[0];
}

int	handle_input_redirection(t_ast *cmd_node, t_chain *token, char *filename,
	char **env)
{
	if (token->type == TYPE_INDIR)
	{
		if (cmd_node->in_file)
			free(cmd_node->in_file);
		cmd_node->in_file = filename;
	}
	else if (token->type == TYPE_HEREDOC)
	{
		if (cmd_node->heredoc_delim)
			free(cmd_node->heredoc_delim);
		cmd_node->heredoc = true;
		cmd_node->heredoc_delim = filename;
		heredoc_handler(cmd_node, token, env);
	}
	return (0);
}
