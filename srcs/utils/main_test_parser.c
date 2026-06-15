/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test_parser.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ragolden <ragolden@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/10 06:26:08 by adchebbi          #+#    #+#             */
/*   Updated: 2026/06/10 11:09:47 by ragolden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static const char	*redir_name(t_redir_type t)
{
	if (t == R_IN)
		return ("<");
	if (t == R_OUT)
		return (">");
	if (t == R_APPEND)
		return (">>");
	return ("<<");
}

static void	print_cmds(t_cmd *c)
{
	int		i;
	int		n;
	t_redir	*r;

	n = 1;
	while (c)
	{
		printf("CMD %d\n  args  : ", n++);
		i = 0;
		while (c->args && c->args[i])
			printf("[%s] ", c->args[i++]);
		if (!c->args)
			printf("(aucun)");
		printf("\n  redirs: ");
		r = c->redirs;
		if (!r)
			printf("(aucune)");
		while (r)
		{
			printf("{%s -> %s} ", redir_name(r->type), r->target);
			r = r->next;
		}
		printf("\n");
		c = c->next;
	}
}

static char	**dup_argv(int argc, char **argv)
{
	char	**arr;
	int		i;

	arr = malloc(sizeof(char *) * argc);
	if (!arr)
		return (NULL);
	i = 1;
	while (i < argc)
	{
		arr[i - 1] = ft_strdup(argv[i]);
		i++;
	}
	arr[argc - 1] = NULL;
	return (arr);
}

int	main(int argc, char **argv)
{
	char	**words;
	t_token	*toks;
	t_cmd	*cmds;
	int		err;

	if (argc < 2)
		return (printf("usage: %s mot \"|\" mot \">\" fichier...\n",
				argv[0]), 0);
	words = dup_argv(argc, argv);
	toks = lexer(words);
	free(words);
	err = 0;
	cmds = parse(toks, &err);
	clear_token(&toks);
	if (!cmds)
		return (printf("-> parse a renvoyé NULL (err_status=%d)\n", err), err);
	print_cmds(cmds);
	cmds_free(cmds);
	return (0);
}
