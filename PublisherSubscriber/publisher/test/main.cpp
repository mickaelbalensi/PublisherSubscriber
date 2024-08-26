#include "../include/shapeCreator.hpp"
#include <iostream>

using namespace std;
int main() {
    unordered_map<SHAPE, unsigned int> map_shapes{{SHAPE::CIRCLE, 2}, {SHAPE::RECTANGLE, 1}};

    ShapeCreator creator(map_shapes);

    //creator.AddShape(CIRCLE, 2);
    //creator.AddShape(RECTANGLE, 1);
    return 0;
}
