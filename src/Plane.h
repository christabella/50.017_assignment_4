#ifndef PLANE_H
#define PLANE_H

#include "Object3D.h"
#include "vecmath.h"
#include <cmath>
using namespace std;
///TODO: Implement Plane representing an infinite plane
///choose your representation , add more fields and fill in the functions
class Plane: public Object3D
{
public:
	Plane() {}
	Plane( const Vector3f& normal , float d , Material* m):Object3D(m) {
        m_normal = normal;
        m_D = d;
        m_material = m;
	}
	~Plane() {}
	virtual bool intersect( const Ray& r , Hit& h , float tmin) {
        Vector3f Rd = r.getDirection();
        Vector3f Ro = r.getOrigin();
        
        // t = -(D + n.Ro) / n.Rd
        float denom = Vector3f::dot(m_normal, Rd);
        if (denom == 0) // direction of ray is parallel to plane
            return false;
        
        float t = -(m_D + Vector3f::dot(m_normal, Ro)) / denom;
        if (t >= tmin && t < h.getT()) {            
            // Update Hit
            h.set(t, m_material, m_normal);
            return true;
        }
		return false;
	}
	
protected:
    Vector3f m_normal;
    float m_D; // offset from the origin
    Material* m_material;
};
#endif //PLANE_H


