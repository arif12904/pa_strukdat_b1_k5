#include <iostream>
#include <cmath>

using namespace std;

struct travel
{
    string jenis_bus;
    string besar_muatan;
    int harga;
    int tanggal_pemesanan;
    int bulan_pemesanan;
    int tahun_pemesanan;
    int nomor_terakhir_pesanan = 0;
    travel *next;
};

struct pemesanan
{
    int nomor_pesanan;
    string nama_pemesan;
    string no_hp_pemesan;
    string jenis_bus;
    int harga;
    int total_tiket;
    int tanggal_pemesanan;
    int bulan_pemesanan;
    int tahun_pemesanan;
    int harga_total;
    pemesanan *next;
};

int jml_order = 0;
int jml_data = 0;
int idx_bus, idx_pemesanan, idx;

void shellSortByHargaBus(travel *&head) {
    if (head == nullptr || head->next == nullptr) return;

    // Menentukan jumlah node dalam linked list
    int n = 0;
    travel *temp = head;
    while (temp != nullptr) {
        n++;
        temp = temp->next;
    }

    // Memulai dengan gap yang besar dan kemudian memperkecilnya
    for (int gap = n / 2; gap > 0; gap /= 2) {
        travel *current = head;

        for (int i = 0; i < gap; i++) {
            // Untuk setiap gap, kita mulai dengan elemen di posisi `i`
            travel *innerCurrent = head;
            for (int j = 0; j < i; j++) {
                innerCurrent = innerCurrent->next;
            }

            while (innerCurrent != nullptr) {
                travel *gapNode = innerCurrent;

                // Mencari node berjarak `gap` dari `gapNode`
                for (int k = 0; k < gap && gapNode != nullptr; k++) {
                    gapNode = gapNode->next;
                }

                if (gapNode != nullptr && innerCurrent->harga > gapNode->harga) {
                    // Tukar seluruh data antar node jika diperlukan
                    swap(innerCurrent->jenis_bus, gapNode->jenis_bus);
                    swap(innerCurrent->besar_muatan, gapNode->besar_muatan);
                    swap(innerCurrent->harga, gapNode->harga);
                    swap(innerCurrent->tanggal_pemesanan, gapNode->tanggal_pemesanan);
                    swap(innerCurrent->bulan_pemesanan, gapNode->bulan_pemesanan);
                    swap(innerCurrent->tahun_pemesanan, gapNode->tahun_pemesanan);
                }

                innerCurrent = innerCurrent->next;
            }
        }
    }
}

pemesanan* getTail(pemesanan *cur) {
    while (cur != nullptr && cur->next != nullptr) {
        cur = cur->next;
    }
    return cur;
}


pemesanan* partition(pemesanan *head, pemesanan *end, pemesanan **newHead, pemesanan **newEnd, bool ascending) {
    pemesanan *pivot = end;
    pemesanan *prev = nullptr, *cur = head, *tail = pivot;

    while (cur != pivot) {
        if ((ascending && cur->nomor_pesanan < pivot->nomor_pesanan) || (!ascending && cur->nomor_pesanan > pivot->nomor_pesanan)) {
            if (*newHead == nullptr) *newHead = cur;
            prev = cur;
            cur = cur->next;
        } else {
            if (prev) prev->next = cur->next;
            pemesanan *tmp = cur->next;
            cur->next = nullptr;
            tail->next = cur;
            tail = cur;
            cur = tmp;
        }
    }

    if (*newHead == nullptr) *newHead = pivot;
    *newEnd = tail;
    return pivot;
}

pemesanan* quickSortRecur(pemesanan *head, pemesanan *end, bool ascending) {
    if (!head || head == end) return head;

    pemesanan *newHead = nullptr, *newEnd = nullptr;
    pemesanan *pivot = partition(head, end, &newHead, &newEnd, ascending);

    if (newHead != pivot) {
        pemesanan *tmp = newHead;
        while (tmp->next != pivot) tmp = tmp->next;
        tmp->next = nullptr;

        newHead = quickSortRecur(newHead, tmp, ascending);
        tmp = getTail(newHead);
        tmp->next = pivot;
    }
    pivot->next = quickSortRecur(pivot->next, newEnd, ascending);
    return newHead;
}

void quickSort_nomor_pesanan(pemesanan **headRef, bool ascending = true) {
    *headRef = quickSortRecur(*headRef, getTail(*headRef), ascending);
}

void lihat_data_bus(travel *&head)
{

    travel *temp = head;
    int nomor = 1;

    if (temp == nullptr)
    {
        cout << "" << endl;
        cout << "Data bus masih kosong." << endl;
        return;
    }

    cout << "" << endl;
    cout << " ------------------------------------------------------------------------------------- " << endl;
    cout << "|                   Berikut Jenis bus yang Available Beserta Harganya                 |" << endl;
    cout << " ------------------------------------------------------------------------------------- " << endl;
    cout << "|    Rute Kebarangkatan   |   Max Penumpang   |  Harga Tiket  | Tanggal Keberangkatan |" << endl;
    cout << " ------------------------------------------------------------------------------------- " << endl;
    while (temp != nullptr)
    {
        cout << "| " << nomor << ". " << temp->jenis_bus << " |     " << temp->besar_muatan << " orang" << "      | Rp. " << temp->harga << "    |       " << temp-> tanggal_pemesanan << "/" << temp->bulan_pemesanan << "/" << temp -> tahun_pemesanan << "       |" << endl;
        temp = temp->next;
        nomor++;
    }
    cout << " ------------------------------------------------------------------------------------- " << endl;
    cout << "" << endl;
}

int total_harga(int *harga_bus, int &jml_tiket)
{

    if (jml_tiket == 1)
    {
        return *harga_bus;
    }

    else
    {
        jml_tiket = jml_tiket - 1;
        return *harga_bus + total_harga(harga_bus, jml_tiket);
    }
}

void tampilkan_pesanan(pemesanan* order_baru) {
    cout << "------------------------------------------------------ " << endl;
    cout << "Nomor Tiket             : " << order_baru->nomor_pesanan << endl;
    cout << "------------------------------------------------------ " << endl;
    cout << "Nama Pemesan            : " << order_baru->nama_pemesan << endl;
    cout << "------------------------------------------------------ " << endl;
    cout << "Nomor Telepon           : " << order_baru->no_hp_pemesan << endl;
    cout << "------------------------------------------------------ " << endl;
    cout << "Bus                     : " << order_baru->jenis_bus << endl;
    cout << "------------------------------------------------------ " << endl;
    cout << "Tanggal Keberangkatan   : " << order_baru->tanggal_pemesanan << "/" << order_baru->bulan_pemesanan << "/" << order_baru->tahun_pemesanan << endl;
    cout << "------------------------------------------------------ " << endl;
    cout << "Harga Tiket             : " << order_baru->harga << endl;
    cout << "------------------------------------------------------ " << endl;
    cout << "Total Tiket             : " << order_baru->total_tiket << endl;
    cout << "------------------------------------------------------ " << endl;
    cout << "Total Harga             : " << order_baru->harga_total << endl;
    cout << "------------------------------------------------------ " << endl;

}

void tambah_data(travel *&head) // push untuk stack
{
    string jenis;
    string muatan;
    int hrga;
    int tgl;
    int bln;
    int thn;

    travel *baru = new travel;

    cin.ignore();
    cout << "" << endl;
    cout << "Masukkan Jenis Bus: ";
    fflush(stdin);
    getline(cin, jenis);
    cout << "Masukkan Muatan Maximal Bus (Berapa Orang) : ";
    fflush(stdin);
    getline(cin, muatan);
    cout << "Harga Tiket Bus: ";
    fflush(stdin);
    cin >> hrga;
    if(!cin.fail() && hrga > 0){
        cout << "Masukkan Tanggal keberangkatan: ";
        fflush(stdin);
        cin >> tgl;
        if(!cin.fail() && (tgl > 0 && tgl <= 31)){
            cout << "Masukkan Bulan Keberangkatan: ";
            fflush(stdin);
            cin >> bln;
            if(!cin.fail() && (bln > 0 && bln <=12)){
                cout << "Masukkan Tahun Keberangkatan: ";
                fflush(stdin);
                cin >> thn;
                if(!cin.fail() && thn > 0){
                    baru->jenis_bus = jenis;
                    baru->besar_muatan = muatan;
                    baru->harga = hrga;
                    baru->harga = hrga;
                    baru->tanggal_pemesanan = tgl;
                    baru->bulan_pemesanan = bln;
                    baru->tahun_pemesanan = thn;
                    baru->next = head;
                    head = baru;
                    jml_data++;
                    cout << "" << endl;
                } else{
                    cout << "Tahun harus berupa angka dan lebih besar dari 0" << endl;
                    cin.clear();
                    cin.ignore(1000,'\n');
                    return;
                }
            }else{
                cout << "Bulan harus berupa angka dan lebih besar dari 0 dan lebih kecil sama dengan 12" << endl;
                cin.clear();
                cin.ignore(1000,'\n');
                return;
            }
        }else{
            cout << "tanggal harus berupa angka dan lebih besar dari 0" << endl;
            cin.clear();
            cin.ignore(1000,'\n');
            return;
        }
    }else{
       cout << "harga harus berupa angka dan lebih besar dari 0" << endl;
       cin.clear();
       cin.ignore(1000,'\n');
       return; 
    }
}

void edit_data(travel *&head)
{
    string jenis;
    string muatan;
    int hrga;
    int tgl;
    int bln;
    int thn;

    travel *temp = head;

    if (head == nullptr)
    {
        cout << "" << endl;
        cout << "Data bus masih kosong." << endl;
        return;
    }

    cout << "" << endl;
    lihat_data_bus(head);
    cout << "Masukkan nomor_pesanan bus yang ingin diedit: " << endl;
    cin >> idx;

    for (int i = 1; i < idx; i++)
    {
        temp = temp->next;
    }

    cin.ignore();
    cout << "Masukkan Jenis Bus: ";
    fflush(stdin);
    getline(cin, jenis);
    cout << "Masukkan Muatan Maximal Bus (Berapa Orang) : ";
    fflush(stdin);
    getline(cin, muatan);
    cout << "Harga Tiket Bus: ";
    fflush(stdin);
    cin >> hrga;
    if(!cin.fail() && hrga > 0){
        cout << "Masukkan Tanggal keberangkatan: ";
        fflush(stdin);
        cin >> tgl;
        if(!cin.fail() && (tgl > 0 && tgl <= 31)){
            cout << "Masukkan Bulan Keberangkatan: ";
            fflush(stdin);
            cin >> bln;
            if(!cin.fail() && (bln > 0 && bln <=12)){
                cout << "Masukkan Tahun Keberangkatan: ";
                fflush(stdin);
                cin >> thn;
                if(!cin.fail() && thn > 0){
                    temp->jenis_bus = jenis;
                    temp->besar_muatan = muatan;
                    temp->harga = hrga;
                    temp->tanggal_pemesanan = tgl;
                    temp->bulan_pemesanan = bln;
                    temp->tahun_pemesanan = thn;

                    cout << "Data bus berhasil diedit." << endl;
                    cout << "" << endl;
                } else{
                    cout << "Tahun harus berupa angka dan lebih besar dari 0" << endl;
                    cin.clear();
                    cin.ignore(1000,'\n');
                    return;
                }
            }else{
                cout << "Bulan harus berupa angka dan lebih besar dari 0 dan lebih kecil sama dengan 12" << endl;
                cin.clear();
                cin.ignore(1000,'\n');
                return;
            }
        }else{
            cout << "tanggal harus berupa angka dan lebih besar dari 0" << endl;
            cin.clear();
            cin.ignore(1000,'\n');
            return;
        }
    }else{
       cout << "harga harus berupa angka dan lebih besar dari 0" << endl;
        cin.clear();
        cin.ignore(1000,'\n');
        return; 
    }
}

void pop_data(travel *&head) // pop untuk stack
{
    if (head == nullptr) {
        cout << "Data bus masih kosong." << endl;
        return;
    }
    if (head->next == nullptr) {
        delete head;
        head = nullptr;
    } else {
        travel* temp = head;
        while (temp->next->next != nullptr) {
            temp = temp->next;
        }
        delete temp->next;
        temp->next = nullptr;
    }

    cout << "Data bus berhasil dihapus." << endl;
}

void lihat_orderan(pemesanan *HEAD)
{
    quickSort_nomor_pesanan(&HEAD);

    int total;
    pemesanan *temp = HEAD;

    if (HEAD == nullptr)
    {
        cout << "Data orderan masih kosong." << endl;
        return;
    }

    cout << "Berikut List Orderan Tiket Bus" << "\n"
         << endl;
    while(temp!=nullptr){
        tampilkan_pesanan(temp);
        cout << "" << endl;
        temp = temp->next;
    }
}
    

void pemesanan_bus(pemesanan *&HEAD, travel *head) // Enqueue untuk Queue
{
    string nama, no_telp;
    int tiket, harga_bus, hasil, pilih2, ttl_tiket;

    cout << "" << endl;
    lihat_data_bus(head);
    cout << "0. Keluar" << endl;
    cout << "Masukkan Jenis Bus yang Ingin Dipilih: ";
    cin >> pilih2;

    if (pilih2 == 0)
    {
        cout << "Keluar dari menu pemesanan." << endl;
        return;
    }

    pemesanan *order_baru = new pemesanan;
    travel *temp = head;

    for (int i = 1; i < pilih2; i++)
    {
        if (temp != nullptr)
        {
            temp = temp->next;
        }
    }

    if (pilih2 <= jml_data && temp != nullptr)
    {
        cin.ignore();
        cout << "Masukkan Nama Pemesan: ";
        getline(cin, nama);
        cout << "Masukkan Nomor Telepon Pemesan: ";
        getline(cin, no_telp);
        cout << "Masukkan Jumlah Tiket yang Ingin Dibeli: ";
        cin >> tiket;
        ttl_tiket = tiket;
        temp->nomor_terakhir_pesanan += 1;
        jml_order++;
        int nomor_pesanan = temp->nomor_terakhir_pesanan;

        order_baru->total_tiket = ttl_tiket;
        order_baru->nomor_pesanan = jml_order;
        order_baru->nama_pemesan = nama;
        order_baru->no_hp_pemesan = no_telp;
        harga_bus = temp->harga;
        hasil = total_harga(&harga_bus, ttl_tiket);
        order_baru->harga_total = hasil;
        order_baru->jenis_bus = temp->jenis_bus;
        order_baru->harga = temp->harga;
        order_baru->tanggal_pemesanan = temp->tanggal_pemesanan;
        order_baru->bulan_pemesanan = temp->bulan_pemesanan;
        order_baru->tahun_pemesanan = temp->tahun_pemesanan;
        
        cout << "\nBerikut Pesanan Anda: " << endl;
        tampilkan_pesanan(order_baru);
        cout << "Terima Kasih Telah Memesan!" << endl;


        if (HEAD == nullptr)
        {
            HEAD = order_baru;
        }
        else
        {
            pemesanan *temp_order = HEAD;
            while (temp_order->next != nullptr)
            {
                temp_order = temp_order->next;
            }
            temp_order->next = order_baru;
        }

        order_baru->next = nullptr;
    }
    else
    {
        cout << "Pilihan tidak valid!" << endl;
    }

}

int getListLength(pemesanan *HEAD) {
    int length = 0;
    while (HEAD != nullptr) {
        length++;
        HEAD = HEAD->next;
    }
    return length;
}

pemesanan* getNodeAt(pemesanan *HEAD, int k) {
    int count = 0;
    while (HEAD != nullptr && count < k) {
        HEAD = HEAD->next;
        count++;
    }
    return HEAD;
}

pemesanan* fibonacciSearch(pemesanan *HEAD, int nomor_pesanan) {
    int n = getListLength(HEAD);
    int fibMMm2 = 0;
    int fibMMm1 = 1;
    int fibM = fibMMm2 + fibMMm1;

    while (fibM < n) {
        fibMMm2 = fibMMm1;
        fibMMm1 = fibM;
        fibM = fibMMm2 + fibMMm1;
    }

    int offset = -1;

    while (fibM > 1) {
        int i = min(offset + fibMMm2, n - 1);
        pemesanan* node = getNodeAt(HEAD, i);

        if (node == nullptr) break;

        if (node->nomor_pesanan < nomor_pesanan) {
            fibM = fibMMm1;
            fibMMm1 = fibMMm2;
            fibMMm2 = fibM - fibMMm1;
            offset = i;
            HEAD = node->next;
        }
        else if (node->nomor_pesanan > nomor_pesanan) {
            fibM = fibMMm2;
            fibMMm1 = fibMMm1 - fibMMm2;
            fibMMm2 = fibM - fibMMm1;
        }
        else {
            return node;
        }
    }

    if (offset + 1 < n && HEAD != nullptr && HEAD->nomor_pesanan == nomor_pesanan) {
        return HEAD;
    }

    return nullptr;
}

void CariOrderandariNomor(pemesanan* HEAD) { // Searching Berdasarkan Nomor Tiket

    quickSort_nomor_pesanan(&HEAD);

    int cariNomorPesanan;
    cout << "Masukkan nomor tiket untuk mencari informasi: ";
    cin >> cariNomorPesanan;
    if(!cin.fail() && cariNomorPesanan > 0){
        pemesanan* hasil = fibonacciSearch(HEAD, cariNomorPesanan);
        if (hasil) {
            cout << "Pesanan ditemukan: " << endl;
            tampilkan_pesanan(hasil);
        } else {
            cout << "Pesanan tidak ditemukan." << endl;
        }
    }else{
        cout << "Bulan harus berupa angka dan lebih besar dari 0" << endl;
        cin.clear();
        cin.ignore(1000,'\n');
        return;
    }


}


void boyer_moore_search(pemesanan* HEAD, const string& pattern) {
    int m = pattern.length();
    pemesanan* temp = HEAD;
    int index = 1;
    bool found = false;

    while (temp != nullptr) {
        int n = temp->nama_pemesan.length();
        int i = m - 1;
        int j = n - 1;

        while (i >= 0 && j >= 0 && pattern[i] == temp->nama_pemesan[j]) {
            i--;
            j--;
        }

        if (i == -1) {
            found = true;
            tampilkan_pesanan(temp);
        }

        temp = temp->next;
        index++;
    }

    if (!found) {
        cout << "Pemesanan dengan nama tersebut tidak ditemukan!" << endl;
    }
}

void menu_pencarian(pemesanan* HEAD) { // Search berdasarkan Nama Pemesan
    string nama_dipilih;
    cout << "Masukkan Nama Pemesan untuk Menampilkan Informasi: ";
    cin.ignore();
    getline(cin, nama_dipilih);

    boyer_moore_search(HEAD, nama_dipilih);
}

void inputTanggal(int &tanggal, int &bulan, int &tahun) {
    cout << "Masukkan tanggal keberangkatan: ";
    cin >> tanggal;
    if(!cin.fail() && tanggal > 0){
        cout << "Masukkan bulan keberangkatan: ";
        cin >> bulan;
        if(!cin.fail() && bulan > 0){
            cout << "Masukkan tahun keberangkatan: ";
            cin >> tahun;
            if(cin.fail() || tahun < 0){
                cout << "Tahun harus berupa angka dan lebih besar dari 0" << endl;
                cin.clear();
                cin.ignore(1000,'\n');
                return;
            }
        }else{
            cout << "Bulan harus berupa angka dan lebih besar dari 0" << endl;
            cin.clear();
            cin.ignore(1000,'\n');
            return;
        }
    }else{
        cout << "tanggal harus berupa angka dan lebih besar dari 0" << endl;
        cin.clear();
        cin.ignore(1000,'\n');
        return;
    }
}

void jumpSearchByTanggal(pemesanan* HEAD, int tanggal, int bulan, int tahun) { // Seacrhing berdasarkan tanggal keberangkatan
    if (HEAD == nullptr) {
        cout << "Data tidak ditemukan." << endl;
        return;
    }

    int n = 0;
    pemesanan* temp = HEAD;
    while (temp != nullptr) {
        n++;
        temp = temp->next;
    }

    int step = sqrt(n);
    pemesanan* prev = nullptr;
    pemesanan* current = HEAD;

    while (current != nullptr && current->tanggal_pemesanan < tanggal) {
        prev = current;
        for (int i = 0; i < step && current != nullptr; i++) {
            if (current->tanggal_pemesanan == tanggal && current->bulan_pemesanan == bulan && current->tahun_pemesanan == tahun) {
                tampilkan_pesanan(current);
                return;
            }
            current = current->next;
        }
    }

    while (current != nullptr) {
        if (current->tanggal_pemesanan == tanggal && current->bulan_pemesanan == bulan && current->tahun_pemesanan == tahun) {
            cout << "" << endl;
            cout << "Pesanan ditemukan. " << endl;
            tampilkan_pesanan(current);
            return;
        }
        current = current->next;
    }

    cout << "Data tidak ditemukan untuk tanggal yang dicari." << endl;
}



void menu_admin(travel *&head, pemesanan *&HEAD)
{
    string pilihan;

    while (pilihan != "7")
    {
        cout << "" << endl;
        cout << "1. Lihat Data Bus" << endl;
        cout << "2. Tambah Data" << endl;
        cout << "3. Hapus Data" << endl;
        cout << "4. Edit Data" << endl;
        cout << "5. Lihat Orderan" << endl;
        cout << "6. Cari Orderan Berdasarkan Tanggal Keberangkatan" << endl;
        cout << "7. Keluar" << endl;
        cout << "Masukkan pilihan anda: " << endl;
        cout << "" << endl;
        cin >> pilihan;

        if (pilihan == "1")
        {
            shellSortByHargaBus(head);
            lihat_data_bus(head);
            cout << "" << endl;
            system("Pause");
        }
        else if (pilihan == "2")
        {
            tambah_data(head);
            cout << "" << endl;
            system("Pause");
        }
        else if (pilihan == "3")
        {
            pop_data(head);
            cout << "" << endl;
            system("Pause");
        }
        else if (pilihan == "4")
        {
            edit_data(head);
            cout << "" << endl;
            system("Pause");
        }
        else if (pilihan == "5")
        {
            lihat_orderan(HEAD);
            cout << "" << endl;
            system("Pause");
        }
        else if (pilihan == "6")
        {
            int tanggal, bulan, tahun;
            inputTanggal(tanggal, bulan, tahun);
            jumpSearchByTanggal(HEAD, tanggal, bulan, tahun);
            cout << "" << endl;
            system("Pause");
        }

        else if (pilihan == "7")
        {
            cout << "Anda telah keluar dari menu admin." << endl;
        }
        else
        {
            cout << "Pilihan anda salah" << endl;
        }
    }
}



void menu_pemesan(travel *&head, pemesanan *&HEAD)
{

    string pilihan;

    while (pilihan != "5")
    {
        cout << "" << endl;
        cout << "1. Lihat List Harga" << endl;
        cout << "2. Buat Pesanan" << endl;
        cout << "3. Cari Informasi Orderan Berdasarkan Nomor Tiket" << endl;
        cout << "4. Cari Informasi Orderan Berdasarkan Nama" << endl;
        cout << "5. Keluar" << endl;
        cout << "Masukkan pilihan anda: " << endl;
        cin >> pilihan;

        if (pilihan == "1")
        {
            lihat_data_bus(head);
            cout << "" << endl;
            system("Pause");
        }
        else if (pilihan == "2")
        {
            pemesanan_bus(HEAD, head);
            cout << "" << endl;
            system("Pause");
        }
        else if (pilihan == "3")
        {
            CariOrderandariNomor(HEAD);
            cout << "" << endl;
            system("Pause");
        }
        else if (pilihan == "4")
        {
            menu_pencarian(HEAD);
            cout << "" << endl;
            system("Pause");
        }
        else if (pilihan == "5")
        {
            cout << "" << endl;
        }
        else
        {
            cout << "Pilihan anda salah" << endl;
        }
    }
}

int main()
{
    travel *head = nullptr;
    pemesanan *HEAD = nullptr;

    string pilihan;

    while (pilihan != "3")
    {
        cout << "" << endl;
        cout << "1. Admin" << endl;
        cout << "2. Pengguna" << endl;
        cout << "3. Keluar" << endl;
        cout << "Masukkan pilihan anda: " << endl;
        cin >> pilihan;
        fflush(stdin);
        cout << "" << endl;

        if (pilihan == "1")
        {
            cin.ignore();
            int coba;
            coba = 0;
            while (coba < 3)
            {
                string pass;
                cout << "Masukkan Password: " << endl;
                getline(cin, pass);

                if (pass == "admin")
                {
                    cout << "" << endl;
                    cout << "Berhasil Login!!" << endl;
                    menu_admin(head, HEAD);
                    break;
                }
                else
                {
                    cout << "Password anda salah" << endl;
                }
                if (coba == 2)
                {
                    cout << "Percobaan mencapai batas maksimal. Coba lagi nanti." << endl;
                    return 0;
                }
                coba++;
            }
        }
        else if (pilihan == "2")
        {
            menu_pemesan(head, HEAD);
        }
        else if (pilihan == "3")
        {
            cout << "Anda memilih Keluar" << endl;
            return 0;
        }
        else
        {
            cout << "Pilihan anda tidak tersedia" << endl;
        }
    }
}