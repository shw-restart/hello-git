#include <iostream>
#include <condition_variable>
#include <thread>
#include <vector>

using namespace std;

mutex lock;
condition_variable cv;
int ready = 0; // 表示应该第i个线程进行等待


void func(int seq, int times, int count) {
    int time = 0;
    unique_lock<mutex> ul(lock);
    while (time < times) {
        while (ready != seq) {
            cv.wait(ul);
        }
        cout << static_cast<char>(seq + 'A') << " ";
        ++time;
        ready = (ready + 1) % count;
        cv.notify_all();

    }
}

int main() {
    vector<thread> contains;
    int count = 10;
    int times = 2;
    for (int i = 0; i < count; ++i) {
        contains.emplace_back(thread(func, i, times, count));
    }
    for (auto& _thread : contains) {
        _thread.join();
    }
    cout << "所有输出结束" << endl;



    return 0;
}