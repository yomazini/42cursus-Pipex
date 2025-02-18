/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymazini <ymazini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 14:24:04 by ymazini           #+#    #+#             */
/*   Updated: 2025/02/18 11:13:31 by ymazini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../lib/libft.h"
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <sys/wait.h>

void	check_args(int ac);
void	setup_child_redirection(char *infile, int *pipe_fds);
void	setup_parent_redirection(char *outfile, int *pipe_fds);
char	**get_env_arr(char **env);
void	free_all(char **tofree);
char	*get_path(char **all_path, char *cmd);
void	handle_cmd_not_found(char **cmd, char **path_arr);

#endif