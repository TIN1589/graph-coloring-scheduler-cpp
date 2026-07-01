<<<<<<< HEAD
/**
 * @file    ScheduleBuilder.h
 * @author  To Quyen
 * @brief   Khai bao module gán phòng học và ca học cho các môn dựa trên kết quả tô màu.
 */
#ifndef SCHEDULE_BUILDER_H
#define SCHEDULE_BUILDER_H


#include "../models/ScheduleData.h"
#include "../algorithm/GreedyColoring.h"
#include <vector>
#include <string>


/**
 * @class ScheduleBuilder
 * @brief Xây dựng lịch học hoàn chỉnh từ kết quả thuật toán tô màu đồ thị.
 */
class ScheduleBuilder {
public:
    /**
     * @brief Xây dựng lịch học từ kết quả tô màu.
     *
     * @param subjects Danh sách các môn học.
     * @param result Kết quả tô màu (màu = ca học).
     * @param timeslots Danh sách các ca học có sẵn.
     * @param rooms Danh sách các phòng học có sẵn.
     * @return vector<ScheduleItem> Danh sách các mục lịch học đã được gán đầy đủ.
     * @throws runtime_error Nếu không tìm được phòng học phù hợp hoặc thiếu timeslot.
     */
    static std::vector<ScheduleItem> build(
        const std::vector<Subject>& subjects,
        const ColoringResult& result,
        const std::vector<Timeslot>& timeslots,
        const std::vector<Room>& rooms
    );
};


#endif // SCHEDULE_BUILDER_H




=======
#ifndef SCHEDULE_BUILDER_H
#define SCHEDULE_BUILDER_H

#include <vector>
#include <string>

// Gọi đúng file duy nhất chứa cấu trúc dữ liệu
#include "../models/ScheduleData.h"

struct FinalScheduleItem {
    Subject subject;
    Timeslot slot;
    Room room;
};

std::vector<FinalScheduleItem> buildScheduleWithRooms(
    const std::vector<Subject>& subjects,
    const std::vector<int>& colors,
    const std::vector<Timeslot>& timeslots,
    std::vector<Room>& rooms
);

#endif // SCHEDULE_BUILDER_H
>>>>>>> d5d823b5aba332cec20856debecf02dab6a209a3
