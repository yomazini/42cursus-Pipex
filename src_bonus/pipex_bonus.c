/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymazini <ymazini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 14:24:20 by ymazini           #+#    #+#             */
/*   Updated: 2025/02/17 15:20:43 by ymazini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


// src_bonus/pipex_bonus.c
#include "pipex_bonus.h"

static void	pipe_chain(char *cmd, int *prev_pipe, char **env)
{
	int		new_pipe[2];
	pid_t	pid;

	pipe(new_pipe);
	pid = fork();
	if (pid < 0)
		(perror("fork"), exit(EXIT_FAILURE));
	if (pid == 0)
	{
		close(new_pipe[0]);
		if (*prev_pipe != STDIN_FILENO)
			dup2(*prev_pipe, STDIN_FILENO);
		dup2(new_pipe[1], STDOUT_FILENO);
		exec_cmd(cmd, env);
	}
	else
	{
		close(new_pipe[1]);
		if (*prev_pipe != STDIN_FILENO)
			close(*prev_pipe);
		*prev_pipe = new_pipe[0];
	}
}

void	handle_multipipe(int ac, char **av, char **env, int hdoc)
{
	int		i;
	int		prev_pipe;
	int		out_fd;

	i = hdoc + HDOC_CMD - 1;
	prev_pipe = STDIN_FILENO;
	out_fd = open_outfile(av[ac - 1], hdoc);
	while (++i < ac - 2)
		pipe_chain(av[i], &prev_pipe, env);
	if (prev_pipe != STDIN_FILENO)
		dup2(prev_pipe, STDIN_FILENO);
	dup2(out_fd, STDOUT_FILENO);
	exec_cmd(av[ac - 2], env);
}

int	main(int ac, char **av, char **env)
{
	int		in_fd;
	int		hdoc;

	if (ac < 5)
		(ft_putstr_fd("Invalid number of arguments\n", 2), exit(1));
	hdoc = (ft_strncmp(av[1], "here_doc", 9) == 0);
	if (hdoc && ac < 6)
		(ft_putstr_fd("here_doc requires 6+ arguments\n", 2), exit(1));
	if (hdoc)
	{
		handle_hdoc(av[HDOC_LIMITER], &in_fd);
		handle_multipipe(ac, av, env, 1);
	}
	else
	{
		in_fd = open(av[1], O_RDONLY);
		if (in_fd < 0)
			(perror(av[1]), exit(1));
		dup2(in_fd, STDIN_FILENO);
		handle_multipipe(ac, av, env, 0);
	}
	while (wait(NULL) > 0)
		;
	return (0);
}
