#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dosya_okuma.h"
#include "kayac_gezegen.h"
#include "gaz_devi_gezegen.h"
#include "buz_devi_gezegen.h"
#include "cuce_gezegen.h"
#include "zaman.h"

#define MAX_LINE 256

// ------------------------------------------
// الأشخاص
Kisi** kisileriOku(const char* dosyaAdi, int* kisiSayisi) {
    FILE* file = fopen(dosyaAdi, "r");
    if (!file) return NULL;

    Kisi** kisiler = NULL;
    *kisiSayisi = 0;

    char line[MAX_LINE];
    while (fgets(line, sizeof(line), file)) {
        char* isim = strtok(line, "#");
        char* yasStr = strtok(NULL, "#");
        char* omurStr = strtok(NULL, "#");
        char* _ = strtok(NULL, "#"); // نجهل اسم المركبة الآن

        if (isim && yasStr && omurStr) {
            int yas = atoi(yasStr);
            double kalanOmur = atof(omurStr);

            Kisi* k = kisiOlustur(isim, yas, kalanOmur);
            kisiler = (Kisi**)realloc(kisiler, sizeof(Kisi*) * (*kisiSayisi + 1));
            kisiler[*kisiSayisi] = k;
            (*kisiSayisi)++;
        }
    }

    fclose(file);
    return kisiler;
}

// ------------------------------------------
// الكواكب
Gezegen** gezegenleriOku(const char* dosyaAdi, int* gezegenSayisi) {
    FILE* file = fopen(dosyaAdi, "r");
    if (!file) return NULL;

    Gezegen** gezegenler = NULL;
    *gezegenSayisi = 0;

    char line[MAX_LINE];
    while (fgets(line, sizeof(line), file)) {
        char* isim = strtok(line, "#");
        char* turStr = strtok(NULL, "#");
        char* saatStr = strtok(NULL, "#");
        char* tarihStr = strtok(NULL, "#");

        if (isim && turStr && saatStr && tarihStr) {
            int tur = atoi(turStr);
            int gunlukSaat = atoi(saatStr);
            int gun, ay, yil;
            sscanf(tarihStr, "%d.%d.%d", &gun, &ay, &yil);
            Zaman z = zamanOlustur(gun, ay, yil, 0);

            Gezegen* g = NULL;
            if (tur == 0)
                g = (Gezegen*)kayacGezegenOlustur(isim, gunlukSaat, z);
            else if (tur == 1)
                g = (Gezegen*)gazDeviGezegenOlustur(isim, gunlukSaat, z);
            else if (tur == 2)
                g = (Gezegen*)buzDeviGezegenOlustur(isim, gunlukSaat, z);
            else if (tur == 3)
                g = (Gezegen*)cuceGezegenOlustur(isim, gunlukSaat, z);

            if (g) {
                gezegenler = (Gezegen**)realloc(gezegenler, sizeof(Gezegen*) * (*gezegenSayisi + 1));
                gezegenler[*gezegenSayisi] = g;
                (*gezegenSayisi)++;
            }
        }
    }

    fclose(file);
    return gezegenler;
}

// ------------------------------------------
// المركبات الفضائية + ربط الأشخاص بها
UzayAraci** araclariOku(const char* dosyaAdi,
                        int* aracSayisi,
                        Kisi** kisiler,
                        int kisiSayisi,
                        Gezegen** gezegenler,
                        int gezegenSayisi) {
    FILE* file = fopen(dosyaAdi, "r");
    if (!file) return NULL;

    UzayAraci** araclar = NULL;
    *aracSayisi = 0;

    char line[MAX_LINE];
    while (fgets(line, sizeof(line), file)) {
        char* isim = strtok(line, "#");
        char* cikis = strtok(NULL, "#");
        char* varis = strtok(NULL, "#");
        char* tarihStr = strtok(NULL, "#");
        char* mesafeStr = strtok(NULL, "#");

        if (isim && cikis && varis && tarihStr && mesafeStr) {
            int gun, ay, yil;
            sscanf(tarihStr, "%d.%d.%d", &gun, &ay, &yil);
            Zaman cikisTarihi = zamanOlustur(gun, ay, yil, 0);
            int mesafe = atoi(mesafeStr);

            Gezegen* g1 = gezegenBul(gezegenler, gezegenSayisi, cikis);
            Gezegen* g2 = gezegenBul(gezegenler, gezegenSayisi, varis);
            UzayAraci* a = uzayAraciOlustur(isim, cikis, varis, g1, g2, cikisTarihi, mesafe);
            uzayAraciHedefeVarisTarihiAtama(a);
            // الأشخاص داخل هذه المركبة
            FILE* f2 = fopen("veri/Kisiler.txt", "r");
            if (f2) {
                char tempLine[MAX_LINE];
                int i = 0;
                while (fgets(tempLine, sizeof(tempLine), f2) && i < kisiSayisi) {
                    char* isim2 = strtok(tempLine, "#");
                    strtok(NULL, "#");
                    strtok(NULL, "#");
                    char* araciAdi = strtok(NULL, "#\n");

                    if (isim2 && araciAdi && strcmp(araciAdi, isim) == 0) {
                        uzayAraciYolcuEkle(a, kisiler[i]);
                    }
                    i++;
                }
                fclose(f2);
            }

            araclar = (UzayAraci**)realloc(araclar, sizeof(UzayAraci*) * (*aracSayisi + 1));
            araclar[*aracSayisi] = a;
            (*aracSayisi)++;
        }
    }

    fclose(file);
    return araclar;
}
