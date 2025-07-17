#ifndef DOSYA_OKUMA_H
#define DOSYA_OKUMA_H

#include "kisi.h"
#include "gezegen.h"
#include "uzay_araci.h"

// Not: Dinamik diziler döner, *sayilar out parametre olarak verilir

// Kisi dosyasını oku
Kisi** kisileriOku(const char* dosyaAdi, int* kisiSayisi);

// Gezegen dosyasını oku
Gezegen** gezegenleriOku(const char* dosyaAdi, int* gezegenSayisi);

// Uzay aracı dosyasını oku
UzayAraci** araclariOku(const char* dosyaAdi,
                        int* aracSayisi,
                        Kisi** kisiler,
                        int kisiSayisi,
                        Gezegen** gezegenler,
                        int gezegenSayisi);

#endif
