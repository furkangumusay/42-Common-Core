# Minitalk

İki farklı UNIX prosesi arasında (Client ve Server), yalnızca `SIGUSR1` ve `SIGUSR2` sinyallerini kullanarak bit seviyesinde asenkron veri iletişimi kurmayı sağlayan haberleşme programıdır.

## 🛠️ Mimari Kararlar ve Kullanılan Teknolojiler
- **Dil:** C
- **Teknolojiler:** UNIX Signals (`signal`, `sigaction`), Inter-Process Communication (IPC).
- **Mantık:** Verilerin bitwise operatörler (>> ve &) ile ikilik sisteme (binary) çevrilerek sinyaller halinde taşınması.

Server sürekli olarak sinyal bekler konumdadır. Client, verilen PID numarası üzerinden karakterin her bir bit'ini (0 veya 1) sırasıyla gönderir. `SIGUSR1` 0'ı, `SIGUSR2` ise 1'i temsil eder. Server, bit bazlı aldığı verileri tekrar asimile edip char türüne dönüştürerek ekrana basar.

## 🚀 Derleme ve Çalıştırma

Derleme işlemi sonrasında iki farklı çalıştırılabilir dosya elde edilir:

```bash
make
```

Önce `server` programını başlatın:
```bash
./server
# Ekranda server'ın PID si belirecektir.
```

Ardından farklı bir terminalde `client` üzerinden mesajınızı iletebilirsiniz:
```bash
./client <SERVER_PID> "Merhaba Dünya!"
```

---
**Author:** Furkan Gümüşay (fgumusay) 
[GitHub Profilim](https://github.com/furkangumusay)
