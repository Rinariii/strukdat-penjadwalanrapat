#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include "stack.h" 
#include "queue.h"
using namespace std;

void loginAsHR();
void loginAsStaff();
void hrDashboard();
void staffDashboard();
void addNewMeeting();
void lihatmeeting();
void urutkanrapat();
void undo();
void hadir();
void daftarhadir();
void linkrapat();
void addStaff();
void viewStaff();
void updateMeeting();
void requestMeeting(); 
void viewMeetingRequests();
void viewRequestStatus();

class rapat {
public:
    string meetingName;
    string meetingDate;
    string startTime;
    string endTime;
    string meetingLocation;

    rapat(string name, string date, string start, string end, string location)
        : meetingName(name), meetingDate(date), startTime(start), endTime(end), meetingLocation(location) {}

    void displayMeeting() const {
        cout << "| " << left << setw(23) << meetingName
             << "| " << setw(13) << meetingDate
             << "| " << setw(13) << (startTime + " - " + endTime)
             << "| " << setw(18) << meetingLocation << "|\n";
        cout << "------------------------------------------------------------------------\n";
    }

    string ambilTanggal() const {
        return meetingDate;
    }
};

class PermintaanRapat {
public:
    string requesterName;
    string meetingName;
    string meetingDate;
    string startTime;
    string endTime;
    string meetingLocation;
    string status;

    PermintaanRapat(string reqName, string name, string date, string start, string end, string location)
        : requesterName(reqName), meetingName(name), meetingDate(date), startTime(start), endTime(end), meetingLocation(location), status("Pending") {}

    void displayRequest() const {
        cout << "| " << left << setw(15) << requesterName
             << "| " << setw(20) << meetingName
             << "| " << setw(10) << meetingDate
             << "| " << setw(10) << (startTime + "-" + endTime)
             << "| " << setw(15) << meetingLocation
             << "| " << setw(10) << status << "|\n";
        cout << "-------------------------------------------------------------------------------------------------------\n";
    }
};


bool sortingmeeting(const rapat &m1, const rapat &m2) {
    return m1.ambilTanggal() > m2.ambilTanggal();
}

vector<rapat> Rapat;
Stack<vector<rapat>> undoStack;
Queue<PermintaanRapat> meetingRequestsQueue;
vector<PermintaanRapat> allMeetingRequests;


int main() {
    int choice;
    do {
        cout << "Selamat Datang di Sistem Penjadwalan Rapat:\n";
        cout << "1. HR LOGIN" << endl;
        cout << "2. STAFF LOGIN" << endl;
        cout << "3. EXIT" << endl;
        cout << "\nEnter your choice: ";
        cin >> choice;
        cout << endl;

        switch (choice) {
            case 1:
                loginAsHR();
                break;
            case 2:
                loginAsStaff();
                break;
            case 3:
                cout << "Terimakasih telah menggunakan program penjadwalan rapat kami.\n";
                break;
            default:
                cout << "Pilihan tidak ditemukan\n" << endl;
        }
    } while (choice != 3);

    return 0;
}

void loginAsHR() {
    string inputUser, inputPass;
    string fileUser, filePass;
    bool found = false;

    system("cls");
    cout << "Masukan data dibawah ini" << endl;
    cout << "USERNAME: ";
    cin >> inputUser;
    cout << "PASSWORD: ";
    cin >> inputPass;

    ifstream inputFile("data_pengguna.txt");
    if (!inputFile.is_open()) {
        cout << "Error: data_pengguna.txt not found. Please create it." << endl;
        return;
    }

    string line;
    while (getline(inputFile, line)) {
        stringstream ss(line);
        string fileRole;
        getline(ss, fileRole, ',');
        getline(ss, fileUser, ',');
        getline(ss, filePass, ',');

        if (fileRole == "HR" && fileUser == inputUser && filePass == inputPass) {
            found = true;
            break;
        }
    }
    inputFile.close();

    if (found) {
        system("cls");
        cout << "\nHello " << inputUser << "\n" << endl;
        hrDashboard();
    } else {
        cout << "\nLOGIN ERROR\n" << endl;
    }
}

void loginAsStaff() {
    string inputUser, inputPass;
    string fileUser, filePass;
    bool found = false;

    system("cls");
    cout << "Masukan data data dibawah ini" << endl;
    cout << "USERNAME: ";
    cin >> inputUser;
    cout << "PASSWORD: ";
    cin >> inputPass;

    ifstream inputFile("data_pengguna.txt");
    if (!inputFile.is_open()) {
        cout << "Error: data_pengguna.csv not found. Please create it." << endl;
        return;
    }

    string line;
    while (getline(inputFile, line)) {
        stringstream ss(line);
        string fileRole;
        getline(ss, fileRole, ',');
        getline(ss, fileUser, ',');
        getline(ss, filePass, ',');

        if (fileRole == "Staff" && fileUser == inputUser && filePass == inputPass) {
            found = true;
            break;
        }
    }
    inputFile.close();

    if (found) {
        system("cls");
        cout << "\nHello " << inputUser << "\n" << endl;
        staffDashboard();
    } else {
        cout << "\nLOGIN ERROR\nPlease check your username and password for Staff\n" << endl;
    }
}

void hrDashboard() {
    int choice;
    do {
        cout << "\n--- HR Dashboard ---\n";
        cout << "1. Lihat Jadwal Rapat" << endl;
        cout << "2. Tambah Rapat" << endl;
        cout << "3. Urutkan Rapat" << endl;
        cout << "4. Daftar Hadir Rapat" << endl;
        cout << "5. Dapatkan Link Rapat" << endl;
        cout << "6. Batalkan Perubahan (Undo)" << endl;
        cout << "7. Tambah Akun Staff Baru" << endl;
        cout << "8. Lihat Daftar Akun Staff" << endl;
        cout << "9. Update Rapat" << endl;
        cout << "10. Lihat Request Rapat" << endl; 
        cout << "11. Logout" << endl;
        cout << "Pilihan: ";
        cin >> choice;

        switch (choice) {
            case 1:
                lihatmeeting();
                break;
            case 2:
                addNewMeeting();
                break;
            case 3:
                urutkanrapat();
                break;
            case 4:
                daftarhadir();
                break;
            case 5:
                linkrapat();
                break;
            case 6:
                undo();
                break;
            case 7:
                addStaff();
                break;
            case 8:
                viewStaff();
                break;
            case 9:
                updateMeeting();
                break;
            case 10:
                viewMeetingRequests();
                break;
            case 11: 
                cout << "Logging out....\n" << endl;
                break;
            default:
                cout << "Pilihan Error.\n" << endl;
        }
    } while (choice != 11);
}

void staffDashboard() {
    int choice;
    do {
        cout << "\n--- STAFF Dashboard ---\n";
        cout << "1. Lihat Jadwal Rapat" << endl;
        cout << "2. Urutkan Rapat" << endl;
        cout << "3. Konfirmasi Kehadiran Rapat" << endl;
        cout << "4. Dapatkan Link Rapat" << endl;
        cout << "5. Request Rapat" << endl;
        cout << "6. Lihat Status Pengajuan Rapat" << endl;
        cout << "7. Logout" << endl;
        cout << "Pilihan: ";
        cin >> choice;

        switch (choice) {
            case 1:
                lihatmeeting();
                break;
            case 2:
                urutkanrapat();
                break;
            case 3:
                hadir();
                break;
            case 4:
                linkrapat();
                break;
            case 5:
                requestMeeting();
                break;
            case 6:
                viewRequestStatus();
                break;
            case 7:
                cout << "Logging out....\n" << endl;
                break;
            default:
                cout << "Pilihan Error.\n" << endl;
        }
    } while (choice != 7);
}

void addNewMeeting() {
    string meetingName, meetingDate, startTime, endTime, meetingLocation;

    system("cls");
    cout << "--- Penjadwalan Rapat Baru ---\n";
    cout << "Masukkan Nama Rapat: ";
    cin.ignore();
    getline(cin, meetingName);
    cout << "Masukkan Tanggal Rapat (YYYY-MM-DD): ";
    getline(cin, meetingDate);
    cout << "Masukkan Jam Mulai (HH:MM): ";
    getline(cin, startTime);
    cout << "Masukkan Jam Selesai (HH:MM): ";
    getline(cin, endTime);
    cout << "Masukkan Lokasi Rapat (bisa link Zoom jika online): ";
    getline(cin, meetingLocation);

    for (const auto& r : Rapat) {
        if (r.meetingDate == meetingDate && r.meetingLocation == meetingLocation) {
            if (!(endTime <= r.startTime || startTime >= r.endTime)) {
                cout << "\n[ERROR] Lokasi \"" << meetingLocation << "\" sudah digunakan pada "
                     << meetingDate << " dari " << r.startTime << " sampai " << r.endTime << ".\n";
                cout << "Silakan pilih waktu atau lokasi lain.\n";
                cout << "\nTekan tombol apapun untuk kembali.";
                cin.get();
                return;
            }
        }
    }

    undoStack.push(Rapat);
    rapat newMeeting(meetingName, meetingDate, startTime, endTime, meetingLocation);
    Rapat.push_back(newMeeting);

    cout << "\nSukses Menambah Meeting!\n";
    cout << "\nTekan tombol apapun untuk kembali.";
    cin.get();
}

void urutkanrapat(){
    system("cls");
    cout << "--- Jadwal Rapat (Terurut Berdasarkan Tanggal) ---\n\n";

    sort(Rapat.begin(), Rapat.end(), sortingmeeting);

    if (Rapat.empty()) {
        cout << "~Tidak ada rapat yang terjadwal~.\n";
    } else {
        cout << "------------------------------------------------------------------------\n";
        cout << "| " << left << setw(23) << "Nama Rapat"
             << "| " << setw(13) << "Tanggal"
             << "| " << setw(13) << "Waktu"
             << "| " << setw(18) << "Lokasi" << "|\n";
        cout << "------------------------------------------------------------------------\n";
        for (const auto& r : Rapat) {
            r.displayMeeting();
        }
    }

    cout << "\nTekan tombol apapun untuk kembali.";
    cin.ignore();
    cin.get();
}

void undo(){
    if (undoStack.isEmpty()) {
        cout << "Tidak ada perubahan yang bisa dibatalkan.\n";
    } else {
        Rapat = undoStack.pop();
        cout << "Perubahan berhasil dibatalkan.\n";
    }
    cout << "\nTekan tombol apapun untuk kembali.";
    cin.ignore();
    cin.get();
}

void hadir() {
    system("cls");
    cout << "--- Konfirmasi Kehadiran Rapat ---\n\n";

    if (Rapat.empty()) {
        cout << "Tidak ada rapat yang tersedia untuk konfirmasi kehadiran.\n";
        cout << "\nTekan tombol apapun untuk kembali.";
        cin.ignore();
        cin.get();
        return;
    }

    cout << "Daftar Rapat:\n";
    cout << "------------------------------------------------\n";
    cout << "| No | Nama Rapat                       | Tanggal    | Waktu        |\n";
    cout << "------------------------------------------------\n";

    for (size_t i = 0; i < Rapat.size(); ++i) {
        cout << "| " << setw(2) << i + 1 << " | "
             << setw(24) << left << Rapat[i].meetingName << " | "
             << setw(10) << Rapat[i].meetingDate << " | "
             << setw(13) << (Rapat[i].startTime + " - " + Rapat[i].endTime) << "|\n";
    }
    cout << "------------------------------------------------\n";

    int pilihan;
    cout << "\nPilih nomor rapat untuk konfirmasi kehadiran: ";
    cin >> pilihan;

    if (pilihan < 1 || pilihan > static_cast<int>(Rapat.size())) {
        cout << "Pilihan tidak valid.\n";
        cout << "\nTekan tombol apapun untuk kembali.";
        cin.ignore();
        cin.get();
        return;
    }

    cin.ignore();
    string namaStaff;
    cout << "Masukkan nama Anda: ";
    getline(cin, namaStaff);

    int pilihanHadir;
    cout << "\nKonfirmasi Kehadiran:\n";
    cout << "1. Hadir\n";
    cout << "2. Tidak Hadir\n";
    cout << "Pilih: ";
    cin >> pilihanHadir;

    string statusHadir;
    if (pilihanHadir == 1) statusHadir = "Hadir";
    else if (pilihanHadir == 2) statusHadir = "Tidak Hadir";
    else {
        cout << "Pilihan tidak valid.\n";
        cout << "\nTekan tombol apapun untuk kembali.";
        cin.ignore();
        cin.get();
        return;
    }

    ofstream file("kehadiran.txt", ios::app);
    if (file.is_open()) {
        file << "Nama: " << namaStaff
             << ", Rapat: " << Rapat[pilihan - 1].meetingName
             << ", Tanggal: " << Rapat[pilihan - 1].meetingDate
             << ", Kehadiran: " << statusHadir << endl;
        file.close();
        cout << "\nKehadiran berhasil dicatat.\n";
    } else {
        cout << "Gagal membuka file kehadiran.txt\n";
    }
    cout << "\nTekan tombol apapun untuk kembali.";
    cin.ignore();
    cin.get();
}

void daftarhadir() {
    system("cls");
    cout << "--- Rekap Kehadiran Rapat ---\n\n";

    if (Rapat.empty()) {
        cout << "Belum ada data rapat yang tersedia.\n";
        cout << "\nTekan tombol apapun untuk kembali.";
        cin.ignore();
        cin.get();
        return;
    }

    cout << "Daftar Rapat:\n";
    cout << "----------------------------------------------\n";
    cout << "| No | Nama Rapat                       | Tanggal    |\n";
    cout << "----------------------------------------------\n";
    for (size_t i = 0; i < Rapat.size(); ++i) {
        cout << "| " << setw(2) << i + 1 << " | "
             << setw(24) << left << Rapat[i].meetingName << " | "
             << setw(10) << Rapat[i].meetingDate << " |\n";
    }
    cout << "----------------------------------------------\n";

    int pilihan;
    cout << "\nPilih nomor rapat untuk melihat kehadiran: ";
    cin >> pilihan;

    if (pilihan < 1 || pilihan > static_cast<int>(Rapat.size())) {
        cout << "Pilihan tidak valid.\n";
        cout << "\nTekan tombol apapun untuk kembali.";
        cin.ignore();
        cin.get();
        return;
    }

    string namaRapatFilter = Rapat[pilihan - 1].meetingName;

    ifstream file("kehadiran.txt");
    if (!file.is_open()) {
        cout << "Gagal membuka file atau belum ada data kehadiran.\n";
        cout << "\nTekan tombol apapun untuk kembali.";
        cin.ignore();
        cin.get();
        return;
    }

    string line;
    bool ditemukan = false;

    cout << "\n--- Kehadiran untuk Rapat: " << namaRapatFilter << " ---\n";
    cout << "-------------------------------------------\n";
    cout << "| Nama Pegawai             | Kehadiran  |\n";
    cout << "-------------------------------------------\n";

    while (getline(file, line)) {
        if (line.find("Rapat: " + namaRapatFilter) != string::npos) {
            size_t posNama = line.find("Nama: ");
            size_t posRapat = line.find(", Rapat:");
            size_t posKehadiran = line.find("Kehadiran: ");

            string nama = line.substr(posNama + 6, posRapat - (posNama + 6));
            string kehadiran = line.substr(posKehadiran + 11);

            cout << "| " << setw(24) << left << nama << " | "
                 << setw(10) << kehadiran << " |\n";
            ditemukan = true;
        }
    }

    cout << "-------------------------------------------\n";
    file.close();

    if (!ditemukan) {
        cout << "Belum ada yang mengisi kehadiran untuk rapat ini.\n";
    }

    cout << "\nTekan tombol apapun untuk kembali.";
    cin.ignore();
    cin.get();
}

void linkrapat() {
    system("cls");
    cout << "--- Lokasi Rapat ---\n\n";

    if (Rapat.empty()) {
        cout << "~Tidak ada rapat yang terjadwal~.\n";
    } else {
        cout << "Daftar Rapat:\n";
        cout << "----------------------------------------------\n";
        cout << "| No | Nama Rapat                       | Tanggal    |\n";
        cout << "----------------------------------------------\n";
        for (size_t i = 0; i < Rapat.size(); ++i) {
            cout << "| " << setw(2) << i + 1 << " | "
                 << setw(24) << left << Rapat[i].meetingName << " | "
                 << setw(10) << Rapat[i].meetingDate << " |\n";
        }
        cout << "----------------------------------------------\n";

        cout << "\nPilih nomor rapat untuk melihat lokasinya: ";
        int pilihan;
        cin >> pilihan;

        if (pilihan < 1 || pilihan > static_cast<int>(Rapat.size())) {
            cout << "Pilihan tidak valid.\n";
        } else {
            cout << "\nLokasi rapat \"" << Rapat[pilihan - 1].meetingName << "\":\n";
            cout << Rapat[pilihan - 1].meetingLocation << endl;
        }
    }

    cout << "\nTekan tombol apapun untuk kembali.";
    cin.ignore();
    cin.get();
}

void addStaff() {
    string username, password;
    system("cls");
    cout << "--- Tambah Akun Staff Baru ---\n";
    cout << "Masukkan Username Staff: ";
    cin.ignore();
    getline(cin, username);
    cout << "Masukkan Password Staff: ";
    getline(cin, password);

    ofstream file("data_pengguna.txt", ios::app);
    if (file.is_open()) {
        file << "Staff," << username << "," << password << endl;
        file.close();
        cout << "\nAkun staff '" << username << "' berhasil ditambahkan ke data_pengguna.csv!\n";
    } else {
        cout << "Gagal membuka file data_pengguna.csv. Pastikan file ada dan dapat diakses.\n";
    }
    cout << "\nTekan tombol apapun untuk kembali.";
    cin.get();
}

void viewStaff() {
    system("cls");
    cout << "--- Daftar Akun Staff ---\n\n";

    ifstream inputFile("data_pengguna.txt");
    if (!inputFile.is_open()) {
        cout << "Error: data_pengguna.csv not found or cannot be opened.\n";
        cout << "\nTekan tombol apapun untuk kembali.";
        cin.ignore();
        cin.get();
        return;
    }

    string line;
    bool foundStaff = false;

    cout << "-------------------------------\n";
    cout << "| " << left << setw(15) << "Username"
             << "| " << setw(10) << "Role" << "|\n";
    cout << "-------------------------------\n";

    while (getline(inputFile, line)) {
        stringstream ss(line);
        string fileRole, fileUser, filePass;
        getline(ss, fileRole, ',');
        getline(ss, fileUser, ',');
        getline(ss, filePass, ',');

        if (fileRole == "Staff") {
            cout << "| " << left << setw(15) << fileUser
                 << "| " << setw(10) << fileRole << "|\n";
            foundStaff = true;
        }
    }
    inputFile.close();

    cout << "-------------------------------\n";

    if (!foundStaff) {
        cout << "Belum ada akun staff terdaftar.\n";
    }

    cout << "\nTekan tombol apapun untuk kembali.";
    cin.ignore();
    cin.get();
}

void lihatmeeting() {
    system("cls");
    cout << "--- Jadwal Rapat ---\n\n";

    if (Rapat.empty()) {
        cout << "~Tidak ada rapat yang terjadwal~.\n";
    } else {
        cout << "------------------------------------------------------------------------\n";
        cout << "| " << left << setw(23) << "Nama Rapat"
             << "| " << setw(13) << "Tanggal"
             << "| " << setw(13) << "Waktu"
             << "| " << setw(18) << "Lokasi" << "|\n";
        cout << "------------------------------------------------------------------------\n";

        for (const auto& r : Rapat) {
            r.displayMeeting();
        }
    }

    cout << "\nTekan tombol apapun untuk kembali.";
    cin.ignore();
    cin.get();
}


void updateMeeting() {
    system("cls");
    cout << "--- Update Rapat ---\n\n";

    if (Rapat.empty()) {
        cout << "~Tidak ada rapat yang terjadwal untuk diupdate~.\n";
        cout << "\nTekan tombol apapun untuk kembali.";
        cin.ignore();
        cin.get();
        return;
    }

    cout << "Daftar Rapat:\n";
    cout << "------------------------------------------------------------------------\n";
    cout << "| No | " << left << setw(23) << "Nama Rapat"
             << "| " << setw(13) << "Tanggal"
             << "| " << setw(13) << "Waktu"
             << "| " << setw(18) << "Lokasi" << "|\n";
    cout << "------------------------------------------------------------------------\n";
    for (size_t i = 0; i < Rapat.size(); ++i) {
        cout << "| " << setw(2) << i + 1 << " ";
        Rapat[i].displayMeeting();
    }

    int choice;
    cout << "\nPilih nomor rapat yang ingin diupdate: ";
    cin >> choice;

    if (choice < 1 || choice > static_cast<int>(Rapat.size())) {
        cout << "Pilihan tidak valid.\n";
        cout << "\nTekan tombol apapun untuk kembali.";
        cin.ignore();
        cin.get();
        return;
    }

    undoStack.push(Rapat);

    rapat& meetingToUpdate = Rapat[choice - 1];

    string newMeetingName, newMeetingDate, newStartTime, newEndTime, newMeetingLocation;

    cin.ignore();
    cout << "\nMasukkan detail baru (tekan Enter untuk mempertahankan nilai lama): \n";

    cout << "Nama Rapat (" << meetingToUpdate.meetingName << "): ";
    getline(cin, newMeetingName);
    if (!newMeetingName.empty()) {
        meetingToUpdate.meetingName = newMeetingName;
    }

    cout << "Tanggal Rapat (YYYY-MM-DD) (" << meetingToUpdate.meetingDate << "): ";
    getline(cin, newMeetingDate);
    if (!newMeetingDate.empty()) {
        meetingToUpdate.meetingDate = newMeetingDate;
    }

    cout << "Jam Mulai (HH:MM) (" << meetingToUpdate.startTime << "): ";
    getline(cin, newStartTime);
    if (!newStartTime.empty()) {
        meetingToUpdate.startTime = newStartTime;
    }

    cout << "Jam Selesai (HH:MM) (" << meetingToUpdate.endTime << "): ";
    getline(cin, newEndTime);
    if (!newEndTime.empty()) {
        meetingToUpdate.endTime = newEndTime;
    }

    cout << "Lokasi Rapat (bisa link Zoom jika online) (" << meetingToUpdate.meetingLocation << "): ";
    getline(cin, newMeetingLocation);
    if (!newMeetingLocation.empty()) {
        meetingToUpdate.meetingLocation = newMeetingLocation;
    }

    for (size_t i = 0; i < Rapat.size(); ++i) {
        if (i != (choice - 1) && Rapat[i].meetingDate == meetingToUpdate.meetingDate && Rapat[i].meetingLocation == meetingToUpdate.meetingLocation) {
            if (!(meetingToUpdate.endTime <= Rapat[i].startTime || meetingToUpdate.startTime >= Rapat[i].endTime)) {
                cout << "\n[ERROR] Lokasi \"" << meetingToUpdate.meetingLocation << "\" sudah digunakan pada "
                     << meetingToUpdate.meetingDate << " dari " << Rapat[i].startTime << " sampai " << Rapat[i].endTime << ".\n";
                cout << "Pembaharuan dibatalkan. Silakan pilih waktu atau lokasi lain.\n";
                if (!undoStack.isEmpty()) {
                    Rapat = undoStack.pop();
                }
                cout << "\nTekan tombol apapun untuk kembali.";
                cin.get();
                return;
            }
        }
    }


    cout << "\nRapat berhasil diupdate!\n";
    cout << "\nTekan tombol apapun untuk kembali.";
    cin.get();
}


void requestMeeting() {
    string requesterName, meetingName, meetingDate, startTime, endTime, meetingLocation;

    system("cls");
    cout << "--- Ajukan Permintaan Rapat Baru ---\n";
    cin.ignore();
    cout << "Masukkan Nama Anda (Staff): ";
    getline(cin, requesterName);
    cout << "Masukkan Nama Rapat yang diajukan: ";
    getline(cin, meetingName);
    cout << "Masukkan Tanggal Rapat (YYYY-MM-DD): ";
    getline(cin, meetingDate);
    cout << "Masukkan Jam Mulai (HH:MM): ";
    getline(cin, startTime);
    cout << "Masukkan Jam Selesai (HH:MM): ";
    getline(cin, endTime);
    cout << "Masukkan Lokasi Rapat (bisa link Zoom jika online): ";
    getline(cin, meetingLocation);

    PermintaanRapat newRequest(requesterName, meetingName, meetingDate, startTime, endTime, meetingLocation);
    meetingRequestsQueue.enqueue(newRequest);
    allMeetingRequests.push_back(newRequest);

    cout << "\nPermintaan rapat Anda telah diajukan. Mohon tunggu konfirmasi dari HR.\n";
    cout << "\nTekan tombol apapun untuk kembali.";
    cin.get();
}

void viewMeetingRequests() {
    system("cls");
    cout << "--- Lihat & Setujui/Tolak Permintaan Rapat ---\n\n";

    if (meetingRequestsQueue.isEmpty()) {
        cout << "~Tidak ada permintaan rapat yang tertunda~.\n";
        cout << "\nTekan tombol apapun untuk kembali.";
        cin.ignore();
        cin.get();
        return;
    }

    Queue<PermintaanRapat> tempQueue;
    vector<PermintaanRapat> currentPendingRequests;
    int index = 0;

    cout << "Daftar Permintaan Rapat Tertunda:\n";
    cout << "-------------------------------------------------------------------------------------------------------\n";
    cout << "| No | Requester      | Nama Rapat           | Tanggal    | Waktu      | Lokasi          | Status    |\n";
    cout << "-------------------------------------------------------------------------------------------------------\n";

    while (!meetingRequestsQueue.isEmpty()) {
        PermintaanRapat req = meetingRequestsQueue.front();
        currentPendingRequests.push_back(req);
        tempQueue.enqueue(req);
        meetingRequestsQueue.dequeue();

        cout << "| " << setw(2) << ++index << " ";
        req.displayRequest();
    }
    meetingRequestsQueue = tempQueue; 

    if (currentPendingRequests.empty()) {
        cout << "~Tidak ada permintaan rapat yang tertunda~.\n";
        cout << "\nTekan tombol apapun untuk kembali.";
        cin.ignore();
        cin.get();
        return;
    }

    int pilihan;
    cout << "\nPilih nomor permintaan yang ingin Anda proses (0 untuk kembali): ";
    cin >> pilihan;

    if (pilihan == 0) {
        cout << "\nKembali ke Dashboard HR.\n";
        cin.ignore();
        cin.get();
        return;
    }

    if (pilihan < 1 || pilihan > static_cast<int>(currentPendingRequests.size())) {
        cout << "Pilihan tidak valid.\n";
        cout << "\nTekan tombol apapun untuk kembali.";
        cin.ignore();
        cin.get();
        return;
    }

    PermintaanRapat selectedRequest = currentPendingRequests[pilihan - 1];

    int approveChoice;
    cout << "\nAnda memilih permintaan rapat:\n";
    selectedRequest.displayRequest();
    cout << "\nApakah Anda ingin menyetujui atau menolak permintaan ini?\n";
    cout << "1. Setujui\n";
    cout << "2. Tolak\n";
    cout << "Pilihan: ";
    cin >> approveChoice;

    if (approveChoice == 1) {
        bool conflict = false;
        for (const auto& r : Rapat) {
            if (r.meetingDate == selectedRequest.meetingDate && r.meetingLocation == selectedRequest.meetingLocation) {
                if (!(selectedRequest.endTime <= r.startTime || selectedRequest.startTime >= r.endTime)) {
                    conflict = true;
                    cout << "\n[ERROR] Lokasi \"" << selectedRequest.meetingLocation << "\" sudah digunakan pada "
                         << selectedRequest.meetingDate << " dari " << r.startTime << " sampai " << r.endTime << ".\n";
                    cout << "Permintaan rapat ini tidak dapat disetujui karena konflik jadwal.\n";
                    break;
                }
            }
        }

        if (conflict) {
            selectedRequest.status = "Rejected";
            cout << "\nPermintaan rapat ditolak karena konflik jadwal.\n";
        } else {
            undoStack.push(Rapat);
            rapat newMeeting(selectedRequest.meetingName, selectedRequest.meetingDate, selectedRequest.startTime, selectedRequest.endTime, selectedRequest.meetingLocation);
            Rapat.push_back(newMeeting);
            selectedRequest.status = "Approved";
            cout << "\nPermintaan rapat berhasil disetujui dan ditambahkan ke jadwal rapat.\n";
        }
    } else if (approveChoice == 2) {
        selectedRequest.status = "Rejected";
        cout << "\nPermintaan rapat berhasil ditolak.\n";
    } else {
        cout << "Pilihan tidak valid. Tidak ada tindakan yang dilakukan.\n";
    }

    for (auto& req : allMeetingRequests) {
        if (req.requesterName == selectedRequest.requesterName &&
            req.meetingName == selectedRequest.meetingName &&
            req.meetingDate == selectedRequest.meetingDate) {
            req.status = selectedRequest.status;
            break;
        }
    }

    Queue<PermintaanRapat> updatedQueue;
    for (const auto& req : allMeetingRequests) {
        if (req.status == "Pending") {
            updatedQueue.enqueue(req);
        }
    }
    meetingRequestsQueue = updatedQueue;

    cout << "\nTekan tombol apapun untuk kembali.";
    cin.ignore();
    cin.get();
}

void viewRequestStatus() {
    string currentStaffUser;
    cout << "Masukkan username Anda untuk melihat status request: ";
    cin.ignore();
    getline(cin, currentStaffUser);

    system("cls");
    cout << "--- Status Permintaan Rapat Anda ---\n\n";

    bool foundRequests = false;
    cout << "-------------------------------------------------------------------------------------------------------\n";
    cout << "| Requester      | Nama Rapat           | Tanggal    | Waktu      | Lokasi          | Status    |\n";
    cout << "-------------------------------------------------------------------------------------------------------\n";

    for (const auto& req : allMeetingRequests) {
        if (req.requesterName == currentStaffUser) {
            req.displayRequest();
            foundRequests = true;
        }
    }

    if (!foundRequests) {
        cout << "~Anda belum mengajukan permintaan rapat atau username salah~.\n";
    }

    cout << "\nTekan tombol apapun untuk kembali.";
    cin.get();
}