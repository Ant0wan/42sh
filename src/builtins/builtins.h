/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 18:33:04 by abarthel          #+#    #+#             */
/*   Updated: 2020/03/03 14:40:56 by efischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

#include "shell.h"

/*
** Flags for hash options
*/
# define HASH_D_OPTION 1
# define HASH_L_OPTION 2
# define HASH_P_OPTION 4
# define HASH_R_OPTION 8
# define HASH_T_OPTION 16

/*
** Values used to hash strings
*/
#define FNV_OFFSET 2166136261
#define FNV_PRIME 16777619

/*
** Utils for builtins
*/
int				ft_putenv_table(char ***env, const char *name,
				const char *value, int overwrite);
int				is_a_builtin(char *cmd);

/*
** Functions in builtins.c
*/
int				cmd_unsetenv(int argc, char **argv);
int				cmd_setenv(int argc, char **argv);
int				cmd_echo(int agrc, char **argv);
int				cmd_type(int agrc, char **argv);
int				cmd_exit(int argc, char **argv);
int				cmd_true(int argc, char **argv);
int				cmd_false(int argc, char **argv);
int				cmd_pwd(int argc, char **argv);
int				cmd_cd(int argc, char **argv);
int				cmd_set(int argc, char **argv);
int				cmd_fg(int argc, char **argv);
int				cmd_bg(int argc, char **argv);
int				cmd_jobs(int argc, char **argv);
int				cmd_hash(int argc, char **argv);
int				cmd_export(int argc, char **argv);
int				cmd_unset(int argc, char **argv);

/*
** Hash Functions
*/
char			get_next_opt(char ***argv);
int				check_for_needed_arguments(int options_list, char **argv);
int				exec_hash_builtin(int options_list, char **argv);
int				print_hashed_commands(int options_list);
void			del_hashed_commands(void);
int				print_hashed_targets(int options_list, char **argv);
int				change_hash_entry(char *pathname, char *name);
void			remove_hash_entry(char *name);
int				print_error(int error_no, char *message, int ret);
void			print_hashed_targets_util(t_hash_table *tmp, int l_option, \
		char *arg, int multiple);
void			print_hashed_commands_util(t_hash_table *tmp, int l_option);
char			deal_with_p_opt(char ***args, int *x);
char			return_next_opt(char ***args, int *x);

/*
** Global var util for -p opt of hash builtin
*/
extern char	*g_pathname;

/*
** Functions in builtins_dispatcher.c
*/
int				builtins_dispatcher(char **argv);
typedef struct	s_builtins
{
	const char *const	key;
	int		(*const f)(int, char**);
}				t_builtins;

extern const t_builtins	g_builtins[];

struct	s_keywords
{
	const char *const	keyword;
};

#endif
