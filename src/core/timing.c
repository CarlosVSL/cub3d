#include "../../include/cub3d.h"

/* ------------------------------------------------------------------------ */
double	timer_delta(void)
{
	static struct timeval	prev;
	static int				init;
	struct timeval			now;
	double					dt;

	gettimeofday(&now, NULL);
	if (!init)
	{
		prev = now;
		init = 1;
		return (0.0);
	}
	dt = (now.tv_sec - prev.tv_sec)
		+ (now.tv_usec - prev.tv_usec) / 1000000.0;
	prev = now;
	return (dt);
}

/* ------------------------------------------------------------------------ */
void	timer_sleep(long target_fps, double dt)
{
	struct timeval	start;
	struct timeval	now;
	double			frame_time;
	double			elapsed;

	if (target_fps <= 0)
		return ;
	frame_time = 1.0 / (double)target_fps;
	if (dt >= frame_time)
		return ;
	gettimeofday(&start, NULL);
	elapsed = 0.0;
	while (elapsed < frame_time - dt)
	{
		gettimeofday(&now, NULL);
		elapsed = (now.tv_sec - start.tv_sec)
			+ (now.tv_usec - start.tv_usec) / 1000000.0;
	}
}
