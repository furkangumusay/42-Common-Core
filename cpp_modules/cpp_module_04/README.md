# C++ Module 04

Object Oriented Programming'in son büyük omurgası Polimorfizm (Subtype Polymorphism) konusuna odaklanan harika bir modüldür.

## 🛠️ Mimari Kararlar ve Kullanılan Teknolojiler
- **Konseptler:** Subtype Polymorphism, Virtual Functions (`virtual` keyword), Abstract Classes (`= 0`), Interfaces.

C++ modüler ilerleyişinin bu aşamasında "Hayvanlar" örneği üzerinden türeyen Kedi ve Köpek sınıflarının ses çıkarma eylemleri base-class olan Animal referansından çalıştırıldığında "virtual" dispatcher sayesinde compiler (derleme) aşaması yerine "runtime (çalışma zamanı)" aşamasında çözümlenir. Abstract Class yapısına çevrilmeye zorlanan yapı ile saf sanal (pure virtual) fonksiyon mantığı projenin core (ana) iskeletidir.

## 🚀 Derleme

Polimorfizm yeteneklerini deneyimlemek için:

```bash
cd ex00 # Veya ilgili exercise klasörü
make
./polymorphism_test
```

---
**Author:** Furkan Gümüşay (fgumusay) 
[GitHub Profilim](https://github.com/furkangumusay)
