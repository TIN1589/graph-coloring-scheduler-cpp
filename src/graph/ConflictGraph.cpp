/**
 * @file    ConflictGraph.cpp
 * @author  Dinh Chi
 * @brief   Trien khai chi tiet lop ConflictGraph.
 */
#include "ConflictGraph.h"


#include <algorithm>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <set>
#include <sstream>
#include <stdexcept>


//  HANG SO TRANG TRI
static const int  COL_IDX  =  4;
static const int  COL_ID   = 15;
static const int  COL_NAME = 25;
static const int  COL_GV   =  7;
static const int  COL_DEG  =  6;
static const int  SEP_LEN  = 70;


static void printLine(int len = SEP_LEN, char c = '-') {
    std::cout << std::string(len, c) << '\n';
}


static std::string conflictTypeName(ConflictType t) {
    switch (t) {
        case ConflictType::TEACHER_CONFLICT:       return "Trung giang vien";
        case ConflictType::STUDENT_GROUP_CONFLICT:  return "Trung nhom sinh vien";
        case ConflictType::BOTH:                    return "Trung ca GV lan nhom SV";
        default:                                    return "Khong xac dinh";
    }
}




//  CONSTRUCTOR


ConflictGraph::ConflictGraph(const std::vector<Subject>& subjectList) {
    if (subjectList.empty()) {
        throw std::invalid_argument(
            "[ConflictGraph] Danh sach mon hoc khong duoc de trong.");
    }


    subjects_ = subjectList;
    int n = static_cast<int>(subjects_.size());


    for (int i = 0; i < n; ++i) {
        const std::string& sid = subjects_[i].id;
        if (idToIndex_.count(sid)) {
            throw std::runtime_error(
                "[ConflictGraph] Ton tai hai mon hoc trung ma hoc phan: " + sid);
        }
        idToIndex_[sid] = i;
    }


    adjMatrix_.assign(n, std::vector<bool>(n, false));
    degree_.assign(n, 0);
}





//  XAY DUNG DO THI


void ConflictGraph::buildGraph() {
    int n = static_cast<int>(subjects_.size());


    edges_.clear();
    adjMatrix_.assign(n, std::vector<bool>(n, false));
    degree_.assign(n, 0);
    built_ = false;


    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            const Subject& si = subjects_[i];
            const Subject& sj = subjects_[j];


            bool teacherConflict = false;
            bool studentConflict = false;
            std::vector<std::string> sharedGroups;


            // HC1: Trung giang vien
            if (!si.teacherId.empty() && si.teacherId == sj.teacherId) {
                teacherConflict = true;
            }


            // HC2: Trung nhom sinh vien
            if (findStudentGroupConflicts(si, sj, sharedGroups)) {
                studentConflict = true;
            }


            if (!teacherConflict && !studentConflict) continue;


            ConflictType type;
            if      (teacherConflict && studentConflict) type = ConflictType::BOTH;
            else if (teacherConflict)                    type = ConflictType::TEACHER_CONFLICT;
            else                                         type = ConflictType::STUDENT_GROUP_CONFLICT;


            ConflictEdge edge;
            edge.u            = i;
            edge.v            = j;
            edge.type         = type;
            edge.sharedGroups = sharedGroups;
            edge.description  = buildDescription(type, si.teacherId, sharedGroups);
            edges_.push_back(std::move(edge));


            adjMatrix_[i][j] = true;
            adjMatrix_[j][i] = true;
            degree_[i]++;
            degree_[j]++;
        }
    }


    built_ = true;
    computeStats();
}





//  TRUY VAN DO THI


bool ConflictGraph::isAdjacent(int u, int v) const {
    assertBuilt("isAdjacent");
    int n = static_cast<int>(subjects_.size());
    if (u < 0 || u >= n || v < 0 || v >= n) return false;
    return adjMatrix_[u][v];
}


int ConflictGraph::getDegree(int vertexIdx) const {
    assertBuilt("getDegree");
    if (vertexIdx < 0 || vertexIdx >= static_cast<int>(degree_.size())) return -1;
    return degree_[vertexIdx];
}


int ConflictGraph::getVertexCount() const {
    return static_cast<int>(subjects_.size());
}


int ConflictGraph::getEdgeCount() const {
    assertBuilt("getEdgeCount");
    return static_cast<int>(edges_.size());
}


std::vector<int> ConflictGraph::getNeighbors(int vertexIdx) const {
    assertBuilt("getNeighbors");
    std::vector<int> neighbors;
    int n = static_cast<int>(subjects_.size());
    if (vertexIdx < 0 || vertexIdx >= n) return neighbors;
    for (int j = 0; j < n; ++j) {
        if (adjMatrix_[vertexIdx][j]) neighbors.push_back(j);
    }
    return neighbors;
}


int ConflictGraph::getIndexById(const std::string& subjectId) const {
    auto it = idToIndex_.find(subjectId);
    return (it != idToIndex_.end()) ? it->second : -1;
}


const std::vector<Subject>& ConflictGraph::getSubjects() const {
    return subjects_;
}


const std::vector<std::vector<bool>>& ConflictGraph::getAdjMatrix() const {
    assertBuilt("getAdjMatrix");
    return adjMatrix_;
}


const std::vector<ConflictEdge>& ConflictGraph::getEdges() const {
    assertBuilt("getEdges");
    return edges_;
}


const GraphStats& ConflictGraph::getStats() const {
    assertBuilt("getStats");
    return stats_;
}




//  Output


void ConflictGraph::printVertexList() const {
    assertBuilt("printVertexList");
    printLine(SEP_LEN, '=');
    std::cout << "DANH SACH DINH (MON HOC) & BAC XUNG DOT\n";
    printLine();
    std::cout << std::left
              << std::setw(COL_IDX)  << "STT"
              << std::setw(COL_ID)   << "Ma HP"
              << std::setw(COL_NAME) << "Ten mon hoc"
              << std::setw(COL_GV)   << "GV"
              << std::setw(COL_DEG)  << "Bac"
              << "Nhom SV\n";
    printLine();


    for (int i = 0; i < static_cast<int>(subjects_.size()); ++i) {
        const Subject& s = subjects_[i];
        std::string groups;
        for (size_t g = 0; g < s.studentGroups.size(); ++g) {
            if (g > 0) groups += ", ";
            groups += s.studentGroups[g];
        }
        std::cout << std::left
                  << std::setw(COL_IDX)  << i
                  << std::setw(COL_ID)   << s.id
                  << std::setw(COL_NAME) << s.name
                  << std::setw(COL_GV)   << s.teacherId
                  << std::setw(COL_DEG)  << degree_[i]
                  << groups << '\n';
    }
    printLine();
}


void ConflictGraph::printEdgeList() const {
    assertBuilt("printEdgeList");
    printLine(SEP_LEN, '=');
    std::cout << "DANH SACH CANH XUNG DOT (" << edges_.size() << " canh)\n";
    printLine();


    if (edges_.empty()) {
        std::cout << "  (Khong co xung dot nao)\n";
        printLine();
        return;
    }


    int no = 1;
    for (const auto& e : edges_) {
        const Subject& su = subjects_[e.u];
        const Subject& sv = subjects_[e.v];


        std::cout << "  [" << no++ << "] "
                  << su.name << "  <--->  " << sv.name << '\n';
        std::cout << "       Loai    : " << conflictTypeName(e.type) << '\n';
        std::cout << "       Chi tiet: " << e.description << '\n';


        if (!e.sharedGroups.empty()) {
            std::cout << "       Nhom trung:";
            for (const auto& g : e.sharedGroups) std::cout << " [" << g << "]";
            std::cout << '\n';
        }
        std::cout << '\n';
    }
    printLine();
}


void ConflictGraph::printStats() const {
    assertBuilt("printStats");
    printLine(SEP_LEN, '=');
    std::cout << "THONG KE TONG QUAN DO THI\n";
    printLine();
    std::cout << "  So dinh (mon hoc)      : " << stats_.vertexCount    << '\n';
    std::cout << "  So canh (xung dot)     : " << stats_.edgeCount      << '\n';
    std::cout << "  Bac cao nhat           : " << stats_.maxDegree      << '\n';
    std::cout << "  Bac thap nhat          : " << stats_.minDegree      << '\n';
    std::cout << "  Bac trung binh         : "
              << std::fixed << std::setprecision(2) << stats_.avgDegree << '\n';
    std::cout << "  Dinh bi lap (bac = 0)  : " << stats_.isolatedCount  << '\n';
    std::cout << '\n';
    std::cout << "  Phan loai canh:\n";
    std::cout << "    Trung giang vien       : " << stats_.teacherConflicts << '\n';
    std::cout << "    Trung nhom sinh vien   : " << stats_.studentConflicts << '\n';
    std::cout << "    Trung ca hai           : " << stats_.bothConflicts    << '\n';
    printLine();
}


void ConflictGraph::printAdjMatrix() const {
    assertBuilt("printAdjMatrix");
    int n = static_cast<int>(subjects_.size());
    std::cout << '\n';
    printLine(n * 2 + 6, '=');
    std::cout << "MA TRAN KE (1=xung dot, 0=doc lap)\n";
    printLine(n * 2 + 6);
    std::cout << "    ";
    for (int j = 0; j < n; ++j) std::cout << std::setw(2) << j;
    std::cout << '\n';
    printLine(n * 2 + 6);
    for (int i = 0; i < n; ++i) {
        std::cout << std::setw(3) << i << "|";
        for (int j = 0; j < n; ++j)
            std::cout << std::setw(2) << (adjMatrix_[i][j] ? 1 : 0);
        std::cout << "  <- " << subjects_[i].name << '\n';
    }
    printLine(n * 2 + 6, '=');
}


void ConflictGraph::printGraphInfo(bool detailed) const {
    assertBuilt("printGraphInfo");
    std::cout << '\n';
    printLine(SEP_LEN, '=');
    std::cout << "  BAO CAO DO THI XUNG DOT - PHASE 2  (Dinh Chi)\n";
    printLine(SEP_LEN, '=');
    std::cout << '\n';
    printVertexList();
    std::cout << '\n';
    printEdgeList();
    std::cout << '\n';
    printStats();
    if (detailed && static_cast<int>(subjects_.size()) <= 15) {
        printAdjMatrix();
    }
}




//  PRIVATE HELPERS



bool ConflictGraph::findStudentGroupConflicts(const Subject& s1,
                                              const Subject& s2,
                                              std::vector<std::string>& shared) const {
    shared.clear();
    if (s1.studentGroups.empty() || s2.studentGroups.empty()) return false;
    std::set<std::string> set1(s1.studentGroups.begin(), s1.studentGroups.end());
    for (const auto& g : s2.studentGroups) {
        if (set1.count(g)) shared.push_back(g);
    }
    std::sort(shared.begin(), shared.end());
    return !shared.empty();
}


void ConflictGraph::computeStats() {
    int n = static_cast<int>(subjects_.size());
    stats_.vertexCount = n;
    stats_.edgeCount   = static_cast<int>(edges_.size());
    if (n == 0) return;


    stats_.maxDegree  = *std::max_element(degree_.begin(), degree_.end());
    stats_.minDegree  = *std::min_element(degree_.begin(), degree_.end());
    double sum        = std::accumulate(degree_.begin(), degree_.end(), 0.0);
    stats_.avgDegree  = sum / n;
    stats_.isolatedCount = static_cast<int>(
        std::count(degree_.begin(), degree_.end(), 0));


    stats_.teacherConflicts = 0;
    stats_.studentConflicts = 0;
    stats_.bothConflicts    = 0;
    for (const auto& e : edges_) {
        switch (e.type) {
            case ConflictType::TEACHER_CONFLICT:       stats_.teacherConflicts++; break;
            case ConflictType::STUDENT_GROUP_CONFLICT:  stats_.studentConflicts++; break;
            case ConflictType::BOTH:                   stats_.bothConflicts++;    break;
        }
    }
}


std::string ConflictGraph::buildDescription(ConflictType type,
                                            const std::string& teacherId,
                                            const std::vector<std::string>& shared) const {
    std::ostringstream oss;
    switch (type) {
        case ConflictType::TEACHER_CONFLICT:
            oss << "Ca hai mon deu do GV '" << teacherId << "' giang day.";
            break;
        case ConflictType::STUDENT_GROUP_CONFLICT:
            oss << "Co " << shared.size() << " nhom SV hoc chung: ";
            for (size_t i = 0; i < shared.size(); ++i) {
                if (i > 0) oss << ", ";
                oss << "'" << shared[i] << "'";
            }
            oss << ".";
            break;
        case ConflictType::BOTH:
            oss << "GV '" << teacherId << "' trung va co "
                << shared.size() << " nhom SV chung: ";
            for (size_t i = 0; i < shared.size(); ++i) {
                if (i > 0) oss << ", ";
                oss << "'" << shared[i] << "'";
            }
            oss << ".";
            break;
    }
    return oss.str();
}


void ConflictGraph::assertBuilt(const std::string& callerName) const {
    if (!built_) {
        throw std::logic_error(
            "[ConflictGraph::" + callerName + "] "
            "Phai goi buildGraph() truoc khi su dung ham nay.");
    }
}



