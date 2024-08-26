#include "shapesv1.hpp"

const char* BLUEPRINT = "\033[0;34m";
const char* GREENPRINT = "\033[0;32m";
const char* WHITEPRINT = "\033[0;37m";
    
ISerialize::~ISerialize() {}

IShape::IShape(SHAPE shape, COLORS color, unsigned int size)
    :m_shape(shape), m_color(color), m_size(size), m_coordinates() {}

IShape::~IShape() {}

std::shared_ptr<char[]> IShape::Serialize() {
    size_t size = GetSize();

    std::shared_ptr<char[]> bufferPtr(new char[size]);
    char *buffer = bufferPtr.get();
    size_t offset = 0;

    *(SHAPE*)(buffer) = m_shape;
    offset += sizeof(m_shape);

    *(COLORS*)(buffer + offset) = m_color; 
    offset += sizeof(m_color);

    *(unsigned int*)(buffer + offset) = m_size;
    offset += sizeof(m_size);

    *(unsigned int*)(buffer + offset) = m_coordinates.m_latitude;
    offset += sizeof(m_coordinates.m_latitude);

    *(unsigned int*)(buffer + offset) = m_coordinates.m_longitude;

    return bufferPtr;
}

void IShape::Deserialize(char* buffer) {
    memcpy(&m_shape, buffer, sizeof(m_shape));
    buffer += sizeof(m_shape);

    memcpy(&m_color, buffer, sizeof(m_color));

    buffer += sizeof(m_color);
    memcpy(&m_size, buffer, sizeof(m_size));

    buffer += sizeof(m_size);
    memcpy(&m_coordinates.m_latitude, buffer, sizeof(m_coordinates.m_latitude));

    buffer += sizeof(m_coordinates.m_latitude);
    memcpy(&m_coordinates.m_longitude, buffer, sizeof(m_coordinates.m_longitude));
}

size_t IShape::GetSize() {
    return sizeof(m_color) + sizeof(m_size) 
        + sizeof(m_coordinates.m_latitude) + sizeof(m_coordinates.m_longitude);
}

void IShape::print() const 
{      
    std::cout << "Color: " << m_color << "\n";
    std::cout << "Size: " << m_size << "\n";
    std::cout << "Coordinates: (" << m_coordinates.m_latitude
              << ", " << m_coordinates.m_longitude << ")\n";
}

Circle::Circle(unsigned int size)
    : IShape(SHAPE::CIRCLE, COLORS::GREEN, size) {}

std::shared_ptr<char[]> Circle::Serialize() {
    std::shared_ptr<char[]> buffer(new char[GetSize()]);
    memcpy(buffer.get(), IShape::Serialize().get(), IShape::GetSize());
    return buffer;
}

void Circle::Deserialize(char* buffer) {
    IShape::Deserialize(buffer);

    
}

void Circle::print() const {
    std::cout << "**************************************" << std::endl;
    if (m_color == COLORS::BLUE) 
        std::cout << BLUEPRINT;
    else if (m_color == COLORS::GREEN)
        std::cout << GREENPRINT;
    std::cout << "Shape: Circle\n";
    IShape::print();

    std::cout << WHITEPRINT;
    std::cout << "**************************************" << std::endl;

}

size_t Circle::GetSize() {
    return IShape::GetSize();
}

Rectangle::Rectangle(unsigned int size)
    : IShape(SHAPE::RECTANGLE, COLORS::BLUE, size) {}

std::shared_ptr<char[]> Rectangle::Serialize() {
    /* std::shared_ptr<char[]> buffer(new char[GetSize()]);
    memcpy(buffer.get(), IShape::Serialize().get(), IShape::GetSize());
 */
    return IShape::Serialize();
}

void Rectangle::Deserialize(char* buffer) {
    IShape::Deserialize(buffer);
}

void Rectangle::print() const {
    std::cout << "**************************************" << std::endl;

    if (m_color == COLORS::BLUE) 
        std::cout << BLUEPRINT;
    else if (m_color == COLORS::GREEN)
        std::cout << GREENPRINT;
    std::cout << "Shape: Rectangle\n";
    IShape::print();

    std::cout << WHITEPRINT;
    std::cout << "**************************************" << std::endl;

}

size_t Rectangle::GetSize() {
    return IShape::GetSize();
}
