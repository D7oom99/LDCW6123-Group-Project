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