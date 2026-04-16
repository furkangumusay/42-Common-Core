# C++ Module 02

Floating point (kayan noktalı sayı) verilerinin donanımsal yetersizliklerde nasıl Fixed Point (sabit nokta) veri yapısı olarak simüle edileceğini öğretir. 

## 🛠️ Konseptler ve Teknik Yapı
- **Kavramlar:** Ad-Hoc Polymorphism, Operator Overloading, Orthodox Canonical Form Sınıfı kuralı.

Proje boyunca varsayılan Constructor, Copy Constructor, Copy Assignment Operator ve Destructor kuralları zorunlu formatta tanımlanır (`Orthodox Canonical Form`). Ardından bir `Fixed` sayısı üretime geçilir. Bu noktada `+`, `-`, `>`, `<`, `++` gibi operatörler overload edilerek (aşırı yüklenerek) custom tiplerimizi sanki C++'ın primitive `int` veya `float` gibi sistemlerle uyumlu kullanabilmesi sağlanmıştır.

## 🚀 Derleme

Derleme basittir:

```bash
cd ex01
make
./fixed_point
```

---
**Author:** Furkan Gümüşay (fgumusay) 
[GitHub Profilim](https://github.com/furkangumusay)
