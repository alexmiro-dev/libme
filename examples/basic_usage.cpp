
#include <array>
#include <print>

// ATTENTION: This import must be after the includes, otherwise will get multiple definition errors
import me.ds.circular_buffer;

int main() {
    me::ds::circular_buffer<int, 5> buffer;

    std::array<int, 4> const v = {1, 2, 3, 4};
    me::ds::circular_buffer<int, 5> buffer2(v);

    me::ds::circular_buffer<int, 5> buffer3{buffer2};

    // auto const buffer4{buffer2};


    /*
    // Demonstrate basic operations
    std::cout << "Adding numbers 1-5 to buffer...\n";
    for(int i = 1; i <= 5; ++i) {
        buffer.push(i);
        std::cout << "Pushed: " << i << ", Size: " << buffer.size() << "\n";
    }

    std::cout << "\nBuffer full? " << (buffer.full() ? "Yes" : "No") << "\n";
    std::cout << "Front element: " << buffer.front() << "\n";
    */

    return 0;
}