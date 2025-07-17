// uzay_araci.c

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "uzay_araci.h"
#include "zaman.h"


UzayAraci* uzayAraciOlustur(const char* isim,
                            const char* cikis,
                            const char* varis,
                            Gezegen* cikisGezegen,
                            Gezegen* varisGezegen,
                            Zaman cikis_tarihi,
                            int mesafe){

    UzayAraci* a = (UzayAraci*)malloc(sizeof(UzayAraci));

    a->cikisGezegen = cikisGezegen;
    a->varisGezegen = varisGezegen;

    a->isim = strdup(isim);
    a->cikis_gezegeni = strdup(cikis);
    a->varis_gezegeni = strdup(varis);
    a->cikis_tarihi = cikis_tarihi;
    a->mesafe_saat = mesafe;
    a->hedefe_kalan_saat = mesafe;
    a->durum = BEKLIYOR;
    a->hedefe_varis_tarihi = cikis_tarihi; // Başlangıçta varış tarihi kalkış tarihi ile aynı
    a->yolcu_sayisi = 0;
    a->yolcular = NULL;
    return a;
}

void uzayAraciYolcuEkle(UzayAraci* araci, Kisi* kisi) {
    araci->yolcular = (Kisi**)realloc(araci->yolcular,
                          sizeof(Kisi*) * (araci->yolcu_sayisi + 1));
    araci->yolcular[araci->yolcu_sayisi] = kisi;
    araci->yolcu_sayisi++;
}

// Kabis yıl kontrolü
int artikYilMi(int yil) {
    return (yil % 4 == 0 && yil % 100 != 0) || (yil % 400 == 0);
}

// Aylara göre gün sayısı
static int aylarinGunleri[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

int tariheGoreGunSayisi(Zaman z) {
    int gunSayisi = z.gun;

    // Her ayın gününü topla (Şubat = 28)
    for (int i = 0; i < z.ay - 1; i++) {
        gunSayisi += aylarinGunleri[i];
    }

    // Sadece aynı yıl için Şubat kontrolü
    if (z.ay > 2 && artikYilMi(z.yil)) {
        gunSayisi += 1;  // 29 Şubat varsa ekle
    }

    // Yıla göre toplam yıl gününü ekle
    gunSayisi += z.yil * 365 + z.yil / 4 - z.yil / 100 + z.yil / 400;

    return gunSayisi;
}
Zaman zamanEkleVeDondur(Zaman baslangic, int ekGun, int ekSaat, int gunlukSaat) {
    Zaman z = baslangic;
    z.saat += ekSaat;

    while (z.saat >= gunlukSaat) {
        z.saat -= gunlukSaat;
        ekGun++;
    }

    z.gun += ekGun;

    static int aylarinGunleri[12] = {31,28,31,30,31,30,31,31,30,31,30,31};

    while (1) {
        int ayGun = aylarinGunleri[z.ay - 1];
        if (z.ay == 2 && artikYilMi(z.yil)) ayGun = 29;

        if (z.gun <= ayGun) break;

        z.gun -= ayGun;
        z.ay++;
        if (z.ay > 12) {
            z.ay = 1;
            z.yil++;
        }
    }

    z.saat = gunlukSaat;
    return z;
}


// İki zaman arasındaki saat farkı
int zamanFarkSaat(Zaman z1, Zaman z2, int gunSaat) {
    int gun1 = tariheGoreGunSayisi(z1);
    int gun2 = tariheGoreGunSayisi(z2);
    return (gun1 - gun2) * gunSaat;
}

void uzayAraciHedefeVarisTarihiAtama(UzayAraci* araci) {
    int saatFarki = zamanFarkSaat(araci->cikis_tarihi,
                                  araci->cikisGezegen->tarih,
                                  araci->cikisGezegen->gunlukSaat);

    int toplamSaat = saatFarki + araci->mesafe_saat;

    int hedefGunlukSaat = araci->varisGezegen->gunlukSaat;
    int eklenecekGun = toplamSaat / hedefGunlukSaat;
    int eklenecekSaat = toplamSaat % hedefGunlukSaat;

    Zaman varisTarihi = zamanEkleVeDondur(araci->cikisGezegen->tarih, eklenecekGun, eklenecekSaat, hedefGunlukSaat);

    araci->hedefe_varis_tarihi = varisTarihi;
}

void uzayAraciIlerle(UzayAraci* araci) {
    // BEKLIYOR veya YOLDA durumundaysa ve henüz hedefe ulaşmadıysa:
    if ((araci->durum == BEKLIYOR || araci->durum == YOLDA)
         && araci->hedefe_kalan_saat > 0) {
        // kalkış zamanı geldiğinde otomatik YOLDA’ya geçiş
        araci->durum = YOLDA;
        araci->hedefe_kalan_saat--;
        // hedefe varınca tarih ataması simülasyonda yapılacak
    }
}

int uzayAraciHayattaKalanYolcuSayisi(UzayAraci* araci) {
    int sayac = 0;
    for (int i = 0; i < araci->yolcu_sayisi; i++) {
        if (araci->yolcular[i]->yasiyorMu)
            sayac++;
    }
    return sayac;
}

void uzayAraciYokEt(UzayAraci* araci) {
    if (!araci) return;
    for (int i = 0; i < araci->yolcu_sayisi; i++) {
        kisiYokEt(araci->yolcular[i]);
    }
    free(araci->yolcular);
    free(araci->isim);
    free(araci->cikis_gezegeni);
    free(araci->varis_gezegeni);
    free(araci);
}
