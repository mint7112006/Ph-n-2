# Ph-n-2
Bài tập lớn Phần 2 - Mã nguồn C/C++ và bộ dữ liệu kiểm thử ICPC
MÃ VÒNG TUYẾN TÍNH VÀ GIẢI MÃ NGƯỠNG 
Dự án này bao gồm hai chương trình chính nhằm giải quyết các yêu cầu về kiểm tra tính chất hệ thống mã và mô phỏng thuật toán giải mã thực tế. \\
PHẦN 1: KIỂM TRA MÃ VÒNG TUYẾN TÍNH (CYCLIC CODE CHECKER)
1. Giới thiệu
Chương trình này xác định xem một tập hợp các từ mã cho trước có tạo thành một Mã vòng tuyến tính hay không. Chương trình thực hiện kiểm tra qua 4 tiêu chí nghiêm ngặt của lý thuyết mã hóa.
2. Các bước kiểm tra logic
Kích thước tập mã: Kiểm tra số lượng từ mã $M$ có phải là lũy thừa của $2$ ($M = 2^k$) hay không.
Vector không: Xác nhận sự tồn tại của từ mã toàn $0$ (điều kiện bắt buộc của mã tuyến tính).
Tính tuyến tính (Linearity): Kiểm tra tính đóng đối với phép toán XOR giữa mọi cặp từ mã trong tập hợp.
Tính xoay vòng (Cyclic Property): Kiểm tra xem khi thực hiện dịch vòng phải 1 bit, từ mã mới có còn nằm trong tập mã ban đầu hay không.
3. Hướng dẫn Input (Định dạng chuẩn ICPC)
Dữ liệu được đọc từ file test2.in với cấu trúc:
Dòng 1: Số lượng Test case $T$.
Mỗi Test case gồm:
mode: ($1$ - In kết quả YES/NO ngắn gọn; $2$ - In lời giải chi tiết).
n: Độ dài từ mã.
m: Số lượng từ mã trong tập hợp.
m dòng tiếp theo: Các chuỗi nhị phân.
4. Cách chạy chương trình
Sử dụng ngôn ngữ C++, trên VS code
Kết quả sẽ được ghi vào file test2.out. \\
PHẦN 2: GIẢI MÃ NGƯỠNG TRỰC GIAO (THRESHOLD DECODING SIMULATOR)
1. Giới thiệu
Chương trình mô phỏng hoạt động của mạch giải mã ngưỡng (Threshold Decoder) sử dụng hệ phương trình kiểm tra trực giao. Đây là phương pháp giải mã tốc độ cao dựa trên logic đa số (Majority Logic).
2. Chức năng chính
Mô phỏng thanh ghi dịch: Thực hiện dịch vòng chuỗi nhận được qua từng nhịp clock.
Tính toán phương trình trực giao: Tính toán giá trị XOR tại các vị trí bit được chỉ định ($A_j$).
Quyết định ngưỡng (T): Sử dụng logic đa số để xác định xem bit tại vị trí kiểm tra có bị lỗi hay không ($T=1$ nếu số lượng phương trình thỏa mãn $> J/2$).
Xuất bảng trạng thái: Sinh bảng hoạt động chi tiết giống như trình bày trong bài tập tự luận, hỗ trợ căn lề tự động cho mọi độ dài mã.
3. Hướng dẫn Input
Dữ liệu được đọc từ file test2.in với cấu trúc:
Dòng 1: Chuỗi nhị phân $r$ nhận được (ví dụ: 1101001).
Dòng 2: Số lượng phương trình trực giao $J$.
$J$ dòng tiếp theo: Danh sách các chỉ số (index) của từng phương trình $A_j$, cách nhau bởi dấu cách.
4. Cách chạy chương trình
Sử dụng ngôn ngữ C++ trên VS Code
Kết quả bảng trạng thái sẽ được ghi vào file test2.out.
THÔNG TIN NHÓM THỰC HIỆN
Ngày hoàn thành: 16/05/2026
Ngôn ngữ: C++ (Sử dụng các thư viện chuẩn STL, iomanip, bits/stdc++).
Môi trường kiểm thử: Đã vượt qua các bộ test chuẩn mã Hamming (7,4) và các mã vòng tùy chỉnh.

