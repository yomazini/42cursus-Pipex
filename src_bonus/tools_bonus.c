/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymazini <ymazini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 14:24:25 by ymazini           #+#    #+#             */
/*   Updated: 2025/02/17 15:17:57 by ymazini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	exec_cmd(char *cmd, char **env)
{
	char	**args;
	char	*path;
	char	**paths;

	args = ft_split(cmd, ' ');
	if (!args)
		(ft_putstr_fd("Command split error\n", 2), exit(1));
	if (ft_strchr(args[0], '/'))
		path = args[0];
	else
	{
		paths = get_env_arr(env);
		path = get_path(paths, cmd);
		free_all(paths);
	}
	if (!path || execve(path, args, env) < 0)
	{
		ft_putstr_fd("pipex: command not found: ", 2);
		ft_putendl_fd(args[0], 2);
		free_all(args);
		exit(127);
	}
}

void	handle_hdoc(char *limiter, int *prev_pipe)
{
	int		fd[2];
	pid_t	pid;
	char	*line;

	pipe(fd);
	pid = fork();
	if (pid < 0)
		(perror("fork"), exit(1));
	if (pid == 0)
	{
		close(fd[0]);
		while (1)
		{
			line = get_next_line(STDIN_FILENO);
			if (!line || !ft_strncmp(line, limiter, ft_strlen(limiter) + 1))
				break ;
			write(fd[1], line, ft_strlen(line));
			free(line);
		}
		close(fd[1]);
		exit(0);
	}
	else
	{
		close(fd[1]);
		*prev_pipe = fd[0];
		waitpid(pid, NULL, 0);
	}
}

int	open_outfile(char *path, int hdoc)
{
	int	fd;

	if (hdoc)
		fd = open(path, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		(perror(path), exit(1));
	return (fd);
}