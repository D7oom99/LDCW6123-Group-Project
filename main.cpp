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