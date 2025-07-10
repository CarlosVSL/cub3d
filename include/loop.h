#ifndef LOOP_H
# define LOOP_H

int	set_hooks(t_cub *cub);
int	loop_hook(void *param);
int	key_press(int keycode, void *param);
int	key_release(int keycode, void *param);
int	exit_program(void *param);

#endif
