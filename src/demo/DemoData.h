/**
 * @file DemoData.h
 * @brief Khai báo module sinh dữ liệu giả lập và các API truy xuất dataset.
 */
#ifndef DEMO_DATA_H
#define DEMO_DATA_H

#include "../models/ScheduleData.h"
#include <string>
#include <vector>

using namespace std;

// Tạo tài nguyên dùng chung (Thời gian & Không gian)
vector<Timeslot> createTimeslots();
vector<Room> createRooms();

// Các hàm helper nội bộ để sinh dữ liệu
vector<Subject> createBasicDemoData();
vector<Subject> createMediumDemoData();
vector<Subject> createComplexDemoData();

// --- API CÔNG KHAI ---
// Lấy danh sách tên các bộ dữ liệu hiện có
vector<string> getAvailableDatasetNames();

// Lấy bộ dữ liệu dựa trên tên truyền vào
vector<Subject> getDemoDataByName(const string& name);

#endif // DEMO_DATA_H