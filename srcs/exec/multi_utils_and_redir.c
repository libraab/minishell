#include "../../includes/minishell.h"

void	init_vars_cm1(t_data *data)
{
	data->cmd1 = NULL;
	data->fid = 1;
}

char	*check_cmd(t_data *data)
{
	char	**env_exec;
	char	*cmd1;

	cmd1 = NULL;
	if (data->cmd->cmd != NULL)
	{
		env_exec = take_env(data->cmd->cmd);
		if (env_exec)
		{
			cmd1 = find_cmd(data->cmd->cmd, env_exec);
			free_tab(env_exec);
		}
	}
	return (cmd1);
}

void	no_cmd_redirs(t_data *data, int *pp0)
{
	int	inf;
	int	outf;
	int	save1;
	int	save2;

	close(pp0[1]);
	outf = 1;
	save1 = dup(STDIN_FILENO);
	save2 = dup(STDOUT_FILENO);
	take_redir(data->cmd[0].redir, &inf, &outf);
	dup2(save1, STDOUT_FILENO);
	dup2(save2, STDIN_FILENO);
}

void	check_red(char **red)
{
	int	i;

	if (red[0] != NULL)
	{
		if (red[1][0] == '\0')
		{
			g_exe.rs = 0;
			return ;
		}
		i = 3;
		if (red[2] != NULL)
		{
			while (i <= tab_len(red))
			{
				if (red[i][0] == '\0')
				{
					g_exe.rs = 0;
					break ;
				}
				i += 2;
			}
		}
	}
}
