#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <iomanip>

enum class Zone { Inner = 0, Middle = 1, Outer = 2, Airport = 3 };

constexpr long long BASE_FARES[] = {1000, 2000, 3000, 6000};
constexpr long long MIN_BALANCE_PAISE = 5000;

class MonthlyPass {
private:
    Zone zoneA;
    Zone zoneB;
    bool active;

public:
    MonthlyPass(Zone a, Zone b, bool isActive = true)
        : zoneA(a), zoneB(b), active(isActive) {}

    bool covers(Zone z) const {
        if (!active) return false;
        return (z == zoneA || z == zoneB);
    }
};

class SmartCardV2 {
private:
    std::string cardId;
    long long balancePaise;
    std::unique_ptr<MonthlyPass> pass;

public:
    SmartCardV2(std::string id, long long balance)
        : cardId(std::move(id)), balancePaise(balance), pass(nullptr) {}

    void assignPass(std::unique_ptr<MonthlyPass> p) {
        pass = std::move(p);
    }

    bool hasPassCovering(Zone z) const {
        return pass && pass->covers(z);
    }

    bool deduct(long long fare) {
        if (balancePaise - fare < MIN_BALANCE_PAISE) {
            return false;
        }
        balancePaise -= fare;
        return true;
    }

    long long getBalance() const { return balancePaise; }
    std::string getId() const { return cardId; }
};

class FareEngineV2 {
public:
    static long long computeFare(const SmartCardV2& card, Zone zone, bool isPeak, bool isWeekend) {
        if (card.hasPassCovering(zone)) {
            return 0;
        }

        long long fare = BASE_FARES[static_cast<int>(zone)];

        if (isWeekend) {
            fare -= (fare * 10) / 100;
        } else if (isPeak) {
            fare += (fare * 20) / 100;
        }

        return fare;
    }
};

int main() {
    SmartCardV2 regularCard("REG-192524077", 10000);
    SmartCardV2 passCard("PASS-192524077", 10000);

    passCard.assignPass(std::make_unique<MonthlyPass>(Zone::Inner, Zone::Airport));

    std::cout << "--- NAMMA METRO DESIGN CHALLENGE (REG: 192524077) ---\n";

    long long fare1 = FareEngineV2::computeFare(regularCard, Zone::Airport, false, true);
    regularCard.deduct(fare1);
    std::cout << "Regular Card -> Airport (Weekend): Fare = Rs " << fare1 / 100 
              << " | Remaining = Rs " << regularCard.getBalance() / 100 << "\n";

    long long fare2 = FareEngineV2::computeFare(passCard, Zone::Airport, true, false);
    passCard.deduct(fare2);
    std::cout << "Pass Card    -> Airport (Pass applied): Fare = Rs " << fare2 / 100 
              << " | Remaining = Rs " << passCard.getBalance() / 100 << "\n";

    long long fare3 = FareEngineV2::computeFare(passCard, Zone::Middle, false, false);
    passCard.deduct(fare3);
    std::cout << "Pass Card    -> Middle Zone (Not covered): Fare = Rs " << fare3 / 100 
              << " | Remaining = Rs " << passCard.getBalance() / 100 << "\n";

    return 0;
}
