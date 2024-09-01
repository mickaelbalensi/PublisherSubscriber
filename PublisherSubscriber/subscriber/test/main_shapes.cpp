#include "subscriber_shapes.hpp"
#include <thread>
#include <chrono>

int main(int argc, char *argv[]) {

    std::shared_ptr<SHAPE[]> shapes(new SHAPE[argc - 1]);

    for (int i = 1; i < argc; i++)
    {
        if (strncmp(argv[i], "1", 1) == 0)
        {
            shapes[i - 1] = SHAPE::CIRCLE;
        }
        else 
        {
            shapes[i - 1] = SHAPE::RECTANGLE;
        }
    }

    Subscriber subscriber(shapes, argc - 1);
    std::this_thread::sleep_for(std::chrono::seconds(30));

    return 0;
}
