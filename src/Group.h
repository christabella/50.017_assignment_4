#ifndef GROUP_H
#define GROUP_H


#include "Object3D.h"
#include "Ray.h"
#include "Hit.h"
#include <iostream>

using  namespace std;

///TODO:
///Implement Group
///Add data structure to store a list of Object*
class Group:public Object3D
{
public:
	
	Group(){
		
	}
	
	Group( int num_objects ){
		
	}
	
	~Group(){
		
	}
	
	virtual bool intersect( const Ray& r , Hit& h , float tmin ) {
        bool result = false;
        for (Object3D* obj : m_objects) {
            if (obj->intersect(r, h, tmin))
                result = true;
        }
		return result;
	}
	
	void addObject( int index , Object3D* obj ){
        m_objects.push_back(obj);
	}
	
	int getGroupSize(){
		return (int) m_objects.size();
	}
	
private:
    vector<Object3D*> m_objects;
};

#endif