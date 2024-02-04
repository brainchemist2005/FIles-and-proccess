  
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char** argv) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <commande>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    char* program = argv[1];

    while (1) {
        printf("Lancement du programme %s...\n", program);

        pid_t pid = fork();

        if (pid == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            execvp(program, &argv[1]);
            perror("execvp");
            exit(EXIT_FAILURE);
        } else {
            int status;
            waitpid(pid, &status, 0);
            if (WIFEXITED(status)) {
                if (WEXITSTATUS(status) == 0) {
                    printf("Le programme s'est terminé avec succès.\n");
                    exit(EXIT_SUCCESS);
                } else {
                    printf("Le programme a retourné un code d'erreur. Redémarrage automatique dans 5 secondes...\n");
                }
            } else {
                printf("Le programme a planté. Redémarrage automatique dans 5 secondes...\n");
            }

        }
    }

    return 0;
}

