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

#### Penjelasan sourcode umum
1. Untuk mempermudah dan mempersingkat pembuatan fork kita buat fungsi ```eksekusi``` dimana di dalam terdapat pembuatan child proses 
```
void eksekusi(char perintah[],char *arg[]){

        int status;
        pid_t child_id;
        child_id=fork();
        if(child_id==0){
            printf("%s",perintah);
            execv(perintah,arg);
        }
        else{
           ((wait(&status))>0);
        }
}

```
2. Selain itu terdapat fungsi cut yang membantu untuk menghapus string index ke 4

```
char* cut(char *arr){
        int n,i;
        char* cuts; 
        for(i=0;arr[i]!='\0';i++);
           n=i-4+1;

        if(n<1) return NULL;

        cuts=(char*)malloc(n*sizeof(char));

        for(i=0;i<n-1;i++)
        cuts[i]=arr[i];
        cuts[i]='\0';
        return cuts;
}

```

#### 2A. Mengestrak File zip ke folder /home/user/modul2/petshop dan menghapus file yang tidak penting
****
Untuk pertama tama di dalam fungsi main kita buat kan folder /home/user/modul/petshop dengan perintah fork yang telah kita buat
seperti berikut :
```
 //membuat folder untuk menyimpan ekstrak
        char *argv[]={"mkdir","-p","/home/abdunnafi25/modul2/petshop",NULL};
        eksekusi("/bin/mkdir",argv);
```

Setelah selesai membuat kita unzip file pets.zip ke folder tersbut dengan kode seperti berikut.
```
char *argv2[]={"unzip","-q","pets.zip","-d","/home/abdunnafi25/modul2/petshop",NULL};
        execv("/usr/bin/unzip",argv2);
        }
```

setelah semua file di unzip selanjutnya kita pindah direktory dengan code sebagai berikut :
```
DIR *dir=opendir("/home/abdunnafi25/modul2/petshop");
```

Setelah berhasil pindah direktory selanjutnya kita membuat struct dengan variabel ```dent``` yang bertipe ```dirent```
setelah selesai selanjutnya mengecek apakah di dalam direktori ada file jika ada maka eksekusi.
dengan kode sebagai berikut :
```
struct dirent *dent;
        if(dir!=NULL){
        while((dent=readdir(dir))!=NULL)
```

jika ada file di dalam direktori maka kita cek file dengan membandingkan string dengan menggunakan fungsi ```strcmp``` jika file mengandung ```.``` atau ```..```
maka continue dengan code sebagai berikut.
```
if(strcmp(dent->d_name,".")==0 || strcmp(dent->d_name,"..")==0) continue; 
```
Selanjutnya kita menghapus file dengan menggunakan execv ```/bin/rm``` dengan code sebagai berikut.

```
else if(dent->d_type==DT_DIR){
                        char fileName[100]="/home/abdunnafi25/modul2/petshop/";
                        //Menggabungkan folder dengan file yang tidak penting
                        strcat(fileName,dent->d_name);
                        //Menghapus file tidak penting
                        char *argv[]={"rm","-rf",fileName,NULL};
                        eksekusi("/bin/rm",argv);
                        exit(EXIT_SUCCESS); 
                }
```




####  2B.  Membuat folder nama hewan sesuai kategori dalam folder petshop misal ```petshop/cat``` dan ```petshop/dog```
****
Untuk no 2B pertama kita ambil string yang menjadi nama file sebagai nama pembuatan nama folder.

1. Pertama kita memakai fungsi cut yang telah kita buat untuk menghapus index ke 4 yaitu ".jpg" dan disimpan dalam pointer cuts dengan code sebagai berikut
```
char *cutss=cut(dent->d_name);
```
2. Setelah yang tersimpan hanya ```jenis```, ```nama``` , dan ```umur``` maka selanjutnya kita looping semua nama file dan pisahkan string dengan menggunankan fungsi ```strtok``` dengan pemisah looping pertama adalah ```_``` untuk gambar yang mengandung 2 hewan
selanjutnya kita pisahkan string lagi dengan pemisah ```;``` yang menjadi pemisah antara jenis, nama dan umur dan disimpan dalam variabel photo

3. Jika sudah terpisah maka untuk index-0 yaitu yang menyimpan ```jenis hewan``` kita buatkan folder baru sesuai nama hewan.
dan kita sediakan char file untuk membuat path ```/home/user/modul2/petshop```
dan kita expand dengan menggunakan fungsi ```strcat``` dengan variabel file. seperti code berikut :
```
while(photo=strtok_r(ph,";",&ph)){
                                if(i==0){
                                //buat folder sesuai nama pets
                                char files[80]="/home/abdunnafi25/modul2/petshop/";
                                strcat(files,photo);
                                char *argv[]={"mkdir","-p",files,NULL};
                                eksekusi("/bin/mkdir",argv);
                                strcpy(pet,photo);
                                }
```

5. Selanjutnya untuk index-1 kita menyimpan nama hewan ke array ```pName```
6. Selanjutnya untuk index-2 kita menyimpan umur hewan ke array ```pAge```
sebagai contoh code berikut:

```
if(i==1){
  //Mengcopy isi dari arrat photo ke array  nama pets
  strcpy(pName,photo);
}
if(i==2){
   //Mencopy isi index 3 ke umurnya pets
   strcpy(pAge,photo);
 }
 i++;
                        
```

####  2C dan D.  Memindahkan foto ke folder dengan kategori yang sesuai dan di rename dengan nama peliharaan. misal ```petshop/cat/joni.jpg``` Memindahkan ke masing-masing kategori yang sesuai. Contoh: foto dengan nama ```dog;baro;1_cat;joni;2.jp``` dipindah ke folder    ```/petshop/cat/joni.jpg” dan “/petshop/dog/baro.jp```.
****
1. Selanjutnya untuk memindahkan gambar yang telah di ekstrak ke file masing masing maka kita harus membuat string fileku yang merupakan copy dari string   "/home/user/modul2/petshop/" 
2. setelah variabel fileku tersimpan nama path selanjutnya kita expand dengan d_name file
dengan code sebagai berikut :
```
while((wait(NULL))>0);
                        char fileku[80];
                        strcpy(fileku,"/home/abdunnafi25/modul2/petshop/");
                        strcat(fileku,dent->d_name);
```
dimana char fileku disimpan untuk mencopy file nya ke masing masing folder

3. Selanjut kita membuat file destination untuk mencopy file gambar ke masing 2 folder dengan menggunakan fungsi ```strcpy``` dan ```strcat``` dan menggunakan fork dengan code sebagai berikut 

```
char dest[80];
                        strcpy(dest,"/home/abdunnafi25/modul2/petshop/");
                        strcat(dest,pet);
                        strcat(dest,"/");
                        strcat(dest,pName);
                        strcat(dest,".jpg");
                        char *argv[]={"cp",fileku,dest,NULL};
                        eksekusi("/bin/cp",argv);
```
####  2E.  Di setiap folder buatlah sebuah file "keterangan.txt" yang berisi nama dan umur semua peliharaan dalam folder tersebut.

****
Setelah semua file masuk selanjutnya membuat file keterangan.txt disetiap folder dengan code sebagai berikut.
```
 //keterangan.txt di masing2 folder pets
                        char file[50];
                        strcpy(file,"/home/abdunnafi25/modul2/petshop/");
                        strcat(file,pet);
                        strcat(file,"/keterangan.txt");

                        //isi file keterangan.txt
                        char ch[50];
                        strcat(ch,"nama : ");
                        strcat(ch,pName);
                        strcat(ch,"\numur: ");
                        strcat(ch,pAge);
                        strcat(ch,"tahun\n\n");
```

dimana kita menyimpan nya dalam array ch untuk isi dari keterangan.

Selanjutnya kita membuka file keterangan dengan kode sebagai berikut
```
 //buat keterangan.txt
                        FILE *fp;
                        fp=fopen(file,"a");
                        fputs(ch,fp);
                        fclose(fp);
```
dimana ```fopen``` untuk membuka file yang berisi ``` /home/user/modul2/petshop/jenispat/keterangan.txt ```keterangan "a" itu merupakan argumen untuk memasukan string ke dalam file keterangan.txt
dan fungsi fput untuk memindah string yang berada pada array ```ch``` disimpan dalam file fp
lalu kita tutup file dengan fungsi ```fclose```

Untuk yang terakhir dikarenakan masih ada gambar yang belum terhapus di folder petshop maka kita hapus semua folder dengan menggunakan code sebagai berikut :

```
 char hapus[60]="/home/abdunnafi25/modul2/petshop/";
        strcat(hapus,dent->d_name);
        char *args[]={"rm",hapus,NULL};
        execv("/bin/rm",args);
```

Lalu setelah terhapus kita tutup directory dengan fungsi ```closedir(dir);```


## Penjelasn nomor 3 ##

****
Sebelum menjelaskan nomer 3, pertama-tama kami menggunkana template daemon yang sudah disediakan oleh asisten pada modul. Kemudian untuk algoritma caesar cypher sendiri, kami mengambil dari website dan ditambahkan sedikit modifikasi, linknya adalah 
https://www.thecrazyprogrammer.com/2016/11/caesar-cipher-c-c-encryption-decryption.html

#### 3A.Membuat sebuah program C dimana setiap 40 detik membuat sebuah direktori dengan nama sesuai timestamp [YYYY-mm-dd_HH:ii:ss]
Berikut adalah sourcecodenya, pertaman kita harus mendapatkan waktu saat ini dan disimpan ke dalam array
```
char waktuSekarang[100];
      time_t now = time(NULL);
      struct tm *timeNow = localtime(&now);
      char *platform = waktuSekarang;
      strftime(waktuSekarang,sizeof(waktuSekarang)-1, "%Y-%m-%d_%H:%M:%S", timeNow);
```

Kemudian kita buat chilld yang nantinya menjadi daemon dan parent tidak menunggu child saat menjalankan proses berikutnya. Kita memberi nilai 40 pada proses sleep, agar proses berjalan setiap 40 detik sesuai keinginan soal
```
child_ID = fork();
      if (child_ID < 0){
          exit(EXIT_FAILURE);
      }
      if (child_ID ==0){
          //buat folder (untuk nomer berikutnya)
	  }
sleep(40);
```
Buat child yang baru dan jalankan wait() untuk menunggu proses selesai
```
child_ID2 = fork();
          if (child_ID2 < 0){
              exit(EXIT_FAILURE);
          }
          if (child_ID2 == 0){
              char *argv[] = {"makeDir", waktuSekarang, NULL};
              execv("/bin/mkdir", argv); 
          }
        while(wait(&status) > 0);
```
#### 3B.Mengisi direktori yang sudah dibuat dengan 10 gambar yang didownload dari https://picsum.photos/, dimana setiap gambar akan didownload setiap 5 detik. Setiap gambar yang didownload akan diberi nama dengan format timestamp [YYYY-mm-dd_HH:ii:ss] dan gambar tersebut berbentuk persegi dengan ukuran (n%1000) + 50 pixel dimana n adalah detik Epoch Unix.

Langkah pertama yaitu kita berpindah ke direktori sesuai timestamp, dan melakukan iterasi dari 1-10 (karena maksimal 10 gambar) dan berikan sleep(5) untuk jeda 5 detik tiap download. Jangan lupa juga jalankan fungsi wait()
```
chdir(waktuSekarang);
        for(int i=1; i<= 10;i++){
            time_t now2;
            struct tm * timenow2;

            time (&now2);
            timenow2 = localtime(&now2);
            char imgname[100];
	        char link[100];
            strftime(imgname, 100, "%Y-%m-%d_%H:%M:%S", timenow2);
            sprintf(link , "https://picsum.photos/%ld", (now2 % 1000) + 50);
            pid_t child_id_pic;
            child_id_pic = fork();
            if(child_id_pic<0)
            {
                exit(EXIT_FAILURE);
            }
            if(child_id_pic==0)
            {
                char *argv[]= {"wget", link, "-O", imgname, "-o", "/dev/null", NULL};
                execv("/usr/bin/wget", argv);
            }
            sleep(5);
        }
        while(wait(&status2)>0);
```

Jangan lupa karena gambar harus berukuran (n%1000) + 50 px, dimana n adalah detik Epoch Unix, maka kita tambahkan metode ukuran gambar pada akhir kalimat untuk mendownload gambar. Lalu lakukan rename dengan timestamp saat ini.

#### 3C.Melakukan enkripsi dengan metode Caesar Cypher ####
Setelah direktori terisi 10 gambar, maka akan membuat file status.txt, dimana didalamnya berisi pesan "Download Success" yang terenkripsi dengan shift 5. Dilakukan dengan penggeseran 5 karakter dengan memperhatikan huruf kecil dan huruf besar serta dimodulo 26.
```
void cipherCrypt(char msg[], int key)
{
    for(int j = 0; msg[j] != '\0'; ++j)
    {
        char ch = msg[j];
        if(ch >= 'a' && ch <= 'z')
        {
            ch = ch + key;
            if(ch > 'z')
            {
                ch = ch - 'z' + 'a' - 1;
            }
            msg[j] = ch;
        }

        else if(ch >= 'A' && ch <= 'Z')
        {
            ch = ch + key;
            if(ch > 'Z')
            {
                ch = ch - 'Z' + 'A' - 1;
            }
            msg[j] = ch;
        }
    }
}
```
