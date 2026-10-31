#include <iostream>

class Time {
    int h, m;
public:
    Time(int hh, int mm) : h(hh), m(mm) {}
    friend int minutesBetween(const Time& a, const Time& b);
    friend bool earlier(const Time& a, const Time& b);
};

inline int minutesBetween(const Time& a, const Time& b)
{
    int first = a.h * 60 + a.m;
    int second = b.h * 60 + b.m;
    int difference = first - second;
    return difference < 0 ? -difference : difference;
}

inline bool earlier(const Time& a, const Time& b)
{
    return a.h < b.h || (a.h == b.h && a.m < b.m);
}

int main()
{
    Time departure(9, 45), arrival(13, 10);
    std::cout << minutesBetween(departure, arrival) << ' '
              << std::boolalpha << earlier(arrival, departure) << '\n';

    Time noonBefore(11, 59), noonAfter(12, 1), same(12, 1);
    std::cout << minutesBetween(noonBefore, noonAfter) << ' '
              << earlier(noonBefore, noonAfter) << ' '
              << earlier(same, noonAfter) << '\n';
}
