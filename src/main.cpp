#include <iostream>
#include "demo/DemoData.h"
#include "graph/ConflictGraph.h"


int main() {
    std::cout << "KHOI DONG HE THONG KIEM THU TICH HOP PHASE 1 & 2\n\n";


    // 1. Lay du lieu demo muc do "medium" tu Phase 1
    std::vector<Subject> testSubjects = getDemoDataByName("medium");
    std::cout << "-> Phase 1: Load thanh cong " << testSubjects.size() << " mon hoc.\n";


    // 2. Khoi tao do thi va dung lien ket tu Phase 2
    ConflictGraph graph(testSubjects);
    graph.buildGraph();
    std::cout << "-> Phase 2: Dung thanh cong do thi xung dot.\n";


    // 3. In thong tin do thi de kiem tra tinh dung dan cua logic
    //    Tham so 'true' se in them ma tran ke (chi hien thi khi N <= 15)
    graph.printGraphInfo(true);


    return 0;
}



