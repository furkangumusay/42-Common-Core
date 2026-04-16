# C++ Module 06

Explicit type casting (açık tür dönüşümü) operasyonlarını derinleştiren modüldür. C dilindeki primitif `(int) variable` mantığından kurtulup güvenli tür dönüşümlerine geçişi sağlar.

## 🛠️ Mimari Kararlar ve Kullanılan Teknolojiler
- **Konseptler:** C++ Casts (`static_cast`, `dynamic_cast`, `reinterpret_cast`, `const_cast`).
- **Problemler:** Veri kayıpları ve kalıtımsal pointer dönüşümleri.

Downcasting ve upcasting senaryolarında, hafızanın rastgele bellek bölgelerini referanslamasını engellemek, RTTI (Run-Time Type Information) bağlamında çalışma zamanı hatalarını (örneğin C dilinde segmentation fault ile sonuçlanan pointer atamalarını) `dynamic_cast` ile kontrol edebilmek üzere scaler bir converter programı kodlanmıştır.

## 🚀 Derleme ve Kullanımı

Girilen herhangi bir literal değeri (int, float, double veya char tabanlı string formatında olan) çevirmek için:

```bash
cd ex00
make
./convert 42.0f
```

---
**Author:** Furkan Gümüşay (fgumusay) 
[GitHub Profilim](https://github.com/furkangumusay)
