#include <iostream>
#include <iomanip>

int main() {
    constexpr long long TOTAL_JOURNEYS = 3000000LL;
    constexpr long long FARE_PAISE = 3600LL;
    constexpr double FARE_RUPEES = 36.00;

    int intPaiseTotal = 0;
    long long llPaiseTotal = 0;
    double doubleRupeesTotal = 0.0;

    for (long long i = 0; i < TOTAL_JOURNEYS; ++i) {
        intPaiseTotal += static_cast<int>(FARE_PAISE);
        llPaiseTotal += FARE_PAISE;
        doubleRupeesTotal += FARE_RUPEES;
    }

    std::cout << "--- 3,000,000 Journeys Accumulation Report ---\n";
    std::cout << "Expected Fare Sum:       " << TOTAL_JOURNEYS * FARE_PAISE << " paise (Rs 108,000,000)\n";
    std::cout << "32-bit signed int Total: " << intPaiseTotal << " paise [OVERFLOW DETECTED]\n";
    std::cout << "64-bit long long Total:  " << llPaiseTotal << " paise [EXACT]\n";
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Double Accumulation:     Rs " << doubleRupeesTotal << "\n";
    return 0;
}
