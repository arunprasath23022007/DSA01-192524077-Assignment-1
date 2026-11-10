#include <iostream>
#include <string>

namespace Procedural {
    struct SmartCardData {
        long long balancePaise;
    };

    bool deduct(SmartCardData& card, long long farePaise, long long minBalance) {
        if (card.balancePaise - farePaise >= minBalance) {
            card.balancePaise -= farePaise;
            return true;
        }
        return false;
    }
}

namespace OOP {
    class SmartCard {
    private:
        std::string cardId;
        long long balancePaise;
        static constexpr long long MIN_BALANCE_PAISE = 5000;

    public:
        SmartCard(std::string id, long long initialBalance)
            : cardId(std::move(id)), balancePaise(initialBalance) {}

        bool canTravel(long long fare) const {
            return (balancePaise - fare) >= MIN_BALANCE_PAISE;
        }

        bool deduct(long long fare) {
            if (!canTravel(fare)) {
                return false;
            }
            balancePaise -= fare;
            return true;
        }

        long long getBalance() const { return balancePaise; }
    };
}

int main() {
    Procedural::SmartCardData pCard{6000};
    pCard.balancePaise = -1000;

    OOP::SmartCard oopCard("SC001", 6000);
    bool success = oopCard.deduct(2000);
    std::cout << "Procedural Corrupted Balance: " << pCard.balancePaise << " paise\n";
    std::cout << "OOP Deduction successful: " << std::boolalpha << success 
              << " | Final Balance: " << oopCard.getBalance() << " paise\n";
    return 0;
}
