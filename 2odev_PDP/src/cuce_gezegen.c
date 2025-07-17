#include <stdlib.h>
#include <string.h>
#include "cuce_gezegen.h"
#include "zaman.h"

// Yaşlanma çarpanı (0.01 = 100 kat daha uzun yaşar)
static double cuceYaslanma(struct Gezegen* g) {
    return 0.01;
}

// Saat ilerletme fonksiyonu
static void saatIlerleCuce(struct Gezegen* g) {
    zamanIlerle(&(g->tarih), 1, g->gunlukSaat);
}

CuceGezegen* cuceGezegenOlustur(const char* isim, int gunlukSaat, Zaman tarih) {
    CuceGezegen* c = (CuceGezegen*)malloc(sizeof(CuceGezegen));
    c->base.isim = strdup(isim);
    c->base.tur = CUCE;
    c->base.gunlukSaat = gunlukSaat;
    c->base.tarih = tarih;
    c->base.nufus = 0;
    c->base.yaslanmaCarpani = cuceYaslanma;
    c->base.saatIlerle = saatIlerleCuce;
    return c;
}
