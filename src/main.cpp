#include "fixed_queue.hpp"
#include <cstdint>

int main() {
    FixedQueue<uint16_t, 8> q;
    q.push(100);
    q.push(200);

    uint16_t val;
    q.pop(val);
    
    return 0;
}
