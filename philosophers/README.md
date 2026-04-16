# Philosophers

Bu proje, ünlü bilgisayar bilimleri problemi "Yemek Yiyen Filozoflar (Dining Philosophers)" üzerine inşa edilmiştir. Eşzamanlı (concurrent) programlamadaki race condition (kargaşa), deadlock (kilitlenme) ve thread yönetimi problemlerini ele alır.

## 🛠️ Mimari Kararlar ve Kullanılan Teknolojiler
- **Dil:** C
- **Teknolojiler:** POSIX Threads (`pthread`), Mutex (`pthread_mutex_lock/unlock`).
- **Problemin Taraması:** Deadlock prevention, Data Races.

Projenin mimarisi, her filozofun bağımsız bir thread olarak çalıştırılmasına ve kaynakların (masadaki çatallar) mutexler aracılığıyla senkronize edilmesine dayanır. Zaman yönetimi yüksek hassasiyetli time fonksiyonları (gettimeofday) ile kontrol altındadır. Bir asenkron dedektif (monitor thread), filozofların senkronunu düzenli kontrol ederek ölümleri zaman kilitli milisaniyeler altında denetler.

## 🚀 Derleme ve Çalıştırma

Projeyi derlemek için:

```bash
make
```

Çalıştırma formatı milisaniye cinsinden argümanlar alır (`Filozof_Sayısı`, `Ölme_Süresi`, `Yeme_Süresi`, `Uyuma_Süresi`, `[Hedef_Öğün]`):

```bash
./philo 5 800 200 200
```
Bu örnek; 5 filozofun olduğu, 800ms aç kalırlarsa ölecekleri ve 200'er ms yiyip uyuyacakları bir senaryodur. Sistem anlık zaman durumuyla eylemleri output olarak verecektir.

---
**Author:** Furkan Gümüşay (fgumusay) 
[GitHub Profilim](https://github.com/furkangumusay)
