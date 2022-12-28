/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vasargsy <vasargsy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 13:48:27 by vasargsy          #+#    #+#             */
/*   Updated: 2022/12/28 17:57:07 by vasargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void handler(int sig)
{
	(void)sig;
	write(1,"\n",1);
	rl_replace_line("",0);
	rl_on_new_line();
	rl_redisplay();
}

void do_redir(t_main *node)
{
	int i;

	i = -1;
	if(*node->heredoc)
		while(node->heredoc[++i])
			heredoc_redirect(node->heredoc[i]);
	i = -1;
	if(*node->infile)
		while(node->infile[++i])
			outfile(node->infile[i]);
	i = -1;
	if(*node->outfile)
		while(node->outfile[++i])
			infile_redir(node->outfile[i]);
		i = -1;
	if(*node->append)
		while(node->append[++i])
			append_redir(node->append[i]);
}

int	main(int argc, char **argv, char **envp)
{
	char		*line;
	char		**path;
	char		*tmp;
	pid_t		pid;
	int			i;
	t_main		*node;
	t_env		**envv;
	// int			in_cpy;
	// int			out_cpy;

	i = -1;
	(void)argc;
	(void)argv;
	node = malloc(sizeof(t_main));
	envv = malloc(sizeof(t_env *));
	*envv = NULL;
	env_to_list(envv, envp);
	while ((ft_strncmp(envp[++i], "PATH=", 5) != 0))
		;
	envp[i] += 5;
	path = ft_split(envp[i], ':');
	printf(GRN"wellcome! \n"CYN);
	rl_catch_signals = 0;
	signal(SIGINT,&handler);
	//signal(SIGINT,SIG_DFL);
	signal(SIGQUIT,SIG_IGN);
	// in_cpy = dup(0);
	// out_cpy = dup(1);
	while (1)
	{
		line = readline("minishell> ");
		if(line == 0)
		{
			printf("exit\n");
			exit(0);
		}
		if (line[0])
			add_history(line);
		else
			continue ;
		i = -1;
		node->cmd = ft_split(line, ' ');
		node->cmd[0] = ft_strjoin("/", node->cmd[0]);
		while (path[++i])
		{
			tmp = ft_strjoin(path[i], node->cmd[0]);
			if (access(tmp, 0) == 0)
				break ;
		}
		// lexer(&node,line);
		// parser(&node);
		//do_redir(node);
		//printf("%s\n", node->cmd[0]);
		//tmp = cmd_to_acc(node->cmd, envv);
		builtin(&node, envv);
		//printf("%d\n", __LINE__);
		//system("leaks minishell");
		pid = fork();
		if (pid == 0)
		{
			//printf("%s, %s\n", tmp, node->cmd[0]);
			//execve(tmp, node->cmd, envp);
			exit (0);
		}
		//else
			wait(NULL);
		// dup2(in_cpy,0);
		// dup2(out_cpy,1);
		// close(in_cpy);
		// close(out_cpy);
	}
	return (0);
}