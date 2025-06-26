Erzeugen Sie f¨ur einen gegebenen Username u und einer Anzahl n mit einem Shell-
Skript generate tan eine TAN-Liste von n Nummern f¨ur u, die f¨ur ein Online-
Banking-System benutzt werden k¨onnten. Verwenden Sie hierbei eines der in der
Vorlesung vorgestellten Verfahren (Lamport, HOTP oder TOTP).
Simulieren Sie den Server durch ein Shell-Skript bank transaction, das
  • in einer Endlosschleife läuft,
  • nicht mit [STRG+C] abgebrochen werden kann und
  • von der Tastatur zwei Eingaben entgegennimmt:
    – Username
    – TAN
Pro User soll in einem Unterverzeichnis TAN eine Datei existieren, die die aktuel-
le TAN-Liste enth¨alt. ¨Uberlegen Sie sich einen geeigneten Mechanismus, dass die
aktuelle TAN gepr¨uft wird.
Das Skript bank transaction soll ausgeben
  • Zugriff erlaubt, wenn die aktuelle TAN richtig war
  • Zugriff verweigert, wenn
    – die aktuelle TAN falsch war oder
  – die TAN-Liste des Users aufgebraucht ist
