#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <unistd.h>
#include <windows.h>

char cari[50];
struct data {
	char judul[20];
	char sutradara[50];
	char tahun[10];
};
data maks[50];
data pencarian[50];
int a, b, c, d;

void tambahdata() {
	system("cls");
	printf("\t\t\t\t\t\tMENU TAMBAH DATA\n\n");
	printf("Masukkan Jumlah Data Yang Akan diinput : ");
	scanf("%i", &b);
	printf("\nUntuk Bagian NPM pada Data kedua dan seterusnya tambahkan Spasi Terlebih Dahulu!\n");
	printf("Format Tanggal : dd-mm-yyyy\n");
	d = 0;
	for(c = 0; c < b; c++) {
		d = d+1;
		printf("\nData ke - %d\n", d);
		printf("Judul Film\t\t:");
		getchar();
		gets(maks[a].judul);
		printf("Sutradara\t\t: ");
		gets(maks[a].sutradara);
		printf("Tahun Terbit\t\t: ");
		gets(maks[a].tahun);
		a++;
	}
}

void tampildata() {
	int i, j;
	j = 0;
	system("cls");
	printf("\t\t\t\t\t\tMENU TAMPILKAN DATA\n\n");
	for (i = 0; i < a; i++) {
		j = j + 1;
		printf(" Data Film Ke - %i\n",j);
		printf(" ------------------------------------\n");
		printf(" Judul Film\t\t: %s\n",maks[i].judul);
		printf(" Sutradara\t\t: %s\n",maks[i].sutradara);
		printf(" Tahun Terbit\t\t: %s\n",maks[i].tahun);
		printf("\n");
	}
	printf(" \nTekan ENTER Untuk Kembali Ke Menu Sebelumnya.\n");
}

void ubahdata() {
	int k, l;
	system("cls");
	printf("\t\t\t\t\t\tMENU EDIT DATA\n\n");
	printf("Masukan Nomor Data yang akan diedit : ");
	scanf("%i", &k);
	l = k-1;
	printf("\nMasukkan Data Baru. \n");
	printf("Judul Film\t\t:");
	getchar();
	gets(maks[l].judul);
	printf("Sutradara\t\t: ");
	gets(maks[l].sutradara);
	printf("Tahun Terbit\t\t: ");
	gets(maks[l].tahun);
	printf("\nData Ke - %i Telah Berhasil Diubah!\n", k);
	printf("\nSilahkan Klik Menu Tampilkan Data Untuk Melihat Hasilnya.\n");
	printf("\nTekan ENTER Untuk Kembali Ke Menu Sebelumnya.\n");
}

void hapusdata() {
	int i, x, y;
	system("cls");
	printf("\t\t\t\t\t\tMENU HAPUS DATA\n\n");
	printf("Masukkan Nomor Data Yang Ingin Dihapus : ");
	scanf("%i", &x);
	y = x-1;
	a--;
	for(i = y; i < a; i++) {
		maks[i] = maks[i+1];
	}
	printf("\nData ke - %d Telah Terhapus!\n", x);
	printf("\nTekan ENTER Untuk Kembali Ke Menu Sebelumnya.\n");
}

int main(int argc, char *argv[]) {
	do {
		system("cls");
		printf("MENU UTAMA\n");
	    puts("\n Pilih Menu dibawah ini untuk menjalankan aplikasi");
	    puts("  1.  Tambah Data");
	    puts("  2.  Tampilkan Data");
	    puts("  3.  Ubah Data");
	    puts("  4.  Hapus Data");
	    puts(" Esc. Exit\n");
	    switch(getch()){
	        case '1' : tambahdata();
	        break;
	        case '2' : tampildata();
	        break;
	        case '3' : ubahdata();
	        break;
	        case '4' : hapusdata();
	        break;
	    }
	}
	while(getch()!=27);
    return 0;
}


