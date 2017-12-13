#include "plane.h"
#include "ray.h"
#include <cfloat>


// Intersect with the half space defined by the plane.  The plane's normal
// points outside.  If the ray starts on the "inside" side of the plane, be sure
// to record a hit with t=0 as the first entry in hits.
bool Plane::
Intersection(const Ray& ray, std::vector<Hit>& hits) const
{
    // TODO
    // NOTE: Recall that ray is the camera ray, and so ray.endpoint() is the camera poition.
    // Formula for a ray: p(t) = e + tw;
    // Formula for plane: f(p) = N * ( p - x1 ) = 0;
    // Solve for t by plugging camera ray in for p of plane eqn.
    // Don't forget to handle cases.
    // x1 is a property of plane (see plane.h).

    double t;   // Parametric value in the ray equation p(t) = e + tw
                // where e is ray.endpoint() and w is ray.direction();

    if ( dot( normal, ray.direction ) == 0.0 )
    {
      return false;
    }

    else if ( dot( normal, ray.direction ) != 0.0 )
    {
      t = -( dot( normal, ( ray.endpoint - x1 ) ) ) / ( dot( normal, ray.direction ) );

      if ( t < 0.0 )
        return false;

      else if ( t >= 0.0 )
      {
        Hit h = { this, t, false };
        hits.push_back( h );

        return true;
      }
    }

    return false;
}

vec3 Plane::
Normal(const vec3& point) const
{
    return normal;
}
