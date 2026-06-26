/**
 * @file DemoData.cpp
 * @brief Triển khai logic khởi tạo dữ liệu giả lập sử dụng mã học phần và chuẩn mã phòng thực tế.
 */
#include "DemoData.h"

vector<Timeslot> createTimeslots() {
    vector<Timeslot> slots;
    vector<string> days = {"Thu 2", "Thu 3", "Thu 4", "Thu 5", "Thu 6", "Thu 7"};
    int id = 1;
    
    for (const auto& day : days) {
        slots.push_back({id++, day, "Ca 1"}); // Sáng
        slots.push_back({id++, day, "Ca 2"}); // Sáng
        slots.push_back({id++, day, "Ca 3"}); // Chiều
        slots.push_back({id++, day, "Ca 4"}); // Chiều
        slots.push_back({id++, day, "Ca 5"}); // Tối (Thường dành cho E-Learning)
    }
    return slots;
}

// Khởi tạo danh sách phòng học chuẩn hóa: [Dãy][Lầu][Số phòng]
vector<Room> createRooms() {
    return {
        // Dãy A
        {"A001", "Phong A001 (Tang tret)", "Theory", 60}, 
        {"A204", "Phong A204 (Lau 2)", "Theory", 60},
        
        // Dãy B - Phân khu lý thuyết / Hội trường
        {"B303", "Phong B303 (Lau 3)", "Theory", 80},
        {"B305", "Phong B305 (Lau 3)", "Theory", 120}, // Phòng lớn theo dữ liệu thực tế
        
        // Dãy C - Phân khu Thực hành (LAB)
        {"C108", "Phong C108 (Lau 1)", "LAB", 45},     // LAB theo dữ liệu thực tế
        {"C202", "Phong C202 (Lau 2)", "LAB", 45},
        
        // Ngoại lệ: Không gian học Trực tuyến / LMS
        // Đặt sức chứa cực lớn để thuật toán không bao giờ báo lỗi thiếu chỗ
        {"ELEARNING", "Phong Hoc Truc Tuyen (Tu hoc o nha)", "Elearning", 9999} 
    };
}

// Dataset Basic: Dữ liệu thưa, thử nghiệm 3 loại phòng khác nhau
vector<Subject> createBasicDemoData() {
    return {
        {"012012400311", "Phan tich thiet ke giai thuat", "GV01", {"CNTT01"}, "Theory", 50},
        {"012012301309", "Lap trinh mang", "GV02", {"CNTT01"}, "LAB", 40},
        {"0120005105117", "Triet hoc Mac - Lenin", "GV03", {"CNTT02"}, "Elearning", 60} // Môn lý luận thường học online
    };
}

// Dataset Medium: Bắt đầu có ghép lớp, kiểm thử sức chứa của phòng Hội trường (B305)
vector<Subject> createMediumDemoData() {
    return {
        {"012012400224", "Cau truc du lieu va giai thuat", "GV01", {"CNTT01", "CNTT02"}, "Theory", 95}, // 95 SV -> Ép thuật toán phải chọn phòng B305
        {"012012100214", "Thiet ke co so du lieu", "GV02", {"CNTT01"}, "LAB", 40}, // Phải chọn C108 hoặc C202
        {"012012210523", "Cong nghe phan mem", "GV01", {"CNTT03"}, "Theory", 55}, // Trùng GV01
        {"012012203807", "Chuyen de He thong giao thong thong minh", "GV04", {"CNTT02"}, "Elearning", 45} // Lịch online theo ảnh thực tế
    };
}

// Dataset Complex: Đồ thị dày đặc
vector<Subject> createComplexDemoData() {
    vector<Subject> data = createMediumDemoData();
    data.push_back({"012012100816", "Phan tich thiet ke he thong", "GV02", {"CNTT03"}, "Theory", 55});
    data.push_back({"012012500107", "He dieu hanh", "GV05", {"CNTT01"}, "LAB", 40});
    data.push_back({"012012300216", "Mang may tinh", "GV06", {"CNTT02", "CNTT03"}, "LAB", 80}); // Xung đột nặng: Cần xếp vào LAB nhưng sĩ số đông
    data.push_back({"012000121509", "Xac suat thong ke", "GV07", {"CNTT01", "CNTT02", "CNTT03"}, "Elearning", 150}); // Ghép 3 lớp học Online
    return data;
}

// --- API CÔNG KHAI ---
vector<string> getAvailableDatasetNames() {
    return {"basic", "medium", "complex"};
}

vector<Subject> getDemoDataByName(const string& name) {
    if (name == "basic") return createBasicDemoData();
    if (name == "medium") return createMediumDemoData();
    if (name == "complex") return createComplexDemoData();
    return {}; 
}