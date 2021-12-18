/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estoffel <estoffel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 15:29:29 by estoffel          #+#    #+#             */
/*   Updated: 2021/12/07 21:44:29 by estoffel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	exec_fcmd(int *pfd, char **cmd, char *file, char **path)
{
	int		fd;
	int		fd_stdin;

	fd = check_file(file, 0, path);
	fd_stdin = dup(STDIN_FILENO);
	dup2(pfd[1], 1);
	dup2(fd, STDIN_FILENO);
	close(pfd[0]);
	close(pfd[1]);
	execve(cat_cmd(path, cmd[0]), cmd, NULL);
	dup2(fd_stdin, STDIN_FILENO);
	close(fd);
	close(fd_stdin);
	exit(EXIT_SUCCESS);
}

void	exec_lcmd(int *pfd, char **cmd, char *file, char **path)
{
	int		fd;
	int		fd_stdout;

	fd = check_file(file, 1, path);
	fd_stdout = dup(STDOUT_FILENO);
	dup2(pfd[0], 0);
	dup2(fd, STDOUT_FILENO);
	close(pfd[0]);
	close(pfd[1]);
	execve(cat_cmd(path, cmd[0]), cmd, NULL);
	dup2(fd_stdout, STDOUT_FILENO);
	close(fd);
	close(fd_stdout);
	exit(EXIT_SUCCESS);
}

void	pipex(char **av, char **path)
{
	pid_t	pid;
	pid_t	pid2;
	int		pfd[2];
	int		status;

	if (pipe(pfd) == -1)
		return (perror(" "));
	pid = fork();
	if (pid == -1)
		return (perror("Fork : "));
	else if (pid == 0)
		exec_fcmd(pfd, ft_split(av[2], ' '), av[1], path);
	pid2 = fork();
	if (pid2 == -1)
		return (perror("Fork : "));
	else if (pid2 == 0)
		exec_lcmd(pfd, ft_split(av[3], ' '), av[4], path);
	close(pfd[1]);
	close(pfd[0]);
	waitpid(pid, &status, 0);
	waitpid(pid2, &status, 0);
}

int	main(int ac, char **av, char **ev)
{
	char	**path;

	if (ac != 5)
	{
		ft_putstr_fd("Wrong number of arguments\n", 2);
		return (-1);
	}
	path = get_path(ev);
	if (check_file(av[1], 0, path) == -1)
		return (1);
	else if (check_file(av[ac - 1], 1, path) == -1)
		return (print_err(av[ac - 1], path));
	pipex(av, path);
	freetab(path);
	return (0);
}
