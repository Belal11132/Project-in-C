#ifndef GAZ_DEVI_GEZEGEN_H
#define GAZ_DEVI_GEZEGEN_H

#include "gezegen.h"

typedef struct {
    Gezegen base; // kalıtım
} GazDeviGezegen;

GazDeviGezegen* gazDeviGezegenOlustur(const char* isim, int gunlukSaat, Zaman tarih);

#endif
