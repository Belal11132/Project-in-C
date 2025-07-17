#include <stdlib.h>
#include <string.h>
#include "buz_devi_gezegen.h"
#include "zaman.h"

// Yaşlanma çarpanı (0.5 = 2 kat uzun yaşar)
static double buzDeviYaslanma(struct Gezegen* g) {
    return 0.5;
}

// Saat ilerletme fonksiyonu
static void saatIlerleBuzDevi(struct Gezegen* g) {
    zamanIlerle(&(g->tarih), 1, g->gunlukSaat);
}

BuzDeviGezegen* buzDeviGezegenOlustur(const char* isim, int gunlukSaat, Zaman tarih) {
    BuzDeviGezegen* b = (BuzDeviGezegen*)malloc(sizeof(BuzDeviGezegen));
    b->base.isim = strdup(isim);
    b->base.tur = BUZ_DEVI;
    b->base.gunlukSaat = gunlukSaat;
    b->base.tarih = tarih;
    b->base.nufus = 0;
    b->base.yaslanmaCarpani = buzDeviYaslanma;
    b->base.saatIlerle = saatIlerleBuzDevi;
    return b;
}
