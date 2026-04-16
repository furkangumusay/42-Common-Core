# So Long

`so_long`, geliştiricilerin 2 boyutlu basit bir oyun motoru inşası üzerinden grafik programlama ve event tabanlı mimarilerle tanışmasını sağlayan bir oyundur.

## 🛠️ Mimari Kararlar ve Kullanılan Teknolojiler
- **Kütüphane:** MiniLibX (42 okullarının dahili OpenGL veya X11 wrap kütüphanesi).
- **Konseptler:** Window Management, Event Handling (Keyhooks), Render Loop, Texture Mapping.
- **Harita Algoritması:** Oyna uygunluğunun Flood Fill, Rectangle veya DFS algoritmaları ile parsellenmesi kısımlarını içerir.

Oyun, dışarıdan `.ber` uzantılı bir harita okur. Oyuncu (`P`), toplanabilir öğeleri (`C`) alarak çıkışa (`E`) sınırlandırılmış yollar dahilinde ulaşmaya çalışır. Nesne yönelimli olmayan bir sistemde stateleri (window boyutu, texture adresleri vd.) tutmak üzere struct tabanlı bir state management uygulanmıştır.

## 🚀 Derleme ve Çalıştırma

Projeyi derlemek için:

```bash
make
```

Oyunu derlediğiniz harita dizini ile başlatın:

```bash
./so_long maps/map1.ber
```

Oyun tuşları standart `W, A, S, D` olup, çıkış ve pencere yönetimi `ESC` ile handle edilir.

---
**Author:** Furkan Gümüşay (fgumusay) 
[GitHub Profilim](https://github.com/furkangumusay)
