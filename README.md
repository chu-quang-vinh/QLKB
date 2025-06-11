Hệ Thống Quản Lý Khám Bệnh 


Đây là một hệ thống quản lý khám bệnh được viết bằng ngôn ngữ C, sử dụng cấu trúc dữ liệu Queue để quản lý hàng đợi bệnh nhân.

Tính Năng Chính


🏥 Quản Lý Bệnh Nhân


Thêm bệnh nhân mới: Tự động tạo mã bệnh nhân duy nhất (BN001-BN999)


Lưu trữ thông tin đầy đủ: Họ tên, giới tính, ngày sinh, CCCD, địa chỉ, SDT


Phân loại mức độ ưu tiên: Cấp cứu, Thông thường, Tái khám


📋 Hàng Đợi Khám Bệnh


Ba trạng thái bệnh nhân:


Chờ khám


Đang khám


Hoàn thành


Sắp xếp theo độ ưu tiên: Cấp cứu được ưu tiên, sau đó theo thời gian đến


🔍 Tìm Kiếm & Tra Cứu


Tìm kiếm theo mã bệnh nhân


Tìm kiếm theo tên bệnh nhân (hỗ trợ tìm kiếm từng phần)


📊 Sắp Xếp Dữ Liệu


Selection Sort: Thuật toán sắp xếp chọn//
Insertion Sort: Thuật toán sắp xếp chèn
💾 Lưu Trữ File
Tự động lưu/đọc dữ liệu từ các file:
benhnhan_tonghop.txt: Tổng hợp tất cả bệnh nhân
benhnhan_chokham.txt: Danh sách chờ khám
benhnhan_dangkham.txt: Danh sách đang khám
benhnhan_hoanthanh.txt: Danh sách hoàn thành
Cấu Trúc Dự Án
Cách Sử Dụng
Biên Dịch Chương Trình
Sử dụng Dev-C++ hoặc GCC:

Hoặc sử dụng Makefile:

Chạy Chương Trình
Menu Chính
Cấu Trúc Dữ Liệu
Struct BenhNhan
Queue Implementation
Sử dụng Linked List để triển khai Queue
Hỗ trợ các thao tác: enqueue, dequeue, isEmpty
Ba Queue riêng biệt cho từng trạng thái
Testing
Chạy unit tests:

Các test case bao gồm:

Test đọc/ghi file
Test thuật toán sắp xếp
Test tìm kiếm bệnh nhân
Tính Năng Nổi Bật
🎯 Tự Động Hóa
Tự động tạo mã bệnh nhân duy nhất
Tự động lấy thời gian hiện tại khi đăng ký
Tự động sắp xếp theo độ ưu tiên
🔄 Quản Lý Trạng Thái
Chuyển đổi trạng thái tự động: Chờ khám → Đang khám → Hoàn thành
Cập nhật đồng bộ giữa Queue và danh sách tổng hợp
🗂️ Persistence
Lưu trữ dữ liệu persistent qua các lần chạy
Khôi phục trạng thái từ file khi khởi động
Yêu Cầu Hệ Thống
Compiler: GCC hoặc Dev-C++
OS: Windows/Linux/macOS
Libraries: Standard C Library (stdio.h, stdlib.h, string.h, time.h)
Giấy Phép
Dự án mã nguồn mở, sử dụng cho mục đích học tập và nghiên cứu.

Lưu ý: Đây là phiên bản demo cho mục đích học tập. Trong môi trường thực tế, cần bổ sung thêm các tính năng bảo mật và xử lý lỗi nâng cao.
