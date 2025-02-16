/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymazini <ymazini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 14:24:10 by ymazini           #+#    #+#             */
/*   Updated: 2025/02/16 20:11:02 by ymazini          ###   ########.fr       */
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
	{
		free_all(path_arr);  // Add this
		ft_putendl_fd("Error: command split failed", 2);
		exit(1);
	}
	cmd_path = get_path(path_arr, av[2]);
	if (!cmd_path)
	{
 		   ft_putstr_fd("pipex: ", 2);
   		 ft_putstr_fd(cmd[0], 2);
   		 ft_putendl_fd(": command not found", 2);
		free_all(cmd);
		free_all(path_arr);
		exit(127);
	}
	if (execve(cmd_path, cmd, env) == -1)
	{
	    ft_putstr_fd("pipex: ", 2);
    	ft_putstr_fd(cmd[0], 2);
    	ft_putendl_fd(": command not found", 2);
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
		free_all(path_arr);  // Add this
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
		perror("pipex: ");
    	free(cmd_path);
    	free_all(cmd);
    	free_all(path_arr);
    	exit(127);
	}
}

int main(int ac, char **av, char **env) 
{
    int     fds[2];
    pid_t   pid1, pid2;
    int     status1;
    int     status2;
    char    **path_arr;

    check_args(ac);
    path_arr = get_env_arr(env);
    if (pipe(fds) == -1)
	{
		free_all(path_arr);  // Add this before exit
        (perror("pipex: pipe"), exit(1));
	}
    pid1 = fork();
    if (pid1 < 0)
	{
    	free_all(path_arr);  // Add this
    	perror("pipex: fork");
    	exit(1);
	}
    if (pid1 == 0) 
        call_child_p(env, av, fds, path_arr);
    
    pid2 = fork();
    if (pid2 < 0)
        (perror("pipex: fork"), exit(1));
    if (pid2 == 0)
        call_parent_p(env, av, fds, path_arr);
    
	close(fds[0]);
	close(fds[1]);
	waitpid(pid1, &status1, 0);
	waitpid(pid2, &status2, 0);
	free_all(path_arr);
	
    if (WIFEXITED(status1) && WEXITSTATUS(status1) != 0)
        exit(WEXITSTATUS(status1));
    if (WIFEXITED(status2))
        exit(WEXITSTATUS(status2));
	free_all(path_arr);
    exit(1);
}
