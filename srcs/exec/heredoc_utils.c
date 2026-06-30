/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ragolden <ragolden@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/30 17:53:53 by ragolden          #+#    #+#             */
/*   Updated: 2026/06/30 17:55:23 by ragolden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "exec.h"

int run_heredocs_pre_exec(t_cmd *cmds, t_env *env)
{
    t_cmd   *c;
    t_redir *r;

    c = cmds;
    while (c)
    {
        r = c->redirs;
        while (r)
        {
            if (r->type == R_HEREDOC)
            {
                r->heredoc_fd = handle_heredoc(r->target, env);
                if (r->heredoc_fd == -3)
                    return (130);
            }
            r = r->next;
        }
        c = c->next;
    }
    return (0);
}
