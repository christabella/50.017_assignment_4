#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "Object3D.h"
#include "vecmath.h"
#include <cmath>
#include <iostream>

using namespace std;
///TODO: implement this class.
///Add more fields as necessary,
///but do not remove hasTex, normals or texCoords
///they are filled in by other components
class Triangle: public Object3D
{
public:
	Triangle();
        ///@param a b c are three vertex positions of the triangle
	Triangle( const Vector3f& a, const Vector3f& b, const Vector3f& c, Material* m):Object3D(m){
        hasTex = false;
        m_a = a;
        m_b = b;
        m_c = c;
	}

	virtual bool intersect( const Ray& r,  Hit& h , float tmin){
        Vector3f Rd = r.getDirection(); // .normalized()?
        Vector3f Ro = r.getOrigin();
        
        float alpha, beta, gamma, t;
        
        Matrix3f A(m_a.x()-m_b.x(), m_a.x()-m_c.x(), Rd.x(),
                   m_a.y()-m_b.y(), m_a.y()-m_c.y(), Rd.y(),
                   m_a.z()-m_b.z(), m_a.z()-m_c.z(), Rd.z());
        
        float detA = A.determinant();
        
        Matrix3f betaMatrix(m_a.x()-Ro.x(), m_a.x()-m_c.x(), Rd.x(),
                            m_a.y()-Ro.y(), m_a.y()-m_c.y(), Rd.y(),
                            m_a.z()-Ro.z(), m_a.z()-m_c.z(), Rd.z());
        
        Matrix3f gammaMatrix(m_a.x()-m_b.x(), m_a.x()-Ro.x(), Rd.x(),
                             m_a.y()-m_b.y(), m_a.y()-Ro.y(), Rd.y(),
                             m_a.z()-m_b.z(), m_a.z()-Ro.z(), Rd.z());
        
        beta =  betaMatrix.determinant() / detA;
        gamma = gammaMatrix.determinant() / detA;
        
        Matrix3f tMatrix(m_a.x()-m_b.x(), m_a.x()-m_c.x(), m_a.x()-Ro.x(),
                         m_a.y()-m_b.y(), m_a.y()-m_c.y(), m_a.y()-Ro.y(),
                         m_a.z()-m_b.z(), m_a.z()-m_c.z(), m_a.z()-Ro.z());
        
        t = tMatrix.determinant() / detA;
        
        if (beta + gamma > 1 || beta < 0 || gamma < 0){
            return false;
        }
        
        if (t >= tmin && t < h.getT()) {
            // Interpolate normals and texture coordinates
            Vector3f normal = (alpha*normals[0] + beta*normals[1] + gamma*normals[2]).normalized();
            Vector2f texCoord = (alpha*texCoords[0] + beta*texCoords[1] + gamma*texCoords[2]);

            h.set(t, material, normal);
            h.setTexCoord(texCoord);
            
            return true;
        }
        return false;
    }
	bool hasTex;
	Vector3f normals[3];
	Vector2f texCoords[3];
protected:
    Vector3f m_a, m_b, m_c;
};

#endif //TRIANGLE_H
