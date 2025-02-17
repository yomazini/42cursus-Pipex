/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymazini <ymazini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 14:34:13 by ymazini           #+#    #+#             */
/*   Updated: 2025/02/17 17:19:58 by ymazini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "../lib/libft.h"
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>  

# define HDOC_LIMITER 2
# define HDOC_CMD 3

void	handle_multipipe(int ac, char **av, char **env, int hdoc);
void	handle_hdoc(char *limiter, int *prev_pipe);
void	exec_cmd(char *cmd, char **env);
int		open_outfile(char *path, int hdoc);
void	setup_child_redirection(char *infile, int *pipe_fds);
char	**get_env_arr(char **env);
void	free_all(char **tofree);
char	*get_path(char **all_path, char *cmd);
void	handle_cmd_not_found(char **cmd, char **path_arr);

#endif
