/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymazini <ymazini@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 14:24:25 by ymazini           #+#    #+#             */
/*   Updated: 2025/02/18 10:57:28 by ymazini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static char	**parse_cmd(char *cmd)
{
	char	**args;
	char	*tmp;

	tmp = ft_strtrim(cmd, " '""");
	args = ft_split(tmp, ' ');
	free(tmp);
	return (args);
}

static char	*find_command_path(char **args, char **env)
{
	char	**paths;
	char	*path;

	if (access(args[0], X_OK) == 0 && ft_strchr(args[0], '/'))
		return (args[0]);
	paths = get_env_arr(env);
	path = get_path(paths, args[0]);
	free_all(paths);
	return (path);
}

void	exec_cmd(char *cmd, char **env)
{
	char	**args;
	char	*path;

	args = parse_cmd(cmd);
	if (!args || !args[0])
		(ft_putstr_fd("pipex: command not found\n", 2), exit(127));
	path = find_command_path(args, env);
	if (!path)
	{
		ft_putstr_fd("pipex: command not found: ", 2);
		ft_putendl_fd(args[0], 2);
		free_all(args);
		exit(127);
	}
	if (execve(path, args, env) == -1)
	{
		if (path != args[0])
			free(path);
		free_all(args);
		exit(126);
	}
}

static void	process_heredoc(int fd, char *expected)
{
	char	*line;

	while (1)
	{
		line = get_next_line(0);
		if (!line || ft_strncmp(line, expected, ft_strlen(line)) == 0)
		{
			free(line);
			break ;
		}
		write(fd, line, ft_strlen(line));
		free(line);
	}
}

void	handle_hdoc(char *limiter, int *prev_pipe)
{
	int		fd[2];
	pid_t	pid;
	char	*expected;

	expected = ft_strjoin(limiter, "\n");
	if (!expected)
		exit(1);
	if (pipe(fd) == -1)
		(perror("pipex: pipe"), free(expected), exit(1));
	pid = fork();
	if (pid == 0)
	{
		close(fd[0]);
		process_heredoc(fd[1], expected);
		close(fd[1]);
		free(expected);
		exit(0);
	}
	close(fd[1]);
	*prev_pipe = fd[0];
	waitpid(pid, NULL, 0);
	free(expected);
}
