# Chapter 7: Deadlocks - Summary Note

Based on *Operating System Concepts - 9th Edition*.

## 1. Deadlock Nedir?
İki veya daha fazla işlemin (process), birbirlerinin elindeki kaynağı beklemesi ve bu yüzden sonsuza kadar ilerleyememesi durumudur.
[cite_start]*Örnek:* Tren yolu kavşağında iki trenin birbirinin geçmesini beklemesi [cite: 2271-2273].

## 2. Deadlock İçin 4 Gerekli Koşul (Necessary Conditions)
[cite_start]Bir deadlock oluşması için bu 4 koşulun **AYNI ANDA** gerçekleşmesi gerekir [cite: 2334-2340]:
1.  **Mutual Exclusion (Karşılıklı Dışlama):** Kaynak aynı anda sadece bir kişi tarafından kullanılabilir.
2.  **Hold and Wait (Tut ve Bekle):** Bir kaynağı tutan süreç, başka bir kaynağı bekliyor.
3.  **No Preemption (Zorla Alma Yok):** Kaynak, sahibi işini bitirmeden zorla elinden alınamaz.
4.  **Circular Wait (Dairesel Bekleme):** $P_0 \rightarrow P_1 \rightarrow P_2 \rightarrow P_0$ şeklinde bir bekleme döngüsü olmalı.

## [cite_start]3. Deadlock ile Mücadele Yöntemleri [cite: 2483-2492]

### A. Deadlock Prevention (Önleme)
[cite_start]4 koşuldan en az birini bozarak deadlock'u imkansız hale getirmektir[cite: 2503].
* *Hold and Wait'i bozmak:* Process başlamadan tüm kaynakları istesin.
* *Circular Wait'i bozmak:* Kaynaklara numara ver ve sadece artan sırada iste.

### B. Deadlock Avoidance (Kaçınma)
[cite_start]Sistem kaynakları vermeden önce "Bu işlemi yaparsam sistem tehlikeye girer mi?" diye analiz eder[cite: 2568].
* [cite_start]**Safe State:** Sistemdeki herkesin ihtiyacını karşılayabilecek bir sıranın var olmasıdır[cite: 2577].
* **Banker's Algorithm:** Çoklu kaynak türleri için kullanılır. [cite_start]`Available`, `Allocation`, `Need` matrislerini kullanarak güvenli sırayı arar[cite: 2695].

### C. Deadlock Detection (Tespit Etme)
[cite_start]Deadlock oluşmasına izin verilir, periyodik olarak kontrol edilir[cite: 2772].
* [cite_start]**Wait-for Graph:** Tek kaynaklı sistemlerde döngü (cycle) var mı diye bakılır[cite: 2780].
* [cite_start]**Detection Algorithm:** Banker's algoritmasına benzer bir mantıkla çalışır[cite: 2821].

### D. Recovery (Kurtarma)
[cite_start]Deadlock tespit edilirse ne yapılır? [cite: 2865]
* Tüm kilitli süreçleri öldür (Abort all).
* Deadlock çözülene kadar tek tek süreçleri öldür.
* Kaynakları zorla geri al (Resource Preemption).