import me.ds.circular_buffer;
#include <iostream>

int main() {
    me::ds::circular_buffer<int, 5> buffer;

    // Demonstrate basic operations
    std::cout << "Adding numbers 1-5 to buffer...\n";
    for(int i = 1; i <= 5; ++i) {
        buffer.push(i);
        std::cout << "Pushed: " << i << ", Size: " << buffer.size() << "\n";
    }

    std::cout << "\nBuffer full? " << (buffer.full() ? "Yes" : "No") << "\n";
    std::cout << "Front element: " << buffer.front() << "\n";

    return 0;
}