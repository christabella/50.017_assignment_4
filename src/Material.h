#ifndef MATERIAL_H
#define MATERIAL_H

#include <cassert>
#include "vecmath.h"

#include "Ray.h"
#include "Hit.h"
#include "texture.hpp"
///TODO:
///Implement Shade function that uses ambient, diffuse, specular and texture
class Material
{
public:
	
    Material( const Vector3f& d_color ,const Vector3f& s_color=Vector3f::ZERO, float s=0):
    diffuseColor( d_color),specularColor(s_color), shininess(s) {}

    virtual ~Material() {}

    virtual Vector3f getDiffuseColor() const 
    { 
        return  diffuseColor;
    }


    Vector3f Shade( const Ray& ray, const Hit& hit,
                  const Vector3f& dirToLight, const Vector3f& lightColor ) {
        
        /*** Diffuse Component ***/
        Vector3f N = hit.getNormal().normalized();
        
        float diffuseShading = Vector3f::dot(N, dirToLight);
        // Clamp diffuseShading
        if (diffuseShading < 0)
            diffuseShading = 0;
        
        Vector3f diffuseComponent;
        if (t.valid()) {
            Vector3f textureColor = t(hit.texCoord[0], hit.texCoord[1]);
            diffuseComponent = diffuseShading * lightColor * textureColor;
        } else {
            diffuseComponent = diffuseShading * lightColor * diffuseColor;
        }
        
        /*** Specular Component ***/
        // direction of reflected ray R = 2 * (dirToLight.N) * N - dirToLight
        // The specular term is large only when the viewer direction V is aligned with the reflection direction R.
        // https://en.wikipedia.org/wiki/Phong_reflection_model
        Vector3f R = 2 * diffuseShading * N - dirToLight;
        Vector3f V = -ray.getDirection().normalized();
        
        float specularShading = Vector3f::dot(V, R);
        if (specularShading < 0)
            specularShading = 0;
        
        Vector3f specularComponent = pow(specularShading, shininess) * lightColor * specularColor;
        
        return diffuseComponent + specularComponent;
    }

    void loadTexture(const char * filename){
        t.load(filename);
    }
 protected:
    Vector3f diffuseColor;
    Vector3f specularColor;
    float shininess;
    Texture t;
};



#endif // MATERIAL_H
