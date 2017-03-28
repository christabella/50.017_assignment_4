#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <iostream>

#include "SceneParser.h"
#include "Image.h"
#include "Camera.h"
#include <string.h>

using namespace std;

float clampedDepth ( float depthInput, float depthMin , float depthMax);

#include "bitmap_image.hpp"

int main( int argc, char* argv[] )
{
    // Fill in your implementation here.

    // This loop loops over each of the input arguments.
    // argNum is initialized to 1 because the first
    // "argument" provided to the program is actually the
    // name of the executable (in our case, "a4").

    char* input;
    int width;
    int height;
    char* output;
    float depthMin;
    float depthMax;
    char* depthOutput;
    bool depthMode = false;
    
    
    // "Arguments and Parameters": http://www.cplusplus.com/articles/DEN36Up4/
    for (int argNum = 1; argNum < argc; ++argNum ) {
        std::cout << "Argument " << argNum << " is: " << argv[argNum] << std::endl;
        
        if (string(argv[argNum]) == "-input") {
            input = argv[argNum + 1];
        } else if (string(argv[argNum]) == "-size") {
            width = atoi(argv[argNum + 1]);
            height = atoi(argv[argNum + 2]);
        } else if (string(argv[argNum]) == "-output") {
            output = argv[argNum + 1];
            cout << output << endl;
        } else if (string(argv[argNum]) == "-depth") {
            depthMode = true;
            depthMin = atof(argv[argNum + 1]);
            depthMax = atof(argv[argNum + 2]);
            depthOutput = argv[argNum + 3];
//        } else if (string(argv[argNum]) == "-normals") {
//            input = argv[argNum++];
        }
    }

    


    // First, parse the scene using SceneParser.
    // Then loop over each pixel in the image, shooting a ray
    // through that pixel and finding its intersection with
    // the scene.  Write the color at the intersection to that
    // pixel in your output image.

    SceneParser scene = SceneParser(input);
    Image image = Image(width, height);
    
    Group* group = scene.getGroup();
    Camera* camera = scene.getCamera();
    float tmin = camera->getTMin();
    
    for (int j = 0; j < width; j++) {
        for (int i = 0; i < height; i++) {
            // translate image pixel coordinates (i, j) to camera point (x, y)
            // https://www.scratchapixel.com/lessons/3d-basic-rendering/ray-tracing-generating-camera-rays/generating-camera-rays
            // "We first need to normalize this pixel position using the frame's dimensions..."
            // Remap from range [0:width] and [0:height] -> [0:1] -> [-1:1]
            float x = 2.0 * ((i + 0.5) / width) - 1;
            float y = 2.0 * ((j + 0.5) / height) - 1;
            Vector2f cameraPoint = Vector2f(x, y);
            
            Ray r = camera->generateRay(cameraPoint);
            Hit h = Hit();

            if (group->intersect(r, h, tmin)) {
                Material* material = h.getMaterial();
                
                // c_pixel = k_a * c_ambient + sum[(L_i * N) * c_light * k_d)]
                Vector3f c_pixel = material->getDiffuseColor() * scene.getAmbientLight();
                
                // Loop over lights
                for (int i = 0; i < scene.getNumLights(); i++) {
                    Light* light = scene.getLight(i);

                    Vector3f point = r.pointAtParameter(h.getT());
                    Vector3f direction;
                    Vector3f color;
                    float distanceToLight;
                    
                    // Set values of direction, color
                    light->getIllumination(point, direction, color, distanceToLight);
                    
                    Vector3f c_shade = material->Shade(r, h, direction, color);
                    c_pixel += c_shade;
                }
                image.SetPixel(i, j, c_pixel);
            } else {
                image.SetPixel(i, j, scene.getBackgroundColor());
            }
        }
    }
    
    image.SaveImage(output);
    
    //Depth Implementation
    if (depthMode == true){
        Image image = Image(width, height);

        for (int i = 0; i<width; i++){
            for (int j = 0; j<height; j++){
                float x = 2.0 * ((i + 0.5) / width) - 1;
                float y = 2.0 * ((j + 0.5) / height) - 1;
                Vector2f cameraPoint = Vector2f(x, y);
                
                Ray r = camera->generateRay(cameraPoint);
                Hit h = Hit();
                
                if (group->intersect(r, h, tmin)) {
                    float t = h.getT();
                    if (t < depthMin) {
                        t = depthMin;
                    }
                    else if (h.getT() > depthMax) {
                        t = depthMax;
                    }
                    float c_pixel = (depthMax - t) / (depthMax - depthMin);
                    image.SetPixel(i, j, Vector3f(c_pixel));
                }
            }
        }
        image.SaveImage(depthOutput);
    }
}

