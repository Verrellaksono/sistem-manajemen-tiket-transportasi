#include <iostream>
#include <iomanip>
#include <queue>
#include <algorithm>
using namespace std;

//Struct Transportasi
struct Transportasi{
	int id_jadwal;
	string jenis_transportasi;
	string tujuan;
	string waktu_berangkat;
	int harga;
	int kapasitas;
};

//Struct Tiket
struct Tiket{
	int id_pemesanan;
	string nama;
	int id_jadwal;
	int jml_kursi;
	int totalHarga;
	string status;
	Tiket* next;
};

//linked list
Tiket* headTiket = NULL;

//Queue 
queue<Tiket*> queuePembayaran;

//Fungsi menjadikan teks menjadi kecil
string lowerCase(string teks) {
    transform(teks.begin(), teks.end(), teks.begin(), [](unsigned char c) { 
		return tolower(c); 
		});
    return teks;
}

//Fungsi Menampilkan Jadwal Tranportasi Berdasarkan Tujuan atau Waktu Keberangkatan
void pencarianJadwal(Transportasi data[], int jumlahData, int panjangTabel){
	int jawab, jumlahDitemukan;
	string tujuan, waktu;
	
	do {
		cout << "=== Pencarian Jadwal ===" << endl;
		cout << "Mencari berdasarkan:" << endl;
		cout << "1. Tujuan" << endl;
		cout << "2. Waktu Keberangkatan" << endl;
		cout << "0. Keluar" << endl;
		cout << "Masukkan Pilihan Anda: ";
		cin >> jawab;
		jumlahDitemukan = 0;
		
		switch (jawab){
			case 1:
				cout << "Sebutkan Tujuan: ";
				cin.ignore();
				getline(cin, tujuan);
			    
			    // Header Table
				cout << left;
				cout << string(panjangTabel, '-') << endl;
				cout << "|" << setw(10) << "ID Jadwal"
					 << "|" << setw(20) << "Jenis Transportasi"
				     << "|" << setw(15) << "Tujuan"
				     << "|" << setw(15) << "Waktu Berangkat" 
				     << "|" << setw(15) << "Harga" 
				     << "|" << setw(10) << "Kuota" << "|" << endl;
				cout << string(panjangTabel, '-') << endl;
				
				for(int i=0; i<jumlahData; i++){
					if(lowerCase(data[i].tujuan) == lowerCase(tujuan)){		 
						// Data Tabel
						cout << "|" << setw(10) << data[i].id_jadwal
							 << "|" << setw(20) << data[i].jenis_transportasi
				         	 << "|" << setw(15) << data[i].tujuan
				         	 << "|" << setw(15) << data[i].waktu_berangkat
				         	 << "|" << setw(15) << data[i].harga
				        	 << "|" << setw(10) << data[i].kapasitas << "|" << endl;
				        // Footer Tabel
						cout << string(panjangTabel, '-') << endl;
				        jumlahDitemukan++;
					}
				}
				
				if(jumlahDitemukan == 0){
					cout << "Jadwal Transportasi dengan Tujuan yang Anda Inginkan Tidak Ada" << endl;
				}
				
				cout << "\nTekan Enter Untuk Kembali ke Menu Utama...";
				cin.get();
				system("CLS");
				break;
			case 2:
				cout << "Sebutkan Waktu Keberangkatan: ";
				cin.ignore();
				getline(cin, waktu);
				
				// Header Table
				cout << left;
				cout << string(panjangTabel, '-') << endl;
				cout << "|" << setw(10) << "ID Jadwal"
					 << "|" << setw(20) << "Jenis Transportasi"
				     << "|" << setw(15) << "Tujuan"
				     << "|" << setw(15) << "Waktu Berangkat"
				     << "|" << setw(15) << "Harga"
				     << "|" << setw(10) << "Kapasitas" << "|" << endl;
				cout << string(panjangTabel, '-') << endl;
				
				for(int i=0; i<jumlahData; i++){
					if(data[i].waktu_berangkat == waktu){
						// Data Tabel
						cout << "|" << setw(10) << data[i].id_jadwal
							 << "|" << setw(20) << data[i].jenis_transportasi
				         	 << "|" << setw(15) << data[i].tujuan
				         	 << "|" << setw(15) << data[i].waktu_berangkat
				         	 << "|" << setw(15) << data[i].harga
				        	 << "|" << setw(10) << data[i].kapasitas << "|" << endl;
				        jumlahDitemukan++;
					}
				}
				
				if(jumlahDitemukan == 0){
					cout << "|" << setw(74) << "Jadwal Transportasi dengan Waktu Keberangkatan yang Anda Inginkan Tidak Ada" << "|" << endl;
				}
				
				// Footer Tabel
				cout << string(76, '-') << endl;
				
				cout << "\nTekan Enter Untuk Kembali ke Menu Utama...";
				cin.get();
				system("CLS");
				break;
			default:
				cout << "Pilihan tidak ditemukan";
				break;
		}
	} while (jawab != 0);
	system("CLS");
}

//Fungsi untuk pemesanan tiket
void pesanTiket(Transportasi data[], int jumlahData){
	//Variabel
	int id_pemesanan, id_jadwal, jml_kursi, totalHarga = 0;
	string nama;
	
	cout << "=== Pemesanan Tiket ===" << endl;
	cout << "Masukkan ID Pemesanan: ";
	cin >> id_pemesanan;
    cin.ignore();
    cout << "Masukkan Nama Pemesan: ";
    getline(cin, nama);
    cout << "Masukkan ID Jadwal yang dipilih: ";
    cin >> id_jadwal;;
    
    //Cek ID Jadwal
    bool jadwal = false;
    for (int i = 0; i < jumlahData; i++) {
        if (data[i].id_jadwal == id_jadwal) {
           jadwal = true;
        }
    }
    
    if (!jadwal) {
    	cout << "ID Jadwal Tidak Ditemukan" << endl;
    	cout << "Tekan Enter Untuk Kembali ke Menu Utama...";
    	cin.ignore();
		cin.get();
		system("CLS");
		return;
	}
    
    cout << "Masukkan Jumlah Kursi: ";
    cin >> jml_kursi;
    
    //Cek ketersediaan kursi
    bool found = false;
    for (int i = 0; i < jumlahData; i++) {
        if(data[i].id_jadwal == id_jadwal){
        	if (data[i].kapasitas >= jml_kursi) {
	            data[i].kapasitas -= jml_kursi;
	            // Total Harga
	            totalHarga = data[i].harga * jml_kursi;
	            
	            cout << "Total Harga: Rp. " << totalHarga << endl;
				cout << "Pemesanan berhasil!" << endl;
	            
	            
	            // Menyimpan ke linked list
			    Tiket* tiket = new Tiket;
			    tiket->id_pemesanan = id_pemesanan;
			    tiket->nama = nama;
			    tiket->id_jadwal = id_jadwal;
			    tiket->jml_kursi = jml_kursi;
			    tiket->totalHarga = totalHarga;
			    tiket->status = "Belum Bayar";
			    tiket->next = NULL;
			    
			    if (headTiket == NULL) {
			        headTiket = tiket;
			    } else {
			        Tiket* temp = headTiket;
			        while (temp->next != NULL) {
			            temp = temp->next;
			        }
			        temp->next = tiket;
			    }
	        } else {
	            cout << "Kapasitas tidak mencukupi. Pemesanan gagal." << endl;
	        }
		}
    }
    
    cout << "\nTekan Enter Untuk Kembali ke Menu Utama...";
    cin.ignore();
	cin.get();
	system("CLS");
}

//Funngsi pembayaran tiket
void pembayaranTiket(Transportasi data[], int jumlahData, queue<Tiket*> &queuePembayaran){
	Tiket* temp = headTiket;
	int id_pemesanan;
	bool ditemukan = false, belumBayar = false;
	int panjangTabel = 113;
	
	cout << string(panjangTabel, '-') << endl;
	cout << "|" << setw(15) << "ID Pemesanan"
		 << "|" << setw(10) << "Nama"
		 << "|" << setw(20) << "Jenis Transportasi"
		 << "|" << setw(15) << "Tujuan"
		 << "|" << setw(15) << "Jumlah Kursi"
		 << "|" << setw(15) << "Total Harga"
		 << "|" << setw(15) << "Status" << "|" << endl;
	cout << string(panjangTabel, '-') << endl;
	
	//Menampilkan data pesanan tiket
	while (temp != NULL){
		//Variabel utnu data tujuan dan jenis transportasi tiket
		string tujuan, transportasi;
		for (int i = 0; i < jumlahData; i++){
			if(data[i].id_jadwal == temp->id_jadwal){
				tujuan = data[i].tujuan;
				transportasi = data[i].jenis_transportasi;
			}
		}
		
		if (temp->status == "Belum Bayar") {
			belumBayar = true;
			cout << "|" << setw(15) << temp->id_pemesanan
				 << "|" << setw(10) << temp->nama
				 << "|" << setw(20) << transportasi
				 << "|" << setw(15) << tujuan
				 << "|" << setw(15) << temp->jml_kursi
				 << "|" << setw(15) << temp->totalHarga
				 << "|" << setw(15) << temp->status << "|" << endl;
			cout << string(panjangTabel, '-') << endl;	
		}
		temp = temp->next;	
	}
	
	if (belumBayar) {
		temp = headTiket;
		cout << "=== Pembayaran Tiket ===" << endl;
		cout << "Masukkan ID Pemesanan: ";
		cin >> id_pemesanan;
		
		while (temp != NULL) {
			if (temp->id_pemesanan == id_pemesanan) {
				ditemukan = true;
				temp->status = "Sudah Bayar";
				cout << "Tiket dari ID Pemesanan: " << temp->id_pemesanan << " Sudah Dibayar" << endl;
				queuePembayaran.push(temp);
				break;
			}
			temp = temp->next;
		}	
	} else if (!ditemukan || !belumBayar) {
		cout << "Tidak Ada Pemesanan Tiket yang Belum Dibayar" << endl;
	}

	cout << "\nTekan Enter Untuk Kembali ke Menu Utama...";
	cin.ignore();
	cin.get();
	system("CLS");
}

void prosesAntrian(queue<Tiket*>& queuePembayaran) {
	if (queuePembayaran.empty()) {
        cout << "Tidak ada penumpang dalam antrian keberangkatan." << endl;
    } else {
        cout << "Memproses antrian keberangkatan..." << endl;
        while (!queuePembayaran.empty()) {
            Tiket* pemesan = queuePembayaran.front();
            queuePembayaran.pop(); // keluarkan dari antrian
            pemesan->status = "Selesai";

            // Tampilkan data penumpang yang diproses
            cout << "---------------------------------------------" << endl;
            cout << "ID Pemesanan : " << pemesan->id_pemesanan << endl;
            cout << "Nama         : " << pemesan->nama << endl;
            cout << "ID Jadwal    : " << pemesan->id_jadwal << endl;
            cout << "Jumlah Kursi : " << pemesan->jml_kursi << endl;
            cout << "Total Harga  : " << pemesan->totalHarga << endl;
            cout << "Status       : " << pemesan->status << endl;
        }
        cout << "Antrian keberangkatan telah diproses." << endl;
    }

    cout << "\nTekan Enter Untuk Kembali ke Menu Utama...";
    cin.ignore();
    cin.get();
    system("CLS");
}

//Fungsi pencarian pemesanan berdasarkan id pemesanan atau nama pemesan
void pencarianPemesanan(Transportasi data[], int jumlahData) {
	Tiket* pemesanan = headTiket;
	int pilihan, id_pemesanan;
	string nama;
	bool ditemukan = false;
	
	cout << "Pencarian Berdasarkan:" << endl;
	cout << "1. ID Pemesanan" << endl;
	cout << "2. Nama Penumpang" << endl;
	cout << "Masukkan Pilihan: ";
	cin >> pilihan;
	
	switch (pilihan){
		case 1:
			cout << "Masukkan ID Penumpang: ";
			cin >> id_pemesanan;
			
			pemesanan = headTiket;
			cout << "-------------------------------------------------------------------------------------------------" << endl;
			cout << "|" << setw(15) << "ID Pemesanan"
				 << "|" << setw(10) << "Nama"
				 << "|" << setw(20) << "Jenis Transportasi"
				 << "|" << setw(15) << "Tujuan"
				 << "|" << setw(15) << "Jumlah Kursi"
				 << "|" << setw(15) << "Status" << "|" << endl;
			cout << "-------------------------------------------------------------------------------------------------" << endl;
			
			while (pemesanan != NULL) {
				if (pemesanan->id_pemesanan == id_pemesanan) {
					ditemukan = true;
			        string tujuan = "-", transportasi = "-";
			        for (int i = 0; i < jumlahData; i++) {
			            if (data[i].id_jadwal == pemesanan->id_jadwal) {
			                tujuan = data[i].tujuan;
			                transportasi = data[i].jenis_transportasi;
			                break;
			            }
			        }
			
			        cout << "|" << setw(15) << pemesanan->id_pemesanan
			             << "|" << setw(10) << pemesanan->nama
			             << "|" << setw(20) << transportasi
			             << "|" << setw(15) << tujuan
			             << "|" << setw(15) << pemesanan->id_jadwal
			             << "|" << setw(15) << pemesanan->status << "|" << endl;
			        cout << "-------------------------------------------------------------------------------------------------" << endl;
			        break;
				}
				pemesanan = pemesanan->next;
		    }
		    
		    if(!ditemukan) {
		    	cout << "Pencarian Tidak Ditemukan";
			}
		    
		    cout << "\nTekan Enter Untuk Kembali ke Menu Utama...";
			cin.ignore();
			cin.get();
			system("CLS");
			break;
		case 2:			
			cout << "Masukkan Nama Pemesan: ";
			cin.ignore();
			getline(cin, nama);
			pemesanan = headTiket;

			cout << "-------------------------------------------------------------------------------------------------" << endl;
			cout << "|" << setw(15) << "ID Pemesanan"
				 << "|" << setw(10) << "Nama"
				 << "|" << setw(20) << "Jenis Transportasi"
				 << "|" << setw(15) << "Tujuan"
				 << "|" << setw(15) << "Jumlah Kursi"
				 << "|" << setw(15) << "Status" << "|" << endl;
			cout << "-------------------------------------------------------------------------------------------------" << endl;
			
			while (pemesanan != NULL) {
				if (lowerCase(pemesanan->nama) == lowerCase(nama)) {
					ditemukan = true;
			        string tujuan = "-", transportasi = "-";
			        for (int i = 0; i < jumlahData; i++) {
			            if (data[i].id_jadwal == pemesanan->id_jadwal) {
			                tujuan = data[i].tujuan;
			                transportasi = data[i].jenis_transportasi;
			                break;
			            }
			        }
			
			        cout << "|" << setw(15) << pemesanan->id_pemesanan
			             << "|" << setw(10) << pemesanan->nama
			             << "|" << setw(20) << transportasi
			             << "|" << setw(15) << tujuan
			             << "|" << setw(15) << pemesanan->id_jadwal
			             << "|" << setw(15) << pemesanan->status << "|" << endl;
			        cout << "-------------------------------------------------------------------------------------------------" << endl;
			        break;
				}
				pemesanan = pemesanan->next;
		    }
		    
		    if(!ditemukan) {
		    	cout << "Pencarian Tidak Ditemukan";
			}
			
			cout << "\nTekan Enter Untuk Kembali ke Menu Utama...";
			cin.get();
			system("CLS");
			
			break;
	}
	ditemukan = false;
}

//Fungsi peembatalan tiket pemesanan
void pembatalanPemesanan(queue<Tiket*>& queuePembayaran, Tiket*& headTiket) {
    int id_pemesanan;
    bool ditemukan = false;

	cout << "=== Pembatalan Pemesanan Tiket ===" << endl;
    cout << "Masukkan ID Pemesanan: ";
    cin >> id_pemesanan;

    //Cari di linked list
    Tiket* current = headTiket;
    Tiket* prev = NULL;

    while (current != NULL) {
        if (current->id_pemesanan == id_pemesanan) {
            ditemukan = true;

            if (current->status == "Selesai") {
                cout << "Pemesanan tiket dengan id pemesanan " << id_pemesanan << " tidak dapat dibatalkan karena telah Selesai.\n";
                break;
            }

            if (current->status == "Sudah Bayar") {
                //Hapus dari queue pembayaran
                queue<Tiket*> tempQueue;
                while (!queuePembayaran.empty()) {
                    Tiket* item = queuePembayaran.front();
                    queuePembayaran.pop();

                    if (item->id_pemesanan != id_pemesanan) {
                        tempQueue.push(item);
                    }
                }
                queuePembayaran = tempQueue;

                cout << "Pemesanan dengan ID " << id_pemesanan << " telah dibatalkan.\n";
            } else if (current->status == "Belum Bayar") {
                cout << "Pemesanan dengan ID " << id_pemesanan << " dibatalkan.\n";
            }

            //Hapus dari linked list
            if (prev == nullptr) {
                headTiket = current->next;
            } else {
                prev->next = current->next;
            }

            delete current;
            break;
        }

        prev = current;
        current = current->next;
    }

    if (!ditemukan) {
        cout << "Tiket dengan ID " << id_pemesanan << " tidak ditemukan.\n";
    }

    cout << "\nTekan Enter Untuk Kembali ke Menu Utama...";
    cin.ignore();
    cin.get();
    system("CLS");
}

int main(){
	// Data Jadwal Transportasi
	int jumlahDataTransportasi = 6;
	Transportasi dataTransportasi[jumlahDataTransportasi] = {
	    {101, "Bus", "Bandung", "08:00", 130000, 10},
	    {102, "Kereta", "Yogyakarta", "12:30", 250000, 300},
	    {103, "Pesawat", "NTT", "17:45", 2000000, 150},
	    {104, "Bus", "Semarang", "06:15", 200000, 45},
	    {105, "Kereta", "Surabaya", "10:00", 350000, 350},
	    {106, "Pesawat", "Lombok", "14:20", 1800000, 180}
	};
	int pilihan;
	
	do{
		//Table Semua Jadwal
		int panjangTabel = 92;
		cout << left;
		cout << string(panjangTabel, '-') << endl;
		cout << "|" << setw(10) << "ID Jadwal"
			 << "|" << setw(20) << "Jenis Transportasi"
			 << "|" << setw(15) << "Tujuan"
			 << "|" << setw(15) << "Waktu Berangkat"
			 << "|" << setw(15) << "Harga"
			 << "|" << setw(10) << "Kuota" << "|" << endl;
		cout << string(panjangTabel, '-') << endl;
		
		for(int i=0; i < jumlahDataTransportasi; i++){			 
			// Data Tabel
			cout << "|" << setw(10) << dataTransportasi[i].id_jadwal
				<< "|" << setw(20) << dataTransportasi[i].jenis_transportasi
			    << "|" << setw(15) << dataTransportasi[i].tujuan
			    << "|" << setw(15) << dataTransportasi[i].waktu_berangkat
			    << "|" << setw(15) << dataTransportasi[i].harga
			    << "|" << setw(10) << dataTransportasi[i].kapasitas << "|" << endl;
			// Footer Tabel
			cout << string(panjangTabel, '-') << endl;
		}
		
		//Menu Utama
		cout << "=== Menu Utama ===" << endl;
		cout << "1. Pencarian Daftar Jadwal Transportasi" << endl;
		cout << "2. Pemesanan Tiket" << endl;
		cout << "3. Pembayaran Tiket" << endl;
		cout << "4. Proses Antrian Keberangkatan" << endl;
		cout << "5. Pencarian Pemesanan Tiket" << endl;
		cout << "6. Pembatalan Pemesanan Tiket" << endl;
		cout << "0. Keluar" << endl;
		cout << "Masukkan Pilihan Anda: ";
		cin >> pilihan;
		
		switch(pilihan){
			case 1:
				system("CLS");
				pencarianJadwal(dataTransportasi, jumlahDataTransportasi, panjangTabel);
				break;
			case 2:
				system("CLS");
				pesanTiket(dataTransportasi, jumlahDataTransportasi);
				break;
			case 3:
				system("CLS");
				pembayaranTiket(dataTransportasi, jumlahDataTransportasi, queuePembayaran);
				break;
			case 4:
				system("CLS");
				prosesAntrian(queuePembayaran);
				break;
			case 5:
				system("CLS");
				pencarianPemesanan(dataTransportasi, jumlahDataTransportasi);
				break;
			case 6:
				system("CLS");
				pembatalanPemesanan(queuePembayaran, headTiket);
				break;
			case 0:
				cout << "\nKeluar dari Program. Terima Kasih!";
				break;
			default:
				cout << "Pilihan tidak valid. Silakan coba lagi!";
		}
	} while(pilihan != 0);
	
	return 0;
}
