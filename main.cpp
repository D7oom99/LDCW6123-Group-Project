#include <iostream>
#include <string>
#include <limits>
#include <cstdlib>
using namespace std;

// =====================================================================
// PART 1: SETTINGS
// =====================================================================

// ---- Pricing (money is stored in sen, so RM15.00 = 1500) ----
const int BASE_PRICE_SEN   = 1500;  // RM15.00 per month
const int INCLUDED_DEVICES = 5;     // basic plan covers 5 devices
const int EXTRA_DEVICE_SEN = 200;   // RM2.00 per extra device per month
const int MAX_DEVICES      = 10;

// ---- Menu choices (names for the numbers the user types) ----
enum Purpose { REMOTE_WORK = 1, STREAMING, PUBLIC_WIFI, PRIVACY, GAMING };
enum Country { MALAYSIA = 1, CHINA, RUSSIA, IRAN, OTHER };
enum Device  { PHONE = 1, LAPTOP_PC, ROUTER };

// A protocol name plus the reason we recommend it
struct Recommendation {
    string protocol;
    string reason;
};

// =====================================================================
// PART 2: LOGIC  (works out answers, never prints or asks)
// =====================================================================

// Step B: pick a protocol (switch statement)
Recommendation recommendProtocol(int purpose, int device) {
    switch (purpose) {
        case REMOTE_WORK:
            return {"IKEv2/IPsec", "Corporate standard, stable for work."};
        case STREAMING:
            return {"WireGuard", "Fastest option, good for HD video."};
        case PUBLIC_WIFI:
            if (device == PHONE)
                return {"IKEv2/IPsec", "Reconnects well when switching between Wi-Fi and mobile data."};
            return {"WireGuard", "Fast and lightweight on public networks."};
        case PRIVACY:
            return {"OpenVPN over TCP port 443", "Looks like HTTPS traffic, so it is harder to block."};
        case GAMING:
            return {"WireGuard", "Lowest latency."};
        default:
            return {"Unknown", ""};
    }
}

// Step C helper: does this country restrict VPNs?
bool isRestricted(int country) {
    return country == CHINA || country == RUSSIA || country == IRAN;
}

// Step D: cost
int discountPercent(int months) {
    switch (months) {
        case 12: return 40;
        case 24: return 55;
        default: return 0;       // 1 month = no discount
    }
}

int extraDeviceFeeSen(int devices) {
    if (devices > INCLUDED_DEVICES)
        return (devices - INCLUDED_DEVICES) * EXTRA_DEVICE_SEN;
    return 0;
}

int monthlyPriceSen(int months, int devices) {
    // multiply first, divide last, so integer division doesn't round to 0
    int discounted = BASE_PRICE_SEN * (100 - discountPercent(months)) / 100;
    return discounted + extraDeviceFeeSen(devices);
}

int totalPriceSen(int months, int devices) {
    return monthlyPriceSen(months, devices) * months;
}

// Turns 1075 into "RM10.75"
string formatRM(int sen) {
    string cents = to_string(sen % 100);
    if (sen % 100 < 10) cents = "0" + cents;
    return "RM" + to_string(sen / 100) + "." + cents;
}

// =====================================================================
// PART 3: INPUT  (every function keeps asking until the answer is valid)
// =====================================================================

string getName() {
    string name;
    while (true) {
        cout << "Enter your name: ";
        if (!getline(cin, name)) {            // input ended (Ctrl+D / end of file)
            cout << "\nInput closed.\n";
            exit(1);
        }
        if (!name.empty()) return name;
        cout << "Name cannot be empty.\n";
    }
}

int getValidInt(const string& prompt, int min, int max) {
    int value;
    while (true) {
        cout << prompt;
        if (cin >> value && value >= min && value <= max) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');  // throw away rest of line
            return value;
        }
        if (cin.eof()) {                      // stops infinite loop when input runs out
            cout << "\nInput closed.\n";
            exit(1);
        }
        cin.clear();                          // 1) reset the "fail" state
        cin.ignore(numeric_limits<streamsize>::max(), '\n');  // 2) throw away the bad line
        cout << "Invalid choice. Please enter a number from "
             << min << " to " << max << ".\n";
    }
}

int getValidPlan() {
    int months;
    do {
        months = getValidInt("Plan length in months (1, 12 or 24): ", 1, 24);
        if (months != 1 && months != 12 && months != 24)
            cout << "Only 1, 12 or 24 months are available.\n";
    } while (months != 1 && months != 12 && months != 24);
    return months;
}

char getValidYesNo(const string& prompt) {
    string line;
    while (true) {
        cout << prompt;
        if (!getline(cin, line)) {
            cout << "\nInput closed.\n";
            exit(1);
        }
        if (line == "Y" || line == "y") return 'Y';
        if (line == "N" || line == "n") return 'N';
        cout << "Please type Y or N.\n";
    }
}
// =====================================================================
// PART 4: OUTPUT  (everything the user sees as results)
// =====================================================================

void showWelcome() {
    cout << "=============================================\n";
    cout << "        VPN ADVISOR & COST CALCULATOR\n";
    cout << "=============================================\n";
}

// Step C: if / else if chain
void showLegalWarning(int country, int purpose) {
    cout << "\n--- Legal check ---\n";
    if (country == CHINA)
        cout << "WARNING: In China, only state-licensed VPNs are allowed.\n";
    else if (country == RUSSIA)
        cout << "WARNING: In Russia, unauthorised VPNs have been banned since 2017.\n";
    else if (country == IRAN)
        cout << "WARNING: In Iran, a permit is required to use a VPN.\n";
    else
        cout << "No major VPN restrictions on record.\n";

    if (isRestricted(country) && purpose == PRIVACY)
        cout << "EXTRA WARNING: Using a VPN to bypass censorship here carries a high legal risk.\n";
}

void printSummary(const string& name, const Recommendation& rec,
                  int months, int devices) {
    cout << "\n=============================================\n";
    cout << "Hello, " << name << "! Here is your result.\n";
    cout << "=============================================\n";
    cout << "Recommended protocol : " << rec.protocol << "\n";
    cout << "Why                  : " << rec.reason << "\n";
    cout << "---------------------------------------------\n";
    cout << "Base price per month : " << formatRM(BASE_PRICE_SEN) << "\n";
    cout << "Plan discount        : " << discountPercent(months) << "%\n";
    cout << "Extra device fee     : " << formatRM(extraDeviceFeeSen(devices)) << " per month\n";
    cout << "Monthly price        : " << formatRM(monthlyPriceSen(months, devices)) << "\n";
    cout << "Total for " << months << " month(s)  : "
         << formatRM(totalPriceSen(months, devices)) << "\n";
    cout << "=============================================\n\n";
}
