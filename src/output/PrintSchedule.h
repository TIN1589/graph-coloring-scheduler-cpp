<<<<<<< HEAD
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




=======
#ifndef PRINT_SCHEDULE_H
#define PRINT_SCHEDULE_H

#include <vector>
#include "../scheduler/ScheduleBuilder.h"
#include "../models/ScheduleData.h"

void printAllOutputs(
    const std::vector<Subject>& subjects,
    const std::vector<Room>& rooms,
    const std::vector<int>& colors,
    const std::vector<FinalScheduleItem>& finalSchedule
);

#endif // PRINT_SCHEDULE_H
>>>>>>> d5d823b5aba332cec20856debecf02dab6a209a3
