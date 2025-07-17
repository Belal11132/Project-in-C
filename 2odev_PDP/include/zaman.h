#ifndef ZAMAN_H
#define ZAMAN_H

typedef struct {
    int gun;
    int ay;
    int yil;
    int saat;
} Zaman;

// Fonksiyonlar
Zaman zamanOlustur(int gun, int ay, int yil, int saat);
void zamanIlerle(Zaman* z, int saatSayisi, int gunlukSaat); // saat ilerletir
int zamanKarsilastir(Zaman a, Zaman b); // 0: eşit, -1: a<b, 1: a>b
void zamanYazdir(Zaman z, char* buffer); // örn: 3.11.2022
Zaman zamanEkleVeDondur(Zaman baslangic, int ekGun, int ekSaat, int gunlukSaat);

#endif
