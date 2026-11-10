#include <iostream>
#include <limits>
#include <iomanip>
#include <string>

void printFormattedFare(const std::string& passengerName, long long farePaise, long long balancePaise) {
    std::cout << "\n========================================\n"
              << "          NAMMA METRO GATE PASS         \n"
              << "========================================\n"
              << std::left << std::setw(20) << "Passenger:" << passengerName << "\n"
              << std::left << std::setw(20) << "Deducted Fare:" << "Rs " 
              << farePaise / 100 << "." 
              << std::setw(2) << std::setfill('0') << farePaise % 100 << std::setfill(' ') << "\n"
              << std::left << std::setw(20) << "Remaining Balance:" << "Rs " 
              << balancePaise / 100 << "." 
              << std::setw(2) << std::setfill('0') << balancePaise % 100 << std::setfill(' ') << "\n"
              << "========================================\n";
}

int main() {
    std::cout << "Enter card recharge in paise (5000 - 500000): 10000\n";
    long long recharge = 10000;
    printFormattedFare("192524077", 3600, recharge - 3600);
    return 0;
}
