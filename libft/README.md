# Libft

Bu proje, C standart kütüphanesinin (libc) temel veri yapılarını ve bellek yönetim fonksiyonlarını yeniden yazmayı hedefler. Geliştirilen bu kütüphane, sonraki 42 projelerinde temel altyapı bileşeni statüsünde kullanılmaktadır.

## 🛠️ Mimari Kararlar ve Kullanılan Teknolojiler
- **Dil:** C
- **Derleme Aracı:** `Makefile`
- **Konseptler:** Pointer aritmetiği, bellek sızıntısı yönetimi, bağlı liste (linked list) implementasyonları (Bonus part).

Proje standart C fonksiyonlarının (`strlen`, `memset`, `atoi` vb.) yanı sıra, daha karmaşık string manipülasyonu ve bağlı liste operasyonlarını içeren veri yapılarını da sisteme adapte eder. Geliştirilen `libft.a` (static library) modüler bir yapıya sahiptir, böylece linker safhasında sadece kullanılan objelerin derlemeye katılması sağlanır.

## 🚀 Derleme ve Kullanım

Kütüphaneyi derlemek için kök dizinde şu komutu çalıştırmanız yeterlidir:

```bash
make
```

Bu komut statik bir `libft.a` dosyası üretir. Kendi projenizde kullanmak için derleme aşamasında kütüphaneyi dahil edebilirsiniz:
```bash
gcc main.c -L. -lft
```

---
**Author:** Furkan Gümüşay (fgumusay) 
[GitHub Profilim](https://github.com/furkangumusay)
