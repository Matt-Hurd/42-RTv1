//Don't turn in

#include "rtv1.h"
#include <stdio.h>

void	print_vec3(t_vec3 v)
{
	printf("(x: %f, y: %f, z: %f)\n", v.x, v.y, v.z);
}

void	print_RGB(t_RGB rgb)
{
	printf("(r: %f, g: %f, b: %f)\n", rgb.r, rgb.g, rgb.b);
}

void	print_properties(t_props p)
{

	printf("Pos: ");
	print_vec3(p.pos);
	printf("Rot: ");
	print_vec3(p.rot);
	printf("Density: %f\n", p.density);
	printf("Color: ");
	print_RGB(p.color);
	printf("Reflectivity: %f\n", p.reflect);
	printf("Radiance: %f\n\n", p.radiance);
}

void	print_sphere_info(t_sphere *sphere)
{
	printf("[sphere]\n");
	printf("Radius: %f\n", sphere->radius);
	print_properties(sphere->props);
}

void	print_plane_info(t_plane *plane)
{
	printf("[plane]\n");
	print_properties(plane->props);
}

void	print_cone_info(t_cone *cone)
{
	printf("[cone]\n");
	printf("Radius: %f\n", cone->radius);
	printf("Height: %f\n", cone->height);
	print_properties(cone->props);
}

void	print_cylinder_info(t_cylinder *cylinder)
{
	printf("[cylinder]\n");
	printf("Radius: %f\n", cylinder->radius);
	printf("Height: %f\n", cylinder->height);
	print_properties(cylinder->props);
}

void	print_light_info(t_light *light)
{
	printf("[light]\n");
	print_properties(light->props);
}

void	print_scene_info(t_data *d)
{
	printf("Name: %s\n", d->scene->name);
	printf("Size: %dx%d\n", d->scene->size.x, d->scene->size.y);
	printf("Cam Pos: ");
	print_vec3(d->scene->cam_pos);
	printf("Cam Rot: ");
	print_vec3(d->scene->cam_rot);
	printf("\n");
	t_list *a;
	a = d->scene->objects;
	while (a)
	{
		if (a->content_size == SPHERE)
			print_sphere_info(a->content);
		if (a->content_size == CONE)
			print_cone_info(a->content);
		if (a->content_size == CYLINDER)
			print_cylinder_info(a->content);
		if (a->content_size == PLANE)
			print_plane_info(a->content);
		if (a->content_size == LIGHT)
			print_light_info(a->content);
		a = a->next;
	}
}
