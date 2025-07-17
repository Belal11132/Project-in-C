#ifndef UZAY_ARACI_H
#define UZAY_ARACI_H

#include "kisi.h"
#include "zaman.h"
#include "gezegen.h"

typedef enum {
    BEKLIYOR,
    YOLDA,
    IMHA,
    VARDI,
} Durum;

typedef struct {
    char* isim;
    char* cikis_gezegeni;
    char* varis_gezegeni;
    Zaman cikis_tarihi;
    int mesafe_saat; // كم ساعة تحتاج للوصول
    int hedefe_kalan_saat;
    Zaman hedefe_varis_tarihi;
    Durum durum;

    
    Gezegen* cikisGezegen;
    Gezegen* varisGezegen;  



    Kisi** yolcular;
    int yolcu_sayisi;
} UzayAraci;

// Fonksiyonlar
UzayAraci* uzayAraciOlustur(const char* isim,
                            const char* cikis,
                            const char* varis,
                            Gezegen* cikisGezegen,
                            Gezegen* varisGezegen,
                            Zaman cikis_tarihi,
                            int mesafe);
void uzayAraciYolcuEkle(UzayAraci* araci, Kisi* kisi);
void uzayAraciIlerle(UzayAraci* araci);
void uzayAraciYokEt(UzayAraci* araci);
int uzayAraciHayattaKalanYolcuSayisi(UzayAraci* araci);

#endif
