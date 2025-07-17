#include <stdlib.h>
#include <string.h>
#include "gaz_devi_gezegen.h"
#include "zaman.h"

// Yaşlanma çarpanı (0.1 = 10 kat daha uzun yaşar)
static double gazDeviYaslanma(struct Gezegen* g) {
    return 0.1;
}

// Saat ilerletme fonksiyonu
static void saatIlerleGazDevi(struct Gezegen* g) {
    zamanIlerle(&(g->tarih), 1, g->gunlukSaat);
}

GazDeviGezegen* gazDeviGezegenOlustur(const char* isim, int gunlukSaat, Zaman tarih) {
    GazDeviGezegen* g = (GazDeviGezegen*)malloc(sizeof(GazDeviGezegen));
    g->base.isim = strdup(isim);
    g->base.tur = GAZ_DEVI;
    g->base.gunlukSaat = gunlukSaat;
    g->base.tarih = tarih;
    g->base.nufus = 0;
    g->base.yaslanmaCarpani = gazDeviYaslanma;
    g->base.saatIlerle = saatIlerleGazDevi;
    return g;
}
