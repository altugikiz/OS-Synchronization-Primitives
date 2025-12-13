# Chapter 4: Threads - Summary Note

[cite_start]Based on *Operating System Concepts - 9th Edition*[cite: 2].

## 1. Thread Nedir?
* [cite_start]**Tanım:** CPU kullanımının temel birimidir (Fundamental unit of CPU utilization)[cite: 16].
* [cite_start]**Fark:** "Process" oluşturmak "heavy-weight" (ağır) iken, "Thread" oluşturmak "light-weight" (hafif) bir işlemdir[cite: 33].
* **Yapısı:** Her thread'in kendine ait:
    * Program Counter
    * Register Set
    * [cite_start]Stack alanı vardır [cite: 60-69].
    * [cite_start]**Paylaşılanlar:** Code, Data ve Files (Process ile ortaktır)[cite: 116].

## 2. Neden Multithreading? (Benefits)
1.  [cite_start]**Responsiveness (Tepkisellik):** Uygulamanın bir kısmı bloklansa bile (örn: resim yüklenirken) arayüz çalışmaya devam eder[cite: 50].
2.  [cite_start]**Resource Sharing (Kaynak Paylaşımı):** Thread'ler belleği ve kaynakları otomatik paylaşır[cite: 51].
3.  [cite_start]**Economy:** Process oluşturmaktan daha ucuzdur ve context-switch maliyeti düşüktür[cite: 52].
4.  [cite_start]**Scalability:** Multiprocessor mimarilerde her thread farklı bir çekirdekte çalışabilir[cite: 53].

## 3. Concurrency vs Parallelism
* **Concurrency (Eşzamanlılık):** Tek çekirdekte bile olur. [cite_start]Görevler zaman paylaşımıyla ilerler[cite: 68, 69].
* **Parallelism (Paralellik):** Birden fazla çekirdek gerekir. [cite_start]Görevler fiziksel olarak aynı anda çalışır[cite: 67].
    * [cite_start]**Data Parallelism:** Aynı verinin alt kümeleri farklı çekirdeklerde işlenir[cite: 76].
    * [cite_start]**Task Parallelism:** Farklı görevler (fonksiyonlar) farklı çekirdeklerde çalışır[cite: 77].

## 4. Amdahl's Law
[cite_start]Sisteme çekirdek eklemenin performansı ne kadar artıracağını hesaplar[cite: 134].
$$speedup \le \frac{1}{S + \frac{(1-S)}{N}}$$
* **S:** Kodun seri (paralelleştirilemeyen) kısmı.
* **N:** Çekirdek sayısı.
* [cite_start]Seri kısım ne kadar fazlaysa, çekirdek eklemenin faydası o kadar azalır[cite: 140].

## 5. Multithreading Modelleri
* **Many-to-One:** Çoklu kullanıcı thread'i -> 1 Kernel thread'i. [cite_start]Biri bloklanırsa hepsi durur [cite: 170-172].
* **One-to-One:** 1 Kullanıcı thread'i -> 1 Kernel thread'i. [cite_start]Daha fazla concurrency sağlar (Linux, Windows bunu kullanır) [cite: 182-184].
* [cite_start]**Many-to-Many:** M kullanıcı thread'i -> N kernel thread'i[cite: 199].

## 6. Implicit Threading (Örtülü Threading)
[cite_start]Thread yönetimi programcıdan alınıp derleyiciye veya kütüphaneye verilir[cite: 414].
* [cite_start]**Thread Pools:** Önceden oluşturulmuş thread havuzu[cite: 426].
* [cite_start]**OpenMP:** Compiler direktifleri ile paralellik (#pragma omp parallel)[cite: 441].
* [cite_start]**Grand Central Dispatch (GCD):** Apple (Mac OS/iOS) teknolojisi[cite: 465].