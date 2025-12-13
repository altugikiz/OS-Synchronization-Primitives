# Chapter 6: CPU Scheduling - Summary Note

Based on *Operating System Concepts - 9th Edition*.

## 1. Temel Kavramlar (Basic Concepts)
* [cite_start]**CPU-I/O Burst Cycle:** Process yürütümü, CPU kullanımı (CPU burst) ve I/O bekleme (I/O burst) döngülerinden oluşur[cite: 24].
* [cite_start]**CPU Scheduler (Short-term):** Ready kuyruğundaki processlerden hangisinin CPU'yu alacağına karar verir [cite: 69-70].
* **Dispatcher:** Scheduler tarafından seçilen process'e CPU kontrolünü veren modüldür. [cite_start]Context switch ve User mode'a geçişi yapar [cite: 89-91].
* **Preemptive vs Non-preemptive:**
    * [cite_start]**Non-preemptive (Kesintisiz):** Process CPU'yu alınca, işi bitene veya I/O bekleyene kadar bırakmaz [cite: 78-79].
    * [cite_start]**Preemptive (Kesintili):** İşletim sistemi, çalışan bir process'i zorla durdurup başka bir process'e geçebilir (Time-sharing sistemler için gereklidir)[cite: 80].

## [cite_start]2. Planlama Kriterleri (Scheduling Criteria) [cite: 99-105]
Bir algoritmanın başarısı bu metriklere göre ölçülür:
1.  **CPU Utilization:** CPU'yu mümkün olduğunca meşgul tutmak.
2.  **Throughput (Verimlilik):** Birim zamanda tamamlanan process sayısı.
3.  **Turnaround Time:** Bir process'in sisteme girişinden bitişine kadar geçen süre.
4.  **Waiting Time:** Process'in ready kuyruğunda beklediği toplam süre.
5.  **Response Time:** İlk isteğin gönderilmesinden ilk cevabın üretilmesine kadar geçen süre (Time-sharing için kritiktir).

## 3. Planlama Algoritmaları (Scheduling Algorithms)

### A. First-Come, First-Served (FCFS)
* **Mantık:** İlk gelen CPU'yu alır (FIFO kuyruğu).
* [cite_start]**Tür:** Non-preemptive[cite: 139].
* **Sorun:** **Convoy Effect**. [cite_start]Uzun bir process öndeyse, arkasındaki kısa process'ler onu bekler, ortalama bekleme süresi artar[cite: 148].

### B. Shortest-Job-First (SJF)
* [cite_start]**Mantık:** Bir sonraki CPU burst süresi en kısa olan process seçilir[cite: 170].
* [cite_start]**Avantaj:** Ortalama bekleme süresi açısından **Optimal** (en iyi) algoritmadır[cite: 172].
* [cite_start]**Zorluk:** Bir sonraki burst süresini kesin olarak bilmek imkansızdır (Tahmin etmek için *Exponential Averaging* kullanılır)[cite: 173, 210].
* [cite_start]**Preemptive Versiyonu:** *Shortest-Remaining-Time-First* olarak adlandırılır[cite: 218].

### C. Priority Scheduling
* [cite_start]**Mantık:** Her process'e bir öncelik sayısı atanır (genelde düşük sayı = yüksek öncelik)[cite: 297].
* **Sorun:** **Starvation (Açlık)**. [cite_start]Düşük öncelikli processler sonsuza kadar bekleyebilir[cite: 301].
* **Çözüm:** **Aging (Yaşlandırma)**. [cite_start]Bekleyen process'in önceliğini zamanla artırmak[cite: 303].

### D. Round Robin (RR) 

[Image of Round Robin scheduling chart]

* [cite_start]**Mantık:** Her process'e **Time Quantum (q)** denilen küçük bir süre verilir (örn: 10-100ms)[cite: 324]. Süre bitince process kesilir ve kuyruğun sonuna atılır.
* [cite_start]**Tür:** Preemptive[cite: 349].
* **Performans:**
    * [cite_start]`q` çok büyükse -> FCFS'ye dönüşür[cite: 330].
    * [cite_start]`q` çok küçükse -> Context switch maliyeti (overhead) çok artar[cite: 332].

### E. Multilevel Queue
* [cite_start]Ready kuyruğu farklı sınıflara ayrılır (örn: Foreground/Interactive ve Background/Batch)[cite: 435].
* [cite_start]Her kuyruğun kendi algoritması vardır (örn: Foreground için RR, Background için FCFS)[cite: 441].

### F. Multilevel Feedback Queue
* Processler kuyruklar arasında hareket edebilir. [cite_start]Çok CPU kullanan aşağı, çok bekleyen yukarı taşınabilir (Aging uygulanabilir)[cite: 465].

## 4. Çok İşlemcili Planlama (Multiple-Processor Scheduling)
* [cite_start]**SMP (Symmetric Multiprocessing):** Her işlemci kendi kendini planlar (self-scheduling)[cite: 500].
* **Processor Affinity:** Bir process'in sürekli aynı işlemcide çalışmak istemesi (Cache verimliliği için).
    * [cite_start]*Soft Affinity:* İşletim sistemi dener ama garanti etmez[cite: 503].
    * [cite_start]*Hard Affinity:* Process belirli işlemcilerde çalışmayı zorunlu kılar[cite: 504].
* [cite_start]**Load Balancing:** İş yükünü işlemcilere eşit dağıtmak[cite: 523].
    * [cite_start]*Push Migration:* Periyodik kontrolle yükü fazla olandan alıp diğerine itmek[cite: 524].
    * [cite_start]*Pull Migration:* Boşta kalan işlemcinin iş çekmesi[cite: 525].

## 5. İşletim Sistemi Örnekleri
* **Linux (CFS):** *Completely Fair Scheduler* kullanır. [cite_start]Görevleri *Red-Black Tree* yapısında tutar ve `vruntime` (virtual run time) değeri en düşük olanı seçer[cite: 591, 600, 606].
* **Windows:** Öncelik tabanlıdır (Priority-based). 32 öncelik seviyesi vardır. [cite_start]En yüksek öncelikli thread çalışır[cite: 648, 653].