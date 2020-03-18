#include "ft_readline.h"
#include "../src/builtins/builtins.h"

void	vim_hash(void)
{
	g_input_break = 1;
	g_dis.cbpos = 0;
	insert_text("#", 1);
}

void	call_fc(void)
{ /* Need some help from Simon to better implement this */
//	return ; /* If no history */
	char *argv[2];

	argv[0] = "fc";
	argv[1] = NULL;
	cmd_fc(1, argv);
}

void	beg_next_wd(void)
{
	while (g_line.line[g_dis.cbpos] != ' ' && g_dis.cbpos < g_line.len)
		cursor_r();
	while (g_line.line[g_dis.cbpos] == ' ' && g_dis.cbpos < g_line.len)
		cursor_r();
}

void	beg_next_alnum(void)
{
	if (ft_isalnum(g_line.line[g_dis.cbpos]) && g_dis.cbpos < g_line.len)
	{
		while (ft_isalnum(g_line.line[g_dis.cbpos]) && g_dis.cbpos < g_line.len)
			cursor_r();
		while (g_line.line[g_dis.cbpos] == ' ' && g_dis.cbpos < g_line.len)
			cursor_r();
	}
	else if (!ft_isalnum(g_line.line[g_dis.cbpos])&& g_dis.cbpos < g_line.len)
		while (!ft_isalnum(g_line.line[g_dis.cbpos])&& g_dis.cbpos < g_line.len)
			cursor_r();
}

void	end_next_alnum(void)
{
	if (ft_isalnum(g_line.line[g_dis.cbpos]) && g_dis.cbpos < g_line.len)
	{
		while (g_line.line[g_dis.cbpos + 1] == ' ' && g_dis.cbpos + 1 < g_line.len)
			cursor_r();
		while (ft_isalnum(g_line.line[g_dis.cbpos + 1]) && g_dis.cbpos + 1 < g_line.len)
			cursor_r();
	}
	else if (!ft_isalnum(g_line.line[g_dis.cbpos]) && g_dis.cbpos < g_line.len)
		while (!ft_isalnum(g_line.line[g_dis.cbpos + 1])&& g_dis.cbpos + 1 < g_line.len)
			cursor_r();
}