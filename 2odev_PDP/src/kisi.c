#include <stdlib.h>
#include <string.h>
#include "kisi.h"

Kisi* kisiOlustur(const char* isim, int yas, double kalan_omur) {
    Kisi* yeni = (Kisi*)malloc(sizeof(Kisi));
    yeni->isim = strdup(isim);
    yeni->yas = yas;
    yeni->kalan_omur = kalan_omur;
    yeni->yasiyorMu = 1;
    return yeni;
}

void kisiYaslandir(Kisi* kisi, double carpan) {
    if (kisi->yasiyorMu) {
        kisi->kalan_omur -= carpan;
        if (kisi->kalan_omur <= 0) {
            kisi->kalan_omur = 0;
            kisi->yasiyorMu = 0;
        }
    }
}

void kisiYokEt(Kisi* kisi) {
    if (kisi != NULL) {
        free(kisi->isim);
        free(kisi);
    }
}
