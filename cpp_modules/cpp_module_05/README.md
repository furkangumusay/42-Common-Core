# C++ Module 05

Try/Catch bloklarını (Exceptions handling) odaklanan, yazılımların çalışma anı çökmesini (crash) önleme ve hata ayıklama sistemine geçiş projesidir.

## 🛠️ Mimari Kararlar ve Kullanılan Teknolojiler
- **Konseptler:** Exception Handling (`try`, `catch`, `throw`), `std::exception` türetme.
- **Kurgu:** Bürokratlar, form onayları ve imza yetkileri simülasyonu.

Bir "Bureaucrat" sınıfı ve seviyeleri (1 en yüksek, 150 en düşük) simüle edip bir form sistemini imzalama ve execute etme eylemleri sırasında derecesinin eksiye, veya limitten fazlaya çıkması durumunda `new std::exception` logic'ine başvurmak yerine C++'ın Custom Exception inheritance tekniğini kullanarak kendi hata nesnelerimizi program patlamadan yakalamak hedeflenir.

## 🚀 Derleme

Projeyi derlemek ve Exception mekanizmasını konsolda doğrulamak için:

```bash
cd ex03
make
./bureaucrat
```

---
**Author:** Furkan Gümüşay (fgumusay) 
[GitHub Profilim](https://github.com/furkangumusay)
