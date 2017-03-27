If you are using XCode, changing arguments via
Product -> Scheme -> Edit Scheme -> Run -> Arguments 
can be quite convenient for this assignment.

-----------------------------------------
IMPROVEMENTS:

* I should not put functions that are more than one line in the header files... Should factor them out into .cpp files...
-----------------------------------------
USEFUL RESOURCES:

https://www.scratchapixel.com/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes/ray-sphere-intersection
https://www.scratchapixel.com/lessons/3d-basic-rendering/ray-tracing-generating-camera-rays/generating-camera-rays
https://en.wikipedia.org/wiki/Phong_reflection_model.
http://www.cplusplus.com/articles/DEN36Up4/

Friends like William
-----------------------------------------
THE INSTRUCTIONS ARE SO CONFUSING!

In bullet point number 11:
"Implement diffuse shading in Material class, ignoring textures for now. We provide the pure virtual Light class and two subclasses: directional light and point light. Scene lighting can be accessed with the SceneParser::getLight() and
SceneParser::getAmbientLight() methods. Use the Light method:
void getIllumination( const Vector3f& p, Vector3f& dir, Vector3f& col );
to find the illumination at a particular location in space. p is the intersection point that you want to shade, and the function returns the normalized direction toward the light source in dir and the light color and intensity in col."
"
Why do they mention the Light class when talking about the Material class? It sounds as if we need to access the Light class methods in Material class when the light data is already passed in in the parameters of Material::Shade. They should just mention that when talking about the complete lighting model.

I think bullet point 15. also has an error. Shouldn't c_s be V dot R and not L dot R? ._. "direction to the light L" should be "direction to viewer V", according to https://en.wikipedia.org/wiki/Phong_reflection_model.

-----------------------------------------
EXTRA CREDIT:
