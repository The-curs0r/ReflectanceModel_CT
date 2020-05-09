#ifndef LIGHTINGMODELHPP
#define LIGHTINGMODELHPP

void lightObject(light lightDetails,glm::dvec3 int_point,glm::dvec3 int_normal,object* int_object,ray& rayIn,glm::dvec3& outColor,int modelType);

#endif // !LIGHTINGMODELHPP
