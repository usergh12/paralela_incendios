#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "lib_monitorFloresta.h"

#define TAMANHO 30

void* executar_sensor(void* arg) {
    (void)arg;
    while (1) {
        sleep(1);
    }
    return NULL;
}

void* gerar_incendio(void* arg) {
    (void)arg;
    while (1) {
        sleep(3);
        if (monitorFloresta_gerarIncendio()) {
            system("cls");
            monitorFloresta_imprimir();
        }
    }
    return NULL;
}

void* central_de_controle(void* arg) {
    (void)arg;
    while (1) {
        sleep(3);
        if (monitorFloresta_combateIncendio()) {
            system("cls");
            monitorFloresta_imprimir();
        }
    }
    return NULL;
}

int main() {
    srand(time(NULL));
    monitorFloresta_inicializar();
    monitorFloresta_imprimir();

    pthread_t thread_incendio, thread_central;

    pthread_create(&thread_incendio, NULL, gerar_incendio, NULL);
    pthread_create(&thread_central, NULL, central_de_controle, NULL);

    pthread_join(thread_incendio, NULL);
    pthread_join(thread_central, NULL);

    return 0;
}
