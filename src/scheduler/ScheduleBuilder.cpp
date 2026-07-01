<<<<<<< HEAD
/**
 * @file    ScheduleBuilder.cpp
 * @author  To Quyen
 * @brief   Triển khai chi tiết logic gán phòng học và ca học.
 */
#include "ScheduleBuilder.h"
#include <stdexcept>
#include <set>
#include <map>
#include <iostream>


using namespace std;


vector<ScheduleItem> ScheduleBuilder::build(
    const vector<Subject>& subjects,
    const ColoringResult& result,
    const vector<Timeslot>& timeslots,
    const vector<Room>& rooms
) {
    vector<ScheduleItem> schedule;
   
    // Kiểm tra xem số lượng màu (ca học) có vượt quá số ca học thực tế hay không
    if (result.chromaticNumber > static_cast<int>(timeslots.size())) {
        throw runtime_error("[ScheduleBuilder] Khong du timeslot de xep lich. Can: " +
                            to_string(result.chromaticNumber) + ", Co san: " +
                            to_string(timeslots.size()));
    }


    // Map lưu vết các phòng đã được sử dụng trong từng ca học
    // Key: timeslot.id, Value: set các room.id đã bị chiếm
    map<int, set<string>> usedRoomsPerTimeslot;


    for (size_t i = 0; i < subjects.size(); ++i) {
        const Subject& subject = subjects[i];
        int color = result.colors[i]; // color tương ứng với chỉ số của timeslot
       
        if (color < 0 || color >= static_cast<int>(timeslots.size())) {
             throw runtime_error("[ScheduleBuilder] Mau to loi: " + to_string(color));
        }
       
        const Timeslot& assignedTimeslot = timeslots[color];
        int tsId = assignedTimeslot.id;


        // Tìm một phòng phù hợp:
        // 1. Đúng loại phòng (roomType)
        // 2. Sức chứa >= số sinh viên
        // 3. Chưa được sử dụng trong ca học này
        bool roomFound = false;
        Room assignedRoom;


        for (const Room& room : rooms) {
            bool typeMatch = (room.roomType == subject.requiredRoomType);
            bool capacityMatch = (room.capacity >= subject.studentCount);
            bool isFree = (usedRoomsPerTimeslot[tsId].count(room.id) == 0);


            if (typeMatch && capacityMatch && isFree) {
                assignedRoom = room;
                roomFound = true;
                usedRoomsPerTimeslot[tsId].insert(room.id);
                break;
            }
        }


        if (!roomFound) {
            throw runtime_error(
                "[ScheduleBuilder] Khong tim thay phong hop le cho mon: " +
                subject.name + " (Yeu cau: " + subject.requiredRoomType +
                ", Si so: " + to_string(subject.studentCount) + ", Ca: " +
                assignedTimeslot.day + " - " + assignedTimeslot.period + ")"
            );
        }


        schedule.push_back({subject, assignedTimeslot, assignedRoom});
    }


    return schedule;
}




=======
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
>>>>>>> d5d823b5aba332cec20856debecf02dab6a209a3
