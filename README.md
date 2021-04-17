# soal-shift-sisop-modul-2-A03-2021

Anggota : 

### 1. Naufal Fajar  I  05111940000007
### 2. Johnivan Aldo S  05111940000051 
### 3. Abdun Nafi'      05111940000066

***
## Penjelasan nomor 1 ##

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
2. Setelah itu jika fork berhasil dibuat kita menggunakan perintah ```unzip``` untuk mengestrak filenya yang kita simpan di pointer argv
3. Setelah proses selesai yaitu menghapus nya dengan code ```{"rm" , "pets.zip" , NULL };```


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
