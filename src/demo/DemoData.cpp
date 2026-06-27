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

static std::vector<Subject> createBasicDemoData() {
    return {
        {"012012400311", "Lap trinh OOP",       "GV01", {"CNTT01"},           "LAB",       40},
        {"012012301309", "Cau truc du lieu",    "GV02", {"CNTT01"},           "Theory",    50},
        {"012012100214", "Co so du lieu",       "GV01", {"CNTT02"},           "LAB",       45},
        {"012012300216", "Mang may tinh",       "GV03", {"CNTT01", "CNTT02"}, "LAB",       40},
        {"0120005105117","Triet hoc Mac-Lenin", "GV04", {"CNTT03"},           "Elearning", 60}
    };
}

static std::vector<Subject> createMediumDemoData() {
    return {
        {"012012400311", "Lap trinh OOP",       "GV01", {"CNTT01"},                   "LAB",       40},
        {"012012400224", "Cau truc du lieu",    "GV02", {"CNTT01", "CNTT02"},         "Theory",    95},
        {"012012100214", "Co so du lieu",       "GV01", {"CNTT02"},                   "LAB",       45},
        {"012012300216", "Mang may tinh",       "GV03", {"CNTT01", "CNTT03"},         "LAB",       40},
        {"012012500107", "He dieu hanh",        "GV04", {"CNTT03"},                   "Theory",    60},
        {"012012210523", "An toan thong tin",   "GV05", {"CNTT03", "CNTT04"},         "LAB",       35},
        {"012012301309", "Cong nghe web",       "GV02", {"CNTT04"},                   "Theory",    50},
        {"012000121509", "Xac suat thong ke",   "GV06", {"CNTT01","CNTT02","CNTT03"}, "Elearning", 150}
    };
}

static std::vector<Subject> createComplexDemoData() {
    return {
        {"012012400311", "Lap trinh OOP",        "GV01", {"CNTT01"},                   "LAB",       40},
        {"012012400224", "Cau truc du lieu",     "GV02", {"CNTT01", "CNTT02"},         "Theory",    95},
        {"012012100214", "Co so du lieu",        "GV01", {"CNTT02"},                   "LAB",       45},
        {"012012300216", "Mang may tinh",        "GV03", {"CNTT01", "CNTT03"},         "LAB",       40},
        {"012012500107", "He dieu hanh",         "GV04", {"CNTT03"},                   "Theory",    60},
        {"012012210523", "An toan thong tin",    "GV05", {"CNTT03", "CNTT04"},         "LAB",       35},
        {"012012301309", "Cong nghe web",        "GV02", {"CNTT04"},                   "Theory",    50},
        {"012012203807", "Tri tue nhan tao",     "GV06", {"CNTT02", "CNTT04"},         "LAB",       40},
        {"012012100816", "Phan tich thiet ke",   "GV07", {"CNTT01", "CNTT04"},         "Theory",    70},
        {"012012101011", "Kiem thu phan mem",    "GV03", {"CNTT02", "CNTT03"},         "Theory",    60},
        {"012012302205", "Lap trinh mang",       "GV05", {"CNTT01"},                   "LAB",       40},
        {"012000121509", "Xac suat thong ke",    "GV08", {"CNTT01","CNTT02","CNTT03"}, "Elearning", 150}
    };
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