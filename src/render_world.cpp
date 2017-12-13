#include "render_world.h"
#include "flat_shader.h"
#include "object.h"
#include "light.h"
#include "ray.h"


Render_World::Render_World()
    :background_shader(0),ambient_intensity(0),enable_shadows(true),
    recursion_depth_limit(3)
{}

Render_World::~Render_World()
{
    delete background_shader;
    for(size_t i=0;i<objects.size();i++) delete objects[i];
    for(size_t i=0;i<lights.size();i++) delete lights[i];
}

// Find the closest object of intersection and return the object that was
// intersected.  Record the Hit structure in hit.  If no intersection occurred,
// return NULL.  Note that in the case of a Boolean, the object returned will be
// the Boolean, but the object stored in hit will be the underlying primitive.
// Any intersection with t<=small_t should be ignored.
Object* Render_World::Closest_Intersection(const Ray& ray, Hit& hit)
{
    // TODO
    // MY WORK BEGIN
    Object *nearest_object = NULL;

    hit.t = std::numeric_limits<decltype(hit.t)>::max();

    // For all Object pointers in the objects vector
    for ( unsigned i = 0; i < objects.size(); ++i )
    {
      // FIXME: What does this get initialized to? What should its size be, and
      // what should be the properties of its Hit elements?
      std::vector<Hit> hits;

      if ( objects.at(i)->Intersection(ray, hits) )
      {
        for ( unsigned j = 0; j < hits.size(); ++j )
        {
          // FIXME: Verify that this is the correct condition: not sure if hit.t
          // is a vector of Hit object and needs to be referenced using .at(i), or
          // if it is a single Hit object
          if ( hits.at(j).t < hit.t && hits.at(j).t > small_t )
          {
            hit = hits.at(j);
            nearest_object = objects.at(i);
          }
        }
      }
    }

    return nearest_object;
    // MY WORK END
}

// set up the initial view ray and call
void Render_World::Render_Pixel(const ivec2& pixel_index)
{
    Ray ray; // TODO: set up the initial view ray here
    // MY WORK BEGIN

    ray.endpoint = camera.position;
    ray.direction = ( camera.World_Position(pixel_index) - camera.position ).normalized();

    // MY WORK END

    vec3 color=Cast_Ray(ray,1);
    camera.Set_Pixel(pixel_index,Pixel_Color(color));
}

void Render_World::Render()
{
    for(int j=0;j<camera.number_pixels[1];j++)
        for(int i=0;i<camera.number_pixels[0];i++)
            Render_Pixel(ivec2(i,j));
}

// cast ray and return the color of the closest intersected surface point,
// or the background color if there is no object intersection
vec3 Render_World::Cast_Ray(const Ray& ray,int recursion_depth)
{
    // TODO
    vec3 color;

    // MY WORK BEGIN
    Hit hit;
    Object *object;

    // If an intersection occurs between the cast ray and the object
    if ( (object = Closest_Intersection(ray, hit)) != NULL )
    {
      // Create a vector to store the hits
      std::vector<Hit> hits;

      // Set the truth value of the object intersection
      hit.object->Intersection(ray, hits);

      // Get the normal of the intersection point
      vec3 normal = hit.object->Normal( ray.Point(hit.t) );

      if ( hit.ray_exiting )
        normal = normal * -1.0;

      // Determine the colour of the surface pixel using the ray, the point, the normal information,
      // and the recursion depth (in the case that the intersecting ray was itself cast from another
      // reflection).
      color = object->material_shader->Shade_Surface( ray, ray.Point( hit.t ), normal, recursion_depth );
    }

    // If there is no intersection, the assigned colour is the default background shader effect.
    else
      color = background_shader->Shade_Surface( ray, ray.endpoint, ray.endpoint, recursion_depth );

    // MY WORK END

    return color;
}
