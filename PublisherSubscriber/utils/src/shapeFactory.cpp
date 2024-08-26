#include "../include/shapeFactory.hpp"

ShapeFactory::ShapeFactory() {
    AddShape(SHAPE::CIRCLE, [](int size) { return std::make_shared<Circle>(size); });
    AddShape(SHAPE::RECTANGLE, [](int size) { return std::make_shared<Rectangle>(size); });
}

std::shared_ptr<IShape> ShapeFactory::CreateShape(SHAPE shape, int size) {
    return m_shapes[shape](size);
}

void ShapeFactory::AddShape(SHAPE shape, std::function<std::shared_ptr<IShape>(int)> func) {
    m_shapes[shape] = func;
}
