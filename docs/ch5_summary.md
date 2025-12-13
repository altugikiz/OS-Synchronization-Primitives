# Chapter 5: Process Synchronization - Summary Note

[cite_start]Based on *Operating System Concepts - 9th Edition*[cite: 653].

## 1. Temel Kavramlar
* [cite_start]**Race Condition:** Birden fazla process'in paylaşılan veriye (shared data) aynı anda erişip değiştirmesi sonucu oluşan veri tutarsızlığı[cite: 716].
* **Critical Section (Kritik Bölge):** Paylaşılan verinin değiştirildiği kod parçasıdır. [cite_start]Aynı anda sadece 1 process burada olabilir[cite: 746].

## [cite_start]2. Critical Section Çözüm Şartları [cite: 773-775]
1.  **Mutual Exclusion (Karşılıklı Dışlama):** Biri içerideyken diğeri giremez.
2.  **Progress (İlerleme):** İçeride kimse yoksa, girmek isteyen bekletilmez.
3.  **Bounded Waiting (Sınırlı Bekleme):** Bir process içeri girmek istediğinde sonsuza kadar bekletilmemelidir.

## 3. Çözüm Araçları
### [cite_start]A. Mutex Locks [cite: 931]
* En basit araçtır.
* `acquire()`: Kilidi al (meşgulse bekle).
* `release()`: Kilidi bırak.
* [cite_start]**Spinlock:** Beklerken sürekli döngüde kontrol etme (Busy waiting) durumudur[cite: 936].

### [cite_start]B. Semaphores [cite: 958]
* **Counting Semaphore:** Değeri herhangi bir sayı olabilir (Kaynak yönetimi için).
* [cite_start]**Binary Semaphore:** Değeri sadece 0 veya 1 olabilir (Mutex gibi çalışır)[cite: 979].
* Operasyonlar atomiktir:
    * [cite_start]`wait()` (veya P): Değeri azaltır, negatifse bekler[cite: 965].
    * [cite_start]`signal()` (veya V): Değeri artırır, bekleyen varsa uyandırır[cite: 971].

### [cite_start]C. Monitors [cite: 1213]
* Semanforlardan daha yüksek seviyeli (high-level) bir soyutlamadır.
* Bir Class/Modül gibidir, aynı anda sadece bir process içindeki metodu çalıştırabilir.
* [cite_start]**Condition Variables:** `x.wait()` ve `x.signal()` ile özel senkronizasyon sağlar[cite: 1244].

## 4. Klasik Problemler
1.  [cite_start]**Bounded-Buffer (Producer-Consumer):** Dolu ve boş slot sayısını semaforla yönetir[cite: 1068].
2.  [cite_start]**Readers-Writers:** Çoklu okuyucuya izin ver, yazara tek başına izin ver[cite: 1106].
3.  **Dining Philosophers:** 5 filozof, 5 çatal. [cite_start]Deadlock ve Starvation riski vardır[cite: 1162].
    * [cite_start]**Çözüm:** Asimetrik çözüm (Tekler solu, çiftler sağı alır)[cite: 1195].

## 5. Deadlock & Starvation
* [cite_start]**Deadlock:** İki process'in birbirinin tuttuğu kaynağı beklemesi ve sonsuza kadar durması[cite: 1040].
* [cite_start]**Starvation:** Bir process'in semafor kuyruğunda sonsuza kadar beklemesi[cite: 1053].