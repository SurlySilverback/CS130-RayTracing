#include "light.h"
#include "phong_shader.h"
#include "ray.h"
#include "render_world.h"
#include "object.h"


vec3 Phong_Shader::
Shade_Surface(const Ray& ray,const vec3& intersection_point,
    const vec3& same_side_normal,int recursion_depth) const
{
    vec3 color;
    // TODO: determine the color

    // Phong shader consists of ambient + diffuse + specular;
    // We find the components separately, sum them, and return this colour.

    vec3 ambient = world.ambient_color + world.ambient_intensity + color_ambient;

    // L = k_d * I * max( 0, dot(n,l) )
    // where L = Lambertian pixel colour, k_d = diffuse coefficient,
    // I = intensity of light source, n = unit vector of surface normal,
    // l = unit vector pointing towards light source
    vec3 diffuse = max( 0, dot( same_side_normal.normalized() , intersection_point.normalized() ) );

    vec3 specular =

    color = ambient + diffuse + specular;

    return color;
}
