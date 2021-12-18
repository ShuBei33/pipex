/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estoffel <estoffel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 19:54:24 by estoffel          #+#    #+#             */
/*   Updated: 2021/12/07 20:30:18 by estoffel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex_bonus.h"

void	exec_hdoc(char **cmd, char **path, char *delimiter)
{
	char	buffer[4095];
	int		output;
	int		fd;
	int		fd_stdin;
	char	*delim;

	delim = ft_strjoin(delimiter, "\n");
	fd = open("/tmp/caca", O_CREAT | O_WRONLY | O_TRUNC, 0666);
	fd_stdin = dup(STDIN_FILENO);
	write(0, "heredoc> ", 9);
	output = read(0, buffer, 4095);
	while (output > 0)
	{
		buffer[output] = '\0';
		if (!ft_strncmp(delim, buffer, ft_strlen(buffer)))
			break ;
		ft_putstr_fd(buffer, fd);
		write(0, "heredoc> ", 9);
		output = read(0, buffer, 4095);
	}
	close(fd);
	close_hdoc(delim, path, cmd, fd_stdin);
}

void	close_hdoc(char *delim, char **path, char **cmd, int fd_stdin)
{
	int	fd;

	fd = open("/tmp/caca", O_RDONLY);
	dup2(fd, STDIN_FILENO);
	execve(cat_cmd(path, cmd[0]), cmd, NULL);
	dup2(fd_stdin, STDIN_FILENO);
	close(fd);
	close(fd_stdin);
	unlink("/tmp/caca");
	free(delim);
	exit(EXIT_SUCCESS);
}

void	children_hdoc(int ac, int fd_stdin, char **av, char **path)
{
	int		i;
	int		pfd[2];
	char	**cmd;

	i = 0;
	while (i < (ac - 4))
	{
		cmd = ft_split(av[i + 3], ' ');
		pipe(pfd);
		if (fork() == 0)
		{
			if (i != 0)
				dup2(fd_stdin, 0);
			if (i != (ac - 5))
				dup2(pfd[1], 1);
			close_pfd(pfd, fd_stdin);
			if (i == 0)
				exec_hdoc(cmd, path, av[2]);
			else if (i == (ac - 5))
				exec_lcmd(ft_split(av[ac - 2], ' '), av[ac - 1], path);
			else
				execve(cat_cmd(path, cmd[0]), cmd, NULL);
		}
		i = close_child(pfd, fd_stdin, cmd, i);
	}
}
