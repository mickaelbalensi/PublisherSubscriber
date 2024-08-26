#ifndef SHAPE_FACTORY
#define SHAPE_FACTORY

#include <unordered_map>  // unordered_map
#include <memory>         // shared_ptr
#include <functional>     // std::function
#include "shapes.hpp"

class ShapeFactory
{
public:
    ShapeFactory();

    std::shared_ptr<IShape> CreateShape(SHAPE shape, int size = 0);

private:
    void AddShape(SHAPE shape, std::function<std::shared_ptr<IShape>(int)> func);

    std::unordered_map<SHAPE, std::function<std::shared_ptr<IShape>(int)>> m_shapes;
};

#endif // SHAPE_FACTORY
