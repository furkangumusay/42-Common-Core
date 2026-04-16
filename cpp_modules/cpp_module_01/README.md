# C++ Module 01

C++ dünyasında bellek yönetimine, pointer ve referans kullanımlarına odaklanan ikinci OOP modülüdür. Bu projede heap ve stack allocation farkları işlenir.

## 🛠️ Mimari Kararlar ve Kullanılan Teknolojiler
- **Dil:** C++98
- **Konseptler:** Memory Allocation (`new`/`delete` - malloc/free yerine), Reference variables, Pointers as instances.
- **Switch:** Program esnasında sınıfların scope bağlamından çıkınca otomatik Destruction (`~`) edilmesi mekanizması üzerinde çalışıldı.

Modül, sınıf objelerinin tekil ya da dizi şeklinde (`new[]`) belleğe yüklenmesini ve sonrasında Memory Leak çıkmayacak şekilde uygun silinme mimarisinin (`delete[]`) yönetilmesi teknikleri ağırlıklıdır. Ayrıca dosya akışına (File Streams - `<fstream>`) okuma/yazma/kopyalama testleri uygulanır.

## 🚀 Derleme ve Çalıştırma

İstediğiniz egzersizin içine geçiş yaparak çalıştırın:

```bash
cd ex04
make
./replace file.txt "eski_kelime" "yeni_kelime"
```

---
**Author:** Furkan Gümüşay (fgumusay) 
[GitHub Profilim](https://github.com/furkangumusay)
