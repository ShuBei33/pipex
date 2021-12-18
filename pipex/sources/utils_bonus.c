/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estoffel <estoffel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 16:11:07 by estoffel          #+#    #+#             */
/*   Updated: 2021/12/07 22:13:29 by estoffel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex_bonus.h"

char	**get_path(char **ev)
{
	char	**tab;
	int		i;

	i = 0;
	if (!ev || !ev[i])
		return (NULL);
	while (ev[i] && ft_strncmp(ev[i], "PATH=", 5))
		++i;
	ev[i] += 5;
	tab = ft_split(ev[i], ':');
	return (tab);
}

char	*cat_cmd(char **path, char *cmd)
{
	char	*output;
	char	*tmp;
	int		i;

	i = 0;
	while (path && path[i])
	{
		tmp = ft_strjoin(path[i], "/");
		output = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(output, F_OK | X_OK) == 0)
			return (output);
		free(output);
		i++;
	}
	ft_putstr_fd("Error: No such file or directory\n", 2);
	return (NULL);
}

void	freetab(char **output)
{
	int	i;

	i = 0;
	if (!output)
		return ;
	while (output[i])
	{
		free(output[i]);
		++i;
	}
	free(output);
}

int	print_err(char *file, char **path)
{
	ft_putstr_fd("./pipex : ", 2);
	ft_putstr_fd(file, 2);
	perror(" ");
	freetab(path);
	return (-1);
}

int	check_file(char *file, int ioo, char **path)
{
	if (ioo == 0)
	{
		if (access(file, F_OK | R_OK) == -1)
			return (print_err(file, path));
		return (open(file, O_RDONLY));
	}
	else
		return (open(file, O_CREAT | O_WRONLY | O_TRUNC, 0666));
}
