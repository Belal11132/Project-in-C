#ifndef KAYAC_GEZEGEN_H
#define KAYAC_GEZEGEN_H

#include "gezegen.h"

typedef struct {
    Gezegen base; // kalıtım
} KayacGezegen;

// Oluşturma fonksiyonu
KayacGezegen* kayacGezegenOlustur(const char* isim, int gunlukSaat, Zaman tarih);

#endif
