#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>
#include <algorithm>

using namespace std;

// Sử dụng kiểu dữ liệu 64-bit nguyên không dấu
typedef unsigned long long uint64;

// Hàm chuyển chuỗi nhị phân (VD: "1101") thành số nguyên 64-bit
uint64 stringToBin(const string& s) {
    uint64 val = 0;
    for (size_t i = 0; i < s.length(); ++i) {
        if (s[i] == '1') {
            val |= (1ULL << (s.length() - 1 - i));
        }
    }
    return val;
}

// Hàm dịch vòng phải 1 bit trong phạm vi l bit
uint64 cyclicShiftRight(uint64 val, int l) {
    uint64 last_bit = val & 1ULL;
    return (last_bit << (l - 1)) | (val >> 1);
}

int main() {
    // THAM SỐ CẤU HÌNH (Thỏa mãn l <= 64, k <= 20)
    int l = 7; // Độ dài từ mã (n)
    vector<string> input_codes = {
        "0000000", "1010101", "0101010", "1111111" // Ví dụ bộ mã (7, 2)
    };

    // 1. Nạp dữ liệu vào unordered_set để tìm kiếm nhanh O(1)
    unordered_set<uint64> codebook;
    uint64 g = 0;
    int min_weight = 999;

    for (const string& s : input_codes) {
        uint64 val = stringToBin(s);
        codebook.insert(val);

        // Tìm từ mã có trọng số Hamming nhỏ nhất (khác 0) làm phần tử sinh g
        int weight = __builtin_popcountll(val); // Hàm đếm số bit 1 tốc độ cao của C++
        if (val != 0 && weight < min_weight) {
            min_weight = weight;
            g = val;
        }
    }

    // Tự động tính k dựa trên kích thước tập mã (M = 2^k)
    size_t M = codebook.size();
    int k = 0;
    while ((1ULL << k) < M) k++;

    // Kiểm tra tính hợp lệ của số lượng từ mã
    if ((1ULL << k) != M) {
        cout << "Ket luan: Khong phai ma tuyen tinh (Kich thuoc tap ma khong phai dang 2^k)." << endl;
        return 0;
    }

    cout << "--- HE THONG DANG KIEM TRA MA (" << l << ", " << k << ") ---" << endl;

    // BƯỚC 1: KIỂM TRA MÃ KHỐI TUYẾN TÍNH (Sinh tập mã từ Ma trận G)
    vector<uint64> G(k);
    for (int i = 0; i < k; ++i) {
        G[i] = g >> i; // Tạo ma trận sinh bằng cách dịch đại số của g
    }

    bool is_linear = true;
    for (size_t i = 0; i < M; ++i) {
        uint64 codeword = 0;
        for (int j = 0; j < k; ++j) {
            if ((i >> j) & 1ULL) {
                codeword ^= G[j]; // Phép cộng trên trường GF(2)
            }
        }
        // Kiểm tra xem từ mã vừa tạo ra có nằm trong tập ban đầu không
        if (codebook.find(codeword) == codebook.end()) {
            is_linear = false;
            break;
        }
    }

    if (!is_linear) {
        cout << "Ket luan: KHONG PHAI ma khoi tuyen tinh (That bai o B1)." << endl;
        return 0;
    }
    cout << "[OK] Buoc 1: Bo ma dat tinh chat TUYEN TINH." << endl;

    // BƯỚC 2: KIỂM TRA TÍNH XOAY VÒNG (MÃ VÒNG)
    // Lấy hàng cuối cùng của ma trận G, dịch vòng phải 1 bit
    uint64 last_row = G[k - 1];
    uint64 shifted_code = cyclicShiftRight(last_row, l);

    // Nếu từ mã dịch vòng này tồn tại trong tập ban đầu -> Bộ mã là mã vòng
    if (codebook.find(shifted_code) != codebook.end()) {
        cout << "[OK] Buoc 2: Thoa man dieu kien dich vong." << endl;
        cout << "\n==> KET LUAN CUOI CUNG: BO MA LA MA VONG TUYEN TINH!" << endl;
    } else {
        cout << "Ket luan: La ma khoi tuyen tinh nhung KHONG PHAI ma vong (That bai o B2)." << endl;
    }

    return 0;
}
