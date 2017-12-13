#include "light.h"
#include "phong_shader.h"
#include "ray.h"
#include "render_world.h"
#include "object.h"


vec3 Phong_Shader::
Shade_Surface(const Ray& ray,const vec3& intersection_point,
    const vec3& same_side_normal, int recursion_depth) const
{
    vec3 color;
    // TODO: determine the color

    // Phong shader consists of ambient + diffuse + specular;
    // We find the components separately, sum them, and return this colour.

    //vec3 ambient = world.ambient_color + world.ambient_intensity + color_ambient;

    // L = k_d * I * max( 0, dot(n,l) )
    // where L = Lambertian pixel colour, k_d = diffuse coefficient,
    // I = intensity of light source, n = unit vector of surface normal,
    // l = unit vector pointing towards light source.

    vec3 light_color;         // Stores the light intensity of each light source based on its distance from the surface.
    vec3 diffuse = {0,0,0};   // Stores the final diffuse value.
    vec3 specular = {0,0,0};  // Stores the final specular value.

    vec3 n = same_side_normal.normalized();
    vec3 l;                   // Stores the direction of the light source with respect to the surface.
    vec3 r;                   // Stores the direction of the reflection with respect to the surface.
    vec3 v;                   //

    vec3 ambient = world.ambient_intensity * world.ambient_color * this->color_ambient;

    // For all of the lights in the scene
    for ( unsigned i = 0; i < world.lights.size(); ++i )
    {
      light_color = ( world.lights.at(i)->Emitted_Light( ray ) ) / ( ( world.lights.at(i)->position - intersection_point ).magnitude_squared() );

      l = ( world.lights.at(i)->position - intersection_point ).normalized();
      r = ( 2.0 * dot( l, n ) * n - l ).normalized();
      v = ( world.camera.position - intersection_point ).normalized();

      // Calculate the pixel's total diffuse and specular as the sum of all of the lights'
      // effect on the intersection point.
      diffuse += std::max( 0.0, dot( n , l ) ) * light_color * color_diffuse;
      specular += std::pow( std::max( 0.0, dot( v, r ) ), specular_power ) * light_color * color_specular;
    }

    color = ambient + diffuse + specular;

    return color;
}
