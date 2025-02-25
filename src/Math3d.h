// Implementation of basic matrix math formulas 
// that are used for 3d transformations

#ifndef MATH3D
#define MATH3D

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <vector>


struct vector3f_s {
  float x, y, z; 
};


/**
 * @struct vec3f
 * @brief A structure representing a 3D vector with float components.
 *
 * This structure is used to represent a 3D vector with three float values: x, y, and z.
 */
typedef struct vector3f_s vec3f;


struct triangle_s {
  vec3f p[3];
};

typedef struct triangle_vs {
    int vertexid[3];
} triangle_v;


/**
 * @struct triangle
 * @brief A structure representing a triangle matrix with float components.
 *
 * This structure is used to represent a triangle with float values as array of vec3f.
 */
typedef struct triangle_s triangle;


struct mat4x4f_s {
  float m[4][4];
};


/**
 * @struct mat4x4f
 * @brief A structure representing a 4x4 matrix with float components.
 *
 * This structure is used to represent a matrix with float values.
 */
typedef struct mat4x4f_s mat4x4f;

/**
 * @brief Default matrix initialized to zero.
 */
extern struct mat4x4f_s mat4x4f_default;


/**
 * @brief returns true if all elements of a matrix equals to 0.
 * 
 * @param mat4x4f - matrix to check
 * @return true if all elements of a matrix equals to 0, false othervise
 */
bool isMatrixZero(mat4x4f* o);


/**
 * @brief multiplies a vector by a 4x4 matrix
 * 
 * @param *i - pointer to input vector
 * @param *o - pointer to output vector
 * @param *m - pointer to a matrix
 */
void MultiplyMatrixVector(vec3f* i, vec3f* o, mat4x4f* m);


/**
 * @brief multiplies every vector in a triangle by a 4x4 matrix
 *
 * @param *i - pointer to input triangle
 * @param *o - pointer to output triangle
 * @param *m - pointer to a matrix
 */
void MultiplyMatrixTris(triangle* i, triangle* o, mat4x4f* m);
void MultiplyMatrixTris(triangle_v &i, std::vector<vec3f> vertices, triangle &o, mat4x4f &m);

/**
 * @brief Multiplies two 4x4 matrixes
 *
 * Multiplies a 4x4 matrix by another 4x4 matrix and saves results in *o
 * 
 * @param *m1 - pointer to first matrix
 * @param *m2 - pointer to second matrix
 * @param *o - pointer to output matrix
 */
void MultiplyMatrixes(mat4x4f* m1, mat4x4f* m2, mat4x4f* o);
void MultiplyMatrixes(mat4x4f &m1, mat4x4f &m2, mat4x4f &o);

/**
 * @brief Converts a 3D vector (vec3f) into a 4x4 transformation matrix.
 *
 * The function constructs a 4x4 matrix from the given 3D vector by placing
 * the vector's components in the translation column of an identity matrix:
 *
 * |x|
 * 
 * |y|
 * 
 * |z|
 * 
 * =
 * 
 * |1 0 0 x|
 * 
 * |0 1 0 y|
 * 
 * |0 0 1 z|
 * 
 * |0 0 0 1|
 * 
 *
 * @param *transform - Pointer to the input 3D vector (vec3f).
 * @param *o - Pointer to the output 4x4 transformation matrix (mat4x4f).
 */
void vecToMat(vec3f* transform, mat4x4f* o);

void vecToMat(vec3f& transform, mat4x4f& o);


/**
 * @brief Creates a 4x4 rotation matrix around the X-axis.
 *
 * Constructs a rotation matrix that rotates by `fTheta` radians around the X-axis.
 * @param fTheta - Rotation angle in radians.
 * @param *o - Pointer to the output 4x4 rotation matrix.
 */
void rotateMatrixX(float fTheta, mat4x4f* o);


/**
 * @brief Creates a 4x4 rotation matrix around the Y-axis.
 *
 * Constructs a rotation matrix that rotates by `fTheta` radians around the Y-axis.
 * @param fTheta - Rotation angle in radians.
 * @param *o - Pointer to the output 4x4 rotation matrix.
 */
void rotateMatrixY(float fTheta, mat4x4f* o);


/**
 * @brief Creates a 4x4 rotation matrix around the Z-axis.
 *
 * Constructs a rotation matrix that rotates by `fTheta` radians around the Z-axis.
 * @param fTheta - Rotation angle in radians.
 * @param *o - Pointer to the output 4x4 rotation matrix.
 */
void rotateMatrixZ(float fTheta, mat4x4f* o);


/**
 * @brief Creates a 4x4 rotation matrix around for given vector.
 *
 * Constructs a complete rotation matrix that rotates by x, y, z radians around each axis.
 * @param rotation - Rotation vector.
 * @param *o - Pointer to the output 4x4 rotation matrix.
 */
void rotateMatrix(vec3f& rotation, mat4x4f& out);


/**
 * @brief Prints matrix contents into std::cout.
 *
 * Constructs a rotation matrix that rotates by `fTheta` radians around the Z-axis.
 * @param *m - Pointer to the output 4x4 rotation matrix.
 */
void printMatrix(mat4x4f* m);

#endif
