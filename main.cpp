#include <iostream>
#include <algorithm>
#include "circular_buffer.h"

int main()
{
    container::circular_buffer<int, 10> cb{};
    std::cout << cb.front() << std::endl;
    //std::for_each(cb.begin(), cb.end(), [] (auto value) { std::cout << value << std::endl; });
}
