#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;

int main() {

    // ===== 1. Nhập chuỗi nhị phân =====
    string a;

    cout << "Nhap chuoi nhi phan a: ";
    cin >> a;

    int l = a.length();

    vector<int> r(l);

    for (int i = 0; i < l; i++) {
        r[i] = a[i] - '0';
    }

    // ===== 2. Nhập số phương trình =====
    int J;

    cout << "Nhap so luong phuong trinh J: ";
    cin >> J;

    cin.ignore();

    vector<vector<int>> A(J + 1);

    // ===== Nhập các chỉ số của từng phương trình =====
    for (int n = 1; n <= J; n++) {

        string s;

        cout << "Nhap cac chi so cua A" << n << ": ";

        getline(cin, s);

        stringstream ss(s);

        int temp;

        while (ss >> temp) {
            A[n].push_back(temp);
        }
    }

    // ===== Lưu bitRA =====
    vector<int> bitRA;

    // ===== In tiêu đề =====
    cout << "\n--- BANG HOAT DONG CHI TIET GIAI MA ---\n";

    cout << "Nhip\t| r\t\t|";

    for (int i = 1; i <= J; i++) {
        cout << " A" << i << "\t|";
    }

    cout << " T\t| bitRA\n";

    cout << "------------------------------------------------------------\n";

    // ===== Nhịp đầu tiên =====
    cout <<l<< "\t| ";

    for (int x : r) {
        cout << x;
    }

    cout << "\t|";

    for (int i = 1; i <= J; i++) {
        cout << " -\t|";
    }

    cout << " -\t| -\n";
    
    vector<int> tmp(l);
    tmp = r;

    // ===== Dịch vòng để chuẩn bị nhịp 2 =====
    int first_rotate = r[l - 1];

    for (int k = l - 1; k >= 1; k--) {
        r[k] = r[k - 1];
    }

    r[0] = first_rotate;

    // ===== Từ nhịp 2 trở đi =====
    for (int step = 1; step <= l ; step++) {

        cout << step +l<< "\t| ";

        // ===== In r hiện tại =====
        for (int x : r) {
            cout << x;
        }

        cout << "\t|";

        // ===== Tính các phương trình =====
        int count_ones = 0;
        int count_zeros = 0;

        for (int n = 1; n <= J; n++) {

            int sum_mod2 = 0;

            for (int z : A[n]) {

                if (z >= 0 && z < l) {
                    sum_mod2 ^= tmp[z];
                }
            }

            cout << " " << sum_mod2 << "\t|";

            if (sum_mod2 == 1)
                count_ones++;
            else
                count_zeros++;
        }
		
        // ===== Majority Logic =====
        int T = (count_ones > count_zeros) ? 1 : 0;

        // ===== Bit cuối =====
        int last_bit = tmp[l - 1];

        // ===== bitRA =====
        int bitRA_val = T ^ last_bit;

        bitRA.push_back(bitRA_val);

        cout << " " << T << "\t| " << bitRA_val << endl;
		// =====Cập nhât=====
		tmp = r;

        // ===== Dịch vòng phải =====
        int temp = r[l - 1];

        for (int k = l - 1; k >= 1; k--) {
            r[k] = r[k - 1];
        }

        r[0] = temp;
    }

    // ===== In kết quả cuối =====
    cout << "------------------------------------------------------------\n";

    cout << "Mang ket qua bitRA cuoi cung: ";

	reverse(bitRA.begin(), bitRA.end());
    for (int x : bitRA) {
        cout << x;
    }

    cout << endl;

    return 0;
}