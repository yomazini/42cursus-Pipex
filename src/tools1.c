/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymazini <ymazini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 21:06:00 by ymazini           #+#    #+#             */
/*   Updated: 2025/02/18 13:39:40 by ymazini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_all(char **tofree)
{
	int	i;

	if (!tofree)
		return ;
	i = -1;
	while (tofree[++i])
		free(tofree[i]);
	free(tofree);
}

void	check_args(int ac)
{
	if (ac != 5)
		(ft_putstr_fd("Usage: ./pipex infile cmd1 cmd2 outfile\n", 2), exit(1));
}

void	setup_child_redirection(char *infile, int *pipe_fds)
{
	int	fd;

	fd = open(infile, O_RDONLY);
	if (fd == -1)
	{
		perror("pipex: infile");
		exit(1);
	}
	dup2(fd, 0);
	dup2(pipe_fds[1], 1);
	(close(pipe_fds[0]), close(fd));
}

void	setup_parent_redirection(char *outfile, int *pipe_fds)
{
	int	fd;

	fd = open(outfile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
		(perror("pipex: outfile"), exit(1));
	dup2(pipe_fds[0], 0);
	dup2(fd, 1);
	(close(pipe_fds[1]), close(fd));
}

void	handle_cmd_not_found(char **cmd, char **path_arr)
{
	ft_putstr_fd("pipex: command not found: ", 2);
	ft_putendl_fd(cmd[0], 2);
	free_all(cmd);
	free_all(path_arr);
	exit(127);
}
