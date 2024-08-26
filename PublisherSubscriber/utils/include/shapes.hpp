#ifndef SHAPES_HPP
#define SHAPES_HPP

#include <cstdint>
#include <cstring>
#include <arpa/inet.h>  // For htonl and ntohl
#include <memory>


enum class SHAPE : uint32_t
{
    CIRCLE = 0,
    RECTANGLE = 1
};

struct Coordinate
{
    uint32_t m_latitude;
    uint32_t m_longitude;

    explicit Coordinate();
};

enum class COLORS : uint32_t
{
    BLUE,
    GREEN
};

class ISerialize
{
public:
    virtual ~ISerialize() = default;

    virtual std::shared_ptr<uint8_t[]> Serialize() /*const*/= 0;
    virtual void Deserialize(const std::shared_ptr<uint8_t[]>& buffer)/*const*/ = 0;

    virtual size_t GetSerializedSize() const = 0;
protected:
};

#pragma pack(push, 1)
struct ShapeHeader
{
    uint32_t magic;     // Magic number for type safety
    uint32_t version;   // For future versioning
    SHAPE shape;
    COLORS color;
    uint32_t size;
    Coordinate coordinates;
};
#pragma pack(pop)

class IShape : public ISerialize
{
public:
    explicit IShape(SHAPE shape, COLORS color, uint32_t size);
    virtual ~IShape() = default;

    std::shared_ptr<uint8_t[]> Serialize() override = 0;
    void Deserialize(const std::shared_ptr<uint8_t[]>& buffer) override = 0;
    virtual void print() const = 0;

    size_t GetSerializedSize() const override = 0;

protected:
    ShapeHeader m_header;

private:
    static const uint32_t MAGIC = 0x53484150;  // "SHAP" in ASCII
    static const uint32_t VERSION = 1;
};

class Circle : public IShape
{
public:
    explicit Circle(uint32_t size);

    std::shared_ptr<uint8_t[]> Serialize() override;
    void Deserialize(const std::shared_ptr<uint8_t[]>& buffer) override;
    void print() const override;

    size_t GetSerializedSize() const override;
};

class Rectangle : public IShape
{
public:
    explicit Rectangle(uint32_t size);

    std::shared_ptr<uint8_t[]> Serialize() override;
    void Deserialize(const std::shared_ptr<uint8_t[]>& buffer) override;
    void print() const override;

    size_t GetSerializedSize() const override;
};

#endif