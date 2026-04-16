# Minishell

Bu proje, Bash benzeri bir komut satırı arayüzünü (shell) baştan kodlamayı hedefleyen, parse mimarisi ve çevre yolu yönetimlerinin tam kapasite inşasını gerektiren kapsamlı bir Unix projesidir.

## 🛠️ Mimari Kararlar ve Kullanılan Teknolojiler
- **Konseptler:** Lexing/Parsing (AST Ağaçları / Tokenizer), Process Creation (`fork`, `execve`), Pipe / Redirection, Signal Handling.
- **Kütüphaneler:** readline kütüphanesi harici kendi modüler sistemleri kullanıldı.

Mimari aşaması temelde 3 yapı bloğuna ayrılır:
1. **Lexer/Parser:** Kullanıcı girişini okur, stringleri tokenize eder ve pipe `|`, Yönlendirme `>`, `<` vb. söz dizimi ağacında (AST) çözümler.
2. **Expander:** Environment variable'larını (`$USER` veya tırnak yönetimi) parse ortamında işler.
3. **Executor:** AST nodelarını recursive döngüler veya lineer listeler aracılığıyla çalıştırır, built-in fonksiyonları barındırır (cd, pwd, export, unset, env vs). File Descriptor kopyalama (dup2) yoluyla pipe bağlantıları oluşturur.

## 🚀 Derleme ve Çalıştırma

Projeyi tam bağımlılıklarıyla derlemek için:

```bash
make
```

Programı çalıştırdıktan sonra Bash gibi bir prompt satırı açılacaktır:

```bash
./minishell
minishell$ echo Hello $USER | grep "Hello" > output.txt
```

---
**Author:** Furkan Gümüşay (fgumusay) 
[GitHub Profilim](https://github.com/furkangumusay)
