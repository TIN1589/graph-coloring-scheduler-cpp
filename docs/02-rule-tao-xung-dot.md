
## 1. Cơ sở Lý thuyết

### 1.1. Ánh xạ bài toán sang Đồ thị

Bài toán xếp lịch học được mô hình hóa thành bài toán **Tô màu Đồ thị (Graph Coloring)**:

| Khái niệm thực tế | Khái niệm Đồ thị | Cấu trúc C++ |
|:---|:---|:---|
| Môn học | Đỉnh (Vertex) | `Subject` |
| Xung đột lịch | Cạnh (Edge) | `ConflictEdge` |
| Ca học | Màu (Color) | `Timeslot` |
| Phòng học | Ràng buộc tài nguyên | `Room` |

### 1.2. Định nghĩa Xung đột

Hai môn học được xem là **xung đột** khi vi phạm một trong hai ràng buộc cứng:

**Ràng buộc HC1 — Tính độc quyền nhân sự:**
> Một giảng viên không thể dạy hai môn học ở cùng một ca học.  
> → Hai môn có cùng `teacherId` phải được xếp ở hai ca khác nhau.

**Ràng buộc HC2 — Tính độc quyền nhóm học:**
> Một nhóm sinh viên không thể học hai môn cùng lúc.  
> → Hai môn có chung ít nhất một phần tử trong `studentGroups` phải được xếp ở hai ca khác nhau.

### 1.3. Tính chất của Đồ thị Xung đột

- **Vô hướng (Undirected):** Nếu môn A xung đột với môn B thì môn B cũng xung đột với môn A.
- **Không có vòng lặp (No self-loop):** Một môn không thể xung đột với chính nó.
- **Lưu trữ bằng Ma trận kề:** Thuận tiện cho việc kiểm tra xung đột trong O(1).

---

## 2. Thiết kế Cấu trúc Dữ liệu

### 2.1. Enum `ConflictType` — Phân loại xung đột

```cpp
enum class ConflictType {
    TEACHER_CONFLICT,        // Trùng giảng viên (HC1)
    STUDENT_GROUP_CONFLICT,  // Trùng nhóm sinh viên (HC2)
    BOTH                     // Vi phạm đồng thời cả hai
};
```

**Lý do dùng `enum class` thay vì `string`:**  
Kiểu `string` tự do dễ gây lỗi chính tả và không thể kiểm tra bằng `switch-case` hiệu quả. `enum class` đảm bảo type-safety: compiler báo lỗi ngay nếu dùng giá trị không hợp lệ.

### 2.2. Struct `ConflictEdge` — Cạnh xung đột

```cpp
struct ConflictEdge {
    int u;                                 // Chỉ mục đỉnh u
    int v;                                 // Chỉ mục đỉnh v
    ConflictType type;                     // Loại xung đột
    string description;                    // Mô tả nguyên nhân (để in báo cáo)
    vector<string> sharedGroups;           // Danh sách nhóm SV bị trùng
};
```

**Điểm thiết kế quan trọng:** Tách riêng `description` (chuỗi văn bản) và `sharedGroups` (dữ liệu thô). Phase 3 có thể truy cập `sharedGroups` trực tiếp mà không cần phân tích chuỗi.

### 2.3. Struct `GraphStats` — Thống kê đồ thị

```cpp
struct GraphStats {
    int vertexCount      = 0;  // Tổng số đỉnh
    int edgeCount        = 0;  // Tổng số cạnh
    int maxDegree        = 0;  // Bậc lớn nhất
    int minDegree        = 0;  // Bậc nhỏ nhất
    double avgDegree     = 0;  // Bậc trung bình
    int isolatedCount    = 0;  // Số đỉnh bị lập (bậc = 0)
    int teacherConflicts = 0;  // Số cạnh do trùng GV
    int studentConflicts = 0;  // Số cạnh do trùng nhóm SV
    int bothConflicts    = 0;  // Số cạnh vi phạm cả hai
};
```

Thống kê được tính một lần sau `buildGraph()` và cache lại, tránh tính toán lặp lại mỗi khi cần báo cáo.

### 2.4. Lớp `ConflictGraph` — Đồ thị Xung đột

```
ConflictGraph
├── Thuộc tính private
│   ├── subjects_       : vector<Subject>           — Danh sách đỉnh
│   ├── idToIndex_      : map<string, int>           — Tra cứu nhanh theo mã HP
│   ├── adjMatrix_      : vector<vector<bool>>       — Ma trận kề NxN
│   ├── edges_          : vector<ConflictEdge>       — Danh sách cạnh
│   ├── degree_         : vector<int>                — Cache bậc đỉnh
│   ├── stats_          : GraphStats                 — Thống kê tổng quan
│   └── built_          : bool                       — Cờ kiểm soát thứ tự gọi
│
├── API công khai (cho cho phrase3 )
│   ├── buildGraph()                — Xây dựng đồ thị
│   ├── isAdjacent(u, v)            — Kiểm tra xung đột O(1)
│   ├── getDegree(i)                — Lấy bậc đỉnh
│   ├── getNeighbors(i)             — Lấy danh sách đỉnh kề
│   ├── getAdjMatrix()              — Trả về ma trận kề
│   └── getStats()                  — Trả về thống kê
│
└── Hàm nội bộ (private helpers)
    ├── findStudentGroupConflicts() — Tính giao tập hợp nhóm SV
    ├── computeStats()              — Tính toán và cache thống kê
    ├── buildDescription()          — Tạo chuỗi mô tả xung đột
    └── assertBuilt()               — Bảo vệ thứ tự gọi hàm
```

---

## 3. Thuật toán Xây dựng Đồ thị

### 3.1. Pseudocode

```
HÀM buildGraph():
    n = số lượng môn học

    VỚI i từ 0 đến n-1:
        VỚI j từ i+1 đến n-1:       // Chỉ duyệt nửa trên (tránh trùng lặp)

            teacherConflict = (teacherId[i] == teacherId[j])
            sharedGroups    = giao(studentGroups[i], studentGroups[j])
            studentConflict = (sharedGroups không rỗng)

            NẾU KHÔNG có xung đột nào: bỏ qua cặp (i, j)

            type = phân loại xung đột (TEACHER / STUDENT / BOTH)

            Thêm ConflictEdge(i, j, type, mô tả, sharedGroups) vào edges_
            adjMatrix[i][j] = adjMatrix[j][i] = true    // Đồ thị vô hướng
            degree[i]++; degree[j]++

    Tính toán GraphStats
    Đánh dấu built_ = true
```

**Độ phức tạp:** O(N² × G) trong đó N là số môn học và G là kích thước trung bình của `studentGroups`. Với bài toán quy mô thực tế (N ≤ vài trăm), ma trận kề là lựa chọn phù hợp.

### 3.2. Tìm giao tập hợp nhóm sinh viên

```cpp
// Dùng std::set để tra cứu nhanh O(log n) thay vì vòng lặp lồng O(n*m)
bool findStudentGroupConflicts(const Subject& s1, const Subject& s2,
                               vector<string>& shared) {
    set<string> set1(s1.studentGroups.begin(), s1.studentGroups.end());
    for (const auto& g : s2.studentGroups) {
        if (set1.count(g)) shared.push_back(g);
    }
    sort(shared.begin(), shared.end());  // Sắp xếp để kết quả nhất quán
    return !shared.empty();
}
```

### 3.3. Cơ chế `assertBuilt()` — Bảo vệ thứ tự gọi

```cpp
void assertBuilt(const string& callerName) const {
    if (!built_) {
        throw std::logic_error(
            "[ConflictGraph::" + callerName + "] "
            "Phải gọi buildGraph() trước!");
    }
}
```

Tất cả hàm truy vấn đều gọi `assertBuilt()` ở đầu. Nếu quên gọi `buildGraph()`, chương trình ném ngoại lệ rõ ràng thay vì trả về kết quả sai âm thầm.

---

## 4. Kết quả Chạy thực tế

### 4.1. Môi trường kiểm thử

- **Dataset:** `medium` (8 môn học, lấy từ Phase 1 của Khiêm Phạm)
- **Lệnh biên dịch:**  
  ```
  g++ -std=c++17 src/main.cpp src/demo/DemoData.cpp src/graph/ConflictGraph.cpp -I src -o main.exe
  ```

### 4.2. Danh sách đỉnh và bậc

| STT | Mã học phần | Tên môn học | GV | Bậc |
|:---:|:---|:---|:---:|:---:|
| 0 | 012012400311 | Lập trình OOP | GV01 | 4 |
| 1 | 012012400224 | Cấu trúc dữ liệu | GV02 | 5 |
| 2 | 012012100214 | Cơ sở dữ liệu | GV01 | 3 |
| 3 | 012012300216 | Mạng máy tính | GV03 | 5 |
| 4 | 012012500107 | Hệ điều hành | GV04 | 3 |
| 5 | 012012210523 | An toàn thông tin | GV05 | 4 |
| 6 | 012012301309 | Công nghệ web | GV02 | 2 |
| 7 | 012000121509 | Xác suất thống kê | GV06 | **6** |

**Nhận xét:** Môn Xác suất thống kê có bậc cao nhất (6) vì có nhóm sinh viên học chung với hầu hết các môn khác. Đây sẽ là đỉnh được Welsh-Powell ưu tiên xử lý đầu tiên.

### 4.3. Danh sách cạnh xung đột (16 cạnh)

| # | Môn A | Môn B | Loại xung đột | Nhóm trùng |
|:---:|:---|:---|:---|:---|
| 1 | Lập trình OOP | Cấu trúc dữ liệu | Trùng nhóm SV | CNTT01 |
| 2 | Lập trình OOP | Cơ sở dữ liệu | **Trùng giảng viên** | GV01 |
| 3 | Lập trình OOP | Mạng máy tính | Trùng nhóm SV | CNTT01 |
| 4 | Lập trình OOP | Xác suất thống kê | Trùng nhóm SV | CNTT01 |
| 5 | Cấu trúc dữ liệu | Cơ sở dữ liệu | Trùng nhóm SV | CNTT02 |
| 6 | Cấu trúc dữ liệu | Mạng máy tính | Trùng nhóm SV | CNTT01 |
| 7 | Cấu trúc dữ liệu | Công nghệ web | **Trùng giảng viên** | GV02 |
| 8 | Cấu trúc dữ liệu | Xác suất thống kê | Trùng nhóm SV | CNTT01, CNTT02 |
| 9 | Cơ sở dữ liệu | Xác suất thống kê | Trùng nhóm SV | CNTT02 |
| 10 | Mạng máy tính | Hệ điều hành | Trùng nhóm SV | CNTT03 |
| 11 | Mạng máy tính | An toàn thông tin | Trùng nhóm SV | CNTT03 |
| 12 | Mạng máy tính | Xác suất thống kê | Trùng nhóm SV | CNTT01, CNTT03 |
| 13 | Hệ điều hành | An toàn thông tin | Trùng nhóm SV | CNTT03 |
| 14 | Hệ điều hành | Xác suất thống kê | Trùng nhóm SV | CNTT03 |
| 15 | An toàn thông tin | Công nghệ web | Trùng nhóm SV | CNTT04 |
| 16 | An toàn thông tin | Xác suất thống kê | Trùng nhóm SV | CNTT03 |

### 4.4. Thống kê tổng quan

| Thông số | Giá trị |
|:---|:---:|
| Số đỉnh (môn học) | 8 |
| Số cạnh (xung đột) | 16 |
| Bậc cao nhất | 6 (Xác suất thống kê) |
| Bậc thấp nhất | 2 (Công nghệ web) |
| Bậc trung bình | 4.00 |
| Đỉnh bị lập (bậc = 0) | 0 |
| Xung đột do trùng GV | 2 cạnh |
| Xung đột do trùng nhóm SV | 14 cạnh |
| Xung đột cả hai | 0 cạnh |

### 4.5. Ma trận kề (8×8)

```
      0  1  2  3  4  5  6  7
   0 |0  1  1  1  0  0  0  1   <- Lập trình OOP
   1 |1  0  1  1  0  0  1  1   <- Cấu trúc dữ liệu
   2 |1  1  0  0  0  0  0  1   <- Cơ sở dữ liệu
   3 |1  1  0  0  1  1  0  1   <- Mạng máy tính
   4 |0  0  0  1  0  1  0  1   <- Hệ điều hành
   5 |0  0  0  1  1  0  1  1   <- An toàn thông tin
   6 |0  1  0  0  0  1  0  0   <- Công nghệ web
   7 |1  1  1  1  1  1  0  0   <- Xác suất thống kê
```

**Kiểm chứng:** Ma trận hoàn toàn đối xứng — đúng với tính chất đồ thị vô hướng.

---

## 5. Đánh giá và Hướng mở rộng

### 5.1. Kết quả đạt được

- Xây dựng thành công đồ thị xung đột từ dữ liệu Phase 1.
- Phát hiện và phân loại chính xác tất cả các cặp môn xung đột.
- Cung cấp đầy đủ API để Phase 3 (Welsh-Powell) sử dụng.
- In báo cáo trực quan, rõ ràng ra console.

### 5.2. Hướng mở rộng trong tương lai

| Tính năng | Mô tả |
|:---|:---|
| Thêm ràng buộc HC3 | Tích hợp kiểm tra loại phòng (`requiredRoomType`) vào quá trình xây dựng cạnh |
| Đồ thị có trọng số | Gán trọng số cho cạnh theo mức độ nghiêm trọng của xung đột |
| Xuất file | In ma trận kề ra file `.csv` hoặc `.dot` (GraphViz) để vẽ đồ thị |
| Tối ưu bộ nhớ | Dùng danh sách kề (`adjacency list`) thay ma trận kề khi N lớn |


