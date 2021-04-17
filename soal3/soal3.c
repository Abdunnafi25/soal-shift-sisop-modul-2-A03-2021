#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
 
//include untuk menggunakan fungsi time di C
#include <time.h>
 
//include untuk menggunakan fungsi wait pada program
#include <wait.h>
 
//thecrazyprogrammer.com/2016/11/caesar-cipher
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
 
int main (){
    pid_t child_ID, child_ID2, child_ID3, child_ID4, child_ID5, pid, sid; // variabel menyimpan PID
    int status, status2;
    pid = fork(); //Menyimpan PID dari Child Process
 
    /*Keluar saat fork gagal
    *(nilai variabel pid < 0) */
   if (pid <0){
       exit(EXIT_FAILURE);
   } 
 
   /* Keluar saat fork berhasil
   *(nilai variabel pid adalah PID dari child process)*/
  if (pid > 0){
      exit(EXIT_SUCCESS);
  }
 
  umask(0);
 
  sid = setsid();
  if (sid < 0){
      exit(EXIT_FAILURE);
  }
 
  if((chdir("/home/johnivan/Documents/modul2/")) < 0){
      exit(EXIT_FAILURE);
  }
 
  close(STDIN_FILENO);
  close(STDOUT_FILENO);
  close(STDERR_FILENO);
 
  //program utama
  while(1){
      char waktuSekarang[100];
      time_t now = time(NULL);
      struct tm *timeNow = localtime(&now);
      char *platform = waktuSekarang;
      strftime(waktuSekarang,sizeof(waktuSekarang)-1, "%Y-%m-%d_%H:%M:%S", timeNow);
 
      child_ID = fork();
      if (child_ID < 0){
          exit(EXIT_FAILURE);
      }
      if (child_ID ==0){
          //buat folder
          child_ID2 = fork();
          if (child_ID2 < 0){
              exit(EXIT_FAILURE);
          }
          if (child_ID2 == 0){
              char *argv[] = {"makeDir", waktuSekarang, NULL};
              execv("/bin/mkdir", argv); 
          }
        while(wait(&status) > 0);
 
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
        char info[100] = "Download Complete";
        cipherCrypt(info, 5);
 
        FILE* status = fopen("status.txt", "w");
        fprintf(status,"%s", info);
        fclose(status);
        chdir("..");
        char waktu3[120];
            sprintf(waktu3, "%s.zip", waktuSekarang);
            char *arg[] = {"zip", "-r", waktu3, waktuSekarang, NULL};
            execv("/usr/bin/zip", arg);
        }
 
        //perintah hapus directory
        while((wait(&status))>0){
            char *argv3[] = {"remuv", "-r", waktuSekarang, NULL};
            execv("/usr/bin/rm", argv3);
        }
    sleep(40);
    }
}
