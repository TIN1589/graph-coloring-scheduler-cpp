#ifndef SCHEDULE_DATA_H
#define SCHEDULE_DATA_H

#include <string>
#include <vector>

using namespace std;

// Đại diện cho một Ca học (Màu sắc trong tô màu đồ thị)
struct Timeslot {
    int id;
    string day;      // Ví dụ: "Monday", "Tuesday"
    string period;   // Ví dụ: "Morning (07:00 - 09:30)", "Afternoon"
};

// Đại diện cho một Phòng học (Tài nguyên vật lý)
struct Room {
    int id;
    string name;     // Ví dụ: "A1-101", "Lab-205"
    int capacity;    // Sức chứa tối đa của phòng
    string roomType; // "Theory" (Lý thuyết) hoặc "Lab" (Thực hành)
};

// Đại diện cho một Môn học / Lớp học phần (Đỉnh của đồ thị)
struct Subject {
    int id;
    string name;
    string teacherId;      // Dùng để tạo cạnh xung đột nếu trùng giảng viên
    string studentGroupId; // Dùng để tạo cạnh xung đột nếu trùng nhóm sinh viên
    int studentCount;      // Số lượng sinh viên thực tế đăng ký
    string requiredRoom;   // Yêu cầu loại phòng: "Theory" hoặc "Lab"
};

// Đại diện cho một kết quả xếp lịch thành công
struct ScheduleItem {
    Subject subject;
    Timeslot timeslot;
    Room room;
};

#endif // SCHEDULE_DATA_H