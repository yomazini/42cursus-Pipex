/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymazini <ymazini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 14:24:08 by ymazini           #+#    #+#             */
/*   Updated: 2025/02/15 21:46:57 by ymazini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	oh_norms2(char **cmds)
{
	ft_putendl_fd("command not found", 2);
	free_all(cmds);
	return (NULL);
}

static int	oh_norms1(char **cmds)
{
	if (!cmds || !cmds[0])
	{
		if (cmds)
			free_all(cmds);
		return (0);
	}
	return (1);
}

char	*get_path(char **all_path, char *cmd)
{
	char	**cmds;
	char	*joined_cmd;
	char	*full_path;
	int		i;

	cmds = ft_split(cmd, ' ');
	if (oh_norms1(cmds) == 0)
		return (NULL);
	i = -1;
	while (all_path[++i])
	{
		joined_cmd = ft_strjoin(all_path[i], "/");
		if (!joined_cmd)
			return (free_all(cmds), NULL);
		full_path = ft_strjoin(joined_cmd, cmds[0]);
		free(joined_cmd);
		if (!full_path)
			return (free_all(cmds), NULL);
		if (access(full_path, F_OK | X_OK) == 0)
			return (free_all(cmds), full_path);
		free(full_path);
	}
	oh_norms2(cmds);
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

char	**get_env_arr(char **env)
{
	char	*path;

	path = NULL;
	while (*env && path == NULL)
	{
		if (ft_strncmp(*env, "PATH=", 5) == 0)
			path = *env + 5;
		env++;
	}
	if (!path)
	{
		perror("error in path here");
		exit(1);
	}
	return (ft_split(path, ':'));
}
