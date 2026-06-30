/**
 * @file    GreedyColoring.cpp
 * @author  Trung Tin
 * @brief   Trien khai thuat toan To mau Tham lam.
 */
#include "GreedyColoring.h"

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <set>


//  THUAT TOAN GREEDY
ColoringResult GreedyColoring::run(const ConflictGraph& graph) {
    int n = graph.getVertexCount();
    const auto& adj = graph.getAdjMatrix();

    ColoringResult result;
    result.algorithmName = "Greedy Coloring";
    result.colors.assign(n, -1);

    for (int i = 0; i < n; ++i) {
        // Thu thap mau cua cac dinh ke da to
        std::set<int> usedColors;
        for (int j = 0; j < n; ++j) {
            if (adj[i][j] && result.colors[j] != -1)
                usedColors.insert(result.colors[j]);
        }

        // Chon mau nho nhat chua bi dung
        int color = 0;
        while (usedColors.count(color)) color++;
        result.colors[i] = color;
    }

    result.chromaticNumber =
        *std::max_element(result.colors.begin(), result.colors.end()) + 1;
    return result;
}


// OUTPUT (STT | Ten mon | Ca hoc | GV)
void GreedyColoring::printResult(const ColoringResult& result,
                                  const ConflictGraph& graph) {
    const auto& subjects = graph.getSubjects();
    int n = static_cast<int>(subjects.size());
    std::string sep(62, '-');

    std::cout << std::string(62, '=') << '\n';
    std::cout << "  KET QUA: " << result.algorithmName << '\n';
    std::cout << sep << '\n';
    std::cout << std::left
              << std::setw(4)  << "STT"
              << std::setw(16) << "Ma HP"
              << std::setw(26) << "Ten mon hoc"
              << std::setw(10) << "Ca hoc"
              << "Giang vien\n";
    std::cout << sep << '\n';

    for (int i = 0; i < n; ++i) {
        std::cout << std::left
                  << std::setw(4)  << i
                  << std::setw(16) << subjects[i].id
                  << std::setw(26) << subjects[i].name
                  << std::setw(10) << ("Ca " + std::to_string(result.colors[i] + 1))
                  << subjects[i].teacherId << '\n';
    }

    std::cout << sep << '\n';
    std::cout << "  So ca hoc can dung (Chromatic Number): "
              << result.chromaticNumber << '\n';
    std::cout << std::string(62, '=') << "\n\n";
}
