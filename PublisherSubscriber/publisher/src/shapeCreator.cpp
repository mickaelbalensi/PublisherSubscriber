#include "../include/shapeCreator.hpp"

using namespace std::chrono_literals;

unsigned int DEFAULT_SIZE = 1;

ShapeCreator::ShapeCreator(unordered_map<SHAPE, unsigned int> map_shapes) : m_pub(), m_clock(0) {
    for (auto p : map_shapes) {
        AddShape(p.first, p.second);      
    }
    cout << "shapes added" << endl;

    Create();
}

void ShapeCreator::AddShape(SHAPE shape, unsigned int frequency) {
    m_frequency[shape] = frequency;
}

void ShapeCreator::Create() {
    int i = 15;
    while (i--) {
        std::this_thread::sleep_for(1s);
        ++m_clock;

        for (const auto& p : m_frequency) {
            if (m_clock % p.second == 0) {
                m_pub.Publish(p.first, m_shapeFactory.CreateShape(p.first, DEFAULT_SIZE++));
            }
        }
    }
}
