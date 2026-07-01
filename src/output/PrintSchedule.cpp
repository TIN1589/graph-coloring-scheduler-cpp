#include <iostream>
#include <iomanip>
#include "PrintSchedule.h"
#include "../models/ScheduleData.h" // Đảm bảo nhận diện cấu trúc struct

using namespace std;

void printAllOutputs(
    const std::vector<Subject>& subjects,
    const std::vector<Room>& rooms,
    const std::vector<int>& colors,
    const std::vector<FinalScheduleItem>& finalSchedule
) {
    cout << "=========================================================\n";
    cout << "KẾT QUẢ TÔ MÀU ĐỒ THỊ (GÁN CA HỌC ĐÃ KHỚP PHÒNG)\n";
    cout << "=========================================================\n";

    for (size_t i = 0; i < subjects.size(); ++i) {
        cout << "Môn " << subjects[i].id << " (" << subjects[i].name << ") ---> [Mã Màu: " << colors[i] << "]\n";
    }

    cout << "\n=========================================================================================================\n";
    cout << left << setw(10) << "Mã Môn" << setw(22) << "Tên Môn Học" << setw(15) << "Giảng Viên" 
         << setw(12) << "Lớp" << setw(18) << "Thời Gian" << setw(10) << "Phòng" << setw(14) << "Loại Phòng" << "Sức Chứa" << endl;
    cout << "=========================================================================================================\n";

    for (const auto& item : finalSchedule) {
        cout << left << setw(10) << item.subject.id
             << setw(22) << item.subject.name
             << setw(15) << item.subject.teacher
             << setw(12) << item.subject.studentGroup
             << setw(18) << (item.slot.day + " (" + item.slot.time + ")")
             << setw(10) << item.room.id
             << setw(14) << (item.room.type == "LAB" ? "Thực Hành" : "Lý Thuyết")
             << item.room.capacity << endl;
    }
    cout << "=========================================================================================================\n";
}