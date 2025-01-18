# Tiva-TM4-Hibernate

Texas Instruments TM4C123GH6PM mikrodenetleyicisi üzerinde, hibernation (derin uyku) modunun etkinleştirilmesi ve bu moddan çıkış için harici kesmelerin nasıl kullanılacağını ayrıntılı bir şekilde gösteren bir uygulama kodu tasarlanmıştır. Bu uygulama, mikrodenetleyicinin enerji verimliliğini artırmak amacıyla minimum güç tüketimi moduna geçmesini sağlar ve gerektiğinde dış kaynaklı tetiklemelerle yeniden aktif hale gelmesini mümkün kılar. Uygulama aynı zamanda GPIO kesme işlevselliğinin kullanımını ve LED'lerin bu kesmelere bağlı olarak kontrol edilmesini örneklemektedir.

## Özellikler ve Yapılandırmalar
Bu uygulamada, mikrodenetleyicinin enerji tasarrufu sağlayacak şekilde hibernation moduna geçirilmesi ve çevre birimlerinin kapatılması sağlanmıştır. Ayrıca, GPIO tabanlı harici kesmelerle sistemin yeniden aktif hale getirilmesi gösterilmektedir. Özellikle, PF0 ve PF4 pinleri düşen kenar (falling edge) kesmelerine duyarlı olacak şekilde yapılandırılmıştır. Böylece, harici bir tetikleme oluştuğunda mikrodenetleyici derin uyku modundan çıkarak görevine devam eder.

## Uygulamanın Ana Unsurları
1.Mikrodenetleyicinin Güç Tüketimi Yönetimi
Enerji tasarrufu sağlamak için mikrodenetleyici, SRAM ve flash güç yönetimiyle optimize edilmiştir. Çevre birimlerinin güç tüketimi SysCtlDeepSleepClockConfigSet() fonksiyonu ile yönetilebilir, böylece yalnızca gerekli bileşenler enerji harcar.

2.GPIO Kesme Kullanımı
PF0 ve PF4 pinleri, dış tetikleme algılamak amacıyla düşen kenar kesmelerine duyarlı olacak şekilde yapılandırılmıştır. Bu yapılandırma sayesinde, belirli bir olayın meydana gelmesi durumunda sistem uykudan çıkarak ilgili işlemi gerçekleştirebilir.

3.LED Kontrolü
Kesme gerçekleştiğinde, LED'lerin durumu güncellenerek işlemin doğru bir şekilde algılandığı ve kesmeye uygun tepki verildiği gözlemlenebilir.

## Kodun Öne Çıkan İşlevleri
SysCtlDeepSleep(): Mikrodenetleyiciyi derin uyku moduna geçirir ve enerji tüketimini minimuma indirir.
SysCtlDeepSleepClockConfigSet(): Çevre birimleri için saat yapılandırması yapılarak gereksiz bileşenlerin kapatılmasını sağlar.
GPIO Interrupts: PF0 ve PF4 pinleri düşen kenar kesmeleri için yapılandırılarak, harici olayların algılanmasını mümkün kılar.
## Çalışma Prensibi
1.Sistem ve GPIO Yapılandırması
Öncelikle, sistem saati ve GPIO pinleri yapılandırılır. PF0 ve PF4 pinleri, düşen kenar kesmelerine duyarlı olacak şekilde tanımlanır.

2.Hibernation Moduna Geçiş
Mikrodenetleyici, SysCtlDeepSleep() fonksiyonu ile derin uyku moduna geçirilir. Bu modda, enerji tasarrufu sağlamak için çevre birimleri devre dışı bırakılır ve yalnızca kesme sinyalleri takip edilir.

3.Harici Kesme ile Uyanma
Harici bir tetikleme (örneğin bir düğmeye basılması) olduğunda, PF0 veya PF4 pinleri kesmeyi tetikler. Bu kesme, mikrodenetleyiciyi derin uyku modundan çıkarır ve tanımlanan işlemleri gerçekleştirmesini sağlar.

4.Kesme Sonrası İşlemler
Mikrodenetleyici uyandıktan sonra, ilgili kesme doğrultusunda LED'ler kontrol edilerek kullanıcıya görsel bir geri bildirim sunulur.

## Örnek Senaryo
Bir sistemde, enerji tasarrufu sağlamak amacıyla hibernation moduna geçilir ve mikrodenetleyici yalnızca belirli bir tetikleme ile yeniden aktif hale gelir. Bu uygulama, bir düğmeye basıldığında veya harici bir olay gerçekleştiğinde mikrodenetleyicinin uyanmasını sağlar. LED'ler, kesmenin başarıyla algılandığını ve işlemin tamamlandığını göstermek için kullanılır. Bu yöntem, bataryayla çalışan sistemlerde güç tasarrufunu maksimum seviyeye çıkarmak için oldukça etkili bir yaklaşım sunar.

Uygulama kodunun ayrıntıları ve daha fazla bilgi için örnek bir proje dosyasına başvurabilirsiniz. Bu yapılandırma, enerji tasarrufu odaklı mikrodenetleyici projelerinde oldukça geniş bir kullanım alanına sahiptir.







