// zaman.c

#include <stdio.h>
#include "zaman.h"

// Ayların gün sayısı
static int ayGunleri[12] = {
    31,28,31,30,31,30,31,31,30,31,30,31
};

Zaman zamanOlustur(int gun,
                   int ay,
                   int yil,
                   int saat) {
    Zaman z = { gun, ay, yil, saat };
    return z;
}

void zamanIlerle(Zaman* z,
                 int saatSayisi,
                 int gunlukSaat) {
    z->saat += saatSayisi;
    while (z->saat >= gunlukSaat) {
        z->saat -= gunlukSaat;
        z->gun++;
        int maxGun = ayGunleri[z->ay - 1];
        if (z->ay == 2 &&
           ((z->yil % 4 == 0 && z->yil % 100 != 0) ||
            (z->yil % 400 == 0))) {
            maxGun = 29;
        }
        if (z->gun > maxGun) {
            z->gun = 1;
            z->ay++;
            if (z->ay > 12) {
                z->ay = 1;
                z->yil++;
            }
        }
    }
}

int zamanKarsilastir(Zaman a, Zaman b) {
    if (a.yil != b.yil) return (a.yil < b.yil) ? -1 : 1;
    if (a.ay  != b.ay)  return (a.ay  < b.ay)  ? -1 : 1;
    if (a.gun != b.gun) return (a.gun < b.gun) ? -1 : 1;
    if (a.saat!= b.saat)return (a.saat< b.saat)? -1 : 1;
    return 0;
}

void zamanYazdir(Zaman z, char* buffer) {
    sprintf(buffer, "%02d.%02d.%04d", z.gun, z.ay, z.yil);
}
