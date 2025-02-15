/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymazini <ymazini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 14:24:10 by ymazini           #+#    #+#             */
/*   Updated: 2025/02/15 22:18:13 by ymazini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	oh_norms3(char **cmd, char *path_arr)
{
	free_all(cmd);
	free_all(path_arr);
	exit(127);
}

static	void	ft_execve_fail(char **cmd, char *path_arr, char *cmd_path)
{
	perror("ERR in execve: command not found:");
	free(cmd_path);
	oh_norms3(cmd, path_arr);
}

static void	call_child_p(char **env, char **av, int *pipe_fds, char **path_arr)
{
	int		fd;
	char	**cmd;
	char	*cmd_path;

	fd = open(av[1], O_RDONLY);
	if (fd == -1)
	{
		perror("ERROR IN FILE INPUT:");
		exit(1);
	}
	dup2(fd, 0);
	dup2(pipe_fds[1], 1);
	close(pipe_fds[0]);
	close(fd);
	cmd = ft_split(av[2], ' ');
	if (!cmd)
		exit(1);
	cmd_path = get_path(path_arr, av[2]);
	if (!cmd_path)
	{
		ft_putendl_fd("Error: command not found", 2);
		oh_norms3(cmd, path_arr);
	}
	if (execve(cmd_path, cmd, env) == -1)
		ft_execve_fail(cmd, path_arr, cmd_path);
}

static void	call_parent_p(char **env, char **av, int *pipe_fds, char **path_arr)
{
	int		fd;
	char	**cmd;
	char	*cmd_path;

	fd = open(av[4], O_CREAT | O_WRONLY | O_TRUNC, 0777);
	if (fd == -1)
	{
		perror("Error opening output file");
		exit(1);
	}
	dup2(pipe_fds[0], 0);
	dup2(fd, 1);
	close(pipe_fds[1]);
	close(fd);
	cmd = ft_split(av[3], ' ');
	if (!cmd)
	{
		ft_putendl_fd("Error: command split failed", 2);
		exit(1);
	}
	cmd_path = get_path(path_arr, av[3]);
	if (!cmd_path)
	{
		ft_putendl_fd("Error: command not found", 2);
		oh_norms3(cmd, path_arr);
	}
	if (execve(cmd_path, cmd, env) == -1)
		ft_execve_fail(cmd, path_arr, cmd_path);
}

int	main(int ac, char **av, char **env)
{
	int		fds[2];
	pid_t	check_pid;
	char	**path_arr;

	if (ac != 5)
	{
		ft_putstr_fd("Usage: ./pipex infile cmd1 cmd2 outfile\n", 2);
		exit(1);
	}
	if (pipe(fds) == -1)
	{
		perror("pipe:");
		exit(1);
	}
	path_arr = get_env_arr(env);
	if (!path_arr)
	{
		ft_putendl_fd("Error: could not retrieve PATH", 2);
		exit(1);
	}
	check_pid = fork();
	if (check_pid == -1)
	{
		perror("fork:");
		free_all(path_arr);
		exit(1);
	}
	if (check_pid == 0)
		call_child_p(env, av, fds, path_arr);
	else
		call_parent_p(env, av, fds, path_arr);
	return (0);
}
