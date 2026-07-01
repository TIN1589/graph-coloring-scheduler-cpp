#include <iostream>
#include <vector>
#include "demo/DemoData.h"
#include "graph/ConflictGraph.h"
<<<<<<< HEAD
#include "algorithm/GreedyColoring.h"
#include "algorithm/WelshPowell.h"
#include "scheduler/ScheduleBuilder.h"
#include "output/PrintSchedule.h"


int main() {

    std::cout << "  HE THONG XEP LICH HOC - GRAPH COLORING SCHEDULER\n";
   


    std::vector<Subject> subjects = getDemoDataByName("medium");
    std::vector<Timeslot> timeslots = createTimeslots();
    std::vector<Room> rooms = createRooms();
    
    std::cout << "-> Phase 1: Load thanh cong "
              << subjects.size() << " mon hoc, "
              << timeslots.size() << " ca hoc, "
              << rooms.size() << " phong hoc.\n";


    
    ConflictGraph graph(subjects);
    graph.buildGraph();
    std::cout << "-> Phase 2: Dung thanh cong do thi xung dot ("
              << graph.getEdgeCount() << " canh).\n";


    graph.printGraphInfo(false);  // false = khong in ma tran ke


    
    std::cout << "-> Phase 3: Chay thuat toan to mau Welsh-Powell...\n\n";


    // Chạy thuật toán Welsh-Powell (thuật toán tối ưu hơn Greedy)
    ColoringResult wpResult = WelshPowell::run(graph);
    WelshPowell::printResult(wpResult, graph);


    std::cout << "-> Phase 4: Gan phong hoc dua tren mau da to...\n";
    try {
        // Gán phòng học dựa trên kết quả tô màu của Welsh-Powell
        std::vector<ScheduleItem> finalSchedule = ScheduleBuilder::build(subjects, wpResult, timeslots, rooms);
        
        // In kết quả lịch học hoàn chỉnh ra màn hình
        PrintSchedule::printByTimeslot(finalSchedule);
    } catch (const std::exception& e) {
        std::cerr << "\n[LOI PHASE 4] " << e.what() << '\n';
    }


    return 0;
}


=======
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
>>>>>>> d5d823b5aba332cec20856debecf02dab6a209a3
