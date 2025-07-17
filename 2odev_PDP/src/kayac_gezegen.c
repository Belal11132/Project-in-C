#include <stdlib.h>
#include <string.h>
#include "kayac_gezegen.h"
#include "zaman.h"

// Yaşlanma çarpanı (1.0 = normal yaşlanma)
static double kayacYaslanma(struct Gezegen* g) {
    return 1.0;
}

// Saat ilerletme fonksiyonu
static void saatIlerleKayac(struct Gezegen* g) {
    zamanIlerle(&(g->tarih), 1, g->gunlukSaat);
}

KayacGezegen* kayacGezegenOlustur(const char* isim, int gunlukSaat, Zaman tarih) {
    KayacGezegen* k = (KayacGezegen*)malloc(sizeof(KayacGezegen));
    k->base.isim = strdup(isim);
    k->base.tur = KAYAC;
    k->base.gunlukSaat = gunlukSaat;
    k->base.tarih = tarih;
    k->base.nufus = 0;
    k->base.yaslanmaCarpani = kayacYaslanma;
    k->base.saatIlerle = saatIlerleKayac;
    return k;
}
