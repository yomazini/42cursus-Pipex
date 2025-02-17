/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymazini <ymazini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 14:24:25 by ymazini           #+#    #+#             */
/*   Updated: 2025/02/17 22:08:41 by ymazini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static char	**parse_cmd(char *cmd)
{
	char	**args;
	char	*tmp;

	tmp = ft_strtrim(cmd, " '"""); // Trim quotes
	args = ft_split(tmp, ' ');
	free(tmp);
	return (args);
}

void	exec_cmd(char *cmd, char **env)
{
	char	**args;
	char	*path;
	char	**paths;

	args = parse_cmd(cmd);
	if (!args || !args[0])
		(ft_putstr_fd("pipex: command not found\n", 2), exit(127));
	if (access(args[0], X_OK) == 0 && ft_strchr(args[0], '/'))
		path = args[0];
	else
	{
		paths = get_env_arr(env);
		path = get_path(paths, cmd);
		free_all(paths);
	}
	if (!path)
	{
		ft_putstr_fd("pipex: command not found: ", 2);
		ft_putendl_fd(args[0], 2);
		free_all(args);
		exit(127);
	}
	if (execve(path, args, env) == -1)
	{
		if (path != args[0]) // Prevent double free
			free(path);
		free_all(args);
		exit(126);
	}
}

void	handle_hdoc(char *limiter, int *prev_pipe)
{
	int		fd[2];
	pid_t	pid;
	char	*line;
	char	*expected;

	expected = ft_strjoin(limiter, "\n");
	if (!expected)
		exit(EXIT_FAILURE); // Add error check
	if (pipe(fd) == -1)
		(perror("pipex: pipe"), free(expected), exit(EXIT_FAILURE));
	pid = fork();
	if (pid == 0)
	{
		close(fd[0]);
		signal(SIGINT, SIG_DFL); // Handle Ctrl+C
		while (1)
		{
			line = get_next_line(STDIN_FILENO);
			if (!line || ft_strncmp(line, expected, ft_strlen(line)) == 0) // Exact match
			{
				free(line);
				break ;
			}
			write(fd[1], line, ft_strlen(line));
			free(line);
		}
		close(fd[1]);
		free(expected); // Add this
		exit(EXIT_SUCCESS);
	}
	else
	{
		close(fd[1]);
		*prev_pipe = fd[0];
		waitpid(pid, NULL, 0);
	}
	free(expected);
}





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
		(perror("pipex: outfile"), exit(EXIT_FAILURE));
	return (fd);
}
