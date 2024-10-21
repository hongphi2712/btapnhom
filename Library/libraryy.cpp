#include <iostream>
#include <string>
#include <fstream>  // Thu vien de lam viec voi file
using namespace std;

class BOOK
{
protected:
    string idsach;
    string tensach;
    string tacgia;
    int namxuatban;

public:
    void nhap() {
        cout << "Nhap ID sach: "; cin >> idsach;
        cout << "Nhap ten sach: "; cin.ignore(); getline(cin, tensach);
        cout << "Nhap ten tac gia: "; getline(cin, tacgia);
        cout << "Nhap nam xuat ban: "; cin >> namxuatban;
    }

    void xuat() {
        cout << "ID sach: " << idsach << endl;
        cout << "Ten sach: " << tensach << endl;
        cout << "Tac gia: " << tacgia << endl;
        cout << "Nam xuat ban: " << namxuatban << endl;
    }

    void ghivaofile(ofstream &outFile) {
        outFile << idsach << endl;
        outFile << tensach << endl;
        outFile << tacgia << endl;
        outFile << namxuatban << endl;
    }

    void docfile(ifstream &inFile) {
        getline(inFile, idsach);
        getline(inFile, tensach);
        getline(inFile, tacgia);
        inFile >> namxuatban;
    }

    string getID() { return idsach; }
};

// Lop KhachHang - quan ly thong tin khach hang
class KhachHang
{
protected:
    static int idkhachhang;
    string name;
    string ngaysinh;
    string email;
    string sdt;

public:
    KhachHang() {
        idkhachhang++;
    }

    void nhap() {
        cout << "Nhap ten khach hang: "; cin.ignore(); getline(cin, name);
        cout << "Nhap ngay sinh: "; getline(cin, ngaysinh);
        cout << "Nhap email: "; getline(cin, email);
        cout << "Nhap so dien thoai: "; getline(cin, sdt);
    }

    void xuat() {
        cout << "ID khach hang: " << idkhachhang << endl;
        cout << "Ten khach hang: " << name << endl;
        cout << "Ngay sinh: " << ngaysinh << endl;
        cout << "Email: " << email << endl;
        cout << "So dien thoai: " << sdt << endl;
    }
    
    void ghivaofile(ofstream &outFile) {
        outFile << idkhachhang << endl;
        outFile << name << endl;
        outFile << ngaysinh << endl;
        outFile << email << endl;
        outFile << sdt << endl;
    }
    
    void docfile(ifstream &inFile) {
        inFile >> idkhachhang;  // Doc ID khach hang
        inFile.ignore();         // Bo qua ky tu newline
        getline(inFile, name);   // Doc ten
        getline(inFile, ngaysinh); // Doc ngay sinh
        getline(inFile, email);   // Doc email
        getline(inFile, sdt);     // Doc so dien thoai
    }

    int getID() { return idkhachhang; }
};

class Muontra : public BOOK, public KhachHang
{
protected:
    string idmuontra;
    string ngaymuon;
    string ngaytra;
    KhachHang nguoiMuon;  // Su dung doi tuong KhachHang

public:
    void nhap() {
        cout << "Nhap ID muon tra: "; cin >> idmuontra;
        cout << "Nhap thong tin nguoi muon:" << endl;
        nguoiMuon.nhap();  // Nhap thong tin nguoi muon
        cout << "Nhap ngay muon (dd/mm/yyyy): "; cin >> ngaymuon;
        cout << "Nhap ngay tra (dd/mm/yyyy): "; cin >> ngaytra;
    }

    void xuat() {
        cout << "ID muon tra: " << idmuontra << endl;
        cout << "Thong tin nguoi muon:" << endl;
        nguoiMuon.xuat();  // Xuat thong tin nguoi muon
        cout << "Ngay muon: " << ngaymuon << endl;
        cout << "Ngay tra: " << ngaytra << endl;
    }

    void ghivaofile(ofstream &outFile) {
        outFile << idmuontra << endl;
        nguoiMuon.ghivaofile(outFile);  // Ghi thong tin nguoi muon
        outFile << ngaymuon << endl;
        outFile << ngaytra << endl;
    }

    void docfile(ifstream &inFile) {
        getline(inFile, idmuontra);
        nguoiMuon.docfile(inFile);  // Doc thong tin nguoi muon
        getline(inFile, ngaymuon);
        getline(inFile, ngaytra);
    }

    string getID() { return idmuontra; }
};

int KhachHang::idkhachhang = 0;

int main()
{
    setlocale(LC_ALL, "");
    cout << "Chuong trinh quan ly thu vien" << endl;
    cout << "1.Ban la nguoi quan ly" << endl;
    cout << "2.Ban la nguoi doc" << endl;
    cout << "3.Thoat" << endl;
    int n;
    cout << "Nhap lua chon cua ban: ";
    cin >> n;

    switch (n)
    {
        case 1:
            cout << "Chuc nang cua nguoi quan ly" << endl;
            cout << "1.Them sach" << endl;
            cout << "2.Xoa sach" << endl;
            cout << "3.Sua sach" << endl;
            cout << "4.Them khach hang" << endl;
            cout << "5.Xoa khach hang" << endl;
            cout << "6.Them muon tra" << endl;
            cout << "10.Thoat" << endl;
            int m;
            cout << "Nhap lua chon cua ban: ";
            cin >> m;
            switch (m)
            {
                case 1: {
                    BOOK newBook;
                    newBook.nhap();
                    
                    newBook.xuat();

                    ofstream outFile("database.txt", ios::app);
                    if (!outFile) {
                        cerr << "Khong mo duoc file!" << endl;
                        return 1;
                    }

                    newBook.ghivaofile(outFile);
                    outFile.close();
                    cout << "Sach da duoc them vao file database.txt!" << endl;
                    break;
                }
                case 4: {
                    KhachHang newCustomer;
                    newCustomer.nhap();

                    ofstream outFile("customers.txt", ios::app);
                    if (!outFile) {
                        cerr << "Khong mo duoc file!" << endl;
                        return 1;
                    }

                    newCustomer.ghivaofile(outFile);
                    outFile.close();
                    cout << "Khach hang da duoc them vao file customers.txt!" << endl;
                    break;
                }
                case 6: {
                    Muontra newLoan;
                    newLoan.nhap();

                    ofstream outFile("loans.txt", ios::app);
                    if (!outFile) {
                        cerr << "Khong mo duoc file!" << endl;
                        return 1;
                    }

                    newLoan.ghivaofile(outFile);
                    outFile.close();
                    cout << "Thong tin muon tra da duoc them vao file loans.txt!" << endl;
                    break;
                }
                case 10:
                    cout << "Thoat" << endl;
                    break;
                default:
                    cout << "Khong co lua chon cua ban" << endl;
                    break;
            }
            break;
        case 2:
            cout << "Chuc nang cua nguoi doc" << endl;
            cout << "1.Muon sach" << endl;
            cout << "2.Tra sach" << endl;
            cout << "3.Thoat" << endl;
            break;
    }
    return 0;
}
