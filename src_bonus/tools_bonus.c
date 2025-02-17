/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymazini <ymazini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 14:24:25 by ymazini           #+#    #+#             */
/*   Updated: 2025/02/17 17:20:47 by ymazini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	exec_cmd(char *cmd, char **env)
{
	char	**args;
	char	*path;
	char	**paths;

	args = ft_split(cmd, ' ');
	if (!args || !args[0])
		(ft_putstr_fd("pipex: command not found\n", 2), exit(127));
	paths = get_env_arr(env);
	path = get_path(paths, cmd);
	free_all(paths);
	if (!path)
	{
		ft_putstr_fd("pipex: command not found: ", 2);
		ft_putendl_fd(args[0], 2);
		free_all(args);
		exit(127);
	}
	if (execve(path, args, env) == -1)
	{
		perror("pipex");
		free(path);
		free_all(args);
		exit(EXIT_FAILURE);
	}
}

void	handle_hdoc(char *limiter, int *prev_pipe)
{
	int		fd[2];
	pid_t	pid;
	char	*line;
	char	*trimmed;

	if (pipe(fd) == -1)
		(perror("pipex: pipe"), exit(EXIT_FAILURE));
	pid = fork();
	if (pid < 0)
		(perror("pipex: fork"), exit(EXIT_FAILURE));
	if (pid == 0)
	{
		close(fd[0]);
		while (1)
		{
			line = get_next_line(STDIN_FILENO);
			if (!line)
				break ;
			trimmed = ft_strtrim(line, "\n");
			if (strcmp(trimmed, limiter) == 0)
			{
				free(line), free(trimmed);
				break;
			}
			write(fd[1], line, ft_strlen(line));
			free(line);
			free(trimmed);
		}
		close(fd[1]);
		exit(EXIT_SUCCESS);
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
		(perror("pipex: outfile"), exit(EXIT_FAILURE));
	return (fd);
}