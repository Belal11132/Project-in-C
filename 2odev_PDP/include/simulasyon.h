#ifndef SIMULASYON_H
#define SIMULASYON_H

#include "kisi.h"
#include "gezegen.h"
#include "uzay_araci.h"

typedef struct {
    Kisi** kisiler;
    int kisiSayisi;

    Gezegen** gezegenler;
    int gezegenSayisi;

    UzayAraci** araclar;
    int aracSayisi;
} Simulasyon;

// Fonksiyonlar
Simulasyon* simulasyonOlustur(Kisi** kisiler, int kisiSayisi,
                              Gezegen** gezegenler, int gezegenSayisi,
                              UzayAraci** araclar, int aracSayisi);

void simulasyonuBaslat(Simulasyon* sim);
void simulasyonYokEt(Simulasyon* sim);

#endif
    