/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymazini <ymazini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 14:24:08 by ymazini           #+#    #+#             */
/*   Updated: 2025/02/16 20:23:12 by ymazini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	check_args(int ac)
{
	if (ac != 5)
	{
		ft_putstr_fd("Usage: ./pipex infile cmd1 cmd2 outfile\n", 2);
		exit(1);
	}
}

void	setup_child_redirection(char *infile, int *pipe_fds)
{
	int	fd;

	fd = open(infile, O_RDONLY);
	if (fd == -1)
	{
		perror("pipex: infile");
		exit(1);
	}
	dup2(fd, 0);
	dup2(pipe_fds[1], 1);
	close(pipe_fds[0]);
	close(fd);
}

void	setup_parent_redirection(char *outfile, int *pipe_fds)
{
	int	fd;

	fd = open(outfile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror("pipex: outfile");
		exit(1);
	}
	dup2(pipe_fds[0], 0);
	dup2(fd, 1);
	close(pipe_fds[1]);
	close(fd);
}

char	**get_env_arr(char **env)
{
	char	*path;

	path = NULL;
	while (*env && !path)
	{
		if (ft_strncmp(*env, "PATH=", 5) == 0)
			path = *env + 5;
		env++;
	}
	if (!path)
	{
   		ft_putendl_fd("pipex: PATH not found", 2);
  		return (ft_split("", ':'));
	}
	return (ft_split(path, ':'));
}

void	free_all(char **tofree)
{
	int	i;

	i = 0;
	if (!tofree)
		return ;
	while (tofree[i])
	{
		free(tofree[i]);
		i++;
	}
	free(tofree);
}

char	*get_path(char **all_path, char *cmd)
{
	char	**cmds;
	char	*joined_cmd;
	char	*full_path;
	int		i;

	cmds = ft_split(cmd, ' ');
	if (!cmds || !cmds[0] || ft_strlen(cmds[0]) == 0)
	{
	    free_all(cmds);
	    return (NULL);
	}
	if (cmds[0][0] == '/' || (cmds[0][0] == '.' && cmds[0][1] == '/'))
    {
        char *path = ft_strdup(cmds[0]);
        free_all(cmds);
        return (path);
    }
	i = 0;
	while (all_path[i])
	{
		joined_cmd = ft_strjoin(all_path[i], "/");
		if (!joined_cmd)
		{
			free_all(cmds);
			return (NULL);
		}
		full_path = ft_strjoin(joined_cmd, cmds[0]);
		free(joined_cmd);
		if (!full_path)
		{
			perror("pipex");
    		free_all(cmds);
    		return (NULL);
		}
		if (access(full_path, F_OK | X_OK) == 0)
		{
			free_all(cmds);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	free_all(cmds);
	return (NULL);
}
