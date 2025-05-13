#include <iostream>
#include <iomanip>
#include <queue>
using namespace std;

//Struct Transportasi
struct Transportasi{
	int id_jadwal;
	string jenis_transportasi;
	string tujuan;
	string waktu_berangkat;
	int kapasitas;
};

//Struct Tiket
struct Tiket{
	int id_pemesanan;
	string nama;
	int id_jadwal;
	int jml_kursi;
	string status;
	Tiket* next;
};

//linked list
Tiket* headTiket = NULL;

//Queue 
queue<Tiket*> antreanBayar;

//Fungsi Menampilkan Jadwal Tranportasi Berdasarkan Tujuan atau Waktu Keberangkatan
void menampilkanJadwal(Transportasi data[], int jumlahData){
	int jawab, jumlahDitemukan;
	string tujuan, waktu;
	
	cout << "Mencari berdasarkan:" << endl;
	cout << "1. Tujuan" << endl;
	cout << "2. Waktu Keberangkatan" << endl;
	cout << "Masukkan Pilihan Anda: ";
	cin >> jawab;
	
	if (jawab == 1){
		cout << "Sebutkan Tujuan: ";
		cin.ignore();
		getline(cin, tujuan);
	    	 
	    // Header Table
		cout << left;
		cout << string(76, '-') << endl;
		cout << "|" << setw(10) << "ID Jadwal"
			 << "|" << setw(20) << "Jenis Transportasi"
		     << "|" << setw(15) << "Tujuan"
		     << "|" << setw(15) << "Waktu Berangkat" 
		     << "|" << setw(10) << "Kapasitas" << "|" << endl;
		cout << string(76, '-') << endl;
		
		for(int i=0; i<jumlahData; i++){
			if(data[i].tujuan == tujuan){		 
				// Data Tabel
				cout << "|" << setw(10) << data[i].id_jadwal
					 << "|" << setw(20) << data[i].jenis_transportasi
		         	 << "|" << setw(15) << data[i].tujuan
		         	 << "|" << setw(15) << data[i].waktu_berangkat
		        	 << "|" << setw(10) << data[i].kapasitas << "|" << endl;
		        // Footer Tabel
				cout << string(76, '-') << endl;
		        jumlahDitemukan++;
			}
		}
		
		if(jumlahDitemukan == 0){
			cout << "Jadwal Transportasi dengan Tujuan yang Anda Inginkan Tidak Ada" << endl;
		}
		
		
		cout << "\nTekan Enter Untuk Kembali ke Menu Utama...";
		cin.get();
		system("CLS");
	} else if (jawab == 2){
		cout << "Sebutkan Waktu Keberangkatan: ";
		cin.ignore();
		getline(cin, waktu);
		
		// Header Table
		cout << left;
		cout << string(76, '-') << endl;
		cout << "|" << setw(10) << "ID Jadwal"
			 << "|" << setw(20) << "Jenis Transportasi"
		     << "|" << setw(15) << "Tujuan"
		     << "|" << setw(15) << "Waktu Berangkat" 
		     << "|" << setw(10) << "Kapasitas" << "|" << endl;
		cout << string(76, '-') << endl;
		
		for(int i=0; i<jumlahData; i++){
			if(data[i].waktu_berangkat == waktu){
				// Data Tabel
				cout << "|" << setw(10) << data[i].id_jadwal
					 << "|" << setw(20) << data[i].jenis_transportasi
		         	 << "|" << setw(15) << data[i].tujuan
		         	 << "|" << setw(15) << data[i].waktu_berangkat
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
	} else {
		cout << "Pilihan Tidak Valid!\n\n";
	}
}

void pesanTiket(Transportasi data[], int jumlahData){
	//Variabel
	int id_pemesanan, id_jadwal, jml_kursi;
	string nama;
	
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
	            cout << "Pemesanan berhasil!" << endl;
	        } else {
	            cout << "Kapasitas tidak mencukupi. Pemesanan gagal." << endl;
	        }
		}
    }

    // Menyimpan ke linked list
    Tiket* tiket = new Tiket;
    tiket->id_pemesanan = id_pemesanan;
    tiket->nama = nama;
    tiket->id_jadwal = id_jadwal;
    tiket->jml_kursi = jml_kursi;
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
    
    cout << "\nTekan Enter Untuk Kembali ke Menu Utama...";
    cin.ignore();
	cin.get();
	system("CLS");
}

void pembayaranTiket(Transportasi data[], int jumlahData){
	Tiket* temp = headTiket;
	int id_pemesanan;
	bool ditemukan = false, belumBayar = false;
	
	cout << "-------------------------------------------------------------------------------------------------" << endl;
	cout << "|" << setw(15) << "ID Pemesanan"
		 << "|" << setw(10) << "Nama"
		 << "|" << setw(20) << "Jenis Transportasi"
		 << "|" << setw(15) << "Tujuan"
		 << "|" << setw(15) << "Jumlah Kursi"
		 << "|" << setw(15) << "Status" << "|" << endl;
	cout << "-------------------------------------------------------------------------------------------------" << endl;
	
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
				 << "|" << setw(15) << temp->id_jadwal
				 << "|" << setw(15) << temp->status << "|" << endl;
			cout << "-------------------------------------------------------------------------------------------------" << endl;	
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
				cout << "Pemesanan Berhasil Dibayar" << endl;
				
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

int main(){
	// Data Jadwal Transportasi
	int jumlahDataTransportasi = 6;
	Transportasi dataTransportasi[jumlahDataTransportasi] = {
	    {101, "Bus", "Bandung", "08:00", 10},
	    {102, "Kereta", "Yogyakarta", "12:30", 300},
	    {103, "Pesawat", "Jakarta", "17:45", 150},
	    {104, "Bus", "Semarang", "06:15", 45},
	    {105, "Kereta", "Surabaya", "10:00", 350},
	    {106, "Pesawat", "Lombok", "14:20", 180}
	};
	int pilihan;
	
	do{
		//Menu Utama
		cout << "=== Menu Utama ===" << endl;
		cout << "1. Menampilkan Daftar Jadwal Transportasi" << endl;
		cout << "2. Pemesanan Tiket" << endl;
		cout << "3. Pembayaran Tiket" << endl;
		cout << "4. Pencarian Pemesanan Tiket" << endl;
		cout << "5. Daftar Pemesanan Seluruh Tiket" << endl;
		cout << "6. Pembatalan Pemesanan Tiket" << endl;
		cout << "0. Keluar" << endl;
		cout << "Masukkan Pilihan Anda: ";
		cin >> pilihan;
		
		switch(pilihan){
			case 1:
				system("CLS");
				menampilkanJadwal(dataTransportasi, jumlahDataTransportasi);
				break;
			case 2:
				system("CLS");
				pesanTiket(dataTransportasi, jumlahDataTransportasi);
				break;
			case 3:
				system("CLS");
				pembayaranTiket(dataTransportasi, jumlahDataTransportasi);
				break;
//			case 4:
//				break;
//			case 5:
//				break;
//			case 6:
//				break;
			case 0:
				cout << "Keluar dari Program. Terima Kasih!";
				break;
			default:
				cout << "Pilihan tidak valid. Silakan coba lagi!";
		}
	} while(pilihan != 0);
	
	return 0;
}
