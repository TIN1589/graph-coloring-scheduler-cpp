<<<<<<< HEAD
/**
 * @file    PrintSchedule.cpp
 * @author  To Quyen
 * @brief   Triển khai chi tiết logic hiển thị lịch học.
 */
#include "PrintSchedule.h"
#include <iostream>
#include <iomanip>
#include <map>
#include <algorithm>


using namespace std;


void PrintSchedule::printByTimeslot(const vector<ScheduleItem>& schedule) {
    if (schedule.empty()) {
        cout << "Lich hoc trong!\n";
        return;
    }


    // Nhóm lịch học theo Timeslot ID
    map<int, vector<ScheduleItem>> groupedSchedule;
    for (const auto& item : schedule) {
        groupedSchedule[item.timeslot.id].push_back(item);
    }


    string sep(90, '-');

    cout << "  KET QUA XEP LICH HOC CHINH THUC \n";
   
    for (const auto& pair : groupedSchedule) {
        const auto& items = pair.second;
        if (items.empty()) continue;


        const Timeslot& ts = items[0].timeslot;
       
        cout << "\n>>> " << ts.day << " - " << ts.period << " <<<\n";
        cout << sep << '\n';
        cout << left
             << setw(30) << "Ten mon hoc"
             << setw(10) << "Si so"
             << setw(15) << "Phong"
             << setw(15) << "Loai Phong"
             << "Giang vien\n";
        cout << sep << '\n';


        for (const auto& item : items) {
            cout << left
                 << setw(30) << item.subject.name
                 << setw(10) << item.subject.studentCount
                 << setw(15) << item.room.id
                 << setw(15) << item.room.roomType
                 << item.subject.teacherId << '\n';
        }
        cout << sep << '\n';
    }
    cout << "\nTong so mon da xep: " << schedule.size() << "\n\n";
}


=======
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
>>>>>>> d5d823b5aba332cec20856debecf02dab6a209a3
