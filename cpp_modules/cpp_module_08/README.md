# C++ Module 08

C++ Standart Şablon Kütüphanesi'nin (STL - Standard Template Library) Container, Iterator ve Alghorithms veri altyapısına odaklanır. 

## 🛠️ Mimari Kararlar ve Kullanılan Teknolojiler
- **Araçlar:** Kapsayıcılar (`std::vector`, `std::list`, `std::stack`), İteratörler.
- **Mantık:** Verilerin C loop döngüleri yerine Iterator adapter mekanizması ile taranması ve `algorithm` kütüphanesinin kullanımı. 

Bu modülde özellikle standart `std::stack` gibi iterator ile foreach olarak dönmenin direkt desteklenmediği LIFO yapısındaki bir container'da, alttaki mevcut container (`std::deque` vb.) yapısına inerek kendi iteratör iterasyonlarımızı nasıl yaratabileceğimizin bir "MutantStack" mimarisi simülasyonu çalışılmaktadır.

## 🚀 Derleme

Tüm konseptleri çalıştırmak için:

```bash
cd ex02
make
./mutant_stack
```

---
**Author:** Furkan Gümüşay (fgumusay) 
[GitHub Profilim](https://github.com/furkangumusay)
