#ifndef DEMO_DATA_H
#define DEMO_DATA_H

#include "../models/ScheduleData.h"

// Hàm tạo tài nguyên dùng chung
vector<Timeslot> createTimeslots();
vector<Room> createRooms();

// Các bộ dataset để kiểm thử từ dễ đến khó
vector<Subject> createBasicDemoData();
vector<Subject> createMediumDemoData();
vector<Subject> createComplexDemoData();

#endif // DEMO_DATA_H