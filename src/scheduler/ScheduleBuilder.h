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