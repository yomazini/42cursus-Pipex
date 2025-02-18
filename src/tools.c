/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymazini <ymazini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 14:24:08 by ymazini           #+#    #+#             */
/*   Updated: 2025/02/18 11:23:26 by ymazini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*check_path(char *base, char *cmd)
{
	char	*joined;
	char	*full;

	joined = ft_strjoin(base, "/");
	if (!joined)
		return (NULL);
	full = ft_strjoin(joined, cmd);
	free(joined);
	if (!full)
		return (NULL);
	if (access(full, F_OK | X_OK) == 0)
		return (full);
	free(full);
	return (NULL);
}

char	*get_path(char **all_path, char *cmd)
{
	char	**cmds;
	char	*full_path;
	int		i;
	char	*path;

	cmds = ft_split(cmd, ' ');
	if (!cmds || !cmds[0] || !ft_strlen(cmds[0]))
		return (free_all(cmds), NULL);
	if (cmds[0][0] == '/' || (cmds[0][0] == '.' && cmds[0][1] == '/'))
	{
		path = ft_strdup(cmds[0]);
		return (free_all(cmds), path);
	}
	i = -1;
	while (all_path[++i])
	{
		full_path = check_path(all_path[i], cmds[0]);
		if (full_path)
		{
			free_all(cmds);
			return (full_path);
		}
	}
	free_all(cmds);
	return (NULL);
}

char	**get_env_arr(char **env)
{
	char	*path;
	char	**result;

	path = NULL;
	while (*env && !path)
	{
		if (ft_strncmp(*env, "PATH=", 5) == 0)
			path = *env + 5;
		env++;
	}
	if (!path)
		return (ft_split("", ':'));
	result = ft_split(path, ':');
	if (!result)
		exit(1);
	return (result);
}
