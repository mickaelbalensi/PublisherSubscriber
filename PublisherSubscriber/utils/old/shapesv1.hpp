#ifndef SHAPES_HPP
#define SHAPES_HPP

#include <memory>                // std::shared_ptr
#include <cstring>               // memcpy
#include <iostream>              // cout

enum SHAPE
{
    CIRCLE = 0,
    RECTANGLE = 1
};

struct Coordinate
{
    unsigned int m_latitude;
    unsigned int m_longitude;
};

enum COLORS 
{
    BLUE,
    GREEN
};

class ISerialize
{
public:
    virtual ~ISerialize() = 0;

    virtual std::shared_ptr<char[]> Serialize() = 0;
    virtual void Deserialize(char* buffer) = 0;

    virtual size_t GetSize() = 0;
protected:
};

struct IShape : private ISerialize
{
    explicit IShape(SHAPE shape, COLORS color, unsigned int size);
    virtual ~IShape() = 0;

    std::shared_ptr<char[]> Serialize() override = 0; 
    void Deserialize(char* buffer) override = 0;
    virtual void print() const = 0;

    SHAPE m_shape;
    COLORS m_color;
    unsigned int m_size;
    Coordinate m_coordinates;

    size_t GetSize() override;
private:  
    int m_clock;
};

struct Circle : public IShape
{
public:
    explicit Circle(unsigned int size);

    std::shared_ptr<char[]> Serialize() override;
    void Deserialize(char* buffer) override;
    void print() const override;

    size_t GetSize() override;

    
protected:

};

struct Rectangle : public IShape
{
public:
    explicit Rectangle(unsigned int size);

    std::shared_ptr<char[]> Serialize() override;
    void Deserialize(char* buffer) override;
    void print() const override;

    size_t GetSize() override;
protected:
};

#endif // SHAPES_HPP
