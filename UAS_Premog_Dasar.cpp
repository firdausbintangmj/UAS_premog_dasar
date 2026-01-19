#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <iomanip>
#include <cstdio> // Penting agar sscanf tidak eror

using namespace std;

// Spesifikasi: Function return untuk menghitung rata-rata
double hitungRataRata(int n1, int n2, int n3) {
    return (n1 + n2 + n3) / 3.0;
}

// Spesifikasi: Function void untuk menampilkan daftar siswa
void tampilkanData(const vector<string>& nama, const vector<string>& nim, int nilai[][3], int jml) {
    cout << "\n--- DAFTAR SISWA ---" << endl;
    cout << "-----------------------------------------------------------------------" << endl;
    cout << left << setw(15) << "Nama" << setw(15) << "NIM"
        << setw(10) << "Nilai 1" << setw(10) << "Nilai 2" << setw(10) << "Nilai 3"
        << setw(10) << "Rata-rata" << endl;
    cout << "-----------------------------------------------------------------------" << endl;

    for (int i = 0; i < jml; i++) {
        cout << left << setw(15) << nama[i]
            << setw(15) << nim[i]
            << setw(10) << nilai[i][0]
            << setw(10) << nilai[i][1]
            << setw(10) << nilai[i][2]
            << fixed << setprecision(2) << hitungRataRata(nilai[i][0], nilai[i][1], nilai[i][2]) << endl;
    }
    cout << "-----------------------------------------------------------------------" << endl;
}

int main() {
    // Spesifikasi: Vector untuk nama dan Array 2D untuk nilai
    vector<string> namaSiswa;
    vector<string> nimSiswa;
    int nilaiSiswa[100][3];
    int jumlahSiswa = 0;
    int pilihan;

    do {
        cout << "\n=== SISTEM MANAJEMEN NILAI SISWA ===" << endl;
        cout << "1. Input Data Siswa" << endl;
        cout << "2. Tampilkan Data Siswa" << endl;
        cout << "3. Simpan Data ke File" << endl;
        cout << "4. Baca Data dari File" << endl;
        cout << "5. Keluar" << endl;
        cout << "Pilihan: ";
        cin >> pilihan;

        if (pilihan == 1) {
            string nm, ni;
            cout << "\n--- Input Data Siswa ---" << endl;
            cout << "Nama: "; cin.ignore(); getline(cin, nm);
            cout << "NIM: "; cin >> ni;

            namaSiswa.push_back(nm);
            nimSiswa.push_back(ni);

            cout << "Masukkan 3 nilai mata pelajaran:" << endl;
            for (int i = 0; i < 3; i++) {
                cout << "Nilai " << i + 1 << ": ";
                cin >> nilaiSiswa[jumlahSiswa][i];
            }
            jumlahSiswa++;
            cout << "Data berhasil ditambahkan!" << endl;

        }
        else if (pilihan == 2) {
            if (jumlahSiswa == 0) cout << "Data belum ada!" << endl;
            else tampilkanData(namaSiswa, nimSiswa, nilaiSiswa, jumlahSiswa);

        }
        else if (pilihan == 3) {
            // Contoh format: Nama: Andi;NIM: 12345;Nilai: 85,78,92
            ofstream fOut("data_siswa.txt");
            fOut << "Jumlah Siswa: " << jumlahSiswa << endl;
            for (int i = 0; i < jumlahSiswa; i++) {
                fOut << "Nama: " << namaSiswa[i] << ";NIM: " << nimSiswa[i]
                    << ";Nilai: " << nilaiSiswa[i][0] << "," << nilaiSiswa[i][1] << "," << nilaiSiswa[i][2] << endl;
            }
            fOut.close();
            cout << "Data berhasil disimpan ke data_siswa.txt" << endl;

        }
        else if (pilihan == 4) {
            ifstream fIn("data_siswa.txt");
            if (!fIn) {
                cout << "File tidak ditemukan!" << endl;
                continue;
            }
            namaSiswa.clear(); nimSiswa.clear();
            string line;
            getline(fIn, line); // Membaca baris "Jumlah Siswa"

            int c = 0;
            while (getline(fIn, line)) {
                size_t pN = line.find("Nama: ") + 6;
                size_t pM = line.find(";NIM: ");
                size_t pL = line.find(";Nilai: ");

                namaSiswa.push_back(line.substr(pN, pM - pN));
                nimSiswa.push_back(line.substr(pM + 6, pL - (pM + 6)));

                string sN = line.substr(pL + 8);
                sscanf(sN.c_str(), "%d,%d,%d", &nilaiSiswa[c][0], &nilaiSiswa[c][1], &nilaiSiswa[c][2]);
                c++;
            }
            jumlahSiswa = c;
            fIn.close();
            cout << "Data berhasil dibaca dari file. Jumlah siswa: " << jumlahSiswa << endl;
        }
    } while (pilihan != 5);

    return 0;
}