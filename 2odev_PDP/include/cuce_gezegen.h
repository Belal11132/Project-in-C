#ifndef CUCE_GEZEGEN_H
#define CUCE_GEZEGEN_H

#include "gezegen.h"

typedef struct {
    Gezegen base; // kalıtım
} CuceGezegen;

CuceGezegen* cuceGezegenOlustur(const char* isim, int gunlukSaat, Zaman tarih);

#endif
