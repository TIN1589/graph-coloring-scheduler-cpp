# 03 - Thuat toan Welsh-Powell

## Welsh-Powell la gi?

Welsh-Powell la mot thuat toan tham lam dung de to mau do thi.

Trong project, nhom con cai dat Greedy Coloring co ban de so sanh. Greedy thuong to mau theo thu tu input, con Welsh-Powell sap xep dinh theo bac giam dan truoc khi to mau.

## Y tuong

Thuat toan uu tien cac dinh co bac cao truoc. Bac cua dinh la so canh noi voi dinh do.

Dinh co bac cao la dinh co nhieu xung dot, nen neu xu ly som thi giam rui ro bi ket mau ve sau.

## Cac buoc

1. Tinh bac cua tung dinh.
2. Sap xep dinh theo bac giam dan.
3. Chon mau dau tien cho dinh chua to mau co bac cao nhat.
4. Dung cung mau do cho cac dinh khac neu khong ke voi dinh da co mau do.
5. Lap lai voi mau moi den khi tat ca dinh da co mau.

## Pseudocode

```text
Tinh bac moi dinh
Sap xep dinh theo bac giam dan
color = 0

Trong khi con dinh chua to mau:
    chon dinh chua to mau dau tien trong danh sach
    to mau color cho dinh do

    voi moi dinh chua to mau khac:
        neu dinh do khong ke voi dinh nao da mang mau color:
            to mau color cho dinh do

    color = color + 1
```

## Do phuc tap

Voi cach luu bang ma tran ke, viec kiem tra xung dot giua cac dinh rat truc tiep. Ban demo uu tien de doc, de giai thich hon la toi uu hoa hieu nang.

## Han che

Welsh-Powell khong dam bao luon dung so mau toi uu. No la thuat toan tham lam nen ket qua co the phu thuoc vao thu tu sap xep va cau truc do thi.

