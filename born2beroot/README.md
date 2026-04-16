# Born2beroot

## Proje Özeti
Sıfırdan güvenli bir sanal sunucu inşası ve sunucu altyapısı yönetimi projesidir. Bu proje, bir sistem yöneticisinin (System Administrator) yaklaşımıyla işletim sistemi kurulumunu, disk yapılandırmasını ve katı güvenlik önlemlerinin uygulanmasını amaçlar.

## Teknoloji Yığını
- **İşletim Sistemi:** Linux (Debian)
- **Sanallaştırma:** VirtualBox
- **Scripting:** Bash
- **Sistem Mimarisi & Güvenlik:** LVM, UFW, SSH, AppArmor

## Güvenlik ve Yapılandırma Mimarisi
- **LVM ile Şifrelenmiş Disk:** Bölümler Logical Volume Manager (LVM) kullanılarak oluşturulmuş ve disk şifreleme (encryption) uygulanarak veri güvenliği maksimum seviyeye çıkarılmıştır.
- **UFW (Uncomplicated Firewall):** Sunucu dışa kapatılmış olup, sadece belirli kurallarla **4242** portuna izin verecek şekilde firewall (güvenlik duvarı) konfigüre edilmiştir.
- **Güvenli SSH Bağlantısı:** Root kullanıcısının SSH ile uzaktan girişi kapatılmış (PermitRootLogin no), varsayılan 22 portu 4242 ile değiştirilmiş ve public key (açık anahtar) bazlı bağlantı yapısı kurulmuştur.
- **Parola Politikaları (Password Policy):** PAM (Pluggable Authentication Modules) üzerinden şifre karmaşıklığı zorunlu tutulmuş, eski şifrelerin tekrar kullanımı yasaklanmış ve giriş denemeleri sınırlandırılmıştır.
- **Sudo Kuralları:** Tüm sudo komutlarının `/var/log/sudo/` altında katı loglama politikalarıyla izlenmesi ve TTY (Teletype) ortamı gereksinimi zorunlu kılınmıştır.

## Monitoring Script
`monitoring.sh`, sistemin nabzını tutan bir bash script'idir. Cron job ile her 10 dakikada bir otomatik tetiklenir ve o anki sistemin hayati metriklerini hesaplar. Ardından tüm aktif terminallere `wall` komutunu kullanarak bir sunucu durum raporu ("broadcast" mesajı) basar.

---
**Author:** Furkan Gümüşay (fgumusay) - 42 Türkiye
[GitHub Profilim](https://github.com/furkangumusay)
