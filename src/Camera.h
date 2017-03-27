#ifndef CAMERA_H
#define CAMERA_H

#include "Ray.h"
#include "vecmath.h"
#include <float.h>
#include <cmath>


class Camera
{
public:
	//generate rays for each screen-space coordinate
	virtual Ray generateRay( const Vector2f& point ) = 0 ; 
	
	virtual float getTMin() const = 0 ; 
	virtual ~Camera(){}
protected:
	Vector3f m_center;
	Vector3f m_direction;
	Vector3f m_up;
	Vector3f m_horizontal;

};

///TODO: Implement Perspective camera
///Fill in functions and add more fields if necessary
class PerspectiveCamera: public Camera
{
public:
	PerspectiveCamera(const Vector3f& center, const Vector3f& direction,const Vector3f& up , float angle){
        m_center = center;
        m_direction = direction;
        m_up = up;
        m_angle = angle;
	}

	virtual Ray generateRay( const Vector2f& point){
        float x = point[0];
        float y = point[1];
        float D = 1.0/tan(m_angle / 2.0);
        
        Vector3f w = m_direction.normalized();
        Vector3f u = (Vector3f::cross(w, m_up)).normalized();
        Vector3f v = (Vector3f::cross(u, w)).normalized();
        
        // direction
        
        Vector3f r = x*u + y*v + D*w;
        
        Vector3f d = r.normalized();
        
		return Ray(m_center, d);
	}

	virtual float getTMin() const { 
		return 0.0f;
	}

private:
    float m_angle;

};

#endif //CAMERA_H
