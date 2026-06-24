#include "DemoData.h"

// Sinh dữ liệu 10 ca học (5 ngày x 2 buổi)
vector<Timeslot> createTimeslots() {
    vector<Timeslot> slots;
    int id = 1;
    vector<string> days = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday"};
    vector<string> periods = {"Morning", "Afternoon"};
    
    for (const string& day : days) {
        for (const string& period : periods) {
            slots.push_back({id++, day, period});
        }
    }
    return slots;
}

// Sinh dữ liệu phòng học với sự phân hóa về sức chứa và loại phòng
vector<Room> createRooms() {
    return {
        {1, "A1-101", 30, "Theory"},  // Phòng nhỏ
        {2, "A1-102", 100, "Theory"}, // Giảng đường lớn
        {3, "B1-Lab1", 40, "Lab"},    // Phòng máy thực hành
        {4, "B1-Lab2", 40, "Lab"}
    };
}

// Dataset Basic: Rất ít môn học, tài nguyên phòng và ca học dư dả. 
// Thuật toán chạy ngẫu nhiên cũng có thể ra kết quả.
vector<Subject> createBasicDemoData() {
    return {
        {1, "Toan Rr", "GV01", "KTPM01", 25, "Theory"},
        {2, "Lap trinh C++", "GV02", "KTPM01", 35, "Lab"},
        {3, "Triet hoc", "GV03", "KTPM02", 80, "Theory"}
    };
}

// Dataset Medium: Tăng số lượng môn. Bắt đầu xuất hiện xung đột trực tiếp
// (Trùng giảng viên GV01, trùng nhóm sinh viên KTPM01).
vector<Subject> createMediumDemoData() {
    return {
        {1, "Toan Rr", "GV01", "KTPM01", 40, "Theory"},
        {2, "Cau truc DL", "GV01", "KTPM02", 40, "Theory"}, // Trùng GV01
        {3, "Lap trinh C++", "GV02", "KTPM01", 35, "Lab"},  // Trùng nhóm SV KTPM01
        {4, "Mang may tinh", "GV03", "KTPM03", 40, "Lab"},
        {5, "Co so Du lieu", "GV04", "KTPM02", 90, "Theory"}// Lớp đông, ép phải dùng phòng A1-102
    };
}

// Dataset Complex: Đồ thị dày đặc (Dense Graph). Nhiều môn học đan chéo nhau về giảng viên 
// và nhóm sinh viên. Nút thắt cổ chai nằm ở các phòng Lab (chỉ có 2 phòng nhưng nhiều môn yêu cầu).
vector<Subject> createComplexDemoData() {
    vector<Subject> complexData = createMediumDemoData();
    complexData.push_back({6, "AI", "GV02", "KTPM03", 30, "Lab"});
    complexData.push_back({7, "HQT CSDL", "GV04", "KTPM01", 35, "Lab"});
    complexData.push_back({8, "Phat trien Web", "GV05", "KTPM02", 35, "Lab"});
    complexData.push_back({9, "Cong nghe PM", "GV01", "KTPM03", 80, "Theory"});
    complexData.push_back({10, "Kien truc MT", "GV06", "KTPM01", 95, "Theory"});
    return complexData;
}