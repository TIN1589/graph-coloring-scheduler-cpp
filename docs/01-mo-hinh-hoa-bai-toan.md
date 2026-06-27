## 1. Cơ sở Lý thuyết và Ánh xạ Đồ thị (Graph Mapping)

Bài toán xếp thời khóa biểu đại học thuộc lớp bài toán tối ưu hóa tổ hợp (Combinatorial Optimization) và có thể được mô hình hóa trực tiếp thành bài toán Tô màu đồ thị (Graph Coloring Problem). 

### 1.1. Bảng Ánh xạ Thực thể
| Thực thể (Domain) | Lý thuyết Đồ thị | Cấu trúc Dữ liệu (C++) | Cơ chế Hoạt động Cốt lõi |
| :--- | :--- | :--- | :--- |
| **Sự kiện** | **Đỉnh (Vertex)** | `Subject` | Mỗi lớp học phần là một đỉnh độc lập, mang theo các siêu dữ liệu về sĩ số, giảng viên. |
| **Xung đột** | **Cạnh (Edge)** | *Logic Ma trận kề* | Một cạnh nối hai đỉnh nếu chúng vi phạm giới hạn tài nguyên (trùng giảng viên/nhóm sinh viên). |
| **Thời gian** | **Màu sắc (Color)** | `Timeslot` | Quá trình lập lịch là việc tô màu các đỉnh sao cho **không có hai đỉnh kề nhau cùng màu**. |
| **Không gian** | **Trọng số Ràng buộc**| `Room` | Yếu tố vật lý (sức chứa) đóng vai trò là chốt chặn giới hạn không gian nghiệm trước khi gán màu. |

### 1.2. Sơ đồ Chuyển đổi Không gian

```mermaid
flowchart TD
    %% 1. Phân hệ Ánh xạ Không gian (Đi ngang)
    subgraph AnhXa[BẢNG ÁNH XẠ KHÔNG GIAN]
        direction LR
        
        subgraph ThucTe[Thực tế Đại học]
            direction TB
            C[Xung đột GV / Sinh viên]
            T[Ca học khả dụng]
            S[Lớp học phần]
        end
        
        subgraph DoThi[Không gian Đồ thị]
            direction TB
            E{Cạnh / Edge}
            Col[Màu sắc / Color]
            V((Đỉnh / Vertex))
        end
        
        C ==>|Sinh ra| E
        T ==>|Cấp phát qua| Col
        S ==>|Ánh xạ thành| V
    end

    %% 2. Phân hệ Logic Đồ thị (Đi dọc phía dưới, tách biệt hoàn toàn)
    subgraph Logic[CƠ CHẾ TÔ MÀU ĐỒ THỊ]
        direction LR
        V1((Đỉnh 1)) --- E_Logic{Cạnh / Mối xung đột} --- V2((Đỉnh 2))
        Col_Logic[Màu sắc / Ca học] -->|Tô màu / Định ca| V1
    end
    
    AnhXa --> Logic

### 2.1. Ràng buộc Cứng (Hard Constraints)
> ⚠️ **Quy tắc Tuyệt đối:** Đây là các ranh giới không thể phá vỡ. Bất kỳ cấu hình màu nào vi phạm dù chỉ một điều kiện sẽ khiến toàn bộ lịch trình bị vô hiệu hóa (Infeasible).

* **[HC1] Tính độc quyền nhân sự:** Một giảng viên tuyệt đối không thể xuất hiện tại hai đỉnh cùng màu (không thể dạy hai môn ở cùng một ca học) *[1]*.
* **[HC2] Tính độc quyền nhóm học:** Các lớp học phần có chung một nhóm sinh viên đăng ký không được phép diễn ra đồng thời *[2]*.
* **[HC3] Giới hạn không gian vật lý:** Sĩ số đăng ký thực tế (`studentCount`) không được phép vượt qua giới hạn sức chứa (`capacity`) của phòng học được cấp phát.

### 2.2. Ràng buộc Mềm (Soft Constraints)
> 💡 **Mục tiêu Tối ưu:** Đây là các hàm mục tiêu nhằm nâng cao chất lượng lịch trình. Việc vi phạm không làm hỏng lịch trình, nhưng làm giảm trải nghiệm của giảng viên và sinh viên.

* **Tối ưu hóa thời gian chờ:** Các môn học thực hành (Sessional / LAB) cần được ưu tiên xếp vào các khung giờ liên tiếp nhau trong cùng một ngày để tránh thời gian chết (dead time) *[3]*.
* **Định tuyến không gian:** Ưu tiên chọn các phòng học nằm cùng tầng hoặc cùng dãy nhà cho các ca học liên tiếp để giảm thiểu thời gian di chuyển vật lý của sinh viên.

---

## 3. Phá vỡ thiên kiến của Lý thuyết Đồ thị truyền thống

Trong quá trình nghiên cứu, các thuật toán tô màu đồ thị kinh điển (như Welsh-Powell hay DSATUR) thường bộc lộ một **thiên kiến ngầm (implicit bias)** rất lớn: 
> *Chúng chỉ tập trung giải quyết bài toán trên trục thời gian (phân bổ màu để tránh trùng lặp) và ngầm mặc định rằng trục không gian (phòng học) là nguồn tài nguyên vô hạn.*

Kiến trúc dữ liệu của dự án này được thiết kế để khắc phục triệt để điểm mù đó thông qua 3 chốt chặn kỹ thuật:

### 3.1. Ràng buộc Sức chứa (`capacity`) - Chốt chặn lỗi logic không gian
```cpp
struct Room {
    string id;
    string roomType;
    int capacity; // Màng lọc an toàn không gian
};
```
Nếu chỉ dùng lý thuyết đồ thị thuần túy, thuật toán sẽ hợp lệ hóa việc xếp 100 sinh viên vào phòng 30 chỗ (miễn là chúng không bị trùng lịch). Bằng cách khai báo thuộc tính `capacity`, hệ thống ép thuật toán phải rẽ nhánh kiểm tra: **Trước khi gán màu, phải xác thực xem ca học đó có còn phòng trống đủ sức chứa hay không.**

## 3.2. Quản trị Nút thắt cổ chai bằng `roomType`

Việc chia phòng thành Theory (Lý thuyết) và LAB (Thực hành) giải quyết hiện tượng khan hiếm tài nguyên cục bộ. Nếu hệ thống chỉ có 2 phòng LAB nhưng có tới 10 lớp Lập trình mạng, thuộc tính `roomType` sẽ cảnh báo thuật toán nhận diện đây là một "nút thắt cổ chai" (bottleneck), buộc nó phải rải đều các môn này ra nhiều dải màu khác nhau thay vì dồn ứ gây cạn kiệt phòng máy.

## 3.3. Xử lý giao thoa tập hợp với `vector<string> studentGroups`

Thực tiễn đào tạo đại học vận hành theo mô hình Ghép lớp (một mã học phần chứa sinh viên từ nhiều lớp danh nghĩa).

Thay vì định nghĩa tỷ lệ 1:1, việc thiết kế `studentGroups` dưới dạng mảng `vector` cho phép thuật toán tính toán giao thoa tập hợp.

Ví dụ:

* Đỉnh A có tập sinh viên `{CNTT01, CNTT02}`
* Đỉnh B có tập `{CNTT02, CNTT03}`

Trình phân tích sẽ phát hiện phần tử giao nhau là `CNTT02` và tự động giăng một Cạnh xung đột giữa A và B.

---

# 4. Tối ưu hóa Kiến trúc và Trừu tượng hóa Tài nguyên

## 4.1. Chuẩn hóa Mã phòng học (Semantic Room ID)

Thay vì sử dụng các số nguyên vô nghĩa, hệ thống quy chuẩn định danh phòng học theo định dạng:

```
[Dãy nhà] + [Lầu] + [Số thứ tự]
```

Ví dụ:

```
B305
C108
```

Quy tắc Semantic ID này mở đường cho các giải thuật Heuristic hoặc Nhánh cận (Branch & Bound) trong tương lai phân rã chuỗi ký tự để biết hai phòng học có nằm cùng một tòa nhà hay không, từ đó tối ưu hóa quãng đường di chuyển của sinh viên.

## 4.2. Ảo hóa Không gian (Resource Virtualization) cho E-Learning

Hệ thống xử lý mô hình học trực tuyến (LMS/E-Learning) không bằng cách viết thêm mã lệnh ngoại lệ rườm rà, mà bằng tư duy Ảo hóa phòng học.

Thiết lập một không gian ảo:

```text
id = "ELEARNING"
roomType = "Elearning"
capacity = 9999
```

Phá vỡ giới hạn vật lý:

```
capacity = 9999
```

Kỹ thuật này bảo toàn 100% tính nguyên vẹn của đồ thị lõi. Các môn học ở nhà vẫn là những Đỉnh trong đồ thị, vẫn bị giăng Cạnh nếu trùng giảng viên, và vẫn được cấp phát Màu. Tuy nhiên, chúng sẽ không bao giờ kích hoạt bẫy lỗi tràn sĩ số, giúp thuật toán chạy trơn tru.

---

# 5. Thiết kế API và Lựa chọn Giải thuật (Algorithm & API Design)

## 5.1. Đóng gói Dữ liệu (Data Encapsulation)

Toàn bộ sự phức tạp của quá trình khởi tạo dữ liệu giả lập (Mock Data) và xây dựng đồ thị được giấu kín phía sau một bộ API Helper.

```mermaid
graph LR
    A[Giao diện CLI / Web UI] -->|Gọi Tên Dataset: 'complex'| B(DemoData API Helper)
    B -->|Xây dựng Mảng & Trả về vectorSubject<>| C{Lõi Giải Thuật Đồ Thị}
    C -->|Output| D[ScheduleItem Report]

Sự cô lập này đảm bảo rằng bất kỳ thay đổi nào trong cấu trúc bộ test case ở tầng dưới sẽ không làm sập giao diện hiển thị ở tầng trên.

## 5.2. Luận cứ Lựa chọn Thuật toán (Algorithm Justification)

Trong không gian bài toán xếp lịch, các nghiên cứu thực nghiệm đã chứng minh rằng thuật toán Welsh-Powell và DSATUR là những phương pháp hiệu quả nhất để tạo ra lịch trình tối ưu.

Hệ thống được định hướng ưu tiên sử dụng chiến lược tham lam của Welsh-Powell. Bằng cơ chế sắp xếp và ưu tiên xử lý các đỉnh có bậc cao nhất theo thứ tự giảm dần, thuật toán chủ động giải quyết các môn học va chạm với nhiều tài nguyên nhất ngay từ giai đoạn đầu, giảm thiểu rủi ro bế tắc cục bộ và gia tăng xác suất tìm thấy cấu hình màu tối ưu toàn cục.
