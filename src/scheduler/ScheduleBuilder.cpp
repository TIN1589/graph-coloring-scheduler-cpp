#include "ScheduleBuilder.h"
#include <map>
#include <string>

std::vector<FinalScheduleItem> buildScheduleWithRooms(
    const std::vector<Subject>& subjects,
    const std::vector<int>& colors,
    const std::vector<Timeslot>& timeslots,
    std::vector<Room>& rooms
) {
    std::vector<FinalScheduleItem> schedule;
    std::map<std::string, bool> roomSlotOccupied;

    for (size_t i = 0; i < subjects.size(); ++i) {
        FinalScheduleItem item;
        item.subject = subjects[i];

        size_t colorId = static_cast<size_t>(colors[i]);
        if (colorId < timeslots.size()) {
            item.slot = timeslots[colorId];
        } else {
            item.slot = { "TS_UNKNOWN", "Chua xep ca", "N/A" };
        }

        Room assignedRoom = { "Chua gan", "N/A", 0 };
        for (const auto& r : rooms) {
            if (r.type != item.subject.requiredRoomType) continue;
            if (r.capacity < item.subject.studentCount) continue;

            std::string key = r.id + "_" + item.slot.id;
            if (roomSlotOccupied[key]) continue;

            roomSlotOccupied[key] = true;
            assignedRoom = r;
            break;
        }

        item.room = assignedRoom;
        schedule.push_back(item);
    }
    return schedule;
}