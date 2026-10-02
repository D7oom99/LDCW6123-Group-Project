# Test Plan – Member 6 (Testing & Git Log)

Program: VPN Advisor & Cost Calculator (main.cpp)
Test cases designed by Member 4 (Program Design), run by Member 6.
Build command: `g++ -std=c++17 -Wall -Wextra -o vpn main.cpp` (compiled with no errors or warnings)

## Test Cases

Input order: purpose, country, device, months, devices

| TC | Description | Input | Expected Output | Actual Output | Pass/Fail |
|----|-------------|-------|-----------------|---------------|-----------|
| 1 | Streaming, 12-month plan | Streaming, Malaysia, Laptop, 12, 3 | WireGuard; no warning; RM9.00/month; total RM108.00 | WireGuard; "No major VPN restrictions"; RM9.00/month; total RM108.00 | Pass |
| 2 | Public Wi-Fi on phone | Public Wi-Fi, Malaysia, Phone, 1, 1 | IKEv2/IPsec; total RM15.00 | IKEv2/IPsec; total RM15.00 | Pass |
| 3 | Public Wi-Fi on laptop (if inside case 3) | Public Wi-Fi, Other, Laptop, 1, 1 | WireGuard; total RM15.00 | WireGuard; total RM15.00 | Pass |
| 4 | Privacy in China, 7 devices | Privacy, China, Laptop, 24, 7 | OpenVPN TCP 443; China warning + extra warning; RM10.75/month; total RM258.00 | OpenVPN over TCP port 443; China warning + EXTRA WARNING; extra fee RM4.00; RM10.75/month; total RM258.00 | Pass |
| 5 | Remote work in Russia, exactly 5 devices | Remote work, Russia, Router, 12, 5 | IKEv2/IPsec; Russia warning only; no extra fee; total RM108.00 | IKEv2/IPsec; Russia warning only; extra fee RM0.00; total RM108.00 | Pass |
| 6 | Gaming in Iran, max devices | Gaming, Iran, PC, 1, 10 | WireGuard; Iran warning; RM25.00 | WireGuard; Iran warning; extra fee RM10.00; total RM25.00 | Pass |
| 7 | Out-of-range menu choice | Purpose = 9 | "Invalid choice" message, asks again | "Invalid choice. Please enter a number from 1 to 5." then asks again | Pass |
| 8 | Letters instead of number | Purpose = abc | No crash or endless loop, asks again | "Invalid choice" message, asks again, no crash | Pass |
| 9 | Devices below and above limit | Devices = 0, then 11 | Both rejected, asks again | Both rejected with "Invalid choice" message | Pass |
| 10 | Plan length not offered | Plan length = 6 | Rejected (only 1, 12 or 24 allowed) | "Only 1, 12 or 24 months are available." then asks again | Pass |
| 11 | Repeat with small letter | Again = y | Program starts again | Program asks all questions again | Pass |
| 12 | Exit | Again = N | Goodbye message, program ends | "Goodbye, Ali!" and program ends | Pass |

## Extra Tests (added by Member 6)

| TC | Description | Input | Expected Output | Actual Output | Pass/Fail |
|----|-------------|-------|-----------------|---------------|-----------|
| 13 | Empty name | (press Enter) | Rejected, asks again | "Name cannot be empty." then asks again | Pass |
| 14 | Name with a space | Ali Ahmed | Full name used | "Hello, Ali Ahmed!" | Pass |
| 15 | Invalid Y/N answer | maybe | Rejected, asks again | "Please type Y or N." then asks again | Pass |
| 16 | Decimal number | Purpose = 2.5 | Rejected | Accepted as 2 (Streaming) | Minor issue |

## Bugs / Issues Found

| # | Description | Status |
|---|-------------|--------|
| 1 | A decimal like 2.5 is read as 2 instead of being rejected, because `cin >> int` stops at the dot. The program does not crash. | Minor, noted |

## Summary

All 12 planned test cases passed. 3 of the 4 extra tests passed; the decimal input issue is minor and does not crash the program.
