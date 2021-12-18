/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multipipes_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estoffel <estoffel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 16:11:01 by estoffel          #+#    #+#             */
/*   Updated: 2021/12/07 21:45:14 by estoffel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex_bonus.h"

void	exec_fcmd(char **cmd, char *file, char **path)
{
	int		fd;
	int		fd_stdin;

	fd = check_file(file, 0, path);
	fd_stdin = dup(STDIN_FILENO);
	dup2(fd, STDIN_FILENO);
	execve(cat_cmd(path, cmd[0]), cmd, NULL);
	dup2(fd_stdin, STDIN_FILENO);
	close(fd);
	close(fd_stdin);
	exit(EXIT_SUCCESS);
}

void	exec_lcmd(char **cmd, char *file, char **path)
{
	int		fd;
	int		fd_stdout;

	fd = check_file(file, 1, path);
	fd_stdout = dup(STDOUT_FILENO);
	dup2(fd, STDOUT_FILENO);
	execve(cat_cmd(path, cmd[0]), cmd, NULL);
	dup2(fd_stdout, STDOUT_FILENO);
	close(fd);
	close(fd_stdout);
	exit(EXIT_SUCCESS);
}

void	children(int ac, int fd_stdin, char **av, char **path)
{
	int		i;
	int		pfd[2];
	char	**cmd;

	i = 0;
	while (i < (ac - 3))
	{
		cmd = ft_split(av[i + 2], ' ');
		pipe(pfd);
		if (fork() == 0)
		{
			if (i != 0)
				dup2(fd_stdin, 0);
			if (i != (ac - 4))
				dup2(pfd[1], 1);
			close_pfd(pfd, fd_stdin);
			if (i == 0)
				exec_fcmd(ft_split(av[2], ' '), av[1], path);
			else if (i == (ac - 4))
				exec_lcmd(ft_split(av[ac - 2], ' '), av[ac - 1], path);
			else
				execve(cat_cmd(path, cmd[0]), cmd, NULL);
		}
		i = close_child(pfd, fd_stdin, cmd, i);
	}
}

int	close_child(int *pfd, int fd_stdin, char **cmd, int i)
{
	int		j;

	dup2(pfd[0], fd_stdin);
	close(pfd[0]);
	close(pfd[1]);
	j = i + 1;
	freetab(cmd);
	return (j);
}

void	close_pfd(int *pfd, int fd_stdin)
{
	close(pfd[0]);
	close(pfd[1]);
	close(fd_stdin);
}
