#ifndef BUZ_DEVI_GEZEGEN_H
#define BUZ_DEVI_GEZEGEN_H

#include "gezegen.h"

typedef struct {
    Gezegen base; // kalıtım
} BuzDeviGezegen;

BuzDeviGezegen* buzDeviGezegenOlustur(const char* isim, int gunlukSaat, Zaman tarih);

#endif
