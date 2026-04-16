# C++ Module 07

Generics konseptini kazandıran Templates (Şablonlar) mimarisidir. DRY (Don't Repeat Yourself) prensibini en iyi uygulatan modüllerden birisidir.

## 🛠️ Mimari Kararlar ve Standartlar
- **Kavramlar:** Function Templates, Class Templates.
- **Odak:** Aynı mantık akışına sahip ama veritipleri farklı olan fonksiyonlar için compiler'a blueprint vermek.

Aynı `swap` ve `max`/`min` gibi eylemlerin integer, float veya karmaşık bir class için sürekli tekrar tekrar fonksiyon overload ederek baştan yazılması yerine `<typename T>` formatı tanımlanarak bir kerelik kod base'i compiler'a aktarılır. Örneklerde Array isimli custom template container simülasyonu çalışılmıştır.

## 🚀 Derleme

Tüm testleri ilgili dizinde çalıştırıp derleyin:

```bash
cd ex02
make
./template_array
```

---
**Author:** Furkan Gümüşay (fgumusay) 
[GitHub Profilim](https://github.com/furkangumusay)
