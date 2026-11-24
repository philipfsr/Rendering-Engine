#include "Scene.h"

Scene::Scene() {
    this-> camera = Camera{Vec3D(0, 0, 0), Vec3D(0, 0, -10)};
}

bool Scene::loadObjects() {

    //for now: hardcoded mini scene:
    Object triangleObject{};
    

    triangleObject.vertices = std::vector<Vertex>{
        Vertex{-10, -10, 0},
        Vertex{-10, 10, 0},
        Vertex{10, 0, 0}
    };

    triangleObject.triangles = std::vector<Triangle>{
        Triangle{0, 1, 2}
    };


    this->objects = std::vector<Object>{triangleObject};

    return true;
}