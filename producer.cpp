#include <iostream>
#include <cstdlib>
#include <ctime>

struct item {
    int id;
    int quantity;
    int price;
};

int main() {
    srand(time(nullptr));

    static int in = 0;
    static int out = 0;
    static int BUFFER_SIZE = (rand() % 100) + 1;
    item buffer[BUFFER_SIZE];

    item next_produced;
    while (true) {

        next_produced.id = (rand() % 100) + 1;
        next_produced.quantity = (rand() % 100) + 1;
        next_produced.price = (rand() % 100) + 1;

        while (((in + 1) % BUFFER_SIZE) == out)
            continue;

        buffer[in] = next_produced;
        in = (in + 1) % BUFFER_SIZE;

        /* std::cout << "Produced: " << next_produced.id << std::endl; */
    }
}
