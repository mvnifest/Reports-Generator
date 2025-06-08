# System RCP (Rejestracja Czasu Pracy)

Ten projekt to system napisany w języku C, który wczytuje dane o czasie pracy pracowników z plików tekstowych i przygotowuje je do dalszego przetwarzania. Wszystko jest podzielone na kilka folderów, dla łatwiejszego zrrozumienia kodu.

## Jak to działa?

- **input/** – tutaj znajduje się cały kod odpowiedzialny za wczytywanie danych z plików. Są tam trzy części:
  - `entries/` – godziny wejścia i wyjścia pracowników,
  - `absences/` – nieobecności,
  - `configs/` – konfiguracja zmian, czyli ile godzin ktoś powinien przepracować w danym miesiącu.

- **reports/** – tutaj będzie generowany raport z podsumowaniem.

- **user/** – są tu dane o pracownikach, np. kto ma jaką zmianę.

- **include/** – wspólne struktury (`Entry`, `Absence`, itd.), których używają wszystkie moduły.

- **main.c** – główny plik, który uruchamia cały program.

## Gdzie wrzucać dane?

- **RCP_IN/** – tutaj wrzucasz pliki z danymi, np. `RCP_2025-06-04.txt` albo `Absence_2025-06-04.txt`
- **RCP_Config/** – tutaj są pliki z wymaganiami godzinowymi dla danej zmiany
- **RCP_OUT/** – tutaj zapisuje się rapot


## Autorzy

- Konrad Biały
- Kamil Celadyn
- Misha Bodnar
-Filip Kasprzycki
