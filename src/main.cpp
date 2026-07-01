#include <iostream>
#include <vector>



#include "demo/DemoData.h"
#include "graph/ConflictGraph.h"
#include "algorithm/GreedyColoring.h"
#include "algorithm/WelshPowell.h"


#include "scheduler/ScheduleBuilder.h"
#include "output/PrintSchedule.h"


int main() {
    std::cout << "============================================================\n";
    std::cout << "  HE THONG XEP LICH HOC - GRAPH COLORING SCHEDULER\n";
    std::cout << "============================================================\n\n";


    
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



