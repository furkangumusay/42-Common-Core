# C++ Module 00

C++ programlama mantığına giriş niteliği taşıyan bu modül, C'nin yapısal (procedural) yaklaşımından Nesne Yönelimli (Object-Oriented) yaklaşıma geçişi öğretir. 

## 🛠️ Mimari Kararlar ve Kullanılan Teknolojiler
- **Dil:** C++98 Standartları
- **Konseptler:** Class yapısı tasarımı, Encapsulation, Pointers to member functions.
- **Standart Kutuphane:** G/Ç objeleri (`std::cout`, `std::cin` vs.) kullanımı ve standart namespace mantığı.

Projede amaçlanan temel unsur, sınıfları (Class) doğru bir formatta (Header `.hpp` ve kaynak `.cpp` ayrımı = Orthodox Canonical Class Form hazırlık) entegre etmektir. Bir telefon rehberi (Phonebook) entegrasyonu oluşturarak public/private scope yönetimlerinin ve getter/setter algoritmalarının hafızayı sızdırmadan uygulanması sağlanmıştır.

## 🚀 Derleme ve Çalıştırma

Projeyi derlemek için ilgili `ex` (exercise) klasörüne girin:

```bash
cd ex01
make
```

Oluşan çalıştırılabilir dosyayı doğrudan başlatın. Telefon rehberi komut bekleyecektir (`ADD`, `SEARCH`, `EXIT`):

```bash
./phonebook
```

---
**Author:** Furkan Gümüşay (fgumusay) 
[GitHub Profilim](https://github.com/furkangumusay)
