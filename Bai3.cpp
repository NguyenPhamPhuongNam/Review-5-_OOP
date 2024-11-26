#include <iostream>
#include <vector>
#include <string>
using namespace std;

class SanPham {
protected:
    string maSP;
    string tieuDe;
    double giaBan;
public:
    SanPham(string ma, string tieu, double gia) : maSP(ma), tieuDe(tieu), giaBan(gia) {}
    virtual void xuatThongTin() const = 0; 
    double getGiaBan() const { return giaBan; }
};

class TranhAnh : public SanPham {
private:
    int chieuRong;
    int chieuCao;
    string hoaSi;
public:
    TranhAnh(string ma, string tieu, double gia, int rong, int cao, string hoaSi) 
        : SanPham(ma, tieu, gia), chieuRong(rong), chieuCao(cao), hoaSi(hoaSi) {}
    
    void xuatThongTin() const override {
        cout << "Tranh Anh: " << tieuDe << ", Gia: " << giaBan << ", Hoasi: " << hoaSi
             << ", Kich thuoc: " << chieuRong << "x" << chieuCao << endl;
    }
};

class CD : public SanPham {
private:
    string caSi;
    string donVi;
public:
    CD(string ma, string tieu, double gia, string caSi, string donVi) 
        : SanPham(ma, tieu, gia), caSi(caSi), donVi(donVi) {}

    void xuatThongTin() const override {
        cout << "CD: " << tieuDe << ", Gia: " << giaBan << ", Casi: " << caSi 
             << ", Don vi: " << donVi << endl;
    }
};

class KhachHang {
public:
    string maKH;
    string tenKH;
    string soDienThoai;
};

class HoaDon {
private:
    string maHD;
    string ngayLap;
    KhachHang khachHang;
    vector<SanPham*> danhSachSP;
    double tongGia;
public:
    HoaDon() : tongGia(0) {}
    
    void nhapHoaDon() {
        cout << "Nhap ma hoa don: ";
        cin >> maHD;
        cout << "Nhap ngay lap hoa don: ";
        cin >> ngayLap;
        cout << "Nhap ma khach hang: ";
        cin >> khachHang.maKH;
        cout << "Nhap ten khach hang: ";
        cin.ignore(); 
        getline(cin, khachHang.tenKH);
        cout << "Nhap so dien thoai khach hang: ";
        cin >> khachHang.soDienThoai;

        int n;
        cout << "Nhap so luong san pham: ";
        cin >> n;

        for (int i = 0; i < n; ++i) {
            int loai;
            while (true) {
                cout << "Chon loai san pham (1. Tranh Anh, 2. CD): ";
                cin >> loai;

                if (loai == 1) {
                    string ma, tieu, hoaSi;
                    double gia;
                    int rong, cao;
                    cout << "Nhap ma so, tieu de, gia ban, chieu rong, chieu cao, ten hoa si: ";
                    cin >> ma >> tieu >> gia >> rong >> cao >> hoaSi;
                    danhSachSP.push_back(new TranhAnh(ma, tieu, gia, rong, cao, hoaSi));
                    break;
                } else if (loai == 2) {
                    string ma, tieu, caSi, donVi;
                    double gia;
                    cout << "Nhap ma so, tieu de, gia ban, ten ca si, don vi san xuat: ";
                    cin >> ma >> tieu >> gia >> caSi >> donVi;
                    danhSachSP.push_back(new CD(ma, tieu, gia, caSi, donVi));
                    break;
                } else {
                    cout << "Lua chon sai! Vui long chon lai." << endl;
                }
            }
        }
        tinhTongGia();
    }

    void tinhTongGia() {
        tongGia = 0;
        for (const auto& sp : danhSachSP) {
            tongGia += sp->getGiaBan();
        }
    }

    void xuatHoaDon() const {
        cout << "Ma hoa don: " << maHD << ", Ngay lap: " << ngayLap << endl;
        cout << "Khach hang: " << khachHang.tenKH << " (" << khachHang.soDienThoai << ")" << endl;
        cout << "Danh sach san pham:\n";
        for (const auto& sp : danhSachSP) {
            sp->xuatThongTin();
        }
        cout << "Tong gia: " << tongGia << endl;
    }

    double getTongGia() const { return tongGia; }
    string getMaKH() const { return khachHang.maKH; }
};

class CuaHang {
private:
    vector<HoaDon> danhSachHoaDon;
public:
    void nhapDanhSachHD() {
        int n;
        cout << "Nhap so hoa don: ";
        cin >> n;

        for (int i = 0; i < n; ++i) {
            HoaDon hd;
            hd.nhapHoaDon();
            danhSachHoaDon.push_back(hd);
        }
    }

    void xuatDanhSachHD() {
        for (const auto& hd : danhSachHoaDon) {
            hd.xuatHoaDon();
            cout << endl;
        }
    }

    double tinhTongThuNhap() {
        double tongThuNhap = 0;
        for (const auto& hd : danhSachHoaDon) {
            tongThuNhap += hd.getTongGia();
        }
        return tongThuNhap;
    }

    void timKhachHangMuaNhieuNhat() {
        string maKHMax;
        double maxTongGia = 0;
        for (const auto& hd : danhSachHoaDon) {
            double tongGia = hd.getTongGia();
            if (tongGia > maxTongGia) {
                maxTongGia = tongGia;
                maKHMax = hd.getMaKH();
            }
        }

        cout << "Khach hang mua nhieu nhat: " << maKHMax << ", Tong gia: " << maxTongGia << endl;
    }
};

int main() {
    CuaHang cuaHang;

    cuaHang.nhapDanhSachHD();
    cuaHang.xuatDanhSachHD();


    cout << "Tong thu nhap cua cua hang: " << cuaHang.tinhTongThuNhap() << endl;


    cuaHang.timKhachHangMuaNhieuNhat();

    return 0;
}

