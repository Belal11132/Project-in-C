// gezegen.c

#include <stdlib.h>
#include <string.h>
#include "gezegen.h"

Gezegen* gezegenOlustur(const char* isim,
                        GezegenTuru tur,
                        int gunlukSaat,
                        Zaman tarih) {
    Gezegen* g = (Gezegen*)malloc(sizeof(Gezegen));
    g->isim = strdup(isim);
    g->tur = tur;
    g->gunlukSaat = gunlukSaat;
    g->tarih = tarih;
    g->nufus = 0;
    g->yaslanmaCarpani = NULL;
    g->saatIlerle = NULL;
    return g;
}

Gezegen* gezegenBul(Gezegen** gezegenler, int sayi, const char* isim) {
    for (int i = 0; i < sayi; i++) {
        if (strcmp(gezegenler[i]->isim, isim) == 0) {
            return gezegenler[i];
        }
    }
    return NULL;  // bulunamazsa
}

void gezegenYokEt(Gezegen* g) {
    if (!g) return;
    free(g->isim);
    free(g);
}
