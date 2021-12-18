/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estoffel <estoffel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 18:36:03 by estoffel          #+#    #+#             */
/*   Updated: 2021/12/07 21:41:04 by estoffel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

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
int		close_child(int *pfd, int fd_stdin, char **cmd, int i);
int		print_err(char *file, char **path);

void	children(int ac, int fd_stdin, char **av, char **path);
void	children_hdoc(int ac, int fd_stdin, char **av, char **path);
void	close_hdoc(char *delim, char **path, char **cmd, int fd_stdin);
void	close_pfd(int *pfd, int fd_stdin);
void	exec_fcmd(char **cmd, char *file, char **path);
void	exec_hdoc(char **cmd, char **path, char *delimiter);
void	exec_lcmd(char **cmd, char *file, char **path);
void	freetab(char **output);
void	pipex(char **av, char **path, int ac);
void	pipex_hdoc(char **av, char **path, int ac);

#endif
