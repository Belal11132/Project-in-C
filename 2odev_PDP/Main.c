#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dosya_okuma.h"
#include "simulasyon.h"
#include "zaman.h"
#include "uzay_araci.h"

// =====================
// تنسيق الطباعة الجديد
// =====================
 void printDurum(Simulasyon* sim) {
    printf("Gezegenler:\n");

    // --- A --- başlıkları
    printf("         ");
    for (int i = 0; i < sim->gezegenSayisi; i++) {
        char gezegenStr[20];
        sprintf(gezegenStr, "--- %s ---", sim->gezegenler[i]->isim);
        printf("%-14s", gezegenStr);
    }
    printf("\n");

    // Tarih
    printf("Tarih    ");
    for (int i = 0; i < sim->gezegenSayisi; i++) {
        char tarihStr[20];
        zamanYazdir(sim->gezegenler[i]->tarih, tarihStr);
        printf("%-14s", tarihStr);
    }
    printf("\n");

printf("Nufus    ");
for (int i = 0; i < sim->gezegenSayisi; i++) {
    int nufus = sim->gezegenler[i]->nufus;
    printf("%6d%8s", nufus, "");  
}
printf("\n\n");




    printf("Uzay Araclari:\n");
    printf("Arac Adi    Durum      Cikis     Varis     Kalan Mesafe     Varis Tarihi\n");


    for (int i = 0; i < sim->aracSayisi; i++) {
        UzayAraci* a = sim->araclar[i];
        char tarihStr[20];
        char bufferMesafe[10];

        const char* durumStr = NULL;
        if (a->durum == BEKLIYOR) {
            durumStr = "Bekliyor";
        } else if (a->durum == YOLDA) {
            durumStr = "Yolda";
        } else if (a->durum == IMHA) {
            durumStr = "Imha";
        } else {
            durumStr = "Vardi";
        }

        if (a->durum == IMHA) {
            strcpy(bufferMesafe, "-");
            strcpy(tarihStr, "--");
        } else {
            sprintf(bufferMesafe, "%d", a->hedefe_kalan_saat);
            zamanYazdir(a->hedefe_varis_tarihi, tarihStr);
        }

        printf("%-12s %-10s %-9s %-9s %-17s %s\n",
               a->isim, durumStr, a->cikis_gezegeni, a->varis_gezegeni,
               bufferMesafe, tarihStr);
    }

    printf("\n\nNufus Durumu:\n");
    printf("-----------------\n");

    int toplam = 0, yasayan = 0, olen = 0;
    for (int i = 0; i < sim->kisiSayisi; i++) {
        toplam++;
        if (sim->kisiler[i]->yasiyorMu) yasayan++;
        else olen++;
    }

    printf("Toplam Kisi: %d\n", toplam);
    printf("Hayatta Kalanlar: %d\n", yasayan);
    printf("Vefat Edenler: %d\n", olen);
    printf("-----------------\n");
}



// ====================
// دالة main الرئيسية
// ====================
int main() {
    int kisiSayisi, gezegenSayisi, aracSayisi;

    Kisi** kisiler = kisileriOku("veri/Kisiler.txt", &kisiSayisi);
    Gezegen** gezegenler = gezegenleriOku("veri/Gezegenler.txt", &gezegenSayisi);
UzayAraci** araclar = araclariOku("veri/Araclar.txt",
                                  &aracSayisi,
                                  kisiler,
                                  kisiSayisi,
                                  gezegenler,          // ✅ مرّر المؤشر
                                  gezegenSayisi);      // ✅ مرّر العدد

    if (!kisiler || !gezegenler || !araclar) {
        printf("Dosya okuma hatasi.\n");
        return 1;
    }

    Simulasyon* sim = simulasyonOlustur(kisiler, kisiSayisi, gezegenler, gezegenSayisi, araclar, aracSayisi);
    simulasyonuBaslat(sim);  // يحتوي على printDurum داخله

    simulasyonYokEt(sim);
    return 0;
}
