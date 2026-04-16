# ft_transcendence

Bu proje, 42 Common Core müfredatının Masterpiece'idir. Gerçek bir web uygulaması olan Pong tabanlı multiplayer online oyun geliştirmeyi amaçlar. Bu projede büyük ölçekli full-stack bir sistem dizayn edilmiştir.

## 🛠️ Mimari Kararlar ve Kullanılan Teknolojiler
- **Backend/API:** Modern bir stack mimarisi. Database olarak ilişkisel yapılar ve Authentication akışları (OAuth 2.0). 
- **Frontend / Client:** SPA (Single Page Application) yapısıyla asenkron akıcı kullanıcı interaksiyonları ve render. 
- **Game Engine:** Client tarafında WebSockets bazlı Live veri transfezi ve Game Rendering logic.
- **Orkestrasyon:** Docker.

Mimari bir monolithic karmaşıklıktan ayrılıp, API Endpoints, Frontend Client ve Live WebSockets tabanlı Socket.IO alt yapılarının birbiri ile izole haberleştiği, security açıkları (XSS, SQLi vb.) için Guard/Middleware konseptlerinin olduğu, DevOps pipeline'ı üzerine oturtulmuş gerçek bir enterprise software dizaynıdır. 

Sistem kullanıcı register/login döngüsüne sahip, profile, ranking scoreboard, 2FA güvenlik konsepti ile beslenmiştir.

## 🚀 Sistem Orkestrasyonu (Deployment)

Tüm container'ize modülleri prodüksiyone çıkartmak:

```bash
docker-compose up --build
```
Proje genel web servis erişim portunuz ve ayarlarınızdan direkt kullanıcılara hizmet verebilir durumdadır.

---
**Author:** Furkan Gümüşay (fgumusay) 
[GitHub Profilim](https://github.com/furkangumusay)
