/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estoffel <estoffel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 20:13:19 by estoffel          #+#    #+#             */
/*   Updated: 2021/12/07 21:42:22 by estoffel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex_bonus.h"

void	pipex_hdoc(char **av, char **path, int ac)
{
	int	fd_stdin;
	int	i;

	fd_stdin = dup(STDIN_FILENO);
	children_hdoc(ac, fd_stdin, av, path);
	i = 0;
	close(fd_stdin);
	while (i < (ac - 4))
	{
		wait(NULL);
		++i;
	}
}

void	pipex(char **av, char **path, int ac)
{
	int	fd_stdin;
	int	i;

	fd_stdin = dup(STDIN_FILENO);
	children(ac, fd_stdin, av, path);
	i = 0;
	close(fd_stdin);
	while (i < (ac - 3))
	{
		wait(NULL);
		++i;
	}
}

int	ft_strcmp(char *s1, char *s2)
{
	while ((*s1 && *s2) && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}

int	main(int ac, char **av, char **ev)
{
	char	**path;

	if ((ac < 5 && ft_strcmp(av[1], "here_doc"))
		|| (ac < 6 && !ft_strcmp(av[1], "here_doc")))
	{
		ft_putstr_fd("Wrong number of arguments\n", 2);
		return (-1);
	}
	path = get_path(ev);
	if (check_file(av[ac - 1], 1, path) == -1)
		return (print_err(av[ac - 1], path));
	if (!ft_strcmp(av[1], "here_doc"))
		pipex_hdoc(av, path, ac);
	else
	{
		if (check_file(av[1], 0, path) == -1)
			return (1);
		pipex(av, path, ac);
	}
	freetab(path);
	return (0);
}
