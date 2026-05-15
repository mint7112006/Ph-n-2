#include <bits/stdc++.h>
using namespace std;

using ull = unsigned long long;

ull stringToBin(const string& s) {
    ull val = 0;
    for (char c : s) {
        val <<= 1;
        if (c == '1') val |= 1ULL;
    }
    return val;
}

string binToString(ull x, int n) {
    string s(n, '0');
    for (int i = n - 1; i >= 0; --i) {
        s[i] = char('0' + (x & 1ULL));
        x >>= 1;
    }
    return s;
}

ull cyclicShiftRight(ull val, int n) {
    if (n == 64) {
        ull last = val & 1ULL;
        return (val >> 1) | (last << 63);
    }

    ull mask = (1ULL << n) - 1;
    ull last = val & 1ULL;

    return ((val >> 1) | (last << (n - 1))) & mask;
}

bool isPowerOfTwo(size_t x) {
    return x > 0 && (x & (x - 1)) == 0;
}

int calcK(size_t m) {
    int k = 0;
    while ((1ULL << k) < m) ++k;
    return k;
}

struct Result {
    bool validInput = true;
    bool validSize = false;
    bool hasZero = false;
    bool linear = false;
    bool cyclic = false;

    string reason;

    ull failA = 0;
    ull failB = 0;
    ull failXor = 0;

    ull failCode = 0;
    ull failShift = 0;
};

Result solveOne(int n, int m, const vector<string>& inputCodes, vector<ull>& codes) {
    Result res;

    unordered_set<ull> codebook;
    codes.clear();

    for (int i = 0; i < m; ++i) {
        string s = inputCodes[i];

        if ((int)s.size() != n) {
            res.validInput = false;
            res.reason = "Tu ma thu " + to_string(i + 1) + " co do dai khong bang n.";
            return res;
        }

        for (char c : s) {
            if (c != '0' && c != '1') {
                res.validInput = false;
                res.reason = "Tu ma thu " + to_string(i + 1) + " chua ky tu khong hop le.";
                return res;
            }
        }

        ull val = stringToBin(s);

        if (codebook.count(val)) {
            res.validInput = false;
            res.reason = "Tap ma co tu ma bi trung lap.";
            return res;
        }

        codebook.insert(val);
        codes.push_back(val);
    }

    res.validSize = isPowerOfTwo(codebook.size());

    if (!res.validSize) {
        res.reason = "Kich thuoc tap ma khong phu hop (khong phai 2^k).";
        return res;
    }

    res.hasZero = codebook.count(0ULL);

    if (!res.hasZero) {
        res.reason = "Tap ma khong chua tu ma khong.";
        return res;
    }

    res.linear = true;

    for (ull a : codes) {
        for (ull b : codes) {
            ull c = a ^ b;
            if (!codebook.count(c)) {
                res.linear = false;
                res.failA = a;
                res.failB = b;
                res.failXor = c;
                res.reason = "Tap ma khong dong voi phep XOR.";
                return res;
            }
        }
    }

    res.cyclic = true;

    for (ull x : codes) {
        ull y = cyclicShiftRight(x, n);
        if (!codebook.count(y)) {
            res.cyclic = false;
            res.failCode = x;
            res.failShift = y;
            res.reason = "Tap ma khong dong voi phep dich vong.";
            return res;
        }
    }

    return res;
}

void printShort(const Result& res) {
    if (res.validInput && res.validSize && res.hasZero && res.linear && res.cyclic) {
        cout << "YES\n";
    } else {
        cout << "NO\n";
    }
}

void printFull(int tc, int n, int m, const vector<string>& inputCodes, const vector<ull>& codes, const Result& res) {
    cout << "========== TEST CASE " << tc << " ==========\n";

    cout << "\nTap ma C gom " << m << " tu ma do dai n = " << n << ":\n";
    for (const string& s : inputCodes) {
        cout << s << '\n';
    }

    if (!res.validInput) {
        cout << "\nKet luan: KHONG PHAI ma vong tuyen tinh.\n";
        cout << "Ly do: " << res.reason << '\n';
        return;
    }

    cout << "\n1. Kiem tra kich thuoc tap ma\n";
    cout << "Ta co |C| = " << codes.size() << ".\n";

    if (res.validSize) {
        int k = calcK(codes.size());
        cout << "Vi |C| = 2^" << k << ", kich thuoc tap ma hop le.\n";
    } else {
        cout << "Vi |C| khong co dang 2^k, C khong the la ma tuyen tinh nhi phan.\n";
        cout << "\nKet luan: KHONG PHAI ma vong tuyen tinh.\n";
        return;
    }

    cout << "\n2. Kiem tra tu ma khong\n";

    if (res.hasZero) {
        cout << "Tap C co chua tu ma khong: " << binToString(0ULL, n) << ".\n";
    } else {
        cout << "Tap C khong chua tu ma khong " << binToString(0ULL, n) << ".\n";
        cout << "\nKet luan: KHONG PHAI ma vong tuyen tinh.\n";
        return;
    }

    cout << "\n3. Kiem tra tinh tuyen tinh\n";
    cout << "Voi ma nhi phan, C la ma tuyen tinh neu C dong voi phep XOR.\n";

    if (res.linear) {
        cout << "Moi cap a, b thuoc C deu co a XOR b thuoc C.\n";
        cout << "Suy ra C la ma khoi tuyen tinh.\n";
    } else {
        cout << "Ton tai a, b thuoc C sao cho a XOR b khong thuoc C.\n";
        cout << "Cu the:\n";
        cout << "a       = " << binToString(res.failA, n) << '\n';
        cout << "b       = " << binToString(res.failB, n) << '\n';
        cout << "a XOR b = " << binToString(res.failXor, n) << " khong thuoc C.\n";
        cout << "\nKet luan: KHONG PHAI ma vong tuyen tinh.\n";
        return;
    }

    cout << "\n4. Kiem tra tinh xoay vong\n";
    cout << "C la ma vong neu moi tu ma sau khi dich vong phai 1 bit van thuoc C.\n";

    if (res.cyclic) {
        cout << "Moi tu ma c thuoc C sau khi dich vong phai van thuoc C.\n";
        cout << "\nKet luan: BO MA LA MA VONG TUYEN TINH.\n";
    } else {
        cout << "Ton tai c thuoc C sao cho dich vong phai cua c khong thuoc C.\n";
        cout << "Cu the:\n";
        cout << "c              = " << binToString(res.failCode, n) << '\n';
        cout << "Dich vong phai = " << binToString(res.failShift, n) << " khong thuoc C.\n";
        cout << "\nKet luan: LA MA TUYEN TINH NHUNG KHONG PHAI MA VONG.\n";
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Kích hoạt đọc file test1.in và ghi file test1.out
    if (freopen("tests/y1/test1.in", "r", stdin) == nullptr) {
        cerr << "Khong the mo file test1.in!\n";
        return 1;
    }
    if (freopen("tests/y1/test1.out", "w", stdout) == nullptr) {
        cerr << "Khong the tao file test1.out!\n";
        return 1;
    }

    int T;
    if (!(cin >> T)) return 0;

    for (int tc = 1; tc <= T; ++tc) {
        int mode;
        int n, m;

        cin >> mode;
        cin >> n >> m;

        vector<string> inputCodes(m);
        for (int i = 0; i < m; ++i) {
            cin >> inputCodes[i];
        }

        vector<ull> codes;
        Result res = solveOne(n, m, inputCodes, codes);

        if (mode == 1) {
            cout << "Test case " << tc << ": ";
            printShort(res);
        } else {
            printFull(tc, n, m, inputCodes, codes, res);
        }

        if (tc != T) {
            cout << "\n----------------------------------------\n\n";
        }
    }

    return 0;
}