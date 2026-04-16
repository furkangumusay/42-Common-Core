# Cub3D

Efsanevi Wolfenstein 3D oyunundan esinlenilen ray-casting (ışın izleme) teknolojisi tabanlı sahte 3 boyutlu bir oyun motoru projesidir.

## 🛠️ Mimari Kararlar ve Kullanılan Teknolojiler
- **Grafik Motoru:** MiniLibX.
- **Odak:* Raycasting algoritması kullanımı, DDA (Digital Differential Analyzer) algoritması.

Projede bir kamera matrisi mevcuttur. Her bir pixel sütunu için oyuncudan dışarı bir ışın (ray) çıkar, labirent haritasındaki duvar blokajlarına çarptığı noktaya kadar mesafesi ölçülüp (perpendicular distance hesaplanması / balık gözü efektinden kaçınma), yansıma uzaklığına göre ekran yüksekliği çizdirilir. Yönlere göre textureların (`N, S, E, W`) memory'e yüklenmesi ve rendering döngüsü performans gerektirir.

## 🚀 Derleme ve Çalıştırma

Oyunu derlemek için:

```bash
make
```

Ardından derlenen projeyi bir map (harita) uzantısı dosyasıyla (`.cub`) çalıştırabilirsiniz:

```bash
./cub3D maps/map.cub
```

---
**Author:** Furkan Gümüşay (fgumusay) 
[GitHub Profilim](https://github.com/furkangumusay)
