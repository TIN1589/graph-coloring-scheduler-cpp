/**
 * @file    ConflictGraph.h
 * @author  Dinh Chi
 * @brief   Khai bao lop ConflictGraph - Mo hinh hoa do thi xung dot cho
 *          bai toan xep lich hoc bang phuong phap To mau do thi.
 */
#ifndef CONFLICT_GRAPH_H
#define CONFLICT_GRAPH_H


#include "../models/ScheduleData.h"
#include <string>
#include <vector>
#include <map>
#include <set>


// ============================================================
//  CAU TRUC PHU TRO
// ============================================================


/**
 * @brief Loai xung dot giua hai mon hoc.
 */
enum class ConflictType {
    TEACHER_CONFLICT,        ///< Trung giang vien: HC1
    STUDENT_GROUP_CONFLICT,  ///< Trung nhom sinh vien: HC2
    BOTH                     ///< Vi pham ca hai rang buoc dong thoi
};


/**
 * @brief Dai dien cho mot canh xung dot trong do thi.
 */
struct ConflictEdge {
    int u;                                 ///< Chi muc dinh u
    int v;                                 ///< Chi muc dinh v
    ConflictType type;                     ///< Phan loai xung dot
    std::string description;               ///< Mo ta nguyen nhan cu the
    std::vector<std::string> sharedGroups; ///< Cac nhom SV bi trung (neu co)
};


/**
 * @brief Thong ke tong quan ve do thi xung dot.
 */
struct GraphStats {
    int vertexCount      = 0;
    int edgeCount        = 0;
    int maxDegree        = 0;
    int minDegree        = 0;
    double avgDegree     = 0;
    int isolatedCount    = 0;
    int teacherConflicts = 0;
    int studentConflicts = 0;
    int bothConflicts    = 0;
};




// ============================================================
//  LOP CONFLICT GRAPH
// ============================================================


class ConflictGraph {
public:
    // Khoi tao do thi voi danh sach mon hoc dau vao
    explicit ConflictGraph(const std::vector<Subject>& subjectList);


    // Xay dung ma tran ke va danh sach canh dua tren cac luat xung dot
    void buildGraph();


    // Kiem tra hai dinh co ke nhau (xung dot) hay khong
    bool isAdjacent(int u, int v) const;


    // Tra ve bac cua mot dinh (-1 neu chi muc khong hop le)
    int getDegree(int vertexIdx) const;


    // So dinh trong do thi
    int getVertexCount() const;


    // So canh xung dot sau buildGraph()
    int getEdgeCount() const;


    // Tra ve danh sach chi muc dinh ke voi dinh cho truoc
    std::vector<int> getNeighbors(int vertexIdx) const;


    // Tra ve chi muc cua mon hoc theo Ma hoc phan (-1 neu khong tim thay)
    int getIndexById(const std::string& subjectId) const;


    // Tra ve danh sach mon hoc (cac dinh)
    const std::vector<Subject>& getSubjects() const;


    // Tra ve ma tran ke NxN (phuc vu Welsh-Powell Phase 3)
    const std::vector<std::vector<bool>>& getAdjMatrix() const;


    // Tra ve danh sach tat ca canh xung dot
    const std::vector<ConflictEdge>& getEdges() const;


    // Tra ve thong ke tong quat
    const GraphStats& getStats() const;


    // In bao cao day du ra console
    void printGraphInfo(bool detailed = false) const;
    void printVertexList() const;
    void printEdgeList() const;
    void printStats() const;
    void printAdjMatrix() const;


private:
    std::vector<Subject>           subjects_;
    std::map<std::string, int>     idToIndex_;
    std::vector<std::vector<bool>> adjMatrix_;
    std::vector<ConflictEdge>      edges_;
    std::vector<int>               degree_;
    GraphStats                     stats_;
    bool                           built_ = false;


    bool findStudentGroupConflicts(const Subject& s1,
                                   const Subject& s2,
                                   std::vector<std::string>& shared) const;
    void computeStats();
    std::string buildDescription(ConflictType type,
                                 const std::string& teacherId,
                                 const std::vector<std::string>& shared) const;
    void assertBuilt(const std::string& callerName) const;
};


#endif // CONFLICT_GRAPH_H



