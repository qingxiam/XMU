#include <iostream>
#include <thread>
#include <vector>
#include <ctime>
#include <cstdlib>
const int NUM_NODES = 5;
const int MAX_RETRY = 3;
void csmaThread(int nodeId) {
    for (int retry = 0; retry < MAX_RETRY; ++retry) {
        std::this_thread::sleep_for(std::chrono::milliseconds(rand() % 100));
        bool collision = rand() % 2;
        if (!collision) {
            std::cout << "Node " << nodeId << " sent successfully!\n";
            return;
        }
        int delay = (1 << retry) * 100; 
        std::this_thread::sleep_for(std::chrono::milliseconds(delay));
    }
    std::cout << "Node " << nodeId << " failed after retries!\n";
}
int main() {
    srand(time(nullptr));
    std::vector<std::thread> threads;
    for (int i = 0; i < NUM_NODES; ++i) {
        threads.emplace_back(csmaThread, i);
    }
    for (auto& th : threads) th.join();
    return 0;
}
