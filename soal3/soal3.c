#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <wait.h>
#include <time.h>

int main(int argc, char *argv[]) {
    
    // Jika banyaknya argumen salah
    if (argc != 2) {
        printf("ERROR! Argumen salah!\n");
        return 1;
    }

    // Jika argumen yang dimasukkan salah
    if (strcmp(argv[1], "-z") != 0 && strcmp(argv[1], "-x") != 0) {
        printf("ERROR! Mode salah!\n");
        return 1;
    }

    pid_t pid, sid;        // Variabel untuk menyimpan PID

    pid = fork();     // Menyimpan PID dari Child Process

    /* Keluar saat fork gagal
    * (nilai variabel pid < 0) */
    if (pid < 0) {
        exit(EXIT_FAILURE);
    }

    /* Keluar saat fork berhasil
    * (nilai variabel pid adalah PID dari child process) */
    if (pid > 0) {
        exit(EXIT_SUCCESS);
    }

    umask(0);

    sid = setsid();
    if (sid < 0) {
        exit(EXIT_FAILURE);
    }

    FILE *killer_prog = fopen("killer.sh", "w");

    if (strcmp(argv[1], "-z") == 0) {
        char *inputan = ""
        "#!/bin/bash\n"
        "killall -9 ./soal3\n"
        "rm $0\n";
        fprintf(killer_prog, inputan, sid);
    }

    else if (strcmp(argv[1], "-x") == 0) {
        char *inputan = ""
        "#!/bin/bash\n"
        "kill %d\n"
        "rm $0\n";
        fprintf(killer_prog, inputan, getpid());
    }

    fclose(killer_prog);

    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);

    while (1) {
        time_t rawtime = time(NULL);
        struct tm *timeinfo;
        char buffer[80];

        timeinfo = localtime(&rawtime);
        strftime(buffer, 80, "%Y-%m-%d_%X", timeinfo);

        pid_t child_id, child_id2, child_id3, child_id4;
        child_id = fork();

        // Child process 1
        if (child_id == 0) {
            char *argv[] = {"mkdir", buffer, NULL};
            execv("/bin/mkdir", argv);
        }

        child_id2 = fork();

        // Child process 2
        if (child_id2 == 0) {
            for (int i = 0; i < 10; i++) {
                child_id3 = fork();
                
                // Child process 3
                if (child_id3 == 0) {
                    char buffer2[80], location[160], link[80];
                    rawtime = time(NULL);

                    timeinfo = localtime(&rawtime);
                    strftime(buffer2, 80, "%Y-%m-%d_%X", timeinfo);

                    sprintf(location, "%s/%s", buffer, buffer2);
                    sprintf(link, "https://picsum.photos/%ld", ((rawtime % 1000) + 50));

                    char *argv[] = {"wget", "-q", "-O", location, link, NULL};
                    execv("/bin/wget", argv);
                }

                sleep(5);
            }
            
            while (wait(NULL) > 0);

            child_id4 = fork();

            // Child process 4
            if (child_id4 == 0) {
                char message[80] = "Download Success", file_name[160];
                
                for (int j = 0; j < strlen(message); j++) {
                    if (message[j] >= 'a' && message[j] <= 'z') {
                        message[j] += 5;

                        if (message[j] > 'z') {
                            message[j] = message[j] - 'z' + 'a' - 1;
                        }
                    }

                    else if (message[j] >= 'A' && message[j] <= 'Z') {
                        message[j] += 5;

                        if (message[j] > 'Z') {
                            message[j] = message[j] - 'Z' + 'A' - 1;
                        }
                    }
                }
                
                sprintf(file_name, "%s/%s", buffer, "status.txt");
                FILE *txt = fopen(file_name, "w");

                fputs(message, txt);
                fclose(txt);

                sprintf(file_name, "%s.zip", buffer);
                
                char *argv[] = {"zip", "-r", file_name, buffer, NULL};
                execv("/bin/zip", argv);
            }

            while (wait(NULL) != child_id4);
            
            char *argv[] = {"rm", "-r", buffer, NULL};
            execv("/bin/rm", argv);
        }        
        sleep(40);
    }
}
