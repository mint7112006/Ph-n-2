#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <cstdio> // Thư viện cần thiết cho freopen
#include <iomanip>
using namespace std;

int main() {
    // ===== KÍCH HOẠT ĐỌC/GHI FILE =====
    // Lưu ý: Dấu ../ để lùi ra khỏi thư mục src nếu bạn đang chạy từ đó
    if (freopen("../tests/y2/test3.in", "r", stdin) == nullptr) {
        cerr << "Khong the mo file test3.in!" << endl;
        return 1;
    }
    if (freopen("../tests/y2/test3.out", "w", stdout) == nullptr) {
        cerr << "Khong the tao file test3.out!" << endl;
        return 1;
    }

    // ===== 1. Nhập chuỗi nhị phân =====
    string a;
    if (!(cin >> a)) return 0;

    int l = a.length();
    vector<int> r(l);
    for (int i = 0; i < l; i++) {
        r[i] = a[i] - '0';
    }

    // ===== 2. Nhập số phương trình =====
    int J;
    if (!(cin >> J)) return 0;

    cin.ignore();
    vector<vector<int>> A(J + 1);

    // ===== Nhập các chỉ số của từng phương trình =====
    for (int n = 1; n <= J; n++) {
        string s;
        getline(cin, s);
        stringstream ss(s);
        int temp;
        while (ss >> temp) {
            A[n].push_back(temp);
        }
    }

    // ===== Lưu bitRA =====
    vector<int> bitRA;

   // ===== In tiêu đề bảng =====
    cout << "\n--- BANG HOAT DONG CHI TIET GIAI MA ---\n\n";

    // Cố định độ rộng các cột
    int col_nhip = 6;
    int col_r = a.length() + 4;
    int col_A = 8;
    int col_T = 5;
    int col_RA = 8;

    // In dòng đầu
    cout << left << setw(col_nhip) << "Nhip" << "| " 
         << setw(col_r) << "r" << "|";
    for (int i = 1; i <= J; i++) {
        cout << setw(col_A) << (" A" + to_string(i)) << "|";
    }
    cout << setw(col_T) << " T" << "| " << "bitRA" << endl;

    // In đường kẻ ngang
    int total_width = col_nhip + col_r + (col_A * J) + col_T + col_RA + 5;
    cout << string(total_width, '-') << endl;

    // ===== Nhịp đầu tiên (Nhip L) =====
    cout << left << setw(col_nhip) << l << "| ";
    for (int x : r) cout << x;
    cout << setw(col_r - l) << "" << "|"; // Bù khoảng trống cho r
    for (int i = 1; i <= J; i++) cout << setw(col_A) << " -" << "|";
    cout << setw(col_T) << " -" << "| -" << endl;

    vector<int> tmp = r;
    // Dịch vòng lần đầu để khớp logic của bạn
    int first_rotate = r[l - 1];
    for (int k = l - 1; k >= 1; k--) r[k] = r[k - 1];
    r[0] = first_rotate;

    // ===== Từ nhịp tiếp theo trở đi =====
    for (int step = 1; step <= l; step++) {
        cout << left << setw(col_nhip) << (step + l) << "| ";

        // In r hiện tại
        for (int x : r) cout << x;
        cout << setw(col_r - l) << "" << "|";

        int count_ones = 0, count_zeros = 0;
        for (int n = 1; n <= J; n++) {
            int sum_mod2 = 0;
            for (int z : A[n]) {
                if (z >= 0 && z < l) sum_mod2 ^= tmp[z];
            }
            cout << " " << setw(col_A - 1) << sum_mod2 << "|";
            if (sum_mod2 == 1) count_ones++; else count_zeros++;
        }

        int T = (count_ones > count_zeros) ? 1 : 0;
        int bitRA_val = T ^ tmp[l - 1];
        bitRA.push_back(bitRA_val);

        cout << " " << setw(col_T - 1) << T << "| " << bitRA_val << endl;

        tmp = r;
        int temp_val = r[l - 1];
        for (int k = l - 1; k >= 1; k--) r[k] = r[k - 1];
        r[0] = temp_val;
    }

    cout << string(total_width, '-') << endl;

    cout << "------------------------------------------------------------\n";
    cout << "Mang ket qua bitRA cuoi cung: ";

    reverse(bitRA.begin(), bitRA.end());
    for (int x : bitRA) cout << x;
    cout << endl;

    return 0;
}