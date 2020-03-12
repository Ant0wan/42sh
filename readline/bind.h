/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bind.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 17:20:25 by abarthel          #+#    #+#             */
/*   Updated: 2020/03/10 14:13:21 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BIND_H
# define BIND_H

# include "keymaps.h"

extern struct s_keymap_entry	*g_keymap;

void	insert_text(const char *string, int len);
void	clear_line(void);

void	bind_keys(struct s_keymap_entry *keymap);
void	cut_prev_wd(void);
void	clear_befline(void);
void	paste_via_input(unsigned long v);
void	clip_paste(void);
void	wd_right(void);
void	wd_left(void);
void	clear_scr(void);
void	clear_eol(void);
void	autocomplete(void);
void	rl_home(void);
void	rl_void(void);
void	rl_end(void);
void	rl_delete(void);
void	rl_backspace(void);
void	rl_insert(int c);
void	cursor_l(void);
void	cursor_r(void);
void	cursor_u(void);
void	cursor_d(void);
void	history_up(void);
void	history_down(void);
void	kill_line(void);

#endif