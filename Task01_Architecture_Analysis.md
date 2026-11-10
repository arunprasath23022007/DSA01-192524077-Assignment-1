# Task 01: Object Identification and Domain Modeling

## 1. Core Object Identification & Responsibilities
- **`SmartCard`**:
  - Maintains `cardId` and `balancePaise` (stored as 64-bit integer paise).
  - Enforces the business invariant: `balance - fare >= MIN_BALANCE_PAISE` (Rs 50 = 5000 paise).
  - Rejects transactions that would leave less than Rs 50.
- **`Journey`**:
  - Holds trip metadata: `sourceStation`, `destStation`, `farthestZone`, entry time (`hour`, `minute`), and passenger profile.
- **`FareEngine`**:
  - Encapsulates fare calculation based on zones, dynamic peak surcharges (20%), and passenger concession rules.
- **`Passenger`**:
  - Categorizes commuter tier (Regular, Student - 25% discount, Senior Citizen - 50% discount).

## 2. Key OOP Principles
1. **Encapsulation**: `balancePaise` is private inside `SmartCard`; mutations are strictly mediated through `canTravel()`, `deduct()`, and `recharge()`.
2. **Abstraction**: Turnstile hardware invokes `card.deduct(fare)` without knowing internal representation or rounding logic.
3. **Polymorphism**: `DiscountPolicy` hierarchy enables plugging new concession models without altering core fare deduction code.

## 3. Complexity & Maintainability
- **Time/Space Complexity**: Journey validation runs in O(1) time and requires O(1) auxiliary memory per card.
- **Maintainability**: In a procedural codebase, updating the minimum reserve balance requires searching and modifying manual checks scattered across many functions. In OOP, updating `MIN_BALANCE_PAISE` in `SmartCard` automatically enforces the invariant globally.
