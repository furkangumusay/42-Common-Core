# ft_printf

Standart C kütüphanesindeki meşhur `printf` fonksiyonunun baştan yazılmış versiyonudur. Değişken sayıda argüman alan (Variadic Functions) fonksiyonların çalışma mantığını anlamayı sağlar.

## 🛠️ Mimari Kararlar ve Kullanılan Teknolojiler
- **Dil:** C
- **Kavramlar:** Variadic Arguments (`stdarg.h`), Parsing (Format Strings), Format Specifiers (cspdiuxX%).
- **Derleme Aracı:** `Makefile`

Proje yapısında her bir format (%d, %x, %s vb.) için ayrıştırılmış özel output fonksiyonları bulunur. `libft` kütüphanesiz olarak modüler parse algoritmaları kullanılmıştır. Bu tasarım pattern'i sayesinde yeni yazdırma tiplerinin eklenmesi O(1) maliyetle gerçekleştirilebilir.

## 🚀 Derleme ve Kullanım

Projeyi derleyip `libftprintf.a` kütüphanesini elde etmek için:

```bash
make
```

Kendi kodunuzda şu şekilde kullanabilirsiniz:

```c
#include "ft_printf.h"

int main() {
    ft_printf("Merhaba, sayı: %d, hexadecimal: %x\n", 42, 42);
    return 0;
}
```
Derleme parametresi olarak `-L. -lftprintf` vermeyi unutmayın.

---
**Author:** Furkan Gümüşay (fgumusay) 
[GitHub Profilim](https://github.com/furkangumusay)
