#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h> 
#include "lib_monitorFloresta.h"

#define TAMANHO 30

static char floresta[TAMANHO][TAMANHO];
static pthread_mutex_t exclusaoMutua = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t cond_fogo = PTHREAD_COND_INITIALIZER;

void monitorFloresta_inicializar() {
    pthread_mutex_lock(&exclusaoMutua);
    for (int i = 0; i < TAMANHO; i++) {
        for (int j = 0; j < TAMANHO; j++) {
            floresta[i][j] = LIVRE;
        }
    }
    for (int i = 1; i < TAMANHO - 1; i++) {
        for (int j = 1; j < TAMANHO - 1; j++) {
            if ((i % 2 == 1) && (j % 2 == 1)) {
                floresta[i][j] = SENSOR;
            }
        }
    }
    pthread_mutex_unlock(&exclusaoMutua);
}

void monitorFloresta_imprimir() {
    pthread_mutex_lock(&exclusaoMutua);
    for (int i = 0; i < TAMANHO; i++) {
        for (int j = 0; j < TAMANHO; j++) {
            printf("%c ", floresta[i][j]);
        }
        printf("\n");
    }
    pthread_mutex_unlock(&exclusaoMutua);
}

int monitorFloresta_gerarIncendio() {
    pthread_mutex_lock(&exclusaoMutua);
    int x = rand() % TAMANHO;
    int y = rand() % TAMANHO;

    if (floresta[x][y] == LIVRE || floresta[x][y] == SENSOR) {
        floresta[x][y] = FOGO;
        printf("Gerar incendio em [%d, %d].\n", x, y);
        pthread_cond_broadcast(&cond_fogo);
        pthread_mutex_unlock(&exclusaoMutua);
        sleep(2);
        return 1;
    }

    pthread_mutex_unlock(&exclusaoMutua);
    return 0;
}

int monitorFloresta_combateIncendio() {
    int mudou = 0;
    pthread_mutex_lock(&exclusaoMutua);
    for (int i = 0; i < TAMANHO; i++) {
        for (int j = 0; j < TAMANHO; j++) {
            if (floresta[i][j] == FOGO) {
                floresta[i][j] = QUEIMADO;
                mudou = 1;
                printf("Comabter o incendio em [%d, %d].\n", i, j);
                sleep(2);
            }
        }
    }
    pthread_mutex_unlock(&exclusaoMutua);
    return mudou;
}
