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


