#include <iostream>
#include <string>

struct Parcel { double kilograms; bool express; bool insured; };

// Weight in grams: integer overload. The rate is illustrative: 2 currency units / 100 g.
double charge(int grams, bool express = false, bool insured = false)
{
    std::cout << "charge(int grams) selected; ";
    return grams * 0.02 + (express ? 50 : 0) + (insured ? 20 : 0);
}

// Weight in kilograms: floating-point overload.
double charge(double kilograms, bool express = false, bool insured = false)
{
    std::cout << "charge(double kg) selected; ";
    return kilograms * 200 + (express ? 50 : 0) + (insured ? 20 : 0);
}

double charge(const Parcel& parcel)
{
    std::cout << "charge(Parcel) selected; ";
    return parcel.kilograms * 200 + (parcel.express ? 50 : 0) + (parcel.insured ? 20 : 0);
}

int main()
{
    // The originally proposed overload set is ambiguous: one- and two-argument
    // overloads overlap with the 3-parameter function's defaults. This redesigned
    // set has only the int, double and Parcel signatures above.
    Parcel p{2.0, true, false};
    std::cout << "charge(2): "; std::cout << charge(2) << '\n';       // exact int match
    std::cout << "charge(2.0f): "; std::cout << charge(2.0f) << '\n'; // float promotes to double
    std::cout << "charge(2.0): "; std::cout << charge(2.0) << '\n'; // exact double match
    std::cout << "charge(200, true): "; std::cout << charge(200, true) << '\n';
    std::cout << "charge(1.5, false, true): "; std::cout << charge(1.5, false, true) << '\n';
    std::cout << "charge(p): "; std::cout << charge(p) << '\n';
}
