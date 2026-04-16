# Inception

Sistem yönetimi (System Administration), sanallaştırma ve DevOps pratikleri konseptini Docker sanallaştırma ekosistemi üzerinde anlatan altyapı projesidir.

## 🛠️ Mimari Kararlar ve Kullanılan Teknolojiler
- **Sanallaştırma:** Docker, Docker-Compose.
- **Servisler:** NGINX (Web sunucusu), MariaDB (Veritabanı ilişkisel motoru), WordPress (PHP-FPM tabanlı içerik yönetim sistemi).

Bu projenin katı bir kuralı olarak hazır imaj kullanamayız. Sadece Alpine Linux v.b gibi temel çok hafif rootfs distro'ları üzerinden bir Dockerfile yazarak, shell scriptleri ile bu servislerin kendi internal custom ağlarında (`--network`) haberleşmesini inşa ederiz. Container içinde 1'den fazla çalışan deamon servis yasaklanarak Microservice prensibine ("Her container için tek bir iş mantığı") tam uyumlu kalındı. Ayrıca Volume mapping mantığı ile host ve container state durumlarının (database kayıtlarının persist edilmesi) korunması sağlandı. 

## 🚀 Başlatma ve Kullanım

Sistemi ayağa kaldırmak için gereken Docker orkestrasyonu:

```bash
cd srcs
docker-compose up -d --build
```

- Sistem ayağa kalktığında `https://fgumusay.42.fr` üzerinden SSL ile erişim gerçekleştirilir. TLS sertifikaları NGINX container'ında yönetilir.

---
**Author:** Furkan Gümüşay (fgumusay) 
[GitHub Profilim](https://github.com/furkangumusay)
