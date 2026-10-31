#include <chrono>
#include <cstddef>
#include <iostream>

// Q7 redesign based on Q4: shifting the retained history costs O(k) per new
// transaction once full. A circular array retains the same fixed storage and
// overwrites the oldest entry in O(1). Both versions run the same workload.
constexpr std::size_t CAPACITY = 50;
constexpr std::size_t OPERATIONS = 5'000'000;

struct ShiftingHistory {
    long long data[CAPACITY]{};
    std::size_t size = 0;
    void add(long long value) {
        if (size < CAPACITY) data[size++] = value;
        else {
            for (std::size_t i = 1; i < CAPACITY; ++i) data[i - 1] = data[i];
            data[CAPACITY - 1] = value;
        }
    }
    long long checksum() const {
        long long sum = 0;
        for (std::size_t i = 0; i < size; ++i) sum += data[i];
        return sum;
    }
};

struct CircularHistory {
    long long data[CAPACITY]{};
    std::size_t size = 0;
    std::size_t next = 0; // slot where next value is written; also oldest after full
    void add(long long value) {
        data[next] = value;
        next = (next + 1) % CAPACITY;
        if (size < CAPACITY) ++size;
    }
    long long checksum() const {
        long long sum = 0;
        for (std::size_t i = 0; i < size; ++i) sum += data[i];
        return sum;
    }
};

template <typename History>
long long runWorkload()
{
    History history;
    for (std::size_t i = 0; i < OPERATIONS; ++i)
        history.add(static_cast<long long>(i % 1000));
    return history.checksum();
}

int main()
{
    const auto shiftStart = std::chrono::steady_clock::now();
    const long long shiftSum = runWorkload<ShiftingHistory>();
    const auto shiftEnd = std::chrono::steady_clock::now();

    const auto circleStart = std::chrono::steady_clock::now();
    const long long circleSum = runWorkload<CircularHistory>();
    const auto circleEnd = std::chrono::steady_clock::now();

    const auto shiftMs = std::chrono::duration<double, std::milli>(shiftEnd - shiftStart).count();
    const auto circleMs = std::chrono::duration<double, std::milli>(circleEnd - circleStart).count();
    std::cout << "Original shift checksum: " << shiftSum << "\nOriginal milliseconds: " << shiftMs
              << "\nCircular checksum: " << circleSum << "\nCircular milliseconds: " << circleMs << '\n';
    std::cout << "Same retained data: " << std::boolalpha << (shiftSum == circleSum) << '\n';
}
