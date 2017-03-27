#ifndef SPHERE_H
#define SPHERE_H

#include "Object3D.h"
#include "vecmath.h"
#include <cmath>

#include <iostream>
using namespace std;
///TODO:
///Implement functions and add more fields as necessary
class Sphere: public Object3D
{
public:
	Sphere(){ 
		//unit ball at the center
        m_center = Vector3f();
        m_radius = 1.0;
	}

	Sphere( Vector3f center , float radius , Material* material ):Object3D(material){
        m_center = center;
        m_radius = radius;
        m_material = material;
	}
	

	~Sphere(){}

	virtual bool intersect( const Ray& r , Hit& h , float tmin){
        /* Ray-Sphere Intersection
         
         Sub. explicit ray equation into implicit plane equation and solve for 
         closest positive t.
         
         (Rd*Rd) t^2 + (2Rd*Ro) t + (Ro*Ro - r^2) = 0
         '--,--'       '---,--'     '-----,-----'
            a              b              c
         
         a = 1 since ||Rd|| = ||d|| = 1
         
         discriminant = b^2 - 4a*c
         
         */
        Vector3f Rd = r.getDirection();
        Vector3f Ro = r.getOrigin() - m_center; // uhhh...
        
        float a = Vector3f::dot(Rd, Rd); // should = 1
        float b = 2.0 * Vector3f::dot(Rd, Ro);
        float c = Vector3f::dot(Ro, Ro) - m_radius*m_radius;
        
        float discriminant = b*b - 4*a*c;
        float t0 = (-b - sqrt(discriminant)) / (2.0 * a);
        float t1 = (-b + sqrt(discriminant)) / (2.0 * a);
        
        if (discriminant >= 0) {
            // Check t0 which should be closer to the ray origin
            if (t0 >= tmin && t0 < h.getT()) {
                Vector3f normal = (r.pointAtParameter(t0) - m_center).normalized();
                
                // Update Hit
                h.set(t0, m_material, normal);
                return true;
            }
            
            // Check t1
            if (t1 >= tmin && t1 < h.getT()) {
                Vector3f normal = (r.pointAtParameter(t1) - m_center).normalized();
                
                h.set(t1, m_material, normal);
                return true;
            }
        }
        
        return false;
	}

private:
    Vector3f m_center;
    float m_radius;
    Material* m_material;

};


#endif
