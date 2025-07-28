# Rechenspiel – FPA_01_05_02.c

Dieses Programm ist ein Konsolen-basiertes Rechenspiel, das den Benutzer in bis zu 10 Runden herausfordert, die Summe zweier Zahlen zu berechnen. Es eignet sich ideal zum Üben von Benutzereingaben, Kontrollstrukturen und Validierung in C.

## Funktionsweise

- Zu Beginn kann gewählt werden, ob mit Zufallszahlen gespielt wird.
- - Alternativ ist es möglich, das Programm mit "random" oder "norandom" aufzurufen. Dies startet den gewünschten Modus direkt.
- - Ungültige Kommandozeilenargumente führen zur Beendigung des Programms
- - Gültig ist, neben "random" und "norandom" auch "--help".
- In jeder Runde werden zwei Zahlen vorgegeben (entweder vom Benutzer eingegeben oder zufällig generiert).
- Der Benutzer muss die Summe der beiden Zahlen berechnen und eingeben.
- Alle Eingaben werden auf Gültigkeit geprüft, sodass nur ganze Zahlen akzeptiert werden.
- Nach jeder Runde kann entschieden werden, ob weitergespielt werden soll.
- Nach 10 Runden oder bei Abbruch wird die Anzahl der richtigen und falschen Antworten ausgegeben.

## Bedienung

1. Kompilieren Sie das Programm:
   ```
   make
   ```
2. Starten Sie das Programm:
   ```
   ./rechenspiel
   ```
3. Folgen Sie den Anweisungen im Terminal.

## Installation (Linux)

1. Kompilieren:
   ```
   make
   ```

2. Installieren:
   ```
   make install
   ```

3. Bei Bedarf Deinstallieren:

   ```
   make uninstall
   ```

## Hinweise

- Bei ungültigen Eingaben (keine ganze Zahl, falsche Auswahl) wird eine Fehlermeldung ausgegeben und die Eingabe wiederholt.
- Die Zufallszahlen liegen zwischen 1 und 25.
- Das Spiel endet automatisch nach 10 Runden oder wenn Sie nicht weiterspielen möchten.

---

**Autor:**  
Eric Freiberg  
WBS Schulung FIAE US_IT_74.4  
Übung: Programmiersprachen und prozedurale Programmierung
