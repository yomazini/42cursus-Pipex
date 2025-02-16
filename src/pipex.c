/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymazini <ymazini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 14:24:10 by ymazini           #+#    #+#             */
/*   Updated: 2025/02/16 21:54:09 by ymazini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	handle_exec_error(char *cmd_path, char **cmd, char **path_arr)
{
	ft_putstr_fd("pipex: command not found: ", 2);
	ft_putendl_fd(cmd[0], 2);
	free(cmd_path);
	free_all(cmd);
	free_all(path_arr);
	exit(127);
}

static void	call_child_p(char **env, char **av, int *pipe_fds, char **path_arr)
{
	char	**cmd;
	char	*cmd_path;

	setup_child_redirection(av[1], pipe_fds);
	cmd = ft_split(av[2], ' ');
	if (!cmd)
	{
		free_all(path_arr);
		ft_putendl_fd("Error: command split failed", 2);
		exit(1);
	}
	cmd_path = get_path(path_arr, av[2]);
	if (!cmd_path)
		handle_cmd_not_found(cmd, path_arr);
	if (execve(cmd_path, cmd, env) == -1)
		handle_exec_error(cmd_path, cmd, path_arr);
}

static void	call_parent_p(char **env, char **av, int *pipe_fds, char **path_arr)
{
	char	**cmd;
	char	*cmd_path;

	setup_parent_redirection(av[4], pipe_fds);
	cmd = ft_split(av[3], ' ');
	if (!cmd)
	{
		free_all(path_arr);
		ft_putendl_fd("Error: command split failed", 2);
		exit(1);
	}
	cmd_path = get_path(path_arr, av[3]);
	if (!cmd_path)
		handle_cmd_not_found(cmd, path_arr);
	if (execve(cmd_path, cmd, env) == -1)
	{
		perror("pipex: ");
		free(cmd_path);
		free_all(cmd);
		free_all(path_arr);
		exit(127);
	}
}

static pid_t	safe_fork(char **path_arr)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		perror("pipex: fork");
		free_all(path_arr);
		exit(1);
	}
	return (pid);
}

int	main(int ac, char **av, char **env)
{
	int		fds[2];
	pid_t	pid[2];
	int		status[2];
	char	**path_arr;

	check_args(ac);
	path_arr = get_env_arr(env);
	if (pipe(fds) == -1)
		(perror("pipex: pipe"), free_all(path_arr), exit(1));
	pid[0] = safe_fork(path_arr);
	if (pid[0] == 0)
		call_child_p(env, av, fds, path_arr);
	pid[1] = safe_fork(path_arr);
	if (pid[1] == 0)
		call_parent_p(env, av, fds, path_arr);
	(close(fds[0]), close(fds[1]));
	waitpid(pid[0], &status[0], 0);
	waitpid(pid[1], &status[1], 0);
	free_all(path_arr);
	if (WIFEXITED(status[1]))
		exit(WEXITSTATUS(status[1]));
	else if (WIFEXITED(status[0]))
		exit(WEXITSTATUS(status[0]));
	return (1);
}
