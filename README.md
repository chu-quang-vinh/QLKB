# Hệ Thống Quản Lý Khám Bệnh (QLKB)

Hệ thống quản lý khám bệnh được phát triển bằng ngôn ngữ C, sử dụng cấu trúc dữ liệu Queue để quản lý hàng đợi bệnh nhân theo các trạng thái khác nhau.

## 📋 Mục Lục

- [Tính Năng](#-tính-năng)
- [Cấu Trúc Dự Án](#-cấu-trúc-dự-án)
- [Cài Đặt](#-cài-đặt)
- [Cách Sử Dụng](#-cách-sử-dụng)
- [Cấu Trúc Dữ Liệu](#-cấu-trúc-dữ-liệu)
- [Chức Năng Chi Tiết](#-chức-năng-chi-tiết)
- [File Dữ Liệu](#-file-dữ-liệu)
- [Yêu Cầu Hệ Thống](#-yêu-cầu-hệ-thống)

## 🏥 Tính Năng

### Quản Lý Bệnh Nhân
- ✅ Thêm bệnh nhân mới với mã tự động (BN001-BN999)
- ✅ Lưu trữ thông tin đầy đủ: Họ tên, giới tính, ngày sinh, CCCD, địa chỉ, SDT
- ✅ Phân loại mức độ ưu tiên: **Cấp cứu** / **Thông thường** / **Tái khám**

### Hàng Đợi Khám Bệnh
- 🔄 **Ba trạng thái bệnh nhân**:
  - `Chờ khám` - Bệnh nhân đang xếp hàng đợi
  - `Đang khám` - Bệnh nhân đang được khám
  - `Hoàn thành` - Bệnh nhân đã khám xong
- ⏰ Sắp xếp theo độ ưu tiên và thời gian đến

### Tìm Kiếm & Tra Cứu
- 🔍 Tìm kiếm theo mã bệnh nhân
- 🔍 Tìm kiếm theo tên (hỗ trợ tìm kiếm từng phần)

### Thuật Toán Sắp Xếp
- 📊 **Selection Sort** - Thuật toán sắp xếp chọn
- 📊 **Insertion Sort** - Thuật toán sắp xếp chèn

### Lưu Trữ Dữ Liệu
- 💾 Tự động lưu/đọc dữ liệu từ file
- 🔄 Khôi phục trạng thái khi khởi động

## 📁 Cấu Trúc Dự Án

```
CTDL/
├── QLKB.c                    # File chính chứa toàn bộ source code
├── QLKB.exe                  # File thực thi
├── benhnhan_tonghop.txt      # File lưu tổng hợp tất cả bệnh nhân
├── benhnhan_chokham.txt      # File lưu danh sách chờ khám
├── benhnhan_dangkham.txt     # File lưu danh sách đang khám
├── benhnhan_hoanthanh.txt    # File lưu danh sách hoàn thành
└── README.md                 # File hướng dẫn này
```

## 🔧 Cài Đặt

### Yêu Cầu
- **Compiler**: GCC hoặc Dev-C++
- **OS**: Windows/Linux/macOS
- **Libraries**: Standard C Library

### Biên Dịch

**Sử dụng GCC:**
```bash
gcc QLKB.c -o QLKB.exe
```

**Sử dụng Dev-C++:**
1. Mở file `QLKB.c` trong Dev-C++
2. Nhấn `F9` để biên dịch và chạy

## 🚀 Cách Sử Dụng

### Chạy Chương Trình
```bash
./QLKB.exe
```

### Menu Chính
```
========== HE THONG QUAN LY KHAM BENH ==========
1.  Them benh nhan moi
2.  Hien thi danh sach cho kham
3.  Hien thi danh sach dang kham
4.  Hien thi danh sach hoan thanh
5.  Goi benh nhan tiep theo
6.  Hoan thanh kham benh
7.  Tim kiem benh nhan theo ma
8.  Tim kiem benh nhan theo ten
9.  Hien thi danh sach tong hop
10. Sap xep lai danh sach cho kham
11. Luu du lieu va thoat
================================================
```

### Quy Trình Khám Bệnh

1. **Đăng ký bệnh nhân** (Chọn 1)
   - Nhập thông tin bệnh nhân
   - Hệ thống tự động tạo mã và thêm vào hàng đợi "Chờ khám"

2. **Gọi bệnh nhân** (Chọn 5)
   - Chuyển bệnh nhân từ "Chờ khám" → "Đang khám"

3. **Hoàn thành khám** (Chọn 6)
   - Nhập chẩn đoán
   - Chuyển bệnh nhân từ "Đang khám" → "Hoàn thành"

## 🗃️ Cấu Trúc Dữ Liệu

### Struct BenhNhan
```c
typedef struct {
    char maBenhNhan[10];        // Mã BN (BN001-BN999)
    char hoTen[50];             // Họ tên
    char gioiTinh[10];          // Nam/Nu
    char ngaySinh[15];          // DD/MM/YYYY
    char canCuocCongDan[15];    // Số CCCD
    char hoKhauThuongTru[100];  // Địa chỉ thường trú
    char soDienThoai[15];       // Số điện thoại
    char thoiGianDen[20];       // HH:MM DD/MM/YYYY
    char mucDoUuTien[20];       // Cap cuu/Thong thuong/Tai kham
    char trangThai[20];         // Cho kham/Dang kham/Hoan thanh
    char chanDoan[100];         // Chẩn đoán
} BenhNhan;
```

### Queue Implementation
```c
typedef struct Node {
    BenhNhan data;
    struct Node *next;
} Node;

typedef struct Queue {
    Node *front;
    Node *rear;
} Queue;
```

**Ba Queue riêng biệt:**
- `qChoKham` - Hàng đợi chờ khám
- `qDangKham` - Hàng đợi đang khám  
- `qHoanThanh` - Hàng đợi hoàn thành

## ⚙️ Chức Năng Chi Tiết

### 1. Thêm Bệnh Nhân Mới
- Tự động tạo mã bệnh nhân duy nhất
- Lấy thời gian hiện tại tự động
- Mặc định trạng thái "Chờ khám"

### 2. Quản Lý Hàng Đợi
- **Hiển thị danh sách** theo từng trạng thái
- **Gọi bệnh nhân tiếp theo** theo độ ưu tiên
- **Hoàn thành khám** với nhập chẩn đoán

### 3. Tìm Kiếm
- **Theo mã**: Tìm chính xác một bệnh nhân
- **Theo tên**: Tìm kiếm mờ, hiển thị tất cả kết quả phù hợp

### 4. Sắp Xếp
- **Selection Sort**: O(n²) - Ổn định
- **Insertion Sort**: O(n²) - Hiệu quả với dữ liệu nhỏ
- **Tiêu chí sắp xếp**: Ưu tiên trước, thời gian sau

### 5. Độ Ưu Tiên
```
1. Cấp cứu      (cao nhất)
2. Thông thường (trung bình)  
3. Tái khám     (thấp nhất)
```

## 📄 File Dữ Liệu

### Format File
Mỗi bệnh nhân được lưu theo 11 dòng:
```
BN001
Nguyen Van A
Nam
15/05/1990
123456789012
123 Nguyen Trai, Ha Noi
0123456789
08:00 11/06/2025
Cap cuu
Cho kham
```

### Các File Được Tạo
| File | Mô Tả |
|------|-------|
| `benhnhan_tonghop.txt` | Tổng hợp tất cả bệnh nhân |
| `benhnhan_chokham.txt` | Danh sách chờ khám |
| `benhnhan_dangkham.txt` | Danh sách đang khám |
| `benhnhan_hoanthanh.txt` | Danh sách hoàn thành |

## 💻 Yêu Cầu Hệ Thống

### Phần Cứng Tối Thiểu
- **RAM**: 512 MB
- **Ổ cứng**: 50 MB trống
- **CPU**: Bất kỳ processor hỗ trợ C

### Phần Mềm
- **OS**: Windows 7+, Linux, macOS
- **Compiler**: 
  - GCC 4.0+
  - Dev-C++ 5.0+
  - Code::Blocks
  - Visual Studio Code với C/C++ extension

### Libraries Cần Thiết
```c
#include <stdio.h>      // Input/Output
#include <stdlib.h>     // Memory management
#include <string.h>     // String manipulation  
#include <stdbool.h>    // Boolean type
#include <time.h>       // Time functions
```

## 🔨 Development

### Biên Dịch cho Debug
```bash
gcc -g -Wall -Wextra QLKB.c -o QLKB_debug.exe
```

### Chạy với Valgrind (Linux)
```bash
valgrind --leak-check=full ./QLKB
```

## 📝 Ghi Chú

### Giới Hạn
- Tối đa **100 bệnh nhân** trong hệ thống
- Mã bệnh nhân từ **BN001** đến **BN999**
- File text đơn giản (không mã hóa)

### Tính Năng Tương Lai
- [ ] Backup/Restore database
- [ ] Export báo cáo Excel
- [ ] Giao diện đồ họa (GUI)
- [ ] Hỗ trợ đa ngôn ngữ
- [ ] Mã hóa dữ liệu

## 👥 Đóng Góp

Dự án mã nguồn mở, hoan nghênh mọi đóng góp:

1. Fork repository
2. Tạo feature branch (`git checkout -b feature/AmazingFeature`)
3. Commit changes (`git commit -m 'Add some AmazingFeature'`)
4. Push to branch (`git push origin feature/AmazingFeature`)
5. Tạo Pull Request

## 📞 Hỗ Trợ

Nếu gặp vấn đề trong quá trình sử dụng:

1. Kiểm tra [Issues](../../issues) đã có
2. Tạo issue mới với mô tả chi tiết
3. Bao gồm thông tin hệ thống và error message

## 📄 Giấy Phép

Dự án được phát hành dưới giấy phép MIT License. Xem file `LICENSE` để biết thêm chi tiết.

---

**⚠️ Lưu Ý**: Đây là phiên bản demo cho mục đích học tập. Trong môi trường sản xuất thực tế, cần bổ sung thêm các tính năng bảo mật, xử lý lỗi nâng cao và tối ưu hóa hiệu suất.

---

**📧 Liên Hệ**: Để biết thêm thông tin chi tiết về dự án hoặc đóng góp ý kiến.
