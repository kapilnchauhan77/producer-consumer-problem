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

    item next_consumed;
    while (true) {

        while (in == out)
            continue;

        next_consumed = buffer[out];
        out = (out + 1) % BUFFER_SIZE;

        std::cout << "Consumed: " << next_consumed.id << std::endl;
    }
}
