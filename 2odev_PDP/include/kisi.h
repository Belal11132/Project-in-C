#ifndef KISI_H
#define KISI_H

typedef struct {
    char* isim;
    int yas;
    double kalan_omur; // بالساعات
    int yasiyorMu;     // 1 = حي، 0 = ميت
} Kisi;

// Fonksiyonlar
Kisi* kisiOlustur(const char* isim, int yas, double kalan_omur);
void kisiYaslandir(Kisi* kisi, double carpan); // تناقص العمر حسب نوع الكوكب
void kisiYokEt(Kisi* kisi); // تحرير الذاكرة
#endif
