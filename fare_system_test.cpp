#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

enum class Zone { Inner, Middle, Outer };

struct TestCase {
    std::string description;
    Zone zone;
    int hour;
    int minute;
    long long initialBalance;
    long long expectedFare;
    bool expectedAllowed;
};

class FareEngine {
public:
    static bool isPeak(int hour, int minute) {
        int timeMinutes = hour * 60 + minute;
        bool morningPeak = (timeMinutes >= 8 * 60) && (timeMinutes < 10 * 60);
        bool eveningPeak = (timeMinutes >= 17 * 60) && (timeMinutes < 20 * 60);
        return morningPeak || eveningPeak;
    }

    static long long calculateFare(Zone zone, int hour, int minute) {
        long long basePaise = 0;
        switch (zone) {
            case Zone::Inner:  basePaise = 1000; break;
            case Zone::Middle: basePaise = 2000; break;
            case Zone::Outer:  basePaise = 3000; break;
        }
        if (isPeak(hour, minute)) {
            basePaise += (basePaise * 20) / 100;
        }
        return basePaise;
    }
};

int main() {
    std::vector<TestCase> suite = {
        {"Normal Inner Off-Peak", Zone::Inner, 11, 0, 10000, 1000, true},
        {"Peak Outer 08:00 (Boundary)", Zone::Outer, 8, 0, 10000, 3600, true},
        {"Boundary 10:00 AM (Off-Peak)", Zone::Inner, 10, 0, 10000, 1000, true},
        {"Boundary 17:00 (Evening Peak)", Zone::Middle, 17, 0, 10000, 2400, true},
        {"Boundary 20:00 (Off-Peak)", Zone::Middle, 20, 0, 10000, 2000, true},
        {"Low Balance Rejection", Zone::Outer, 9, 0, 6000, 3600, false}
    };

    std::cout << std::left << std::setw(32) << "Test Case"
              << std::setw(15) << "Calculated"
              << std::setw(15) << "Expected"
              << "Status\n";
    std::cout << std::string(70, '-') << "\n";

    for (const auto& test : suite) {
        long long fare = FareEngine::calculateFare(test.zone, test.hour, test.minute);
        bool allowed = (test.initialBalance - fare) >= 5000;
        bool pass = (fare == test.expectedFare) && (allowed == test.expectedAllowed);

        std::cout << std::left << std::setw(32) << test.description
                  << std::setw(15) << fare
                  << std::setw(15) << test.expectedFare
                  << (pass ? "[PASS]" : "[FAIL]") << "\n";
    }
    return 0;
}
