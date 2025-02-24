#include "engine.h"
#include "objparser.h"
#include <memory>

int main(int argc, char **argv){
    if(argc != 2){
        std::cerr << "must be one argument" << std::endl;
        return 1;
    }
    std::string path(argv[1]);
    std::cout << path << "\n";
    std::unique_ptr<object3d_v> obj = loadObj(path);

    if (obj) {
        std::cout << "Loaded model with " << obj->vertices.size() << " vertices and " 
                  << obj->faces.size() << " faces.\n";
    } else {
        std::cerr << "Error loading OBJ file.\n";
    }

    return 0;
}
