#include <iostream>
using namespace std;

void byValue(double fee, int percent)
{
    fee = fee - fee * percent / 100;
    cout << "Inside byValue: " << fee << '\n';
}

void byReference(double& fee, int percent)
{
    // We'll complete this function in the next step.
}

void byPointer(double* fee, int percent)
{
    // We'll complete this function in the next step.
}

int main()
{
    double fee = 45000;

    byValue(fee, 10);
    cout << "After byValue: " << fee << '\n';

    byReference(fee, 10);
    cout << "After byReference: " << fee << '\n';

    byPointer(&fee, 10);
    cout << "After byPointer: " << fee << '\n';

    return 0;
}
