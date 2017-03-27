#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "vecmath.h"
#include "Object3D.h"
///TODO implement this class
///So that the intersect function first transforms the ray
///Add more fields as necessary
class Transform: public Object3D
{
public: 
    Transform(){}
    Transform( const Matrix4f& m, Object3D* obj ):m_o(obj){
        m_M = m;
    }
    ~Transform(){}
    
    virtual bool intersect( const Ray& r , Hit& h , float tmin){
        Vector3f origin_WS = r.getOrigin();
        Vector3f origin_OS = (m_M.inverse() * Vector4f(origin_WS, 1)).xyz();
        
        Vector3f direction_WS = r.getDirection();
        Vector3f direction_OS = (m_M.inverse() * Vector4f(direction_WS, 0)).xyz();
        
        Ray ray_OS = Ray(origin_OS, direction_OS);
        
        if (m_o->intersect(ray_OS, h, tmin)) {
            Vector3f normal_WS = h.getNormal();
            Vector3f normal_OS = ( m_M.inverse().transposed() * Vector4f(normal_WS, 0)).xyz();
            h.set(h.getT(), h.getMaterial(), normal_OS);
            return true;
        }
        
        return false;
    }

    protected:
        Object3D* m_o; //un-transformed object
        Matrix4f m_M;
};

#endif //TRANSFORM_H
