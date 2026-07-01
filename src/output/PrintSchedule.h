/**
 * @file    PrintSchedule.h
 * @author  To Quyen
 * @brief   Khai báo module xuất kết quả lịch học ra màn hình.
 */
#ifndef PRINT_SCHEDULE_H
#define PRINT_SCHEDULE_H


#include "../models/ScheduleData.h"
#include <vector>


/**
 * @class PrintSchedule
 * @brief Hỗ trợ hiển thị lịch học theo các format khác nhau.
 */
class PrintSchedule {
public:
    /**
     * @brief In danh sách lịch học (nhóm theo ca học).
     * @param schedule Danh sách các mục lịch học đã được gán.
     */
    static void printByTimeslot(const std::vector<ScheduleItem>& schedule);
};


#endif // PRINT_SCHEDULE_H




