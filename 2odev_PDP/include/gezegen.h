#ifndef GEZEGEN_H
#define GEZEGEN_H

#include "zaman.h"

typedef enum {
    KAYAC = 0,
    GAZ_DEVI = 1,
    BUZ_DEVI = 2,
    CUCE = 3
} GezegenTuru;

typedef struct Gezegen {
    char* isim;
    GezegenTuru tur;
    int gunlukSaat;          // الكوكب كم ساعة في اليوم
    Zaman tarih;
    int nufus;

    // Polimorfik yaşlandırma fonksiyonu
    double (*yaslanmaCarpani)(struct Gezegen*); 

    // Zaman ilerletme
    void (*saatIlerle)(struct Gezegen*);

} Gezegen;

Gezegen* gezegenOlustur(const char* isim, GezegenTuru tur, int gunlukSaat, Zaman tarih);
Gezegen* gezegenBul(Gezegen** gezegenler, int sayi, const char* isim);

void gezegenYokEt(Gezegen* g);

#endif
