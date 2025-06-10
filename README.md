# System RCP (Rejestracja Czasu Pracy)

Ten projekt to system napisany w języku C, który wczytuje dane o czasie pracy pracowników z plików tekstowych i generuje raporty oraz podsumowania. Program obsługuje nie tylko godziny wejścia i wyjścia, ale też nieobecności i wymagania dotyczące czasu pracy.

## Jak to działa?

- **input/** – tutaj znajduje się kod odpowiedzialny za
wczytywanie danych z plików:
  - `entries/` – odczytuje godziny rozpoczęcia i zakończenia pracy (RCP_IN),
  - `absences/` – obsługuje dane o nieobecnościach,
  - `configs/` – wczytuje wymagania czasowe dla poszczególnych zmian pracy (np. ile godzin pracownik ma przepracować w danym miesiącu).

- **reports/** – generuje raporty dla pracowników oraz podsumowania całkowite.

- **user/** – przechowuje dane o pracownikach, takie jak ID, imię i nazwisko oraz przypisany schemat pracy.

- **include/** – zawiera pliki nagłówkowe i definicje wspólnych struktur (`Entry`, `User`, `Absence`, `ScheduleConfig`, itd.), używanych przez wszystkie moduły.

- **main.c** – główny plik, który uruchamia cały system i wyświetla menu.

## Gdzie wrzucać dane?

- **RCP_IN/** – tutaj wrzucasz pliki z wejściem/wyjściem pracowników w formacie:
1;2025-06-04 07:00:00;2025-06-04 15:00:00;
2;2025-06-04 07:05:00;2025-06-04 14:45:00;

Nazwy plików mają format `RCP_YYYY_MM_DD.txt`.

- **RCP_Config/** – pliki konfiguracyjne zawierające liczbę wymaganych godzin dla danej zmiany (np. zmiana 1 – poranna). Nazwy plików i zawartość zależą od dnia i typu schematu.

- **RCP_OUT/** – tutaj generowane są gotowe raporty tekstowe dla pracowników.

## Co robi program?

- Wczytuje dane z plików w odpowiednich folderach.
- Pozwala podejrzeć dane o pracownikach.
- Generuje raporty z przepracowanymi godzinami, nadgodzinami, nieobecnościami i porównaniem z wymaganym czasem.
- Obsługuje różne typy zmian pracy: 7–14, 14–22 oraz nienormowany.

## Autorzy

- Konrad Biały
- Kamil Celadyn
- Misha Bodnar
- Filip Kasprzycki
