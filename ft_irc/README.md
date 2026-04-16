# ft_irc

RFC protokol standartları üzerinden TCP bazında haberleşen, C++ dilinde asenkron I/O yapılarını anlamamıza yarayan kendi "Internet Relay Chat - IRC" sunucumuz.

## 🛠️ Mimari Kararlar ve Kullanılan Teknolojiler
- **Dil:** C++98
- **Networking API:** Sockets (AF_INET, SOCK_STREAM).
- **Asenkron I/O Multiplexing:** `poll()` / `epoll` / `select` sistem çağrıları.

Bloke edici olmayan (Non-blocking I/O) server tasarlanmıştır ve tüm kullanıcı bağlantıları File Descriptor düzeyinde polling algoritmaları üzerinden tek bir thread içerisinde handle edilir (Reactor Pattern stili). Sunucuya standard bir IRC clienti (Örneğin: Irssi, nc) üzerinden bağlantı kurulabilir. JOIN, KICK, INVITE, TOPIC komutlarının yanısıra Kanal Modları olan `+i, +t, +k, +o, +l` implementasyonları da eklenmiştir.

## 🚀 Derleme ve Çalıştırma

Sunucuyu verilen bir bağlantı portu ve şifreyle (Örn: 6667 bağlantısı için) çalıştırma:

```bash
make
./ircserv 6667 sirketsifresi123
```

İstemci (Client) üzerinden bağlanırken:
```text
/connect 127.0.0.1 6667 sirketsifresi123
```

---
**Author:** Furkan Gümüşay (fgumusay) 
[GitHub Profilim](https://github.com/furkangumusay)
