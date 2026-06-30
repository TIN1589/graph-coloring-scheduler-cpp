/**
 * @file    WelshPowell.h
 * @author  Trung Tin
 * @brief   Khai bao thuat toan To mau Welsh-Powell.
 *
 * @details Welsh-Powell la cai tien cua Greedy:
 *          sap xep tat ca dinh theo bac GIAM DAN truoc, sau do moi to mau.
 *          Uu tien xu ly dinh co nhieu xung dot truoc giup giam so mau.
 *
 *          Cac buoc thuc hien:
 *            1. Tinh bac tung dinh (lay tu ConflictGraph::getDegree).
 *            2. Sap xep danh sach dinh theo bac giam dan.
 *            3. Lap qua tung mau:
 *               a. Chon dinh chua to co bac cao nhat -> gan mau nay.
 *               b. Lan luot quet cac dinh chua to: neu khong ke voi
 *                  bat ky dinh nao da mang mau hien tai -> gan mau.
 *            4. Tang mau, lap lai den khi tat ca dinh co mau.
 */
#ifndef WELSH_POWELL_H
#define WELSH_POWELL_H

#include "../graph/ConflictGraph.h"
#include "GreedyColoring.h"   // dung lai struct ColoringResult
#include <string>
#include <vector>

/**
 * @class WelshPowell
 * @brief To mau theo thuat toan Welsh-Powell (sap xep bac giam dan truoc).
 */
class WelshPowell {
public:
    /**
     * @brief Chay thuat toan Welsh-Powell tren do thi xung dot.
     * @param graph Do thi da goi buildGraph().
     * @return ColoringResult chua mang mau va chromatic number.
     */
    static ColoringResult run(const ConflictGraph& graph);

    /**
     * @brief In ket qua to mau ra console (nhom theo tung ca hoc).
     * @param result Ket qua tu run().
     * @param graph  Do thi de lay ten mon hoc va thong tin nhom.
     */
    static void printResult(const ColoringResult& result,
                            const ConflictGraph& graph);

    /**
     * @brief In bang so sanh ket qua Greedy va Welsh-Powell.
     * @param greedy Ket qua Greedy Coloring.
     * @param wp     Ket qua Welsh-Powell.
     */
    static void printComparison(const ColoringResult& greedy,
                                const ColoringResult& wp);
};

#endif // WELSH_POWELL_H
