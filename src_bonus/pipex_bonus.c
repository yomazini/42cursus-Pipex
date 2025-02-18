/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymazini <ymazini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 14:24:20 by ymazini           #+#    #+#             */
/*   Updated: 2025/02/18 11:03:58 by ymazini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	open_outfile(char *path, int hdoc)
{
	int	fd;
	int	flags;

	if (hdoc)
		flags = O_WRONLY | O_CREAT | O_APPEND;
	else
		flags = O_WRONLY | O_CREAT | O_TRUNC;
	fd = open(path, flags, 0644);
	if (fd < 0)
		(perror("pipex: outfile"), exit(1));
	return (fd);
}

static void	pipe_chain(char *cmd, int *prev_pipe, char **env)
{
	int		new_pipe[2];
	pid_t	pid;

	if (pipe(new_pipe) == -1)
		(perror("pipex: pipe"), exit(1));
	pid = fork();
	if (pid < 0)
		(perror("pipex: fork"), exit(1));
	if (pid == 0)
	{
		close(new_pipe[0]);
		if (*prev_pipe != 0)
			(dup2(*prev_pipe, 0), close(*prev_pipe));
		dup2(new_pipe[1], 1);
		exec_cmd(cmd, env);
	}
	else
	{
		close(new_pipe[1]);
		if (*prev_pipe != 0)
			close(*prev_pipe);
		*prev_pipe = new_pipe[0];
	}
}

pid_t	handle_multipipe(int ac, char **av, char **env, int hdoc)
{
	int		i;
	int		prev_pipe;
	int		out_fd;
	pid_t	pid;

	i = 2 + hdoc;
	prev_pipe = 0;
	out_fd = open_outfile(av[ac - 1], hdoc);
	while (i < ac - 2)
		pipe_chain(av[i++], &prev_pipe, env);
	pid = fork();
	if (pid == 0)
	{
		if (prev_pipe != 0)
			dup2(prev_pipe, 0);
		(dup2(out_fd, 1), exec_cmd(av[ac - 2], env));
	}
	else
	{
		close(out_fd);
		if (prev_pipe != 0)
			close(prev_pipe);
		return (pid);
	}
	return (-1);
}

static void	handle_input(char **av, int *in_fd, int hdoc)
{
	if (hdoc)
	{
		handle_hdoc(av[2], in_fd);
		(dup2(*in_fd, 0), close(*in_fd));
	}
	else
	{
		*in_fd = open(av[1], O_RDONLY);
		if (*in_fd < 0)
			(perror(av[1]), exit(1));
		(dup2(*in_fd, 0), close(*in_fd));
	}
}

int	main(int ac, char **av, char **env)
{
	int		in_fd;
	int		hdoc;
	int		status;
	pid_t	last_pid;

	if (ac < 5 + (ft_strncmp(av[1], "here_doc", 9) == 0))
		(ft_putstr_fd("Invalid number of arguments\n", 2), exit(1));
	hdoc = (ft_strncmp(av[1], "here_doc", 9) == 0);
	handle_input(av, &in_fd, hdoc);
	last_pid = handle_multipipe(ac, av, env, hdoc);
	waitpid(last_pid, &status, 0);
	while (wait(NULL) > 0)
		;
	if (WIFEXITED(status))
		exit(WEXITSTATUS(status));
	return (1);
}
