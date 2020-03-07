/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efischer <efischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 14:08:44 by efischer          #+#    #+#             */
/*   Updated: 2020/03/07 17:02:03 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <limits.h>
#include <unistd.h>
#include <stdlib.h>

#include <readline/readline.h>
#include <readline/history.h>

#include "libft.h"
#include "shell.h"
#include "error.h"

extern char	**environ;
t_list		*g_env;

void	astdel(t_ast **ast)
{
	if (*ast != NULL)
	{
		ft_lstdel(&(*ast)->content, del);
		if ((*ast)->left != NULL)
			astdel((t_ast**)&(*ast)->left);
		if ((*ast)->right != NULL)
			astdel((t_ast**)&(*ast)->right);
		free(*ast);
		*ast = NULL;
	}
}

int	exec_input(char *input)
{
	t_ast			*ast;
	volatile int	status;

	status = 0;
	ast = NULL;
	lexer(input, &ast);
	debug_ast(ast);
	if (ast != NULL)
	{
	//	expansions(ast);
		if (parser(ast) == EXIT_FAILURE)
			ft_putendl_fd("\nParse error", 2);
		else
		{
/*			ft_putendl("\nOK");
*/			ast_order(&ast);
			debug_ast(ast);
			status = execute_node(ast, 1); /* to capture */
		}
	}
/*	ft_lstdel(&lst, del);*/
	astdel(&ast);
	ft_strdel(&input);
	g_retval = status;
	do_job_notification();
	return (status);
}

int			main(int argc, char **argv)
{
	char			*input;

	(void)argc;
	(void)argv;
	g_progname = argv[0];
	if (init_shell())
		return (EXIT_FAILURE);
	if (!(g_hash_table = ft_memalloc(sizeof(*g_hash_table) * HASH_SIZE)))
		return (EXIT_FAILURE);
	if (!(environ = ft_tabcpy(environ)))
	{
		psherror(e_cannot_allocate_memory, argv[0], e_cmd_type);
		return (1);
	}
	get_env_list(environ);
//	ft_lstprint(g_env, &print_env);
	g_retval = e_success;
	if ((g_retval = set_minimal_env()))
	{
		psherror(g_retval, argv[0], e_cmd_type);
		ft_tabdel(&environ);
		return (1);
	}
	while (21)
	{
		//if (!(input = ft_readline("\e[38;5;44m21sh$ \e[0m")))
		if (!(input = ft_readline("$> ")))
		{
			ft_printf("\nKICCCCCCKKKK OOOOOOFFFFFF\n\n");
			break ;
		}
		exec_input(input);
	}
	free_hash_table();
	ft_tabdel(&environ);
/* Useless free functions, shell quits before in exit builtin */
	ft_lstdel(&g_env, &del_env);
	return (EXIT_SUCCESS);
}
