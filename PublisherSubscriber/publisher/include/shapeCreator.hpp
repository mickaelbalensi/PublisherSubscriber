#ifndef SHAPE_CREATOR
#define SHAPE_CREATOR

#include "../../utils/include/shapes.hpp"
#include "../../utils/include/shapeFactory.hpp"
#include "publisher.hpp"  // Publisher
#include <unordered_map>  // std::unordered_map


class ShapeCreator
{
public:
    explicit ShapeCreator(unordered_map<SHAPE, unsigned int>);

    void AddShape(SHAPE shape, unsigned int frequency);

private:
    ShapeFactory m_shapeFactory;
    Publisher m_pub;
    int m_clock;
    std::unordered_map<SHAPE, unsigned int> m_frequency;

    void Create();
};

#endif // SHAPE_CREATOR
