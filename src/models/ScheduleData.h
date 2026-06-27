/**
 * @file ScheduleData.h
 * @brief Định nghĩa các thực thể dữ liệu cốt lõi cho hệ thống xếp lịch (Bản cập nhật sát thực tế).
 */
#ifndef SCHEDULE_DATA_H
#define SCHEDULE_DATA_H

#include <string>
#include <vector>

using namespace std;

// Đại diện cho một Ca học (Khung thời gian)
struct Timeslot {
    int id;          // TimeslotID vẫn giữ là int để dễ làm chỉ mục/màu sắc
    string day;      // "Thu 2", "Thu 3"...
    string period;   // "Ca 1", "Ca 2"...
};

// Đại diện cho một Phòng học (Tài nguyên vật lý)
struct Room {
    string id;       // Sửa thành string (VD: "LAB01", "A101")
    string name;     // Tên hiển thị đầy đủ
    string roomType; // "Theory" (Lý thuyết) hoặc "LAB" (Thực hành)
    int capacity;    // Sức chứa
};

// Đại diện cho một Lớp học phần cần xếp lịch (Đỉnh của đồ thị)
struct Subject {
    string id;                   // Mã học phần (VD: "012012400311")
    string name;                 // Tên môn học
    string teacherId;            // Mã giảng viên
    vector<string> studentGroups;// Danh sách các nhóm/lớp sinh viên học chung
    string requiredRoomType;     // Yêu cầu phòng ("Theory" hoặc "LAB")
    int studentCount;            // Tổng sĩ số thực tế
};

// Đại diện cho một kết quả xếp lịch thành công
struct ScheduleItem {
    Subject subject;
    Timeslot timeslot;
    Room room;
};

#endif // SCHEDULE_DATA_H