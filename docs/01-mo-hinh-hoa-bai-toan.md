# Phân tích Mô hình hóa Bài toán Xếp lịch bằng Đồ thị

## 1. Dữ liệu đầu vào gồm những gì?
[cite_start]Dữ liệu đầu vào của hệ thống được chia thành 3 mảng tài nguyên cốt lõi, mô phỏng chính xác các thực thể thực tế tại cơ sở đào tạo[cite: 169]:
* **Tài nguyên thời gian (Timeslots):** Danh sách các ca học khả dụng trong tuần.
* **Tài nguyên không gian (Rooms):** Danh sách các phòng học vật lý tại trường.
* **Tập yêu cầu (Subjects):** Danh sách các lớp học phần cần được xếp lịch. [cite_start]Mỗi môn học mang theo các "ràng buộc cứng" (Hard Constraints) nội tại của nó bao gồm: Giảng viên phụ trách, Nhóm sinh viên tham gia, Số lượng sinh viên thực tế, và Loại phòng đặc thù yêu cầu[cite: 166].

## 2. Vì sao bắt buộc phải có `roomType` và `capacity`?
Trong lý thuyết đồ thị hàn lâm, các thuật toán thường mắc một thiên kiến sai lầm là chỉ tập trung phân bổ trục thời gian (tô màu) mà phớt lờ trục không gian. Sự có mặt của `roomType` và `capacity` khắc phục điểm mù này:
* [cite_start]**`capacity` (Sức chứa):** Đóng vai trò là một Ràng buộc Cứng[cite: 166, 168]. Số lượng sinh viên của một lớp (`studentCount`) tuyệt đối không được vượt quá sức chứa của phòng (`capacity`). Nếu không có biến số này, thuật toán có thể xếp 100 sinh viên vào một phòng học chỉ có 30 chỗ ngồi, tạo ra một lịch trình vô nghĩa về mặt thực tiễn.
* **`roomType` (Loại phòng):** Giải quyết tính đặc thù của môn học. Các môn thực hành bắt buộc phải được gán vào các phòng máy (Lab), trong khi các môn học đại cương chỉ cần giảng đường lý thuyết (Theory). 

## 3. Sự khác nhau giữa các Dataset (Basic, Medium, Complex)
Việc phân cấp dữ liệu giả lập giúp kiểm chứng khả năng chịu tải và tính đúng đắn của giải thuật:
* **Basic (Đồ thị thưa):** Số lượng đỉnh (môn học) ít, hầu như không có cạnh xung đột (ít trùng giảng viên/sinh viên). Tài nguyên phòng và ca học dư thừa. Dùng để kiểm tra logic base của code.
* **Medium (Đồ thị trung bình):** Bắt đầu xuất hiện các "Cạnh" kết nối giữa các đỉnh (xung đột tài nguyên con người). Có các lớp học sĩ số lớn ép thuật toán phải tìm đúng phòng lớn.
* **Complex (Đồ thị dày đặc - Dense Graph):** Thách thức lớn nhất đối với giải thuật. Số lượng môn học tăng vọt tạo ra một mạng lưới xung đột chằng chịt. Nút thắt cổ chai xuất hiện khi nhu cầu sử dụng phòng Lab vượt quá số lượng phòng Lab khả dụng trong một ca, ép thuật toán (như Welsh-Powell hoặc DSATUR) phải đẩy các môn học sang các màu (khung giờ) khác một cách thông minh để tránh sập hệ thống.

## 4. Vì sao thêm dữ liệu phòng học làm bài toán thực tế hơn?
Việc chỉ dùng đồ thị để xếp ca học (Môn học -> Thời gian) thực chất chỉ giải quyết được 50% bài toán thực tế. Khi đưa thực thể `Room` vào hệ thống, bài toán lập lịch chuyển từ không gian 2 chiều sang 3 chiều: **Môn học (Sự kiện) -> Thời gian (Ca học) -> Không gian (Phòng học)**.

[cite_start]Sự điều chỉnh này buộc hệ thống đánh giá xung đột (Conflicts) toàn diện hơn: Hai môn học không có chung giảng viên hay sinh viên (về lý thuyết đồ thị là 2 đỉnh độc lập, có thể tô cùng màu) vẫn **có thể bị xung đột** nếu trong ca học đó, trường học đã hết phòng trống hoặc hết phòng đủ sức chứa[cite: 168, 169]. Bằng cách xử lý đồng thời cả không gian và thời gian, kết quả Output đầu ra của chương trình có thể lập tức đưa vào sử dụng trong thực tế quản lý giáo dục.