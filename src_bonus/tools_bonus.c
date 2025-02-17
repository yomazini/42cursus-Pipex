/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymazini <ymazini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 14:24:25 by ymazini           #+#    #+#             */
/*   Updated: 2025/02/17 20:48:40 by ymazini          ###   ########.fr       */
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
		(perror("pipex"), free(path), free_all(args), exit(126));
}

void	handle_hdoc(char *limiter, int *prev_pipe)
{
	int		fd[2];
	pid_t	pid;
	char	*line;
	char	*expected;

	expected = ft_strjoin(limiter, "\n");
	if (pipe(fd) == -1)
		(perror("pipex: pipe"), exit(EXIT_FAILURE));
	pid = fork();
	if (pid == 0)
	{
		close(fd[0]);
		while (1)
		{
			line = get_next_line(STDIN_FILENO);
			if (!line)
				break ;
			if (ft_strncmp(line, expected, ft_strlen(line)) == 0)
			{
				free(line);
				exit(0);
			}
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
