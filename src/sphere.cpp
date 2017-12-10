#include "sphere.h"
#include "ray.h"


// Determine if the ray intersects with the sphere
bool Sphere::Intersection(const Ray& ray, std::vector<Hit>& hits) const
{
    // TODO
    // MY WORK BEGIN

    vec3 w = ray.direction;
    vec3 u = ray.endpoint;
    vec3 v = u - center;
    double discriminant;

    //discriminant = pow( dot( ray.direction, ray.endpoint - center ), 2.0 ) - ( dot( ray.direction, ray.direction ) * ( dot( ray.endpoint - center, ray.endpoint - center ) - pow( radius, 2.0)) );
    discriminant = pow( dot( w, v ), 2.0 ) - ( dot( w, w ) * ( dot( v, v ) - pow( radius, 2.0)) );

    //if ( discriminant > 0 )
      //std::cout << "discriminant is " << discriminant << std::endl << std::endl;

    // No intersection
    if ( discriminant < 0.0 )
    {
      return false;
    }

    // Tangent intersection at a single point

    else if ( discriminant == 0.0 )
    {
      // Calculate the t value of the single hit, then push_back into hits.

      // t = -b/2a : in this case, a == 1 since a == dot(direction, direction), and direction is normalized)
      //double t = -( dot( ray.direction, ray.endpoint - center ) ) / dot( ray.direction, ray.direction );
      double t = (-( dot( w, v ) ) + sqrt( discriminant )) / dot( w, w );

      Hit h1 = { this, t, true };
      hits.push_back( h1 );

      return true;
    }

    // Two intersections
    else if ( discriminant > 0.0 )
    {
      // Calculate the t values of both hits, then push_back into hits.

      // t = -b - sqrt(b^2 - 4ac)/2a
      //double t1 = (-( dot( ray.direction, ray.endpoint - center ) ) - sqrt( discriminant )) / dot( ray.direction, ray.direction );
      double t1 = (-( dot( w, v ) ) - sqrt( discriminant )) / dot( w, w );

      //  t = -b + sqrt(b^2 - 4ac)/2a
      double t2 = (-( dot( w, v ) ) + sqrt( discriminant )) / dot( w, w );

      Hit h1 = { this, t1, false };
      Hit h2 = { this, t2, true };

      if ( t1 >= 0.0 )
        hits.push_back( h1 );

      if ( t2 >= 0.0 )
        hits.push_back( h2 );

      return true;
    }

    // MY WORK END
    return false;
}

vec3 Sphere::Normal(const vec3& point) const
{
    vec3 normal;
    // TODO: set the normal
    return normal;
}
