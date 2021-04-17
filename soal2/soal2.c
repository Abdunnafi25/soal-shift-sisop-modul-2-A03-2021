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
