#include "engine.h"

triangle t[12] = {
    // SOUTH
    {0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f},
    {0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f},

    // EAST
    {1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f},
    {1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f},

    // NORTH
    {1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f},
    {1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f},

    // WEST
    {0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f},
    {0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f},

    // TOP
    {0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f},
    {0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f},

    // BOTTOM
    {1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f},
    {1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f},
};

void makeProjectionMatrix(Camera* c, mat4x4f* o) {
    o->m[0][0] = c->fAspectRatio * c->fFovRad;
    o->m[1][1] = c->fFovRad;
    o->m[2][2] = c->fFar / (c->fFar - c->fNear);
    o->m[3][2] = (-c->fFar * c->fNear) / (c->fFar - c->fNear);
    o->m[2][3] = 1.0f;
    o->m[3][3] = 0.0f;
}
void makeProjectionMatrix(Camera &c, mat4x4f &o) {
    o.m[0][0] = c.fAspectRatio * c.fFovRad;
    o.m[1][1] = c.fFovRad;
    o.m[2][2] = c.fFar / (c.fFar - c.fNear);
    o.m[3][2] = (-c.fFar * c.fNear) / (c.fFar - c.fNear);
    o.m[2][3] = 1.0f;
    o.m[3][3] = 0.0f;
}

std::shared_ptr<object3d_v> makeCubeNew() {
    std::shared_ptr<object3d_v> obj = std::make_shared<object3d_v>();

    obj->triangles.reserve(12);
    obj->isVisible = true;

    obj->transform.position.x = 0.0f;
    obj->transform.position.y = 0.0f;
    obj->transform.position.z = 0.0f;

    obj->transform.rotation.x = 0.0f;
    obj->transform.rotation.y = 0.0f;
    obj->transform.rotation.z = 0.0f;

    obj->origin.x = -0.5f;
    obj->origin.y = -0.5f;
    obj->origin.z = -0.5f;

    for (int i = 0; i < 12; i++) {
        for (int j = 0; j < 3; j++) {
            obj->triangles.push_back(t[i]);
        }
    }

    return obj;
}

object3d* makeCube() {
    // This is bad. malloc in c++? herecy...
    // i don't care. It all started as a raw C code.
    // Why did i make it cpp later? I don't remember.
    // who cares anyway
    object3d* o = (object3d*)malloc(sizeof(object3d) + sizeof(triangle[12]));
    o->isVisible = true;
    o->transform.position.x = 0.0f;
    o->transform.position.y = 0.0f;
    o->transform.position.z = 0.0f;

    o->transform.rotation.x = 0.0f;
    o->transform.rotation.y = 0.0f;
    o->transform.rotation.z = 0.0f;

    o->origin.position.x = -0.5f;
    o->origin.position.y = -0.5f;
    o->origin.position.z = -0.5f;

    o->size = 12;

    for (int i = 0; i < 12; i++) {
        for (int j = 0; j < 3; j++) {
            o->tris[i].p[j] = t[i].p[j];
        }
    }

    return o;
}

object3d* makeLine() {
    object3d* o = (object3d*)malloc(sizeof(object3d) + sizeof(triangle[2]));
    o->transform.position.x = 0.0f;
    o->transform.position.y = 0.0f;
    o->transform.position.z = 0.0f;

    o->transform.rotation.x = 0.0f;
    o->transform.rotation.y = 0.0f;
    o->transform.rotation.z = 0.0f;

    o->size = 2;

    vec3f p1 = { -0.500000f, 0.000000f, 0.012500f };
    vec3f p2 = { 0.500000f, 0.000000f, 0.012500f };
    vec3f p3 = { -0.500000f, 0.000000f, -0.012500f };
    vec3f p4 = { 0.500000f, 0.000000f, -0.012500f };
    o->tris[0].p[0] = p1;
    o->tris[0].p[1] = p2;
    o->tris[0].p[2] = p3;

    o->tris[1].p[0] = p3;
    o->tris[1].p[1] = p4;
    o->tris[1].p[2] = p2;

    return o;
}

scene* makeScene(int amount_ofObjects) {
    scene* s = (scene*)malloc(sizeof(scene) + amount_ofObjects * sizeof(object3d*));
    s->size = amount_ofObjects;
    return s;
}

std::shared_ptr<scene_v> makeSceneNew() {
    std::shared_ptr<scene_v> scene = std::make_shared<scene_v>();
    return scene;
}

void applyTransform(std::shared_ptr<object3d_v> obj, mat4x4f &out) {
    mat4x4f matRot = mat4x4f_default, matTransf = mat4x4f_default;

    out = mat4x4f_default;

    vecToMat(obj->origin, matTransf);

    rotateMatrix(obj->transform.rotation, matRot);

    MultiplyMatrixes(matTransf, matRot, out);
}

void applyTransform(object3d* obj, mat4x4f* o) {
    mat4x4f matRot = mat4x4f_default, matTransf = mat4x4f_default,
        buf2 = mat4x4f_default;

    *o = mat4x4f_default;
    matTransf = mat4x4f_default;
    vecToMat(&obj->origin.position, &matTransf);

    rotateMatrix(obj->transform.rotation, matRot);

    MultiplyMatrixes(&matTransf, &matRot, &buf2);
    *o = buf2;
}



void makeDefaultCamera(Camera* o, int SCREEN_H, int SCREEN_W) {
    vec3f p = o->position;
    o->position = p;
    o->fFar = 1000.0f;
    o->fFov = 40.0f;
    o->fAspectRatio = (float)SCREEN_H / (float)SCREEN_W;
    o->fFovRad = 1.0f / tanf(o->fFov * 0.5f / 180.0f * 3.14159f);
}