#include <iostream>
#include <vector>
#include "demo/DemoData.h"
#include "graph/ConflictGraph.h"
#include "algorithm/WelshPowell.h"

// Tích hợp thêm các file xử lý gán phòng của Tố Quyên
#include "scheduler/ScheduleBuilder.h"
#include "output/PrintSchedule.h"

using namespace std;

int main() {
    // 1. Khởi tạo tập dữ liệu demo (Môn học, Ca học)
    vector<Subject> subjects = getDemoSubjects();
    vector<Timeslot> timeslots = getDemoTimeslots();

    // 2. Xây dựng đồ thị xung đột giữa các môn học
    ConflictGraph graph(subjects.size());
    graph.buildGraph(subjects);

    // 3. Thực hiện thuật toán tô màu đồ thị Welsh-Powell để xếp ca
    vector<int> colors = welshPowellColoring(graph, subjects);

    // =========================================================================
    // // PHẦN KHỞI CHẠY TÍCH HỢP PHASE 4 CỦA TỐ QUYÊN
    // =========================================================================
    // 1. Cấu hình tập dữ liệu phòng học mẫu bao gồm cả phòng máy thực hành và phòng lý thuyết công suất khác nhau
    std::vector<Room> testRooms = {
        {"LAB01", "LAB", 40},
        {"LAB02", "LAB", 50},
        {"PM201", "LEC", 45},
        {"PM202", "LEC", 100}
    };

    // 2. Gọi hàm thực thi xử lý ánh xạ thời gian học và khớp phòng của Tố Quyên
    auto finalSchedule = buildScheduleWithRooms(subjects, colors, timeslots, testRooms);

    // 3. Thực hiện xuất bản toàn bộ dữ liệu ra màn hình Terminal dự án
    printAllOutputs(subjects, testRooms, colors, finalSchedule);

    return 0;
}