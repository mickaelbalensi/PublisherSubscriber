#include "../include/shapes.hpp"

#include <stdexcept> // runtime_error
#include <iostream> // cout
#include <random>

// Add these global variables at the top
std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution<uint32_t> distribution(0, 100000000); // Range of 0 to 100,000,000 for latitude and longitude

const char* BLUEPRINT = "\033[0;34m";
const char* GREENPRINT = "\033[0;32m";
const char* WHITEPRINT = "\033[0;37m";

Coordinate::Coordinate()
{
    m_latitude = distribution(gen);
    m_longitude = distribution(gen);
}

IShape::IShape(SHAPE shape, COLORS color, uint32_t size)
    : m_header{MAGIC, VERSION, shape, color, size, Coordinate()} {}

std::shared_ptr<uint8_t[]> IShape::Serialize() {
    std::shared_ptr<uint8_t[]> buffer(new uint8_t[GetSerializedSize()]);
    auto* header = reinterpret_cast<ShapeHeader*>(buffer.get());

    header->magic = htonl(MAGIC);
    header->version = htonl(VERSION);
    header->shape = static_cast<SHAPE>(htonl(static_cast<uint32_t>(m_header.shape)));
    header->color = static_cast<COLORS>(htonl(static_cast<uint32_t>(m_header.color)));
    header->size = htonl(m_header.size);
    header->coordinates.m_latitude = htonl(m_header.coordinates.m_latitude);
    header->coordinates.m_longitude = htonl(m_header.coordinates.m_longitude);

    return buffer;
}

void IShape::Deserialize(const std::shared_ptr<uint8_t[]>& buffer) {
    if (!buffer) {
        throw std::runtime_error("NULL Buffer for deserialization");
    }

    const auto* header = reinterpret_cast<const ShapeHeader*>(buffer.get());

    uint32_t magic = ntohl(header->magic);
    if (magic != MAGIC) {
        throw std::runtime_error("Invalid magic number in buffer");
    }

    uint32_t version = ntohl(header->version);
    if (version != VERSION) {
        throw std::runtime_error("Unsupported version number");
    }

    m_header.shape = static_cast<SHAPE>(ntohl(static_cast<uint32_t>(header->shape)));
    m_header.color = static_cast<COLORS>(ntohl(static_cast<uint32_t>(header->color)));
    m_header.size = ntohl(header->size);
    m_header.coordinates.m_latitude = ntohl(header->coordinates.m_latitude);
    m_header.coordinates.m_longitude = ntohl(header->coordinates.m_longitude);
}

size_t IShape::GetSerializedSize() const {
    return sizeof(ShapeHeader);
}

void IShape::print() const 
{      
    std::cout << "Color: " << static_cast<int>(m_header.color) << "\n";
    std::cout << "Size: " << m_header.size << "\n";
    std::cout << "Coordinates: (" << m_header.coordinates.m_latitude
              << ", " << m_header.coordinates.m_longitude << ")\n";
}

Circle::Circle(uint32_t size)
    : IShape(SHAPE::CIRCLE, COLORS::GREEN, size) {}

std::shared_ptr<uint8_t[]> Circle::Serialize() {
    return IShape::Serialize();
}

void Circle::Deserialize(const std::shared_ptr<uint8_t[]>& buffer) {
    IShape::Deserialize(buffer);
}

void Circle::print() const {
std::cout << "**************************************" << std::endl;
    if (m_header.color == COLORS::BLUE) 
        std::cout << BLUEPRINT;
    else if (m_header.color == COLORS::GREEN)
        std::cout << GREENPRINT;
    std::cout << "Shape: Circle\n";
    IShape::print();

    std::cout << WHITEPRINT;
    std::cout << "**************************************" << std::endl;
}

size_t Circle::GetSerializedSize() const {
    return IShape::GetSerializedSize();
}

Rectangle::Rectangle(uint32_t size)
    : IShape(SHAPE::RECTANGLE, COLORS::BLUE, size) {}

std::shared_ptr<uint8_t[]> Rectangle::Serialize() {
    return IShape::Serialize();
}

void Rectangle::Deserialize(const std::shared_ptr<uint8_t[]>& buffer) {
    IShape::Deserialize(buffer);
}

void Rectangle::print() const {
std::cout << "**************************************" << std::endl;
    if (m_header.color == COLORS::BLUE) 
        std::cout << BLUEPRINT;
    else if (m_header.color == COLORS::GREEN)
        std::cout << GREENPRINT;
    std::cout << "Shape: Rectangle\n";
    IShape::print();

    std::cout << WHITEPRINT;
    std::cout << "**************************************" << std::endl;
}

size_t Rectangle::GetSerializedSize() const {
    return IShape::GetSerializedSize();
}
