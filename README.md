# BÁO CÁO ĐỀ TÀI: ÁP DỤNG THUẬT TOÁN TÔ MÀU ĐỒ THỊ TRONG BÀI TOÁN XẾP LỊCH HỌC ĐẠI HỌC

---

## MỞ ĐẦU

### 1. Lý do chọn đề tài

Lập lịch học đại học (University Course Timetabling) là quy trình phân bổ các khung giờ học cho các môn học trong một học kỳ nhằm đảm bảo tính vận hành liên tục của nhà trường [2].

Phương pháp xếp lịch thủ công truyền thống do nhân viên quản lý thực hiện thường tốn nhiều thời gian và dễ dẫn đến các lỗi xung đột tài nguyên (trùng lịch sinh viên, trùng lịch giảng viên hoặc trùng phòng học) [2]. Khi quy mô số lượng môn học tăng lên, việc xếp tay trở nên rất phức tạp.

Bài toán lập lịch có thể mô hình hóa thành bài toán tô màu đỉnh đồ thị (Vertex Coloring): Các môn học được biểu diễn dưới dạng các đỉnh (Vertices), mối quan hệ xung đột tài nguyên được biểu diễn bằng các cạnh (Edges), và các khung giờ học (Timeslots) được xem là các màu (Colors) [1, 2].

### 2. Mục tiêu nghiên cứu

- Nghiên cứu cơ sở lý thuyết về đồ thị và giải thuật tô màu đồ thị tuần tự (First Fit, Welsh-Powell) [1].
- Xây dựng cấu trúc dữ liệu trên C++ để chuyển đổi danh sách đăng ký học phần thành đồ thị xung đột.
- Áp dụng thuật toán Welsh-Powell để đưa ra phương án phân bổ khung giờ học giảm thiểu xung đột.
- Xây dựng chương trình Demo nhỏ bằng ngôn ngữ C++ để kiểm chứng tính khả thi của giải thuật.

### 3. Đối tượng và phạm vi nghiên cứu

- **Đối tượng:** Khung lịch học giả lập bao gồm các thực thể: Môn học, Giảng viên, và các Nhóm lớp sinh viên.
- **Phạm vi:** Trong phạm vi một ứng dụng demo nhỏ, thuật toán chỉ tập trung giải quyết các ràng buộc cứng (Hard constraints) liên quan đến việc trùng lịch của giảng viên và nhóm lớp sinh viên. Ràng buộc về số lượng phòng học giới hạn và sức chứa cụ thể của từng phòng chưa được xử lý trực tiếp trong bước tô màu mà được xem là hướng mở rộng nâng cao của đề tài. Dữ liệu đầu vào sử dụng mô hình sinh viên đăng ký học theo các block cố định.

### 4. Phương pháp thực hiện

- **Phương pháp nghiên cứu lý thuyết:** Phân tích mô hình Vertex Coloring áp dụng cho lập lịch [1, 2].
- **Phương pháp thực nghiệm:** Thiết kế thuật toán, hiện thực hóa mã nguồn C++ sử dụng thư viện chuẩn STL và đánh giá kết quả bằng hàm phạt (Penalty Function) [2].

---

## CHƯƠNG 1. TỔNG QUAN BÀI TOÁN XẾP LỊCH

### 1.1. Khái niệm bài toán lập lịch

Lập lịch (Scheduling) là quá trình phân bổ các tài nguyên có hạn cho các công việc theo một trục thời gian tuyến tính nhằm thỏa mãn tối đa các mục tiêu định trước mà không xảy ra xung đột [1].

### 1.2. Bài toán xếp lịch học trong trường đại học

Là quy trình phân phối một tập hợp các ca học trong tuần cho các môn học được giảng dạy trong học kỳ, đảm bảo tính điều hòa giữa việc dạy của giảng viên và việc học của sinh viên [1, 2].

### 1.3. Khó khăn khi xếp lịch thủ công

Khi quy mô số lượng môn học tăng lên, các mối quan hệ ràng buộc chéo sẽ tăng theo cấp số nhân. Chỉ cần một thay đổi nhỏ từ phía giảng viên hoặc chương trình đào tạo, toàn bộ hệ thống thời khóa biểu trước đó có thể bị sụp đổ dây chuyền, khiến việc tính toán lại bằng tay cực kỳ bế tắc [1].

### 1.4. Các ràng buộc trong bài toán xếp lịch

Bản chất toán học của bài toán phát sinh từ hai hệ thống ràng buộc cốt lõi [1, 2]:

- **Ràng buộc cứng (Hard Constraints):** Các điều kiện vật lý bắt buộc phải thỏa mãn để lịch học có tính khả thi. Nếu vi phạm, thời khóa biểu hoàn toàn không thể đưa vào sử dụng. Ví dụ: Một nhóm sinh viên hoặc một giảng viên không thể xuất hiện ở hai môn học khác nhau trong cùng một ca học [2].
- **Ràng buộc mềm (Soft Constraints):** Các tiêu chí tối ưu hóa không bắt buộc nhưng được ưu tiên gài gắm để tăng tính tiện ích cho con người. Ví dụ: Xếp các ca học gọn gàng, tránh việc giảng viên bị dồn quá nhiều tiết trong một ngày hoặc phải đi dạy quá nhiều ngày trong tuần [2].

### 1.5. Hướng tiếp cận bằng thuật toán

Sử dụng các thuật toán heuristic (tham lam) giúp sinh ra lịch học hợp lệ trong thời gian ngắn, hỗ trợ đắc lực cho người quản lý [2].

---

## CHƯƠNG 2. CƠ SỞ LÝ THUYẾT

### 2.1. Lý thuyết đồ thị

Đồ thị vô hướng được định nghĩa là một cặp `G = (V, E)`, trong đó `V` là tập hợp các đỉnh (Vertices) khác rỗng và `E` là tập hợp các cạnh (Edges) biểu diễn mối quan hệ hai ngôi giữa các đỉnh [1].

### 2.2. Đỉnh, cạnh, bậc của đỉnh

- **Đỉnh (v ∈ V):** Mỗi đỉnh đại diện cho một lớp môn học cụ thể cần được xếp lịch [1].
- **Cạnh (e ∈ E):** Cạnh nối giữa hai đỉnh `u` và `v` thể hiện sự xung đột nghiêm trọng, nghĩa là hai môn học này không thể diễn ra đồng thời trong cùng một khung giờ [1, 2].
- **Bậc của đỉnh (deg(v)):** Là số lượng cạnh nối trực tiếp với đỉnh `v`, thể hiện tổng số xung đột của môn học đó với các môn học khác [1].

### 2.3. Bài toán tô màu đồ thị

Tô màu đỉnh (Vertex Coloring) yêu cầu gán màu cho các đỉnh của đồ thị sao cho không có bất kỳ hai đỉnh kề nhau nào nhận cùng một màu [1]. Số sắc số `χ(G)` là số lượng màu tối thiểu cần thiết để tô màu hợp lệ cho đồ thị [2].

### 2.4. Mối liên hệ giữa tô màu đồ thị và xếp lịch học

- Tập các môn học được ánh xạ thành tập đỉnh `V` [2].
- Nếu hai môn học có chung giảng viên hoặc có chung một nhóm sinh viên học, một cạnh thuộc tập `E` sẽ được thiết lập nối giữa hai đỉnh đó [2].
- Tập các màu sắc `{1, 2, …, k}` đại diện cho tập các khung giờ học (Timeslots) trong tuần [2].

### 2.5. Hạn chế thực tế của mô hình

Đồ thị tô màu thuần túy xem các màu (timeslot) là vô hạn và các phòng học là đồng nhất. Trong thực tế, số ca học bị giới hạn bởi số ngày trong tuần và số phòng học thực tế có hạn, do đó mô hình lý thuyết cần phải được hiệu chỉnh trong phần cài đặt cụ thể [2].

---

## CHƯƠNG 3. TỔNG QUAN CÁC THUẬT TOÁN

### 3.1. First Fit / Greedy Coloring

Thuật toán duyệt qua danh sách đỉnh theo thứ tự mặc định của dữ liệu đầu vào. Với mỗi đỉnh được xét, nó quét qua các đỉnh kề và gán màu có chỉ số nhỏ nhất khả dụng chưa bị chiếm dụng [1, 2]. Thuật toán vận hành nhanh nhưng nhược điểm lớn là phụ thuộc hoàn toàn vào trật tự sắp xếp ngẫu nhiên của file dữ liệu đầu vào, dễ dẫn đến việc lãng phí số lượng màu sử dụng [1].

**Mã nguồn tham khảo trong project** — file [`GreedyColoring.cpp`](src/algorithm/GreedyColoring.cpp):

```cpp
ColoringResult GreedyColoring::run(const ConflictGraph& graph) {
    int n = graph.getVertexCount();
    const auto& adj = graph.getAdjMatrix();

    ColoringResult result;
    result.algorithmName = "Greedy Coloring";
    result.colors.assign(n, -1);

    for (int i = 0; i < n; ++i) {
        // Thu thap mau cua cac dinh ke da to
        std::set<int> usedColors;
        for (int j = 0; j < n; ++j) {
            if (adj[i][j] && result.colors[j] != -1)
                usedColors.insert(result.colors[j]);
        }
        // Chon mau nho nhat chua bi dung
        int color = 0;
        while (usedColors.count(color)) color++;
        result.colors[i] = color;
    }

    result.chromaticNumber =
        *std::max_element(result.colors.begin(), result.colors.end()) + 1;
    return result;
}
```

### 3.2. Welsh-Powell

Giải thuật cải tiến chiến lược tham lam bằng cách thiết lập một bước tiền xử lý: **Sắp xếp cố định danh sách đỉnh theo thứ tự bậc giảm dần** `deg(v)` trước khi tiến hành tô màu [1, 2]. Việc ưu tiên gán màu cho các môn học có nhiều xung đột nhất trước giúp kiểm soát chặt chẽ việc phát sinh màu mới ở các giai đoạn sau, đưa số lượng màu sử dụng tiệm cận rất gần với số sắc số lý thuyết `χ(G)` [1].

### 3.3. DSATUR (Degree of Saturation)

Là giải thuật động cao cấp hơn, chọn đỉnh tiếp theo dựa trên bậc bão hòa (số lượng màu khác nhau xuất hiện ở các đỉnh kề xung quanh) [1]. Đỉnh nào đang bị "khủng hoảng" và ít lựa chọn màu nhất sẽ được ưu tiên chọn để gán màu trước [2]. DSATUR cho kết quả rất tốt nhưng cấu trúc dữ liệu phức tạp và chi phí tính toán cao hơn Welsh-Powell [1].

### 3.4. So sánh và lựa chọn thuật toán

Đối với bài toán demo quy mô vừa và nhỏ, **Welsh-Powell mang lại sự cân bằng tốt giữa độ phức tạp cài đặt và chất lượng nghiệm** [1, 2]. Do đó, đề tài lựa chọn Welsh-Powell làm giải thuật cốt lõi để triển khai mã nguồn C++.

---

## CHƯƠNG 4. PHÂN TÍCH VÀ THIẾT KẾ HỆ THỐNG DEMO

### 4.1. Bổ sung bộ dữ liệu mẫu (Dataset)

Để kiểm chứng thuật toán, hệ thống giả lập một học kỳ quy mô nhỏ gồm 5 môn học, 3 giảng viên và 3 lớp sinh viên. Khung giờ học gồm tối đa 5 ca (Màu 1 đến 5).

**Bảng 4.1: Danh sách dữ liệu đầu vào (Input)**

| ID Đỉnh | Tên Môn Học       | Mã Môn | Giảng Viên Phụ Trách | Nhóm Lớp Sinh Viên                   |
| :-----: | :---------------- | :----: | :-------------------: | :------------------------------------ |
|    0    | Lập Trình C++     |  M01   |        GV_An          | Nhóm_Sinh_Viên_X                     |
|    1    | Toán rời rạc      |  M02   |       GV_Bình         | Nhóm_Sinh_Viên_Y                     |
|    2    | Cấu Trúc Dữ Liệu |  M03   |       GV_Chi          | Nhóm_Sinh_Viên_Y, Nhóm_Sinh_Viên_Z  |
|    3    | Cơ sở dữ liệu    |  M04   |        GV_An          | Nhóm_Sinh_Viên_Z                     |
|    4    | Mạng máy tính     |  M05   |       GV_Đức          | Nhóm_Sinh_Viên_X                     |

### 4.2. Cách xây dựng đồ thị xung đột

Cạnh xung đột được thiết lập tự động dựa trên hai quy tắc ràng buộc cứng: **chung giảng viên** hoặc **chung ít nhất một nhóm sinh viên**.

- **Cạnh (0, 3):** Chung giảng viên GV_An.
- **Cạnh (0, 4):** Chung nhóm lớp Nhóm_Sinh_Viên_X.
- **Cạnh (1, 2):** Chung nhóm lớp Nhóm_Sinh_Viên_Y.
- **Cạnh (2, 3):** Chung nhóm lớp Nhóm_Sinh_Viên_Z.

**Ma trận kề kết quả (5 × 5):**

```
     0  1  2  3  4
  ┌                 ┐
0 │  0  0  0  1  1  │
1 │  0  0  1  0  0  │
2 │  0  1  0  1  0  │
3 │  1  0  1  0  0  │
4 │  1  0  0  0  0  │
  └                 ┘
```

### 4.3. Phân tích bậc của đỉnh từ ma trận

| Đỉnh | Đỉnh kề          | Bậc deg(v) |
| :--: | :---------------- | :--------: |
|  0   | Đỉnh 3, Đỉnh 4   |     2      |
|  1   | Đỉnh 2            |     1      |
|  2   | Đỉnh 1, Đỉnh 3   |     2      |
|  3   | Đỉnh 0, Đỉnh 2   |     2      |
|  4   | Đỉnh 0            |     1      |

### 4.4. Cấu trúc project thực tế

```text
graph-coloring-scheduler-cpp/
├── README.md                        # Báo cáo tổng quan (file này)
├── run.bat                          # Script biên dịch và chạy nhanh
├── docs/                            # Tài liệu chi tiết từng chương
│   ├── 01-mo-hinh-hoa-bai-toan.md
│   ├── 02-rule-tao-xung-dot.md
│   ├── 03-thuat-toan-welsh-powell.md
│   ├── 04-kiem-thu-va-danh-gia.md
│   └── 05-huong-dan-chay-demo.md
└── src/                             # Mã nguồn C++
    ├── main.cpp                     # Điểm khởi chạy chương trình
    ├── models/
    │   └── ScheduleData.h           # Định nghĩa struct: Subject, Timeslot, Room, ScheduleItem
    ├── demo/
    │   ├── DemoData.h
    │   └── DemoData.cpp             # Khởi tạo dữ liệu giả lập (basic / medium / complex)
    ├── graph/
    │   ├── ConflictGraph.h
    │   └── ConflictGraph.cpp        # Xây dựng đồ thị xung đột, ma trận kề, tính bậc
    ├── algorithm/
    │   ├── GreedyColoring.h
    │   ├── GreedyColoring.cpp       # Thuật toán Greedy (First Fit)
    │   ├── WelshPowell.h
    │   └── WelshPowell.cpp          # Thuật toán Welsh-Powell
    ├── scheduler/
    │   ├── ScheduleBuilder.h
    │   └── ScheduleBuilder.cpp      # Gán Timeslot + Phòng học thực tế
    ├── validator/
    │   ├── ScheduleValidator.h
    │   └── ScheduleValidator.cpp    # Kiểm tra tính hợp lệ của lịch đầu ra
    └── output/
        ├── PrintSchedule.h
        └── PrintSchedule.cpp        # In bảng thời khóa biểu ra console
```

### 4.5. Mô hình dữ liệu (Data Model)

Các thực thể cốt lõi được định nghĩa trong [`ScheduleData.h`](src/models/ScheduleData.h):

```cpp
struct Subject {
    string id;                    // Mã học phần (VD: "012012400311")
    string name;                  // Tên môn học
    string teacherId;             // Mã giảng viên
    vector<string> studentGroups; // Danh sách nhóm/lớp sinh viên học chung
    string requiredRoomType;      // Yêu cầu loại phòng ("Theory" / "LAB" / "Elearning")
    int studentCount;             // Tổng sĩ số thực tế
};

struct Timeslot {
    int id;           // TimeslotID (dùng làm chỉ mục/màu sắc)
    string day;       // "Thu 2", "Thu 3"...
    string period;    // "Ca 1", "Ca 2"...
};

struct Room {
    string id;        // Mã phòng (VD: "A001", "C108", "ELEARNING")
    string name;      // Tên hiển thị
    string roomType;  // "Theory" / "LAB" / "Elearning"
    int capacity;     // Sức chứa
};
```

---

## CHƯƠNG 5. CÀI ĐẶT THUẬT TOÁN

### 5.1. Mô tả logic thuật toán Welsh-Powell

1. Tính bậc cho toàn bộ các đỉnh trong đồ thị.
2. Sắp xếp danh sách đỉnh theo thứ tự bậc giảm dần. Nếu xuất hiện các đỉnh có bậc bằng nhau, hệ thống ưu tiên đỉnh có chỉ số ID nhỏ hơn để đảm bảo tính nhất quán của luồng chạy.
3. Khởi tạo `Màu hiện tại = 1`.
4. Duyệt từ đầu đến cuối danh sách đã sắp xếp. Gán `Màu hiện tại` cho đỉnh đầu tiên chưa được tô màu, đồng thời tiếp tục quét các đỉnh phía sau, gán màu này cho các đỉnh chưa tô và **không có cạnh nối trực tiếp** (độc lập) với bất kỳ đỉnh nào đã nhận `Màu hiện tại` trong lượt duyệt này.
5. Tăng chỉ số màu lên 1 đơn vị (`Màu = Màu + 1`) và lặp lại bước 4 cho đến khi tất cả các đỉnh đều được gán màu hợp lệ.

### 5.2. Pseudo-code

```
Input:  Ma trận kề adjMatrix[N][N], Danh sách đỉnh V
Output: Mảng lưu trữ kết quả gán màu color[N]

1. Tính bậc cho mọi đỉnh v thuộc V dựa trên adjMatrix[v]
2. Sắp xếp danh sách V theo thứ tự giảm dần của degree
3. Khởi tạo color[v] = -1 với mọi v thuộc V
4. Biến current_color = 1
5. while còn đỉnh chưa tô:
      for u trong danh sách đã sắp:
          nếu u chưa tô:
              kiểm tra u có kề với đỉnh nào đã nhận current_color không
              nếu không kề:
                  color[u] = current_color
      current_color++
6. Trả về mảng kết quả color
```

### 5.3. Mã nguồn C++ thực tế — [`WelshPowell.cpp`](src/algorithm/WelshPowell.cpp)

```cpp
ColoringResult WelshPowell::run(const ConflictGraph& graph) {
    int n = graph.getVertexCount();
    const auto& adj = graph.getAdjMatrix();

    ColoringResult result;
    result.algorithmName = "Welsh-Powell";
    result.colors.assign(n, -1);

    // 1. Tao danh sach dinh
    std::vector<int> vertices(n);
    std::iota(vertices.begin(), vertices.end(), 0);

    // 2. Sap xep danh sach dinh theo bac giam dan
    std::sort(vertices.begin(), vertices.end(), [&](int a, int b) {
        return graph.getDegree(a) > graph.getDegree(b);
    });

    // 3. To mau
    int currentColor = 0;
    int uncoloredCount = n;

    while (uncoloredCount > 0) {
        for (int i = 0; i < n; ++i) {
            int v = vertices[i];
            if (result.colors[v] == -1) {
                result.colors[v] = currentColor;
                uncoloredCount--;

                for (int j = i + 1; j < n; ++j) {
                    int u = vertices[j];
                    if (result.colors[u] == -1) {
                        bool canColor = true;
                        for (int k = 0; k < n; ++k) {
                            if (adj[u][k] && result.colors[k] == currentColor) {
                                canColor = false;
                                break;
                            }
                        }
                        if (canColor) {
                            result.colors[u] = currentColor;
                            uncoloredCount--;
                        }
                    }
                }
                currentColor++;
                break;
            }
        }
    }

    result.chromaticNumber = currentColor;
    return result;
}
```

### 5.4. Nhật ký từng bước chạy của giải thuật Welsh-Powell (Trace Log)

Sau bước tiền xử lý, danh sách đỉnh được sắp xếp theo bậc giảm dần có trật tự cố định là: **[Đỉnh 0, Đỉnh 2, Đỉnh 3, Đỉnh 1, Đỉnh 4]**.

**Bảng 5.1: Nhật ký chạy tay chi tiết của thuật toán Welsh-Powell**

| Vòng lặp | Đỉnh xét | Các đỉnh đã mang màu hiện tại | Trạng thái xung đột | Kết quả gán màu | Lý do                                                                       |
| :------: | :------: | :----------------------------: | :------------------: | :--------------: | :--------------------------------------------------------------------------- |
| Màu 1    |    0     |             Rỗng               |        Không         |     **Màu 1**    | Đỉnh đầu tiên được xét trong danh sách.                                     |
| Màu 1    |    2     |           Đỉnh {0}             |        Không         |     **Màu 1**    | `adjMatrix[2][0] == 0` (Độc lập với 0).                                     |
| Màu 1    |    3     |          Đỉnh {0, 2}           |         Có           |     Bỏ qua       | `adjMatrix[3][0] == 1` và `adjMatrix[3][2] == 1`.                            |
| Màu 1    |    1     |          Đỉnh {0, 2}           |         Có           |     Bỏ qua       | `adjMatrix[1][2] == 1` (Xung đột với đỉnh 2).                               |
| Màu 1    |    4     |          Đỉnh {0, 2}           |         Có           |     Bỏ qua       | `adjMatrix[4][0] == 1` (Xung đột với đỉnh 0).                               |
| Màu 2    |    3     |             Rỗng               |        Không         |     **Màu 2**    | Đỉnh đầu tiên chưa tô ở lượt duyệt mới.                                    |
| Màu 2    |    1     |           Đỉnh {3}             |        Không         |     **Màu 2**    | `adjMatrix[1][3] == 0` (Độc lập với 3).                                     |
| Màu 2    |    4     |          Đỉnh {3, 1}           |        Không         |     **Màu 2**    | `adjMatrix[4][3] == 0` và `adjMatrix[4][1] == 0`.                            |

**→ Kết quả:** Tất cả 5 đỉnh được tô hợp lệ chỉ với **2 màu**.

---

## CHƯƠNG 6. THỰC NGHIỆM VÀ ĐÁNH GIÁ

### 6.1. Bảng kết quả đầu ra lịch học (Output)

Ánh xạ kết quả gán màu sang khung giờ: **Màu 1** quy ước thành **Ca Sáng Thứ 2**, **Màu 2** quy ước thành **Ca Chiều Thứ 2**.

**Bảng 6.1: Thời khóa biểu xuất ra từ thuật toán Welsh-Powell**

| Khung Giờ (Màu)      | Môn Học Được Xếp Lịch                              | Giảng Viên           | Nhóm Lớp                    | Trạng Thái Kiểm Tra                        |
| :-------------------- | :-------------------------------------------------- | :------------------- | :--------------------------- | :------------------------------------------ |
| Ca Sáng T2 (Màu 1)   | Lập Trình C++ (M01), Cấu Trúc Dữ Liệu (M03)       | GV_An, GV_Chi        | Nhóm_X, Nhóm_Y, Nhóm_Z     |  Hợp lệ (Không trùng GV, không trùng lớp) |
| Ca Chiều T2 (Màu 2)  | Toán Rời Rạc (M02), CSDL (M04), Mạng MT (M05)      | GV_Bình, GV_An, GV_Đức | Nhóm_Y, Nhóm_Z, Nhóm_X  |  Hợp lệ (Không trùng GV, không trùng lớp) |

### 6.2. Đối sánh thực nghiệm và hàm phạt (Penalty Function)

Để chứng minh định lượng tính ưu việt của Welsh-Powell, hệ thống tiến hành chạy dry-run thuật toán **First Fit** trên cùng bộ dữ liệu theo thứ tự ID mặc định `[0, 1, 2, 3, 4]`:

| Bước | Đỉnh | Kiểm tra                            | Kết quả                     |
| :--: | :--: | :----------------------------------- | :-------------------------- |
|  1   |  0   | Chưa kề ai                          | → **Màu 1**                |
|  2   |  1   | Không kề 0                           | → **Màu 1**                |
|  3   |  2   | Kề 1 (đang Màu 1)                   | → **Màu 2**                |
|  4   |  3   | Kề 0 (Màu 1) và kề 2 (Màu 2)       | → Bắt buộc tăng **Màu 3** |
|  5   |  4   | Kề 0 (Màu 1), không kề 3            | → **Màu 2**                |

**Kết quả:** First Fit phải tiêu tốn tới **3 khung giờ** (Màu 1, 2, 3).

### 6.3. Hàm phạt tổng hợp (Penalty Function)

Độ hiệu quả được đo lường thông qua giá trị **Hàm phạt tổng hợp (TP)** [2]:

```
TP = P1 × 10 + P2 × 1
```

Trong đó:
- **P1:** Số ca bị vi phạm ràng buộc cứng (trùng lặp thực thể) → Trọng số phạt **10**.
- **P2:** Tổng số khung giờ (màu) hệ thống phải sử dụng → Trọng số phạt **1**.

**Bảng 6.2: Bảng đối sánh chỉ số phạt**

| Giải Thuật           | Vi Phạm Ràng Buộc Cứng (P1) | Số Khung Giờ Dùng (P2) | Tổng Điểm Phạt (TP) |
| :------------------- | :--------------------------: | :---------------------: | :------------------: |
| First Fit (Greedy)   |              0               |            3            |        **3**         |
| **Welsh-Powell**     |              0               |            2            |        **2**         |

**Nhận xét:** Cả hai giải thuật đều không phát hiện vi phạm ràng buộc cứng trên bộ dữ liệu thử nghiệm (`P1 = 0`). Tuy nhiên, trên cùng một cấu trúc xung đột, Welsh-Powell cho điểm phạt thấp hơn (`2 < 3`) nhờ chiến lược sắp xếp bậc thông minh, giúp nén gọn thời khóa biểu và tiết kiệm được **1 khung giờ học** so với giải thuật tham lam thông thường.

---

## CHƯƠNG 7. HƯỚNG DẪN BIÊN DỊCH VÀ CHẠY DEMO

### 7.1. Yêu cầu

- Trình biên dịch `g++` (MinGW / MSYS2) đã thêm vào `PATH`.
- Hệ điều hành: Windows.

### 7.2. Cách chạy nhanh

```bash
# Chạy bằng file batch (tự động biên dịch + chạy)
run.bat

# Hoặc biên dịch thủ công
g++ -std=c++17 -o main.exe src/main.cpp src/demo/DemoData.cpp src/graph/ConflictGraph.cpp src/algorithm/GreedyColoring.cpp src/algorithm/WelshPowell.cpp src/scheduler/ScheduleBuilder.cpp src/validator/ScheduleValidator.cpp src/output/PrintSchedule.cpp
./main.exe
```

### 7.3. Luồng chạy của chương trình

1. Load dữ liệu demo (chọn dataset: `basic` / `medium` / `complex`).
2. In danh sách môn học (đỉnh).
3. Tạo đồ thị xung đột (xây dựng ma trận kề + danh sách cạnh).
4. In danh sách cạnh xung đột kèm lý do.
5. Tính bậc từng đỉnh.
6. Chạy **Greedy** và **Welsh-Powell** để so sánh.
7. Chuyển màu thành Timeslot.
8. Gán phòng học phù hợp (theo loại phòng + sức chứa).
9. In bảng lịch học.
10. Validator kiểm tra lịch có hợp lệ không.
11. Chấm điểm chất lượng lịch (Penalty Function).

---

## KẾT LUẬN

### 1. Kết quả đạt được

- Đề tài đã mô hình hóa thành công bài toán lập lịch lớp học quy mô nhỏ thành bài toán Vertex Coloring một cách tường minh [1, 2].
- Triển khai thành công mã nguồn C++ chạy giải thuật Welsh-Powell, đưa ra kết quả phân bổ khung giờ khả thi, không xảy ra xung đột thực thể và có điểm số phạt tối ưu hơn giải thuật tham lam mặc định [2].

### 2. Hạn chế của hệ thống

- Mô hình cài đặt hiện tại đang hoạt động trong điều kiện giả định số lượng phòng học là vô hạn và các phòng học đồng nhất về sức chứa. Nếu đưa vào áp dụng thực tế tại giảng đường có số phòng giới hạn, thuật toán sẽ cần bổ sung thêm bước kiểm tra tài nguyên phòng.
- Dữ liệu thử nghiệm còn ở quy mô nhỏ, chưa bao quát được kịch bản phức tạp khi sinh viên đăng ký học tín chỉ tự do hoàn toàn.

### 3. Hướng phát triển

- Bổ sung thực thể Phòng học vào cấu trúc ma trận kề, thực hiện thuật toán tô màu mở rộng để xử lý đồng thời bài toán tìm kiếm khung giờ bận và phòng trống.
- Nghiên cứu ứng dụng các thuật toán tối ưu hóa thông minh Meta-heuristic (như thuật toán di truyền - Genetic Algorithm) để xử lý đa mục tiêu khi mở rộng dữ liệu ở quy mô lớn [1].

---

## PHÂN CÔNG THÀNH VIÊN

| Thành viên | Module | File chính |
| :--- | :--- | :--- |
| Khiêm Phạm | Model + Demo data | `ScheduleData.h`, `DemoData.cpp` |
| Đình Chí | Conflict graph | `ConflictGraph.cpp` |
| Trung Tín | Greedy + Welsh-Powell | `GreedyColoring.cpp`, `WelshPowell.cpp` |
| Tố Quyên | Schedule + Output | `ScheduleBuilder.cpp`, `PrintSchedule.cpp` |
| Trang Đài | Validator | `ScheduleValidator.cpp` |
| Trung Tín | Main + Docs | `main.cpp`, `README.md`, `docs/` |

---

## TÀI LIỆU THAM KHẢO

> **[1]** Biswas, S., Nusrat, S. A., Sharmin, N., & Rahman, M. (2023). *Graph Coloring in University Timetable Scheduling*. International Journal of Intelligent Systems and Applications, 15(3), 16–32.
>
> **[2]** Malviya, A., Agrawal, B., & Kumar, S. (2024). *Graph Coloring Algorithm for Course Time Table Scheduling Problem*. ShodhKosh: Journal of Visual and Performing Arts, 5(3), 452–460.
