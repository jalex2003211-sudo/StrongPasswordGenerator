#include <algorithm>
#include <iostream>
#include <random>
#include <string>
#include <vector>
#include <cctype>

using namespace std;

static const string DIGITS  = "0123456789";
static const string SYMBOLS = "!@#$%^&*";
static const string UPPER   = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
static const string LOWER   = "abcdefghijklmnopqrstuvwxyz";

char pickRandomChar(const string& pool, mt19937& rng) {
    uniform_int_distribution<size_t> dist(0, pool.size() - 1);
    return pool[dist(rng)];
}

bool askYesNo(const string& question) {
    while (true) {
        cout << question << " (y/n): ";
        string ans;
        cin >> ans;
        if (!cin) return false;

        if (!ans.empty()) {
            char c = (char)tolower((unsigned char)ans[0]);
            if (c == 'y') return true;
            if (c == 'n') return false;
        }
        cout << "Please type y or n.\n";
    }
}

// ---------- Strength Meter Helpers ----------
bool hasAnyFrom(const string& s, const string& pool) {
    for (size_t i = 0; i < s.size(); i++) {
        if (pool.find(s[i]) != string::npos) return true;
    }
    return false;
}

int countCategories(const string& s) {
    int cats = 0;
    if (hasAnyFrom(s, LOWER))   cats++;
    if (hasAnyFrom(s, UPPER))   cats++;
    if (hasAnyFrom(s, DIGITS))  cats++;
    if (hasAnyFrom(s, SYMBOLS)) cats++;
    return cats;
}

string strengthLabel(const string& pwd) {
    int len = (int)pwd.size();
    int cats = countCategories(pwd);

    int score = 0;

    if (len >= 8)  score++;
    if (len >= 12) score++;
    if (len >= 16) score++;
    if (len >= 20) score++;

    score += cats; // +0..+4 depending on categories

    if (score <= 3) return "Weak";
    if (score <= 5) return "Medium";
    if (score <= 7) return "Strong";
    return "Very Strong";
}
// ------------------------------------------

int main() {
    cout << "=== StrongPasswordGenerator (V2) ===\n";

    int n;
    cout << "Enter the length of the password required: ";
    cin >> n;

    if (!cin || n <= 0) {
        cout << "Invalid length.\n";
        return 1;
    }

    bool useUpper   = askYesNo("Include UPPERCASE letters");
    bool useLower   = askYesNo("Include lowercase letters");
    bool useDigits  = askYesNo("Include digits");
    bool useSymbols = askYesNo("Include symbols");

    // Build the pool and track required categories
    vector<string> requiredPools;
    string pool;

    if (useUpper)   { requiredPools.push_back(UPPER);   pool += UPPER; }
    if (useLower)   { requiredPools.push_back(LOWER);   pool += LOWER; }
    if (useDigits)  { requiredPools.push_back(DIGITS);  pool += DIGITS; }
    if (useSymbols) { requiredPools.push_back(SYMBOLS); pool += SYMBOLS; }

    if (pool.empty()) {
        cout << "You must select at least one character category.\n";
        return 1;
    }

    int requiredCount = (int)requiredPools.size();
    if (n < requiredCount) {
        cout << "Length too small. Minimum length for your selections is: "
             << requiredCount << "\n";
        return 1;
    }

    random_device rd;
    mt19937 rng(rd());

    vector<char> password;
    password.reserve(n);

    // Guarantee at least 1 from each selected category
    for (size_t i = 0; i < requiredPools.size(); i++) {
        password.push_back(pickRandomChar(requiredPools[i], rng));
    }

    // Fill remaining characters from the full pool
    while ((int)password.size() < n) {
        password.push_back(pickRandomChar(pool, rng));
    }

    // Shuffle so guaranteed chars aren't always first
    shuffle(password.begin(), password.end(), rng);

    // Convert to string
    string pwd;
    pwd.reserve(password.size());
    for (size_t i = 0; i < password.size(); i++) pwd += password[i];

    cout << "\nYour Password is: " << pwd << "\n";
    cout << "Strength: " << strengthLabel(pwd) << "\n";

    return 0;
}
