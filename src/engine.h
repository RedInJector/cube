#ifndef SIMPLE_3dENGINE
#define SIMPLE_3dENGINE
#include <stdlib.h>
#include <vector>
#include <memory>
#include "Math3d.h"

struct Camera_s {
  vec3f position;
  float fNear;
  float fFar;
  float fFov;
  float fAspectRatio;
  float fFovRad;
};

typedef struct Camera_s Camera;

struct transformation_s {
  vec3f position;
  vec3f rotation;
};
typedef struct transformation_s transformation;

struct object3d_s {
  transformation transform;
  transformation origin;
  int size;
  bool isVisible;
  triangle tris[];
};
typedef struct object3d_s object3d;

struct scene_s {
  int size;
  object3d *objects[];
};

typedef struct scene_s scene;

typedef struct Face_s {
    std::vector<int> vertexIndices;
} Face;


typedef struct object3d_vs {
	transformation transform;
	vec3f origin;
	bool isVisible;
	std::vector<triangle_v> triangles;
    std::vector<vec3f> vertices;
    std::vector<Face> faces;
} object3d_v;

typedef struct scene_vs {
	std::vector<std::shared_ptr<object3d_vs>> objects;
} scene_v;


/**
 * @brief creates a projection matrix for a specific camera.
 *
 * @param *c - camera to create projection matrix from
 * @param *o - output projection matrix
 * 
 */
void makeProjectionMatrix(Camera* c, mat4x4f* o);

void makeProjectionMatrix(Camera& c, mat4x4f& o);

std::shared_ptr<object3d_v> makeCubeNew();



object3d* makeCube();

object3d* makeLine();


/**
 * @brief creates a scene object that stores pointers to all objects in the scene.
 *
 * @param amount_ofObjects - amount of objects in a scene
 * @return pointer to a scene object
 *
 */
scene* makeScene(int amount_ofObjects);

std::shared_ptr<scene_v> makeSceneNew();


void applyTransform(std::shared_ptr<object3d_v> obj, mat4x4f& out);

/**
 * @brief creates a transformation matrix from objects parameters.
 * 
 * @param *obj - object to create transformation matrix for
 * @param *o - output transformation matrix
 * 
 */
void applyTransform(object3d* obj, mat4x4f* o);


/**
 * @brief Creates a camera with default values.
 * 
 * Default values:
 * 
 * - Fov: 60 deg
 * 
 * - fAspectRatio: CREEN_H / SCREEN_W
 * 
 * @param *o - output camera
 * @param SCREEN_H - height of the screen
 * @param SCREEN_W - width of the screen
 */
void makeDefaultCamera(Camera* o, int SCREEN_H, int SCREEN_W);

#endif
