/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymazini <ymazini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 14:24:10 by ymazini           #+#    #+#             */
/*   Updated: 2025/02/16 16:15:59 by ymazini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	call_child_p(char **env, char **av, int *pipe_fds, char **path_arr)
{
	char	**cmd;
	char	*cmd_path;

	setup_child_redirection(av[1], pipe_fds);
	cmd = ft_split(av[2], ' ');
	if (!cmd)
		exit(1);
	cmd_path = get_path(path_arr, av[2]);
	if (!cmd_path)
	{
		ft_putendl_fd("Error: command not found", 2);
		free_all(cmd);
		free_all(path_arr);
		exit(127);
	}
	if (execve(cmd_path, cmd, env) == -1)
	{
		perror("Error in execve: command not found");
		free(cmd_path);
		free_all(cmd);
		free_all(path_arr);
		exit(127);
	}
}

static void	call_parent_p(char **env, char **av, int *pipe_fds, char **path_arr)
{
	char	**cmd;
	char	*cmd_path;

	setup_parent_redirection(av[4], pipe_fds);
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
		free_all(cmd);
		free_all(path_arr);
		exit(127);
	}
	if (execve(cmd_path, cmd, env) == -1)
	{
		perror("ERR in execve: command not found:");
		free(cmd_path);
		free_all(cmd);
		free_all(path_arr);
		exit(127);
	}
}

int	main(int ac, char **av, char **env)
{
	int		fds[2];
	pid_t	check_pid;
	char	**path_arr;

	check_args(ac);
	if (pipe(fds) == -1)
	{
		perror("Pipe:");
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
		perror("Fork:");
		free_all(path_arr);
		exit(1);
	}
	if (check_pid == 0)
		call_child_p(env, av, fds, path_arr);
	else
		call_parent_p(env, av, fds, path_arr);
	return (0);
}
