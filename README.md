# soal-shift-sisop-modul-2-A03-2021

Anggota : 

### 1. Naufal Fajar  I  05111940000007
### 2. Johnivan Aldo S  05111940000051 
### 3. Abdun Nafi'      05111940000066

***
***
## Penjelasan nomor 1 ##

### 1A. Dikarenakan Stevany sangat menyukai huruf Y, Steven ingin nama folder-foldernya adalah Musyik untuk mp3, Fylm untuk mp4, dan Pyoto untuk jpg.
```
//a)Buat folder musyik,pyoto,fylm
void mkfolder(int * status, pid_t child_id, char *folder[]) {
    if((child_id = fork()) == 0) {
        char *argv[] = {"mkdir",folder[0], folder[1], folder[2], NULL};
        execv("/bin/mkdir", argv);
    }
    while(wait(status) > 0);
}
```
```
//a)Buat folder musyik,pyoto,fylm
		mkfolder(&status, child_id, folder);
```
#### Penjelasan
Dengan memanggil fungsi mkfolder dari main, fungsi tersebut akan fork x exec x wait dengan command mkdir yang akan membuat folder Musyik, Fylm, dan Pyoto dengan string yang sudah dipassing.

### 1B. Download file musik,film,foto dari link di soal
```
//b)Download musik,foto,film
void download(int * status, pid_t child_id, char link[], char dlzip[]) {
    if((child_id = fork()) == 0) {
        char *argv[] = {"wget","-q","--no-check-certificate",link,"-O",dlzip, NULL};
        execv("/bin/wget", argv);
    }
    while(wait(status) > 0);
}
```
```
for(i=0;i<3;i++){
			download(&status, child_id, link[i],dlzip[i]);
		}
```
#### Penjelasan
Dengan memanggil fungsi download dari main, fungsi tersebut akan fork x exec x wait dengan command wget yang akan mendownload file dari link yang telah dipassing dengan bergantian (for loop) dan nama file tsb.

### 1C. Mengextract file yang sudah didownload sebelumnya.

```
//c)Extract zip
void unboxing(int * status, pid_t child_id,char dlzip[]) {
    if((child_id = fork()) == 0) {
        char *argv[] = {"unzip", dlzip, NULL};
        execv("/bin/unzip", argv);
    }
    while(wait(status) > 0);
}
```
```
//c)Unzipping download file
		for(i=0;i<3;i++)
			unboxing(&status,child_id,dlzip[i]);
```
#### Penjelasan
Dengan memanggil fungsi unboxing dari main, fungsi tersebut akan fork x exec x wait dengan command unzip yang akan mengextract file berbentuk zip yang terdownload sebelumnya  dengan bergantian (for loop) sesuai nama file zip yang telah dipassing.

### 1D. Memindahkan isi file ke folder yang telah dibuat sebelumnya (Musyik, Fylm, Pyoto).
```
//d)Move file
void move(int * status, pid_t child_id, char exzip[], char folder[]) {
    DIR * dp;
    struct dirent * ep;
    dp = opendir(exzip);
    if (dp != NULL) {
        while ((ep = readdir(dp))){
        	if (strcmp(ep->d_name, ".") != 0 && strcmp(ep->d_name, "..") != 0){
    			if((child_id = fork()) == 0){
    				char path[100];
    				strcpy(path, exzip);
        			strcat(path, "/");
					strcat(path, ep->d_name);
					
					char *argv[] = {"mv", path, folder, NULL};
        			execv("/bin/mv", argv);
				}
				while(wait(status) > 0);    		
			}     	
		}
        (void) closedir (dp);
    }
	else perror ("Couldn't open the directory"); 
}
```
```
//d)Memindahkan file
	    	for(i=0;i<3;i++){
    		move(&status,child_id,exzip[i],folder[i]);
		}
```
#### Penjelasan
Dengan memanggil fungsi move dari main, fungsi tersebut berjalan dengan Directory Listing in C (seperti pada modul2) yang akan mentraverse secara rekursif terhadap directory dengan bergantian (for loop) sesuai nama directory yang sudah dipassing lalu memindahkan setiap file yang ada di directory tersebut (MUSIK, FOTO, FILM) ke dalam directory yang telah dibuat (Musyik, Pyoto, Fylm) dengan fork x exec x wait.

### 1E. Script berjalan otomatis 6 jam sebelum hbd stevany
```
    time_t t ;
    struct tm *tmp ;
	//char MY_TIME[Size];
    time( &t );  
    tmp = localtime( &t );
```
``` 
if((tmp->tm_mday == 9) && (tmp->tm_mon == 3)&& (tmp->tm_hour == 16 )&& (tmp->tm_min == 22) && (tmp->tm_sec == 0))
```

#### Penjelasan
Untuk menyelesaikan problem ini, tentu saja kita dituntut untuk membuat daemon yang akan berjalan otomatis di background. Tapi tenang, sudah ada template daemon di modul2 h3h3. Lalu, untuk menjalankan step a,b,c,d secara otomatis saat 6 jam sebelum ultah stevany, maka digunakan lah struct tm dari time.h untuk mengetahui waktu sistem. Sisanya tinggal dibandingkan dengan ultah stevany dengan memasukkannya ke dalam kondisi if.

### 1F. Saat ultah stevany, folder akan di zip sehingga hanya ada file zip
```
void boxing(int * status,pid_t child_id, char *folder[], char *lopyu[]) {
    if((child_id = fork()) == 0) {
        char *argv[] = {"zip", "-rmvq", lopyu[0], folder[0], folder[1], folder[2], NULL};
        execv("/bin/zip", argv);
    }
    while(wait(status) > 0);
}
void hapus(int * status, pid_t child_id, char * exzip[]) {
    if((child_id = fork()) == 0) {
        char *argv[] = {"rm", "-rf", exzip[0], exzip[1], exzip[2], NULL};
        execv("/bin/rm", argv);
    }
    while(wait(status) > 0);
}
```
```
boxing(&status,child_id,folder,lopyu);
hapus(&status,child_id,exzip);
```
```
else if((tmp->tm_mday == 9) && (tmp->tm_mon == 3)&& (tmp->tm_hour == 22 )&& (tmp->tm_min == 22) && (tmp->tm_sec == 0))
```

#### Penjelasan
Sama seperti problem E, di sini juga menggunakan struct tm di dalam kondisi else if (setelah if problem E) pada saat waktu ultah stevany, lalu kita menjalankan fungsi boxing, yakni untuk memindahkan dan menzip folder (Musyik, Fylm, Pyoto) ke dalam Lopyu_Stevany.zip. Lalu menjalankan fungsi hapus untuk menghapus folder sisa extract (MUSIK, FOTO, FILM).


****

## Penjelasan nomor 2 ##

****
####  2A.  Mengextract zip yang diberikan ke dalam folder “/home/[user]/modul2/petshop” dan menhapus folder dan file yang tidak dibutuhkan
****
Source Code :
```
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <wait.h>

int main() {
  pid_t child_id;
  int status;

  child_id = fork();

  if (child_id < 0) {
   exit(EXIT_FAILURE);
  }

  if ( child_id == 0) {
   //Mengestrak file ke folder /home/user/modul2/petshop
   char *argv[] = {"unzip" ,"pets.zip" , "*.jpg","-d", "/home/abdunnafi25/modul2/petshop", NULL };
   execv("/usr/bin/unzip",argv);
  }
  else {
   while ((wait(&status)) > 0 );
   //Menghapus file yang tidak dibutuhkan
   char *argv[] = {"rm" , "pets.zip" , NULL };
   execv("/bin/rm",argv);
  }
}

```

##### Penjelasan 2A.
1. Pertama kita membuat fork baru yang disimpan dalam child_id 
2. Setelah itu jika fork berhasil dibuat kita menggunakan perintah ```unzip``` untuk mengestrak filenya ke path /home/abdunnafi25/modul2/petshop 
   yang kita simpan di pointer argv dengan menggunakan kode ```{"unzip" ,"pets.zip" , "*.jpg","-d", "/home/abdunnafi25/modul2/petshop", NULL };```
   dimana ```-d``` untuk menunjukkan path yang akan dituju dan ```*.jpg``` hanya mengestrak file jpg saja
4. Setelah proses selesai yaitu menghapus nya dengan code ```{"rm" , "pets.zip" , NULL };```


####  2B.  Membuat folder nama hewan sesuai kategori dalam folder petshop misal ```petshop/cat``` dan ```petshop/dog```
****
####  2C.  Memindahkan foto ke folder dengan kategori yang sesuai dan di rename dengan nama peliharaan. misal ```petshop/cat/joni.jpg```
****
####  2D.  Memindahkan ke masing-masing kategori yang sesuai. Contoh: foto dengan nama ```dog;baro;1_cat;joni;2.jp``` dipindah ke folder    ```/petshop/cat/joni.jpg” dan “/petshop/dog/baro.jp```.

****
####  2E.  Di setiap folder buatlah sebuah file "keterangan.txt" yang berisi nama dan umur semua peliharaan dalam folder tersebut.

****



## Penjelasn nomor 3 ##

****
#### 3A.Membuat sebuah program C dimana setiap 40 detik membuat sebuah direktori dengan nama sesuai timestamp [YYYY-mm-dd_HH:ii:ss]

