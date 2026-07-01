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