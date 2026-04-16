# Get Next Line (GNL)

`get_next_line`, bir File Descriptor (FD) üzerinden okuma yaparak, her çağrıldığında text satırını (newline karakterine kadar) geri döndüren bir I/O fonksiyonudur. Program bellek manipülasyonunu ve static değişkenlerin kontrolünü test etmek üzere dizayn edilmiştir.

## 🛠️ Mimari Kararlar ve Kullanılan Teknolojiler
- **Dil:** C
- **Kavramlar:** Static Variables, File I/O, Buffer Management, Memory Allocation.
- **Bonus:** Çoklu File Descriptor (Multi-FD) yönetimi.

Projenin temelinde belleği sızdırmadan döngüsel okuma stratejisi yatar. `BUFFER_SIZE` makro tanımına bağlı olarak dinamik okuma yapar, okuduğu karakterleri realloc mantığı ile dinamik olarak genişletebildiği veri havuzunda (`static char *`) saklar.

## 🚀 Derleme ve Kullanım

Kütüphane projenize eklenerek kullanılır. Kullanılacak projede kendi `main.c` dosyanızla derlerken `BUFFER_SIZE` flag'ini tanımlayabilirsiniz:

```bash
gcc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c main.c
```

Örnek kullanım döngüsü:
```c
char *line;
int fd = open("test.txt", O_RDONLY);
while ((line = get_next_line(fd)))
{
    printf("%s", line);
    free(line);
}
```

---
**Author:** Furkan Gümüşay (fgumusay) 
[GitHub Profilim](https://github.com/furkangumusay)
