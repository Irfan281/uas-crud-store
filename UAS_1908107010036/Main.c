/*
    Nama : Muhammad Irfan
    NIM : 1908107010036
    Deskripsi : UAS LAB PEMOGRAMAN - Program Crud Sistem Informasi Swalayan
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//Deklarasi Struct
typedef struct {
    char id[100];
    char nama[200];
    char distributor[200];
    char stok[10];
} data;
data barang;
FILE *fp;

//prototype
void login();
void tampil_data();
void tambah_data();
void cari_data();
void hapus_data();
void ubah_data();
void ubah_data_login();
int hitung_baris();

//Fungsi Utama
int main () {
    login();
    
    //Buka File
    fp = fopen("./data/data.txt", "a+");

    //Menu
    int pilihan;
    printf("========= SELAMAT DATANG ADMIN ===========\n");
    while (1){
        printf("MENU: \n");
        printf("1. Tampilkan Data Barang.\n");
        printf("2. Cari Data Barang.\n");
        printf("3. Tambah Data Barang.\n");
        printf("4. Hapus Data Barang.\n");
        printf("5. Ubah Data Barang.\n");
        printf("6. Ubah Username dan Password Login Admin.\n");
        printf("7. Keluar\n");
        printf("Pilihan : ");
        scanf("%d", &pilihan);
    
        switch (pilihan){
        case 1:
            printf("\nMENAMPILKAN DATA BARANG\n");
            tampil_data();
            printf("\n");
            break;
        case 2:
            printf("\nMENCARI DATA BARANG\n");
            cari_data();
            break;
        case 3:
            printf("\nMENAMBAH DATA BARANG\n");
            tambah_data();
            printf("\n");
            break;
        case 4:
            printf("\nMENGHAPUS DATA BARABG\n");
            hapus_data();
            printf("\n");
            break;
        case 5:
            printf("\nMENGUBAH DATA BARANG\n");
            ubah_data();
            printf("\n");
            break;
        case 6:
            printf("\nMENGUBAH USERNAME DAN PASSWORD\n");
            ubah_data_login();
            printf("========= SELAMAT DATANG ADMIN ===========\n");
            break;
        case 7:
            printf("\nKELUAR DARI PROGRAM\n");
            printf("\n");
            exit(1);
            break;
        default:
            printf("\nINPUT PILIHAN TIDAK TERSEDIA\n");
            printf("\n");
            break;
        }
    }
    fclose(fp);
    return 0;
}

//Fungsi untuk memulai login
void login () {
    char user[100], pass[100], binary_input[100], data_login[2][50];
    
    FILE *login = fopen("./data/login.bin", "rb");
    if (login == NULL){
        puts("error opening file !!");
    } else{
        fread(binary_input, sizeof(binary_input), 1, login);

        //Memisahkan Username dan Password dari File Binary
        int i=0;
        char *token = strtok(binary_input, "@");
        while (token != NULL){
            strcpy(data_login[i], token);
            i++;
            token = strtok(NULL, "@");
        }

        //input username dan passsword dari user
        printf("============ SELAMAT DATANG =============\n======== DI PORTAL DATA BARANG ==========\n========= SWALAYAN IRFAN SUKSES ===========\n");
        input_ulang:
        printf("LOGIN: \n");
        printf("Username: ");
        scanf(" %[^\n]s", user);
        printf("Pasword: ");
        scanf(" %[^\n]s", pass);

        //Informasi hasil login
        if ((strcmp(data_login[0], user) == 0) && (strcmp(data_login[1], pass) == 0)){ 
            printf("\nStatus : Login Berhasil !\n");
        } else{
            printf("\nUsername atau Password salah, silakan input kembali.\n");
            goto input_ulang;
        }    
    }
    fclose(login);
}

//Fungsi untuk menampilkan data tabel
void tampil_data(){
    fp = fopen("./data/data.txt", "a+");
    int baris=hitung_baris();

    //Proses mencetak ke layar
    //%[^,] berfungsi untuk melewaatkan tanda , dari file text
    printf("+----------------+--------------------------------+--------------------------------+------------+\n");
    fscanf(fp, "%[^,], %[^,], %[^,], %[^,\n]", barang.id, barang.nama, barang.distributor, barang.stok); 
    printf("|%-16s| %-30s | %-30s | %-10s |\n", barang.id, barang.nama, barang.distributor, barang.stok);
    printf("+----------------+--------------------------------+--------------------------------+------------+");
    for (int i = 1; i < baris; i++){
        fscanf(fp, "%[^,], %[^,], %[^,], %[^,\n]", barang.id, barang.nama, barang.distributor, barang.stok);
        barang.id[0] = '|';
        printf("\n");
        printf("%-17s| %-30s | %-30s | %-10s |",barang.id, barang.nama, barang.distributor, barang.stok);
    }  
    printf("\n+----------------+--------------------------------+--------------------------------+------------+\n");
    rewind(fp);
}

//Fungsi untuk menambah data
void tambah_data(){
    //Input data yang ingin ditambahkan
    printf("  Nama Barang%4s: ", ""); 
    scanf(" %[^\n]s", barang.nama);
    printf("  Id Barang%6s: ", "");
    scanf(" %[^\n]s", barang.id);
    printf("  Distributor%4s: ", "");
    scanf(" %[^\n]s", barang.distributor);
    printf("  Stok Barang%4s: ", "");
    scanf(" %[^\n]s", barang.stok);
    
    //Informasi hasil proses tambah data
    fprintf(fp, "\n%s, %s, %s, %s", barang.id, barang.nama, barang.distributor, barang.stok);
    printf("Status : Data Berhasil Ditambahkan.\n");
    rewind(fp);
    tampil_data();
}

//Fungsi untuk melakukan pencarian data
void cari_data(){
    char cari[100];
    char enter[100] = "\n";

    //Input untuk melakukan pencarian
    printf("Masukkan Id Barang untuk Mencari data.\n");
    printf("  Id Barang : ");
    scanf(" %[^\n]s", cari); 
    strcat(enter, cari);

    int baris = hitung_baris();
    int cek = 0;

    //Proses pencetakan dari id barang yang ingin dicari
    printf("+----------------+--------------------------------+--------------------------------+------------+\n");
    fscanf(fp, "%[^,], %[^,], %[^,], %[^,\n]", barang.id, barang.nama, barang.distributor, barang.stok);
    printf("|%-16s| %-30s | %-30s | %-10s |\n", barang.id, barang.nama, barang.distributor, barang.stok);
    printf("+----------------+--------------------------------+--------------------------------+------------+");
    for (int i = 1; i < baris; i++){
        fscanf(fp, "%[^,], %[^,], %[^,], %[^,\n]", barang.id, barang.nama, barang.distributor, barang.stok);
        if ((strcmp(barang.id, enter) == 0)){
            barang.id[0] = '|';
            printf("\n");
            printf("%-17s| %-30s | %-30s | %-10s |\n",barang.id, barang.nama, barang.distributor, barang.stok);
            cek = 0;
            break;
        } else{
            cek = 1;
        }
    }
    //Informasi jika data tidak dapat ditemukan
    if (cek){
        printf("\n|%62s%33s|", "Data Tidak Ditemukan !!", "");
        printf("\n");
    }
    printf("+----------------+--------------------------------+--------------------------------+------------+\n");
    rewind(fp);
}

//Fungsi untuk melakukan pengapusan suatu baris
void hapus_data(){
    char hapus_id[100], enter[100] = "\n";
    char input;
    int cek=0;

    //Input id barang yang barisnya ingin dihapus
    printf("Masukkan Id barang yang ingin dihapus.\n");
    printf("Id Barang : ");
    scanf(" %[^\n]s", hapus_id); 
    
    strcat(enter, hapus_id);
    printf("Yakin ingin menghapus baris data dari id barang %s? (y/n) :", hapus_id);
    scanf(" %c", &input); 

    if ((input == 'y') || input == 'Y'){
        FILE *simpan = fopen("./data/simpan.txt", "w");
        int baris = hitung_baris();
        
        //Informasi hasil proses penghapusan baris
        for (int i = 0; i < baris; i++){
            fscanf(fp, "%[^,], %[^,], %[^,], %[^,\n]", barang.id, barang.nama, barang.distributor, barang.stok);
            if (strcmp(barang.id, enter) != 0){
                fprintf(simpan, "%s, %s, %s, %s", barang.id, barang.nama, barang.distributor, barang.stok);
            }else{
                printf("Data berhasil dihapus !!\n");
                cek++;
            }
        }
        fclose(simpan);
        fclose(fp);
        remove("./data/data.txt");
        rename("./data/simpan.txt", "./data/data.txt");

        if (cek==0){
            printf("\nData Tidak Ditemukan...\n");
        } else{
            tampil_data();
        }
    }
}

//Fungsi untuk melakukan proses perubahan terhadap data
void ubah_data(){
    char ubah_id[100], enter[100] = "\n";
    char input[5];
    data ubah;

    //Mencari terlebih dahulu baris data mana yang ingin dirubah
    printf("Masukkan Id barang yang ingin diubah datanya.\n");
    printf("Id Barang : ");
    scanf(" %[^\n]s", ubah_id); 

    strcat(enter, ubah_id);

    int cek=0, baris = hitung_baris();
    FILE *simpan = fopen("./data/simpan.txt", "w");

    for (int i = 0; i < baris; i++){
        fscanf(fp, "%[^,], %[^,], %[^,], %[^,\n]", barang.id, barang.nama, barang.distributor, barang.stok);
        if (strcmp(barang.id, enter) == 0){
            cek = 1;
            //Input apa saja yang ingin dirubah
            printf("Apakah anda ingin mengubah Id Barang? (y/n): "); 
            scanf(" %c", &input[0]);
            if (input[0] == 'y' || input[0] == 'Y'){
                printf("   Masukkan Id Barang baru: "); 
                scanf(" %[^\n]s", ubah.id); 
            }

            printf("Apakah Anda ingin mengubah Nama? (y/n): "); 
            scanf(" %c", &input[1]);
            if (input[1] == 'y' || input[1] == 'Y'){
                printf("   Masukkan Nama Barang baru: "); 
                scanf(" %[^\n]s", ubah.nama);
            }

            printf("Apakah anda ingin mengubah Distributor? (y/n): "); 
            scanf(" %c", &input[2]);
            if (input[2] == 'y' || input[2] == 'Y'){
                printf("   Masukkan Nama Distributor baru: "); 
                scanf(" %[^\n]s", ubah.distributor);
            }

            printf("Apakah anda ingin mengubah stok barang? (y/n): "); 
            scanf(" %c", &input[3]);
            if (input[3] == 'y' || input[3] == 'Y'){
                printf("   Masukkan Stok Barang baru : "); 
                scanf(" %[^\n]s", ubah.stok);
            }

            if(input[0] == 'y' || input[0] == 'Y'){
                fprintf(simpan, "\n%s, ", ubah.id);
            }else{
                fprintf(simpan, "%s, ", barang.id);
            }

            if (input[1] == 'y' || input[1] == 'Y'){
                fprintf(simpan, "%s, ", ubah.nama);
            }else{
                fprintf(simpan, "%s, ", barang.nama);
            }

            if (input[2] == 'y' || input[2] == 'Y'){
                fprintf(simpan, "%s, ", ubah.distributor);
            }else{
                fprintf(simpan, "%s, ", barang.distributor);
            }

            if (input[3] == 'y' || input[3] == 'Y'){
                fprintf(simpan, "%s", ubah.stok);
            }else{
                fprintf(simpan, "%s", barang.id);
            }
        }else{
            fprintf(simpan, "%s, %s, %s, %s", barang.id, barang.nama, barang.distributor, barang.stok);
        } 
    }
    fclose(simpan);
    fclose(fp);
    remove("./data/data.txt");
    rename("./data/simpan.txt", "./data/data.txt");

    //informasi hasil perubahan data
    if (cek != 1){
        printf("\nData Tidak Ditemukan...\n");
    } else{
        printf("Status: Data Berhasil diubah\n");
        tampil_data();
    }

}

//Fungsi untuk merubah username dan password login admin
void ubah_data_login(){
    char us_baru[100], pass_baru[100];

    //input username dan password baru
    FILE *ubah_login = fopen("./data/login.bin", "wb");
    printf("Masukkan Username Baru : ");
    scanf(" %[^\n]s", us_baru);
    printf("Masukkan Password Baru: ");
    scanf(" %[^\n]s", pass_baru);

    strcat(us_baru, "@");
    strcat(us_baru, pass_baru);

    fwrite(us_baru, sizeof(us_baru), 1, ubah_login);

    //Informasi jika proses berhasil dilakukan
    printf("\nUsername dan Password Berhasil Diubah !\nSilakan login kembali.\n\n");
    printf("Tekan Enter untuk melanjutkan ...\n");
    fflush(stdin);
    getchar();
    
    fclose(ubah_login);
    login();
}

//Fungsi untuk mengitung baris dari file teks yang ada
int hitung_baris() {
    int baris=0;
    char str[1000];
    while (fgets(str, 1000, fp) != NULL){
        baris++;
    }
    rewind(fp);
    return baris;    
}
