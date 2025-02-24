#ifndef OBJ_PARSER
#define OBJ_PARSER

#include "Math3d.h"
#include "engine.h"
#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>

std::unique_ptr<object3d_v> loadObj(const std::string &filename) {
    std::ifstream file(filename);
    if(!file.is_open()){
        std::cerr << "Failed to load object from" << filename << std::endl;
        return nullptr;
    }

    std::unique_ptr<object3d_v> object = std::make_unique<object3d_v>();

    std::string line;
    while (std::getline(file, line)){
        std::istringstream iss(line);
        std::string prefix;
        iss >> prefix;

        if (prefix == "v"){
            vec3f vertex;
            iss >> vertex.x >> vertex.y >> vertex.z;
            object->vertices.push_back(vertex);            
        }
        else if (prefix == "vt"){
            
        }
        else if (prefix == "vn"){

        }
        else if (prefix == "f"){
            Face face;
            std::string vertexData;
            while (iss >> vertexData){
                std::istringstream vData(vertexData);
                std::string vIndex, tIndex, nIndex;

                std::getline(vData, vIndex, '/');
                std::getline(vData, nIndex, '/');
                std::getline(vData, tIndex, '/');

                if(!vIndex.empty())
                    face.vertexIndices.push_back(std::stoi(vIndex) - 1);

            }

            object->faces.push_back(face);

            // Triangulate if more than 3 vertices
            std::vector<int> vIndices = face.vertexIndices;
            for (size_t i = 1; i + 1 < vIndices.size(); i++) {
                triangle_v tri;
                tri.vertexid[0] = vIndices.at(0);
                tri.vertexid[1] = vIndices.at(i);
                tri.vertexid[2] = vIndices.at(i + 1);

                object->triangles.push_back(tri);
            }
        }
    }
    
    file.close();
    return object;
}

#endif
