# C++ Module 09

Bu modül, C++ STL kullanıcısını büyük scale edilmiş algoritmik senaryolar kullanarak verilerin en optimal container'da depolanması kararına zorlar.

## 🛠️ Mimari Kararlar ve Kullanılan Algoritmalar
- **Odak:** Ford-Johnson (Merge-Insert) algoritması, RPN hesaplayıcısı ve Bitcoin borsa simülasyonu.

Program verimlilik açısından değerlendirildiğinde `std::vector` ile `std::deque` (veya std::list) gibi yapıların cache-miss performansları kıyaslanabilmesi amacıyla 3000'den büyük boyutlu element listelerinde Ford-Johnson algoritması koşturur. Big-O karmaşıklığında n log n garantisine dayanan optimizasyonlar yapar.

## 🚀 Derleme ve Çalıştırma

Projenin derlenmesi ve analizi:

```bash
cd ex02
make
./PmergeMe 3 5 9 7 4
```

---
**Author:** Furkan Gümüşay (fgumusay) 
[GitHub Profilim](https://github.com/furkangumusay)
