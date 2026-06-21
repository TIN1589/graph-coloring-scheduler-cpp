# Graph Coloring Scheduler C++

Demo xep lich hoc bang to mau do thi, co so sanh Greedy voi Welsh-Powell, gan phong hoc that va validator kiem tra chat luong lich.

## 1. Y tuong

- Mon hoc = dinh cua do thi.
- Xung dot = canh noi giua 2 mon.
- Timeslot = mau cua dinh.
- Phong hoc = tai nguyen duoc gan sau khi da co timeslot.
- Hai mon co xung dot thi khong duoc nam trong cung mot timeslot.
- Hai mon cung timeslot thi khong duoc dung chung mot phong.

## 2. Diem moi cua ban demo

So voi demo graph coloring co ban, project nay co them:

- Gan phong hoc theo loai phong va suc chua.
- Kiem tra trung phong trong cung timeslot.
- So sanh Greedy thuong voi Welsh-Powell.
- Cham diem chat luong lich theo so loi va so timeslot su dung.
- Giai thich ly do tao canh xung dot.

## 3. Rule tao xung dot

Hai mon hoc bi xem la xung dot neu:

- Cung giang vien.
- Hoac co chung nhom sinh vien.

Sau khi to mau, chuong trinh tiep tuc gan phong hoc phu hop:

- Mon can `LAB` phai vao phong `LAB`.
- Mon can `NORMAL` phai vao phong `NORMAL`.
- Suc chua phong phai lon hon hoac bang si so mon.
- Trong cung mot timeslot, moi phong chi duoc dung cho mot mon.

## 4. Cau truc project

```text
graph-coloring-scheduler-cpp/
|-- README.md
|-- run.bat
|-- docs/
|-- src/
|   |-- main.cpp
|   |-- models/
|   |-- demo/
|   |-- graph/
|   |-- algorithm/
|   |-- scheduler/
|   |-- validator/
|   `-- output/
```

## 5. Cach chay nhanh

Yeu cau may da cai `g++` va them vao PATH.

Chay bang file batch:

Chay voi dataset cu the:


Hoac bien dich thu cong:


## 6. Luong chay cua chuong trinh

1. Load du lieu demo.
2. In danh sach mon hoc.
3. Tao do thi xung dot.
4. In danh sach canh xung dot.
5. Tinh bac tung dinh.
6. Chay Greedy va Welsh-Powell de so sanh.
7. Chuyen mau thanh timeslot.
8. Gan phong hoc phu hop.
9. In bang lich hoc.
10. Validator kiem tra lich co hop le khong.
11. Cham diem chat luong lich.

## 7. Phan cong   

| Thanh vien | Module | File chinh |
| --- | --- | --- |
| Kien Pham | Model + demo data | `ScheduleData.h`, `DemoData.cpp` |
| Dinh Chi | Conflict graph | `ConflictGraph.cpp` |
| Trung Tin | Greedy + Welsh-Powell | `GreedyColoring.cpp`, `WelshPowell.cpp` |
| To Quyen | Schedule + output | `ScheduleBuilder.cpp`, `PrintSchedule.cpp` |
| Trang Dai | Validator | `ScheduleValidator.cpp` |
| Trung Tin | Main + docs | `main.cpp`, `README.md`, `docs/` |
