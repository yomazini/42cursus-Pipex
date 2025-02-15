/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymazini <ymazini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 14:24:04 by ymazini           #+#    #+#             */
/*   Updated: 2025/02/15 23:18:14 by ymazini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

#include "../lib/libft.h"
# include <stdio.h>
# include <fcntl.h>
# include <sys/wait.h>
# include "../lib/libft.h"

char	**get_env_arr(char **env);
void	free_all(char **tofree);
char	*get_path(char **all_path, char *cmd);


#endif