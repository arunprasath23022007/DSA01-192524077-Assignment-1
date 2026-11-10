# Task 11: Production Architecture Defense

1. **Decoupled Architecture**: Strict separation of concerns between `SmartCard` (state management and balance invariant validation), `FareEngine` (pricing algorithm), and `GateController` (turnstile physical interactions).
2. **Integer Paise Monetary Model**: Floating-point datatypes are strictly prohibited in financial transactions to prevent cumulative IEEE-754 precision drift. All ledger records use 64-bit signed integers (`long long`).
3. **Dynamic Tariff Ingestion**: Fare tables and peak time windows are externalized to configuration modules, allowing tariff updates without requiring source recompilation.
4. **Boundary Invariant Enforcement**: Card balance validations are strictly verified before approving entry, ensuring `balance - fare >= MIN_BALANCE_PAISE`.
