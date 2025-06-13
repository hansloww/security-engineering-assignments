Implementieren Sie folgendes Erzeuger–Verbraucher–Schema mit Hilfe von Shared
Memory und Semaphoren. Ein Vaterprozess P1 legt Semaphoren und Shared Me-
mory Segment an. Danach erzeugt er den Sohnprozess P2, der als Prozesskopie
die Semaphoren-ID und die Shared–Mem–ID kennt. Hierf¨ur ist nur fork() ohne
exec*() nötig. Der Prozess P1 wird Daten in den gemeinsamen Speicher schreiben,
die Prozess P2 dort herauslesen wird.
Der Erzeugerprozess P1 h¨alt ein Array gef¨ullt mit int–Daten, deren Anzahl sei durch
eine
#define N_DATA 2000000
Direktive festgelegt. Die Daten werden von P1 zufällig erzeugt (siehe srand48(),
lrand48()).
Der Verbraucherprozess P2 soll diese Daten erhalten, indem diese ¨uber einen von
P1 und P2 genutzten shared memory Block übertragen werden. Im shared–memory
Bereich finden weniger als N DATA viele Zahlen Platz, etwa
#define N_SHARED 2000
Prozess P1 muss also die gr¨oßere Anzahl Daten in mehreren Durchläufen durch den
kleineren Shared–Puffer übertragen.
Hinweise: es empfiehlt sich ein schrittweises Vorgehen
• zun¨achst eine Lösung ohne Semaphoren und nur einen Schreib–/Lesevorgang
im Shared–Memory–Bereich:
P2 wartet mittels sleep()), damit P1 Zeit hat, die Daten zu schreiben
• danach Semaphoren hinzunehmen, es werden zwei Semaphoren benötigt:
– eine Semaphore S1, mit der der Erzeuger den Lesevorgang f¨ur den Ver-
braucher freigibt (V–Operation)
– eine Semaphore S2, mit der der Verbraucher den Schreibvorgang f¨ur den
Erzeuger freigibt (V–Operation)
– der Verbraucher muss mit einer P–Operation auf S1 den Lesezugriff an-
fordern
– der Erzeuger muss mit einer P–Operation auf S2 den Schreibzugriff an-
fordern
– inital muss Schreiben erlaubt und Lesen verboten sein
• danach mehrere Schreib–/Lesevorgänge
• beachten Sie, dass Semaphoren und Shared Memory permanent vorhandene
Objekte sind, die explizit gelöscht werden m¨ussen (semctl(), shmctl())
