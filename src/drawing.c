/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelhajou <zelhajou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 16:57:43 by zelhajou          #+#    #+#             */
/*   Updated: 2023/12/31 17:56:55 by zelhajou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	ft_put_pixel_to_image(t_fractol *fractol, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && x < WINDOW_WIDTH && y >= 0 && y < WINDOW_HEIGHT)
	{
		dst = fractol->image.addr + (y * fractol->image.line_length
				+ x * (fractol->image.bits_per_pixel / 8));
		*(unsigned int *)dst = color;
	}
}

double	ft_scale_coordinate_x(t_fractol *fractol, int x)
{
	double	center_x;

	center_x = WINDOW_WIDTH / 2.0;
	return ((x - center_x) * (4.0 * fractol->zoom) / WINDOW_WIDTH);
}

double	ft_scale_coordinate_y(t_fractol *fractol, int y)
{
	double	center_y;
	double	inverted_y;

	center_y = WINDOW_HEIGHT / 2.0;
	inverted_y = WINDOW_HEIGHT - y;
	y = inverted_y - center_y;
	return (y * (4.0 * fractol->zoom) / WINDOW_HEIGHT);
}

void	ft_draw_fractal_pixel(t_fractol *fractol, int x, int y)
{
	int	color;
	int	iterations;

	iterations = 0;
	fractol->pixel.real = ft_scale_coordinate_x(fractol, x);
	fractol->pixel.imaginary = ft_scale_coordinate_y(fractol, y);
	if (fractol->fractal_choice == 1)
		iterations = ft_calculate_mandelbrot(fractol, fractol->max_iterations);
	else if (fractol->fractal_choice == 2)
		iterations = ft_calculate_julia(fractol, fractol->max_iterations);
	color = ft_determine_color(iterations, fractol->max_iterations);
	ft_put_pixel_to_image(fractol, x, y, color);
}
