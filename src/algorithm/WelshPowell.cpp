/**
 * @file    WelshPowell.cpp
 * @author  Trung Tin
 * @brief   Trien khai thuat toan To mau Welsh-Powell.
 */
#include "WelshPowell.h"

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <numeric>


//  THUAT TOAN WELSH-POWELL
ColoringResult WelshPowell::run(const ConflictGraph& graph) {
    int n = graph.getVertexCount();
    const auto& adj = graph.getAdjMatrix();

    ColoringResult result;
    result.algorithmName = "Welsh-Powell";
    result.colors.assign(n, -1);

    // 1. Tao danh sach dinh
    std::vector<int> vertices(n);
    std::iota(vertices.begin(), vertices.end(), 0);

    // 2. Sap xep danh sach dinh theo bac giam dan
    std::sort(vertices.begin(), vertices.end(), [&](int a, int b) {
        return graph.getDegree(a) > graph.getDegree(b);
    });

    // 3. To mau
    int currentColor = 0;
    int uncoloredCount = n;

    while (uncoloredCount > 0) {
        // a. Tim dinh chua to co bac cao nhat
        for (int i = 0; i < n; ++i) {
            int v = vertices[i];
            if (result.colors[v] == -1) {
                // Gan mau hien tai cho dinh v
                result.colors[v] = currentColor;
                uncoloredCount--;

                // b. Quet cac dinh chua to khac, neu khong ke voi bat ky dinh nao
                //    da mang mau hien tai -> gan mau
                for (int j = i + 1; j < n; ++j) {
                    int u = vertices[j];
                    if (result.colors[u] == -1) {
                        bool canColor = true;
                        // Kiem tra u co ke voi dinh nao cung mau currentColor khong
                        for (int k = 0; k < n; ++k) {
                            if (adj[u][k] && result.colors[k] == currentColor) {
                                canColor = false;
                                break;
                            }
                        }
                        if (canColor) {
                            result.colors[u] = currentColor;
                            uncoloredCount--;
                        }
                    }
                }
                // Chuyen sang mau tiep theo sau khi da to het co the
                currentColor++;
                break; // thoat khoi vong lap for (i) de bat dau lai while
            }
        }
    }

    result.chromaticNumber = currentColor; // vi currentColor bat dau tu 0 va tang len
    return result;
}


//  IN KET QUA
void WelshPowell::printResult(const ColoringResult& result,
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


//  OUTPUT SS
void WelshPowell::printComparison(const ColoringResult& greedy,
                                  const ColoringResult& wp) {
    std::string sep(50, '-');
    std::cout << std::string(50, '=') << '\n';
    std::cout << "  SO SANH HIEU QUA THUAT TOAN TONG QUAT\n";
    std::cout << sep << '\n';
    std::cout << std::left 
              << std::setw(25) << "Thuat toan" 
              << "So ca hoc (Chromatic Num)\n";
    std::cout << sep << '\n';
    
    std::cout << std::left 
              << std::setw(25) << greedy.algorithmName 
              << greedy.chromaticNumber << '\n';
              
    std::cout << std::left 
              << std::setw(25) << wp.algorithmName 
              << wp.chromaticNumber << '\n';
    std::cout << std::string(50, '=') << "\n\n";
}
