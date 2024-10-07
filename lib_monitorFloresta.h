#ifndef MONITORFLORESTA_H
#define MONITORFLORESTA_H

#define LIVRE '-'
#define SENSOR 'T'
#define FOGO '@'
#define QUEIMADO '/'

void monitorFloresta_inicializar();
void monitorFloresta_imprimir();
int monitorFloresta_gerarIncendio();
int monitorFloresta_combateIncendio();

#endif
