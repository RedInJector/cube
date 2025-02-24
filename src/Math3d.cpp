#include "Math3d.h"
#include <iostream>

struct mat4x4f_s mat4x4f_default = { 0.0f };

bool isMatrixZero(mat4x4f* o) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (o->m[i][j] != 0.0f)
                return false;
        }
    }
    return true;
}

void MultiplyMatrixVector(vec3f* i, vec3f* o, mat4x4f* m) {
    o->x = i->x * m->m[0][0] + i->y * m->m[1][0] + i->z * m->m[2][0] + m->m[3][0];
    o->y = i->x * m->m[0][1] + i->y * m->m[1][1] + i->z * m->m[2][1] + m->m[3][1];
    o->z = i->x * m->m[0][2] + i->y * m->m[1][2] + i->z * m->m[2][2] + m->m[3][2];
    float w =
        i->x * m->m[0][3] + i->y * m->m[1][3] + i->z * m->m[2][3] + m->m[3][3];

    if (w != 0.0f) {
        o->x /= w;
        o->y /= w;
        o->z /= w;
    }
}

void MultiplyMatrixTris(triangle* i, triangle* o, mat4x4f* m) {
    MultiplyMatrixVector(&i->p[0], &o->p[0], m);
    MultiplyMatrixVector(&i->p[1], &o->p[1], m);
    MultiplyMatrixVector(&i->p[2], &o->p[2], m);
}

void MultiplyMatrixes(mat4x4f* m1, mat4x4f* m2, mat4x4f* o) {
    float num = 0;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            num = 0;
            for (int k = 0; k < 4; k++)
                num += m1->m[i][k] * m2->m[k][j];
            o->m[i][j] = num;
        }
    }
}

void vecToMat(vec3f* transform, mat4x4f* o) {
    o->m[0][0] = 1;
    o->m[1][1] = 1;
    o->m[2][2] = 1;
    o->m[3][3] = 1;
    o->m[3][0] = transform->x;
    o->m[3][1] = transform->y;
    o->m[3][2] = transform->z;
}
void rotateMatrixX(float fTheta, mat4x4f* o) {
    o->m[0][0] = 1;
    o->m[1][1] = cosf(fTheta);
    o->m[1][2] = sinf(fTheta);
    o->m[2][1] = -sinf(fTheta);
    o->m[2][2] = cosf(fTheta);
    o->m[3][3] = 1;
}
void rotateMatrixY(float fTheta, mat4x4f* o) {
    o->m[0][0] = cosf(fTheta);
    o->m[2][0] = sinf(fTheta);
    o->m[1][1] = 1;
    o->m[0][2] = -sinf(fTheta);
    o->m[2][2] = cosf(fTheta);
    o->m[3][3] = 1;
}
void rotateMatrixZ(float fTheta, mat4x4f* o) {
    o->m[0][0] = cosf(fTheta);
    o->m[0][1] = sinf(fTheta);
    o->m[1][0] = -sinf(fTheta);
    o->m[1][1] = cosf(fTheta);
    o->m[2][2] = 1;
    o->m[3][3] = 1;
}

void printMatrix(mat4x4f* m) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            std::cout << m->m[i][j] << " ";
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}
