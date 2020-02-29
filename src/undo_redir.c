#include "libft.h"
#include "error.h"
#include "shell.h"

/* Debugg */
//static void	debug_r(t_redirection *r)
//{
//	static int	i;

//	i = 0;
//	ft_printf("\n");
//	while (r)
//	{
//		ft_printf("\nUNDO redir:%d\n", i++);
//		ft_printf("\tr->redirectee.dest: %d\n", r->redirectee.dest);
//		ft_printf("\tr->save: %d\n", r->save);
//		r = r->next;
//	}
//	ft_printf("\n");
//}

static int	restored_fd(t_shell_fds *shell_fd, int fd)
{
	while (shell_fd)
	{
		if (shell_fd->fd == fd)
			return (1);
		shell_fd = shell_fd->next;
	}
	return (0);
}

static void	add_restored_fd(t_shell_fds **shell_fd, int add)
{
	t_shell_fds	*s;

	if (!*shell_fd)
	{
		*shell_fd = ft_memalloc(sizeof(t_shell_fds));
		(*shell_fd)->fd = add;
	}
	else
	{
		s = *shell_fd;
		while (s->next)
			s = s->next;
		s->next = ft_memalloc(sizeof(t_shell_fds));
		s->next->fd = add;
	}
}

static void	free_restored_fd(t_shell_fds *l)
{
	if (l)
	{
		free_restored_fd(l->next);
		free(l);
	}
}

static int	undo_iowrite(t_redirection *r, t_shell_fds **shell_fd)
{
	if (!restored_fd(*shell_fd, r->redirector.dest))
	{
		add_restored_fd(shell_fd, r->redirector.dest);
		dup2(r->save, r->redirector.dest);
	}
	close(r->save);
	return (0);
}

static int	undo_ioread(t_redirection *r, t_shell_fds **shell_fd)
{
//	debug_r(r); /* Debug */
	/* Multiple close of a given fd is prohibited */
	if (!restored_fd(*shell_fd, r->redirectee.dest))
	{
		add_restored_fd(shell_fd, r->redirectee.dest);
		dup2(r->save, r->redirectee.dest);
	}
	close(r->save);
	return (0);
}

int	undo_redirection_internal(t_redirection *r)
{
	t_shell_fds	*shell_fd;

	shell_fd = NULL;
	while (r)
	{
		if (r->flags & REDSUC)
		{
			if (r->instruction == IOWRITE)
				undo_iowrite(r, &shell_fd);
			else if (r->instruction == IOCAT)
				undo_iowrite(r, &shell_fd);
			else if (r->instruction == IOREAD)
				undo_ioread(r, &shell_fd);
			else if (r->instruction == IODUP && !(r->flags & FDCLOSE))
				undo_iowrite(r, &shell_fd);
			else if (r->instruction == (IODUP | IOREAD) && !(r->flags & FDCLOSE))
				undo_ioread(r, &shell_fd);
		}
		r = r->next;
	}
	/* free shell_fd list here */
	free_restored_fd(shell_fd);
	return (0);
}

int	undo_redirection(t_redirection *r)
{
	if (r)
	{
		undo_redirection_internal(r);
	//	free_restored_fd((t_shell_fds*)r);
		/* should we free at that point ? think so */
	}
	return (0);
}