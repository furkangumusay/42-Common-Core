# C++ Module 03

Gelişmiş OOP'nin omurgalarından "Inheritance" (Kalıtım) üzerine pratik yaptıran modüldür. 

## 🛠️ Mimari Kararlar ve Kullanılan Teknolojiler
- **Konseptler:** Inheritance (Miras alma), Protected Access Modifier, Base - Derived class yapısı.
- **Problem:** Diamond Problem testine giriş (Virtual inheritance).

Modül, bir ana `ClapTrap` oyun karakteri (Robot) sınıfı oluşturulmasıyla başlar. Sonrasında bu sınıftan türemiş `ScavTrap` ve `FragTrap` ek özellikleri taşıyan alt robotlar miras kuralına göre constructor mimarisini çalıştırarak inşa edilir. Public vs. Private türetmelerindeki encapsulation koruması simülasyonu çalışılmış olur.

## 🚀 Derleme

Sıradan bir Make işlemi uygulanır:

```bash
cd ex02
make
./frag_trap
```

---
**Author:** Furkan Gümüşay (fgumusay) 
[GitHub Profilim](https://github.com/furkangumusay)
