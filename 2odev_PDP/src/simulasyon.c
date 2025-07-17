#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#include "simulasyon.h"
#include "zaman.h"

void printDurum(Simulasyon* sim);

static int tumAraclarHedefeVardiMi(Simulasyon* sim) {
    for (int i = 0; i < sim->aracSayisi; i++) {
        UzayAraci* a = sim->araclar[i];
        if (a->durum == IMHA)
            continue;
        if ((a->durum == BEKLIYOR && a->hedefe_kalan_saat > 0)
         || (a->durum == YOLDA && a->hedefe_kalan_saat > 0))
            return 0;
    }
    return 1;
}

Simulasyon* simulasyonOlustur(Kisi** kisiler,
                              int kisiSayisi,
                              Gezegen** gezegenler,
                              int gezegenSayisi,
                              UzayAraci** araclar,
                              int aracSayisi) {
    Simulasyon* sim = (Simulasyon*)malloc(sizeof(Simulasyon));
    sim->kisiler = kisiler;
    sim->kisiSayisi = kisiSayisi;
    sim->gezegenler = gezegenler;
    sim->gezegenSayisi = gezegenSayisi;
    sim->araclar = araclar;
    sim->aracSayisi = aracSayisi;
    return sim;
}

void simulasyonuBaslat(Simulasyon* sim) {
    // Başlangıçta çıkış zamanı gelen araçları YOLDA yap
    for (int i = 0; i < sim->aracSayisi; i++) {
        UzayAraci* a = sim->araclar[i];
        Gezegen* g = gezegenBul(sim->gezegenler, sim->gezegenSayisi, a->cikis_gezegeni);
        if (a->durum == BEKLIYOR && zamanKarsilastir(g->tarih, a->cikis_tarihi) >= 0) {
            a->durum = YOLDA;
        }
    }

    while (!tumAraclarHedefeVardiMi(sim)) {
        system("cls");

        // 1. Gezegen zamanlarını ilerlet
        for (int i = 0; i < sim->gezegenSayisi; i++) {
            sim->gezegenler[i]->saatIlerle(sim->gezegenler[i]);
        }

        // 2. Her bir uzay aracı için işlem
        for (int i = 0; i < sim->aracSayisi; i++) {
            UzayAraci* a = sim->araclar[i];
            Gezegen* cikis = gezegenBul(sim->gezegenler, sim->gezegenSayisi, a->cikis_gezegeni);
            Gezegen* varis = gezegenBul(sim->gezegenler, sim->gezegenSayisi, a->varis_gezegeni);

            // Kalkış zamanı gelmişse YOLDA'ya geç
            if (a->durum == BEKLIYOR && zamanKarsilastir(cikis->tarih, a->cikis_tarihi) >= 0) {
                a->durum = YOLDA;
            }

            // Aracı ilerlet (sadece YOLDA iken)
            if (a->durum == YOLDA && a->hedefe_kalan_saat > 0) {
                uzayAraciIlerle(a);
            }

            // Yaşlandırma işlemi (hedefe ulaşmışsa gezegen çarpanı kullan)
            double carpan = (a->hedefe_kalan_saat > 0) ? 1.0 : varis->yaslanmaCarpani(varis);
            for (int j = 0; j < a->yolcu_sayisi; j++) {
                kisiYaslandir(a->yolcular[j], carpan);
            }

            // Hedefe ulaştıysa durum kontrolü ve nüfus aktarımı
            if (a->hedefe_kalan_saat == 0 && (a->durum == YOLDA || a->durum == BEKLIYOR)) {
                if (uzayAraciHayattaKalanYolcuSayisi(a) == 0) {
                    a->durum = IMHA;
                } else {
                    a->durum = VARDI;
                    for (int j = 0; j < a->yolcu_sayisi; j++) {
                        if (a->yolcular[j]->yasiyorMu) {
                            varis->nufus++;
                        }
                    }
                }
            }
        }

        // 3. Durumu yazdır
        printDurum(sim);
        Sleep(50);
    }
}

void simulasyonYokEt(Simulasyon* sim) {
    free(sim);
}
