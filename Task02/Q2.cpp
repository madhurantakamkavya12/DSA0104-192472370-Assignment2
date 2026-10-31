#include <iostream>
#include <vector>

int& highestMark(int marks[], int count)
{
    int best = 0;
    for (int i = 1; i < count; ++i)
        if (marks[i] > marks[best]) best = i;
    return marks[best];
}

const int& highestMarkReadOnly(const int marks[], int count)
{
    int best = 0;
    for (int i = 1; i < count; ++i)
        if (marks[i] > marks[best]) best = i;
    return marks[best];
}

int highestMarkCopy(const int marks[], int count)
{
    int best = 0;
    for (int i = 1; i < count; ++i)
        if (marks[i] > marks[best]) best = i;
    return marks[best];
}

int highestMarkIndex(const int marks[], int count)
{
    int best = 0;
    for (int i = 1; i < count; ++i)
        if (marks[i] > marks[best]) best = i;
    return best;
}

int* highestMarkPointer(int marks[], int count)
{
    return &highestMark(marks, count);
}

// Deliberately unsafe example requested by the assignment. Do not call it:
// its returned reference dangles as soon as the function returns.
int& danglingLocalReference()
{
    int local = 42;
    return local; // Expected compiler warning; using the result is undefined behavior.
}

int main()
{
    int marks[] = {78, 91, 84, 88};
    const int count = sizeof(marks) / sizeof(marks[0]);

    highestMark(marks, count) += 2;
    std::cout << "Highest after +2 moderation: " << highestMarkReadOnly(marks, count) << '\n';
    std::cout << "Copy of highest: " << highestMarkCopy(marks, count) << '\n';

    const int index = highestMarkIndex(marks, count);
    marks[index] += 1;
    std::cout << "Using index, moderated highest: " << marks[highestMarkIndex(marks, count)] << '\n';

    int* highest = highestMarkPointer(marks, count);
    *highest += 1;
    std::cout << "Using pointer, moderated highest: " << *highest << '\n';

    std::vector<int> growingMarks = {60, 70, 95};
    int& possiblyInvalid = highestMark(growingMarks.data(), static_cast<int>(growingMarks.size()));
    (void)possiblyInvalid; // Do not use after a capacity-changing vector operation.
    // A vector reallocation invalidates references, pointers and iterators to its elements.
    growingMarks.reserve(growingMarks.capacity() + 1);
    std::cout << "After vector growth, find by index again: "
              << growingMarks[highestMarkIndex(growingMarks.data(), static_cast<int>(growingMarks.size()))]
              << '\n';
}
