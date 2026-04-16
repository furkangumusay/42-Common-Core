# Push Swap

Verilen bir dizilimi (integer seti) iki farklı yığın (Stack A ve Stack B) kullanarak, kurallarla sınırlandırılmış talimat seti yardımıyla en az hamle sayısında sıralamayı hedefleyen bir algoritmik sıralama projesidir.

## 🛠️ Mimari Kararlar ve Kullanılan Teknolojiler
- **Dil:** C
- **Algoritmik Yaklaşım:** Radix Sort ve Selection Sort (veri setinin boyutuna göre optimizasyon).
- **Veri Yapısı:** Array/Linked list tabanlı modüler Stack simülasyonu.
- **Kurallar:** `sa, sb, ss, pa, pb, ra, rb, rr, rra, rrb, rrr` spesifik stack operasyonları.

Büyük input setleri (örneğin 500 element) için Big-O notasyonu optimize edilmiş Radix Sort uyarlaması kullanırken, daha ufak input (3, 5 element) setleri için hard-coded minimum instruction (talimat) çözümleri algoritmaya dinamik olarak eklenmiştir.

## 🚀 Derleme ve Çalıştırma

Projeyi derlemek için:

```bash
make
```

Çalıştırmak ve hamle sayısını test etmek için:

```bash
./push_swap 4 67 3 87 23
```
Proje çıktı olarak yalnızca gerçekleştirilmesi gereken talimatları (örn: `ra`, `pa`, `rra`) sıralı bir şekilde stdout'a basar.

---
**Author:** Furkan Gümüşay (fgumusay) 
[GitHub Profilim](https://github.com/furkangumusay)
