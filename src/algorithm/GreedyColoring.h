/**
 * @file    GreedyColoring.h
 * @author  Trung Tin
 * @brief   Khai bao thuat toan To mau Tham lam (Greedy Coloring).
 *
 * @details Greedy to mau theo thu tu chi muc 0 -> N-1 (thu tu nap vao),
 *          khong sap xep truoc. Dung de so sanh hieu qua voi Welsh-Powell.
 *
 *          Quy tac: voi moi dinh, chon mau nho nhat chua duoc dung
 *          boi bat ky dinh ke nao.
 */
#ifndef GREEDY_COLORING_H
#define GREEDY_COLORING_H

#include "../graph/ConflictGraph.h"
#include <string>
#include <vector>

/**
 * @brief Luu tru ket qua to mau cua mot thuat toan.
 */
struct ColoringResult {
    std::vector<int> colors;   ///< colors[i] = so ca hoc cua mon i (0-indexed)
    int chromaticNumber = 0;   ///< So mau it nhat can dung
    std::string algorithmName; ///< Ten thuat toan
};

/**
 * @class GreedyColoring
 * @brief To mau Tham lam - xu ly dinh theo thu tu nap vao (0 -> N-1).
 */
class GreedyColoring {
public:
    /**
     * @brief Chay thuat toan Greedy tren do thi xung dot.
     * @param graph Do thi da goi buildGraph().
     * @return ColoringResult chua mang mau va chromatic number.
     */
    static ColoringResult run(const ConflictGraph& graph);

    /**
     * @brief In ket qua to mau ra console (dang bang theo tung mon).
     * @param result Ket qua tu run().
     * @param graph  Do thi de lay ten mon hoc.
     */
    static void printResult(const ColoringResult& result,
                            const ConflictGraph& graph);
};

#endif // GREEDY_COLORING_H
