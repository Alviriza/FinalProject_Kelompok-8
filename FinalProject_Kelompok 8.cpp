#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <unistd.h>
#include <windows.h>

typedef struct datafilm {
	char judul[30];
	char sutradara[20];
	char genre[15];
	char tanggal[15];
	char rating[5];
	char durasi[10];
}datafilm;

struct pertanyaan {
	char teks[100];
};
pertanyaan jumlah[10] = {
							{"Apakah film ini sesuai ekspetasi anda?"},
							{"Apakah alur cerita film ini menyenangkan?"},
							{"Apakah anda akan merekomendasikan film ini?"},
							{"Seberapa mengerti anda tentang alur cerita film tersebut?"},
							{"Berikan penilaian untuk pemeran dari film tersebut?"},
							{"Bagaimana Akting para aktor dalam film tersebut?"},
							{"Bagaimana menurut anda nilai estetika di film tersebut?"},
							{"Seberapa besar pesan yang disampaikan oleh film tersebut?"},
							{"Bagaimana pemilihan tempat untuk latar film ini?"},
							{"Apakah film ini termasuk kedalam film favorit anda?"},
						};
						
typedef struct penilaian {
	char judulnilai[30];
	char penilai[30];
	char pekerjaan[20];
	struct menilai {
		int nilai;
	}menilai[10];
	int total;
	float rata;
}penilaian;

void delay() {
	int delay;
	delay=1;
	while(delay<100000000) {
		delay++;
	}
}

void loadscr() {
	int i;
	char load[] = {'L','O','A','D','I','N','G'};
	for(i=0; i<=6; i++) {
		printf("%c\t", load[i]);
		delay();
	}
	sleep(2);
}

void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void garis(int x) {
	int z;
	for(z = 0; z < x; z++) {
		printf("=");
	}
	printf("\n");
}

void header(char nama[50], char npm[50], char kelas[10], 
			char matkul[50], char dosen[50]) 
{
	gotoxy(60,1);
	printf("Re - Vie");
	gotoxy(44,2);
	printf("Nilai Film Kesukaanmu Disini!\n");
	garis(120);
	gotoxy(40,4);
	printf("Nama\t\t: %s\n", nama);
	gotoxy(40,5);
	printf("NPM\t\t: %s\n", npm);
	gotoxy(40,6);
	printf("Kelas\t\t: %s\n", kelas);
	gotoxy(40,7);
	printf("Matkul\t\t: %s\n", matkul);
	gotoxy(40,8);
	printf("Dosen Pengampu\t: %s\n", dosen);
}

void tambahdata() {
	datafilm *d;
	FILE *fp;
	int n, i, j;
	system("cls");
	printf("\t\t\t\t\t\tMENU TAMBAH DATA\n\n");
	printf (" Masukkan Jumlah Data Film Yang Akan diinput : ");
	scanf ("%d", &n);
	
	d = (datafilm*) calloc(n, sizeof(datafilm));
	fp = fopen ("datafilm.txt","a");
	
	for (i = 0; i < n; i++) {
		printf("\n Masukkan Data Film ke - %d\n", i+1);
		printf(" Judul Film\t\t: ");
		fflush(stdin);
		gets(d[i].judul);
		printf(" Sutradara\t\t: ");
		gets(d[i].sutradara);
		printf(" Genre\t\t\t: ");
		gets(d[i].genre);
		printf(" Tanggal Penerbitan\t: ");
		gets(d[i].tanggal);
		printf(" Rating Film\t\t: ");
		gets(d[i].rating);
		printf(" Durasi Film\t\t: ");
		gets(d[i].durasi);
		fwrite(&d[i], sizeof(datafilm),1,fp);
	}
	fclose (fp);
	printf(" \n\n Data Film Telah Disimpan.\n");
	printf(" Tekan ENTER Untuk Kembali Ke Menu Sebelumnya.\n");
}

void tambahnilai() {
	datafilm d1;
	penilaian n1;
	FILE *fp, *fp1;
	int i, j, ditemukan = 0;
	system("cls");
	printf("\t\t\t\t\t\tMENU TAMBAH PENILAIAN\n\n");
	fp = fopen ("datafilm.txt", "r");
	fp1 = fopen ("datapenilaian.txt", "a");
	fflush(stdin);
	printf(" Masukkan Nama Film Yang Ingin Dinilai : ");
	gets(n1.judulnilai);

	while (fread(&d1, sizeof(datafilm), 1, fp)) {
		if((strcmp (n1.judulnilai, d1.judul) == 0)) {
			n1.total = 0;
			n1.rata = 0;
			ditemukan = 1;
			printf("\n Nama Penilai\t\t: ");
			fflush(stdin);
			gets(n1.penilai);
			printf(" Pekerjaan\t\t: ");
			gets(n1.pekerjaan);
			printf("\n Berikan Nilai Dengan Skala 1-10!\n\n");
			for (j = 0; j < 10; j++) {
				printf (" %s\n", jumlah[j].teks);
				printf(" Jawaban Anda : ");
				fflush(stdin);
				scanf ("%i", &n1.menilai[j].nilai);
				n1.total += n1.menilai[j].nilai;
			}
			n1.rata = n1.total / 10.0;
			fwrite (&n1, sizeof (penilaian), 1, fp1);
		}	
	}
	if (!ditemukan) {
		printf("\n Data Film Tidak Ditemukan!\n");
		printf(" Tekan ENTER Untuk Kembali Ke Menu Sebelumnya.\n");
	} else {
		printf(" \n\n Data Film Telah Disimpan.\n");
		printf(" Tekan ENTER Untuk Kembali Ke Menu Sebelumnya.\n");
	}
	fclose(fp);
	fclose (fp1);
}

void tampildata() {
	datafilm d1;
	FILE *fp;
	int j = 0;
	system("cls");
	printf("\t\t\t\t\t\tMENU TAMPILKAN DATA\n\n");
	fp = fopen ("datafilm.txt", "r");
	while (fread(&d1, sizeof(datafilm),1,fp)) {
		printf(" Data Film Ke - %i\n",j+1);
		printf(" ------------------------------------\n");
		printf(" Judul Film\t\t: %s\n",d1.judul);
		printf(" Sutradara\t\t: %s\n",d1.sutradara);
		printf(" Genre\t\t\t: %s\n",d1.genre);
		printf(" Tanggal Penerbitan\t: %s\n",d1.tanggal);
		printf(" Rating Film\t\t: %s\n",d1.rating);
		printf(" Durasi Film\t\t: %s\n",d1.durasi);
		printf("\n");
		j++;
	}
	fclose(fp);
	printf(" \n Tekan ENTER Untuk Kembali Ke Menu Sebelumnya.\n");
}

void tampilnilai() {
	penilaian n1;
	FILE *fp;
	int j = 0;
	system("cls");
	printf("\t\t\t\t\t\tMENU TAMPILKAN DATA\n\n");
	fp = fopen ("datapenilaian.txt", "r");
	while (fread(&n1, sizeof(penilaian),1,fp)) {
		printf(" Data Penilaian Ke - %i\n",j+1);
		printf(" ------------------------------------\n");
		printf(" Film Yang Dinilai\t: %s\n",n1.judulnilai);
		printf(" Nama Penilai\t\t: %s\n",n1.penilai);
		printf(" Pekerjaan\t\t: %s\n",n1.pekerjaan);
		printf(" Nilai\t\t\t: %.2f\n",n1.rata);
		printf("\n");
		j++;
	}
	fclose(fp);
	printf(" \n Tekan ENTER Untuk Kembali Ke Menu Sebelumnya.\n");
}

void ubahdata() {
	datafilm d1;
	FILE *fp, *fp1;
	int ditemukan = 0;
	char judul[50];
	system("cls");
	printf("\t\t\t\t\t\tMENU EDIT DATA\n\n");
	fp = fopen ("datafilm.txt", "r");
	fp1 = fopen ("sementara.txt", "w");
	printf(" Masukkan Nama Film Yang Ingin Diubah : ");
	gets(judul);
	while (fread(&d1, sizeof(datafilm), 1, fp)) {
		if((strcmp (judul, d1.judul) == 0)) {
			ditemukan = 1;
			printf("\n Masukkan Data Film Baru \n");
			printf(" Judul Film\t\t: ");
			fflush(stdin);
			gets(d1.judul);
			printf(" Sutradara\t\t: ");
			gets(d1.sutradara);
			printf(" Genre\t\t\t: ");
			gets(d1.genre);
			printf(" Tanggal Penerbitan\t: ");
			gets(d1.tanggal);
			printf(" Rating Film\t\t: ");
			gets(d1.rating);
			printf(" Durasi Film\t\t: ");
			gets(d1.durasi);
		}
		fwrite (&d1, sizeof (datafilm), 1, fp1);
	}
	fclose(fp);
	fclose(fp1);
	if (ditemukan) {
		fp1 = fopen ("sementara.txt", "r");
		fp = fopen ("datafilm.txt", "w");
		while (fread(&d1, sizeof(datafilm), 1, fp1)) {
			fwrite (&d1, sizeof(datafilm), 1, fp);
		}
		printf("\n Data Film Telah Berhasil Diubah!\n");
		printf(" Silahkan Klik Menu Tampilkan Data Untuk Melihat Hasilnya.\n");
		printf(" Tekan ENTER Untuk Kembali Ke Menu Sebelumnya.\n");
		fclose(fp);
		fclose(fp1);
	} else {
		printf("\n Data Film Tidak Ditemukan!\n");
		printf(" Tekan ENTER Untuk Kembali Ke Menu Sebelumnya.\n");
	}
	fclose(fp);
}

void hapusdata() {
	datafilm d1;
	FILE *fp, *fp1;
	int ditemukan = 0;
	char judul[50];
	system("cls");
	printf("\t\t\t\t\t\tMENU HAPUS DATA\n\n");
	fp = fopen ("datafilm.txt", "r");
	fp1 = fopen ("sementara.txt", "w");
	printf(" Masukkan Nama Film Yang Ingin Dihapus : ");
	gets(judul);
	while (fread(&d1, sizeof(datafilm), 1, fp)) {
		if((strcmp (judul, d1.judul) == 0)) {
			ditemukan = 1;
		} else {
			fwrite (&d1, sizeof (datafilm), 1, fp1);
		}
	}
	fclose(fp);
	fclose(fp1);
	if (ditemukan) {
		fp1 = fopen ("sementara.txt", "r");
		fp = fopen ("datafilm.txt", "w");
		while (fread(&d1, sizeof(datafilm), 1, fp1)) {
			fwrite (&d1, sizeof(datafilm), 1, fp);
		}
		printf("\n Data Film Telah Dihapus!\n");
		printf(" Silahkan Klik Menu Tampilkan Data Untuk Melihat Hasilnya.\n");
		printf(" Tekan ENTER Untuk Kembali Ke Menu Sebelumnya.\n");
		fclose(fp);
		fclose(fp1);
	} else {
		printf("\n Data Film Tidak Ditemukan!\n");
		printf(" Tekan ENTER Untuk Kembali Ke Menu Sebelumnya.\n");
	}
	fclose(fp);
}

void hapuspenilaian() {
	penilaian n1;
	FILE *fp, *fp1;
	int ditemukan = 0;
	char penilai[50];
	system("cls");
	printf("\t\t\t\t\t\tMENU HAPUS PENILAIAN\n\n");
	fp = fopen ("datapenilaian.txt", "r");
	fp1 = fopen ("sementara.txt", "w");
	fflush(stdin);
	printf(" Masukkan Nama Penilai Dari Penilaian Yang Ingin Dihapus : ");
	gets(penilai);
	while (fread(&n1, sizeof(penilaian), 1, fp)) {
		if((strcmp (penilai, n1.penilai) == 0)) {
			ditemukan = 1;
		} else {
			fwrite (&n1, sizeof (penilaian), 1, fp1);
		}
	}
	fclose(fp);
	fclose(fp1);
	if (ditemukan) {
		fp1 = fopen ("sementara.txt", "r");
		fp = fopen ("datapenilaian.txt", "w");
		while (fread(&n1, sizeof(penilaian), 1, fp1)) {
			fwrite (&n1, sizeof(penilaian), 1, fp);
		}
		printf("\n Data Film Telah Dihapus!\n");
		printf(" Silahkan Klik Menu Tampilkan Data Untuk Melihat Hasilnya.\n");
		printf(" Tekan ENTER Untuk Kembali Ke Menu Sebelumnya.\n");
		fclose(fp);
		fclose(fp1);
	} else {
		printf("\n Data Film Tidak Ditemukan!\n");
		printf(" Tekan ENTER Untuk Kembali Ke Menu Sebelumnya.\n");
	}
	fclose(fp);
}

void tampilcari() {
	datafilm d1;
	FILE *fp;
	int j = 0;
	printf("\n\t\t\t\t\t\tHASIL PENCARIAN\n");
	fp = fopen ("sementara.txt", "r");
	while (fread(&d1, sizeof(datafilm),1,fp)) {
		printf(" Data Film Ke - %i\n",j+1);
		printf(" ------------------------------------\n");
		printf(" Judul Film\t\t: %s\n",d1.judul);
		printf(" Sutradara\t\t: %s\n",d1.sutradara);
		printf(" Genre\t\t\t: %s\n",d1.genre);
		printf(" Tanggal Penerbitan\t: %s\n",d1.tanggal);
		printf(" Rating Film\t\t: %s\n",d1.rating);
		printf(" Durasi Film\t\t: %s\n",d1.durasi);
		printf("\n");
		j++;
	}
	fclose(fp);
	printf(" \n Tekan ENTER Untuk Kembali Ke Menu Sebelumnya.\n");
}

void carijudul() {
	datafilm d1;
	FILE *fp, *fp1;
	int ditemukan = 0;
	char judul[50];
	system("cls");
	printf("\t\t\t\t\t\tMENU CARI FILM BERDASARKAN JUDUL\n\n");
	fp = fopen ("datafilm.txt", "r");
	fp1 = fopen ("sementara.txt", "w");
	printf(" Masukkan Nama Film Yang Ingin Dicari : ");
	gets(judul);
	while (fread(&d1, sizeof(datafilm), 1, fp)) {
		if((strcmp (judul, d1.judul) == 0)) {
			ditemukan = 1;
			fwrite (&d1, sizeof (datafilm), 1, fp1);
		}
	}
	fclose(fp1);
	if (ditemukan) {
		tampilcari();
	} else {
		printf("\n Data Film Tidak Ditemukan!\n");
		printf(" Tekan ENTER Untuk Kembali Ke Menu Sebelumnya.\n");
	}
	fclose(fp);
}

void carisutra() {
	datafilm d1;
	FILE *fp, *fp1;
	int ditemukan = 0;
	char sutra[50];
	system("cls");
	printf("\t\t\t\t\t\tMENU CARI FILM BERDASARKAN SUTRADARA\n\n");
	fp = fopen ("datafilm.txt", "r");
	fp1 = fopen ("sementara.txt", "w");
	printf(" Masukkan Nama Sutradara Film Yang Ingin Dicari : ");
	gets(sutra);
	while (fread(&d1, sizeof(datafilm), 1, fp)) {
		if((strcmp (sutra, d1.sutradara) == 0)) {
			ditemukan = 1;
			fwrite (&d1, sizeof (datafilm), 1, fp1);
		}
	}
	fclose(fp1);
	if (ditemukan) {
		tampilcari();
	} else {
		printf("\n Data Film Tidak Ditemukan!\n");
		printf(" Tekan ENTER Untuk Kembali Ke Menu Sebelumnya.\n");
	}
	fclose(fp);
}

void carigenre() {
	datafilm d1;
	FILE *fp, *fp1;
	int ditemukan = 0;
	char genre[50];
	system("cls");
	printf("\t\t\t\t\t\tMENU CARI FILM BERDASARKAN GENRE\n\n");
	fp = fopen ("datafilm.txt", "r");
	fp1 = fopen ("sementara.txt", "w");
	printf(" Masukkan Genre Film Yang Ingin Dicari : ");
	gets(genre);
	while (fread(&d1, sizeof(datafilm), 1, fp)) {
		if((strcmp (genre, d1.genre) == 0)) {
			ditemukan = 1;
			fwrite (&d1, sizeof (datafilm), 1, fp1);
		}
	}
	fclose(fp1);
	if (ditemukan) {
		tampilcari();
	} else {
		printf("\n Data Film Tidak Ditemukan!\n");
		printf(" Tekan ENTER Untuk Kembali Ke Menu Sebelumnya.\n");
	}
	fclose(fp);
}

void caritanggal() {
	datafilm d1;
	FILE *fp, *fp1;
	int ditemukan = 0;
	char tanggal[50];
	system("cls");
	printf("\t\t\t\t\t\tMENU CARI FILM BERDASARKAN TANGGAL PENERBITAN\n\n");
	fp = fopen ("datafilm.txt", "r");
	fp1 = fopen ("sementara.txt", "w");
	printf(" Masukkan Tanggal Penerbitan Film Yang Ingin Dicari : ");
	gets(tanggal);
	while (fread(&d1, sizeof(datafilm), 1, fp)) {
		if((strcmp (tanggal, d1.tanggal) == 0)) {
			ditemukan = 1;
			fwrite (&d1, sizeof (datafilm), 1, fp1);
		}
	}
	fclose(fp1);
	if (ditemukan) {
		tampilcari();
	} else {
		printf("\n Data Film Tidak Ditemukan!\n");
		printf(" Tekan ENTER Untuk Kembali Ke Menu Sebelumnya.\n");
	}
	fclose(fp);
}

void caridurasi() {
	datafilm d1;
	FILE *fp, *fp1;
	int ditemukan = 0;
	char durasi[50];
	system("cls");
	printf("\t\t\t\t\t\tMENU CARI FILM BERDASARKAN DURASINYA\n\n");
	fp = fopen ("datafilm.txt", "r");
	fp1 = fopen ("sementara.txt", "w");
	printf(" Masukkan Durasi Film Yang Ingin Dicari : ");
	gets(durasi);
	while (fread(&d1, sizeof(datafilm), 1, fp)) {
		if((strcmp (durasi, d1.durasi) == 0)) {
			ditemukan = 1;
			fwrite (&d1, sizeof (datafilm), 1, fp1);
		}
	}
	fclose(fp1);
	if (ditemukan) {
		tampilcari();
	} else {
		printf("\n Data Film Tidak Ditemukan!\n");
		printf(" Tekan ENTER Untuk Kembali Ke Menu Sebelumnya.\n");
	}
	fclose(fp);
}

void judul_asc() {
	datafilm *d, d1;
	FILE *fp;
	int i,j;
	fp = fopen ("datafilm.txt", "r");
	fseek (fp,0,SEEK_END);
	int n = ftell(fp)/sizeof(datafilm);
	
	d = (datafilm*) calloc (n, sizeof(datafilm));
	
	rewind(fp);
	for (i = 0; i < n; i++) {
		fread (&d[i], sizeof(datafilm), 1, fp);
	}
	
	fp = fopen ("datafilm.txt", "w");
	for (i = 0; i < n; i++) {
		for (j = i+1; j < n; j++) {
			if((strcmp (d[i].judul, d[j].judul) > 0)) {
				d1   = d[i];
				d[i] = d[j];
				d[j] = d1;			
			}
		}
		fwrite(&d[i],sizeof (datafilm),1,fp);
	}
	fclose (fp);
}

void judul_desc() {
	datafilm *d, d1;
	FILE *fp;
	int i,j;
	fp = fopen ("datafilm.txt", "r");
	fseek (fp,0,SEEK_END);
	int n = ftell(fp)/sizeof(datafilm);
	
	d = (datafilm*) calloc (n, sizeof(datafilm));
	
	rewind(fp);
	for (i = 0; i < n; i++) {
		fread (&d[i], sizeof(datafilm), 1, fp);
	}
	
	fp = fopen ("datafilm.txt", "w");
	for (i = 0; i < n; i++) {
		for (j = i+1; j < n; j++) {
			if((strcmp (d[i].judul, d[j].judul) < 0)) {
				d1   = d[i];
				d[i] = d[j];
				d[j] = d1;			
			}
		}
		fwrite(&d[i],sizeof (datafilm),1,fp);
	}
	fclose (fp);
}

void sutra_asc() {
	datafilm *d, d1;
	FILE *fp;
	int i,j;
	fp = fopen ("datafilm.txt", "r");
	fseek (fp,0,SEEK_END);
	int n = ftell(fp)/sizeof(datafilm);
	
	d = (datafilm*) calloc (n, sizeof(datafilm));
	
	rewind(fp);
	for (i = 0; i < n; i++) {
		fread (&d[i], sizeof(datafilm), 1, fp);
	}
	
	fp = fopen ("datafilm.txt", "w");
	for (i = 0; i < n; i++) {
		for (j = i+1; j < n; j++) {
			if((strcmp (d[i].sutradara, d[j].sutradara) > 0)) {
				d1   = d[i];
				d[i] = d[j];
				d[j] = d1;			
			}
		}
		fwrite(&d[i],sizeof (datafilm),1,fp);
	}
	fclose (fp);
}

void sutra_desc() {
	datafilm *d, d1;
	FILE *fp;
	int i,j;
	fp = fopen ("datafilm.txt", "r");
	fseek (fp,0,SEEK_END);
	int n = ftell(fp)/sizeof(datafilm);
	
	d = (datafilm*) calloc (n, sizeof(datafilm));
	
	rewind(fp);
	for (i = 0; i < n; i++) {
		fread (&d[i], sizeof(datafilm), 1, fp);
	}
	
	fp = fopen ("datafilm.txt", "w");
	for (i = 0; i < n; i++) {
		for (j = i+1; j < n; j++) {
			if((strcmp (d[i].sutradara, d[j].sutradara) < 0)) {
				d1   = d[i];
				d[i] = d[j];
				d[j] = d1;			
			}
		}
		fwrite(&d[i],sizeof (datafilm),1,fp);
	}
	fclose (fp);
}

void tanggal_asc() {
	datafilm *d, d1;
	FILE *fp;
	int i,j;
	fp = fopen ("datafilm.txt", "r");
	fseek (fp,0,SEEK_END);
	int n = ftell(fp)/sizeof(datafilm);
	
	d = (datafilm*) calloc (n, sizeof(datafilm));
	
	rewind(fp);
	for (i = 0; i < n; i++) {
		fread (&d[i], sizeof(datafilm), 1, fp);
	}
	
	fp = fopen ("datafilm.txt", "w");
	for (i = 0; i < n; i++) {
		for (j = i+1; j < n; j++) {
			if((strcmp (d[i].tanggal, d[j].tanggal) > 0)) {
				d1   = d[i];
				d[i] = d[j];
				d[j] = d1;			
			}
		}
		fwrite(&d[i],sizeof (datafilm),1,fp);
	}
	fclose (fp);
}

void tanggal_desc() {
	datafilm *d, d1;
	FILE *fp;
	int i,j;
	fp = fopen ("datafilm.txt", "r");
	fseek (fp,0,SEEK_END);
	int n = ftell(fp)/sizeof(datafilm);
	
	d = (datafilm*) calloc (n, sizeof(datafilm));
	
	rewind(fp);
	for (i = 0; i < n; i++) {
		fread (&d[i], sizeof(datafilm), 1, fp);
	}
	
	fp = fopen ("datafilm.txt", "w");
	for (i = 0; i < n; i++) {
		for (j = i+1; j < n; j++) {
			if((strcmp (d[i].tanggal, d[j].tanggal) < 0)) {
				d1   = d[i];
				d[i] = d[j];
				d[j] = d1;			
			}
		}
		fwrite(&d[i],sizeof (datafilm),1,fp);
	}
	fclose (fp);
}

void durasi_asc() {
	datafilm *d, d1;
	FILE *fp;
	int i,j;
	fp = fopen ("datafilm.txt", "r");
	fseek (fp,0,SEEK_END);
	int n = ftell(fp)/sizeof(datafilm);
	
	d = (datafilm*) calloc (n, sizeof(datafilm));
	
	rewind(fp);
	for (i = 0; i < n; i++) {
		fread (&d[i], sizeof(datafilm), 1, fp);
	}
	
	fp = fopen ("datafilm.txt", "w");
	for (i = 0; i < n; i++) {
		for (j = i+1; j < n; j++) {
			if((strcmp (d[i].durasi, d[j].durasi) > 0)) {
				d1   = d[i];
				d[i] = d[j];
				d[j] = d1;			
			}
		}
		fwrite(&d[i],sizeof (datafilm),1,fp);
	}
	fclose (fp);
}

void durasi_desc() {
	datafilm *d, d1;
	FILE *fp;
	int i,j;
	fp = fopen ("datafilm.txt", "r");
	fseek (fp,0,SEEK_END);
	int n = ftell(fp)/sizeof(datafilm);
	
	d = (datafilm*) calloc (n, sizeof(datafilm));
	
	rewind(fp);
	for (i = 0; i < n; i++) {
		fread (&d[i], sizeof(datafilm), 1, fp);
	}
	
	fp = fopen ("datafilm.txt", "w");
	for (i = 0; i < n; i++) {
		for (j = i+1; j < n; j++) {
			if((strcmp (d[i].durasi, d[j].durasi) < 0)) {
				d1   = d[i];
				d[i] = d[j];
				d[j] = d1;			
			}
		}
		fwrite(&d[i],sizeof (datafilm),1,fp);
	}
	fclose (fp);
}

void menuurut() {
	system("cls");
	printf("\t\t\t\t\t\tMENU URUT DATA\n");
	puts("\n Pilih Menu Dibawah Ini Untuk Menentukan Metode Pengurutan");
	puts("  a.  Urut Berdasarkan Judul Film (Ascending)");
    puts("  b.  Urut Berdasarkan Judul Film (Descending)");
    puts("  c.  Urut Berdasarkan Nama Sutradara (Ascending)");
    puts("  d.  Urut Berdasarkan Nama Sutradara (Descending)");
    puts("  e.  Urut Berdasarkan Tanggal Perilisan (Ascending)");
    puts("  f.  Urut Berdasarkan Tanggal Perilisan (Descending)");
    puts("  g.  Urut Berdasarkan Durasi Film (Ascending)");
    puts("  h.  Urut Berdasarkan Durasi Film (Descending)");
    garis(120);
    switch(getch()){
		case 'a' : judul_asc(); 
		printf(" Menu Pilihan  : Urut Berdasarkan Judul Film (Ascending)");
        printf("\n Data Telah Berhasil Diurutkan!");
        printf("\n Silahkan Klik Menu Tampilkan Data Untuk Melihat Hasilnya.");
        printf("\n Tekan ENTER untuk kembali ke Menu Utama.");
        break;
        case 'b' : judul_desc();
        printf(" Menu Pilihan  : Urut Berdasarkan Judul Film (Descending)");
        printf("\n Data Telah Berhasil Diurutkan!");
        printf("\n Silahkan Klik Menu Tampilkan Data Untuk Melihat Hasilnya.");
        printf("\n Tekan ENTER untuk kembali ke Menu Utama.");
        break;
        case 'c' : sutra_asc();
        printf(" Menu Pilihan  : Urut Berdasarkan Nama Sutradara (Ascending)");
        printf("\n Data Telah Berhasil Diurutkan!");
        printf("\n Silahkan Klik Menu Tampilkan Data Untuk Melihat Hasilnya.");
        printf("\n Tekan ENTER untuk kembali ke Menu Utama.");
        break;
        case 'd' : sutra_desc();
        printf(" Menu Pilihan  : Urut Berdasarkan Nama Sutradara (Descending)");
        printf("\n Data Telah Berhasil Diurutkan!");
        printf("\n Silahkan Klik Menu Tampilkan Data Untuk Melihat Hasilnya.");
        printf("\n Tekan ENTER untuk kembali ke Menu Utama.");
        break;
		case 'e' : tanggal_asc();
        printf(" Menu Pilihan  : Urut Berdasarkan Tanggal Perilisan (Ascending)");
        printf("\n Data Telah Berhasil Diurutkan!");
        printf("\n Silahkan Klik Menu Tampilkan Data Untuk Melihat Hasilnya.");
        printf("\n Tekan ENTER untuk kembali ke Menu Utama.");
        break;
        case 'f' : tanggal_desc();
        printf(" Menu Pilihan  : Urut Berdasarkan Tanggal Perilisan (Descending)");
        printf("\n Data Telah Berhasil Diurutkan!");
        printf("\n Silahkan Klik Menu Tampilkan Data Untuk Melihat Hasilnya.");
        printf("\n Tekan ENTER untuk kembali ke Menu Utama.");
        break;
        case 'g' : durasi_asc();
        printf(" Menu Pilihan  : Urut Berdasarkan Durasi Film (Ascending)");
        printf("\n Data Telah Berhasil Diurutkan!");
        printf("\n Silahkan Klik Menu Tampilkan Data Untuk Melihat Hasilnya.");
        printf("\n Tekan ENTER untuk kembali ke Menu Utama.");
        break;
        case 'h' : durasi_desc();
        printf(" Menu Pilihan  : Urut Berdasarkan Durasi Film (Descending)");
        printf("\n Data Telah Berhasil Diurutkan!");
        printf("\n Silahkan Klik Menu Tampilkan Data Untuk Melihat Hasilnya.");
        printf("\n Tekan ENTER untuk kembali ke Menu Utama.");
        break;
    }
}

void menucari() {
	do {
		system("cls");
		printf("\t\t\t\t\t\tMENU SEARCHING DATA\n\n");
		puts("\n  Pilih Menu Dibawah Ini Untuk Menentukan Metode Pencarian");
		puts("   1.  Cari Berdasarkan Judul Film");
	    puts("   2.  Cari Berdasarkan Nama Sutradara");
	    puts("   3.  Cari Berdasarkan Genre Film");
	    puts("   4.  Cari Berdasarkan Tanggal Penerbitan");
	    puts("   5.  Cari Berdasarkan Durasi Film");
	    puts("  00.  Kembali Ke Menu Awal");
		switch(getch()){
			case '1' : carijudul();
	        break;
	        case '2' : carisutra();
	        break;
	        case '3' : carigenre();
	        break;
	        case '4' : caritanggal();
	        break;
	        case '5' : caridurasi();
	        break;
	        case '0' : goto awal;
	        break;
		}	
	}
	while(getch()!=27);
	awal:;
}

void menunilai() {
	do {
		system("cls");
		printf("\t\t\t\t\t\tMENU PENILAIAN PENGGUNA\n\n");
		puts("\n  Pilih Menu Dibawah Ini Untuk Melakukan Penilaian");
		puts("   1.  Tambahkan Penilaian");
	    puts("   2.  Tampilkan Penilaian");
	    puts("   3.  Hapus Penilaian");
	    puts("  00.  Kembali Ke Menu Awal");
		switch(getch()){
			case '1' : tambahnilai();
	        break;
	        case '2' : tampilnilai();
	        break;
	        case '3' : hapuspenilaian();
	        break;
	        case '0' : goto awal;
	        break;
		}	
	}
	while(getch()!=27);
	awal:;
}

int main(int argc, char *argv[]) {
	system("color 70");
	gotoxy(32,13);
	loadscr();
	system("cls");
	do {
		system("cls");
		garis(120);
		header("Muhammad Alviriza Ramadhan", "20081010143", 
				"D081", "Pemrograman Lanjut", "Fawwaz Ali Akbar, S.Kom, M.Kom");
		garis(120);
		gotoxy(55,10);
		printf("MENU UTAMA\n");
	    puts("\n Pilih Menu dibawah ini untuk menjalankan aplikasi");
	    puts("  1.  Tambah Data Film");
	    puts("  2.  Tampilkan Data Film");
	    puts("  3.  Ubah Data Film");
	    puts("  4.  Hapus Data Film");
	    puts("  5.  Urutkan Data Film");
	    puts("  6.  Cari Data Film");
	    puts("  7.  Penilaian Film");
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
	        case '5' : menuurut();
	        break;
	        case '6' : menucari();
	        break;
	        case '7' : menunilai();
	        break;
	    }
	}
	while(getch()!=27);
    return 0;
}
