/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estoffel <estoffel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 19:38:29 by estoffel          #+#    #+#             */
/*   Updated: 2021/12/07 21:41:16 by estoffel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <stdio.h>
# include <string.h>
# include <errno.h>
# include "./libft/libft.h"

char	*cat_cmd(char **path, char *cmd);

char	**get_path(char **ev);

int		check_file(char *file, int ioo, char **path);
int		print_err(char *file, char **path);

void	exec_fcmd(int *pfd, char **cmd, char *file, char **path);
void	exec_lcmd(int *pfd, char **cmd, char *file, char **path);
void	freetab(char **output);
void	pipex(char **av, char **path);

#endif
