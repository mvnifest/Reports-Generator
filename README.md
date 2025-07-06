# RCP System (Working Time Registration)

This project is a system written in C that reads employee working time data from text files and generates reports and summaries. The program handles not only clock-in and clock-out times but also absences and work time requirements.

## How does it work?

- **input/** – contains the code responsible for reading data from files:
  - `entries/` – reads clock-in and clock-out times (RCP_IN),
  - `absences/` – handles absence data,
  - `configs/` – loads time requirements for different work shifts (e.g., how many hours an employee must work in a given month).

- **reports/** – generates employee reports and overall summaries.

- **user/** – stores data about employees such as ID, first and last name, and assigned work schedule.

- **include/** – contains header files and definitions of shared structures (`Entry`, `User`, `Absence`, `ScheduleConfig`, etc.) used by all modules.

- **main.c** – the main file that runs the entire system and displays the menu.

## Where to put the data?

- **RCP_IN/** – put the clock-in/clock-out files here in the format:
1;2025-06-04 07:00:00;2025-06-04 15:00:00;
2;2025-06-04 07:05:00;2025-06-04 14:45:00;

Filenames follow the format `RCP_YYYY_MM_DD.txt`.

- **RCP_Config/** – configuration files specifying required work hours for each schedule (e.g., shift 1 – morning).
Filename format: `Config_YYYY_MM.txt`
File content example:

# Format: scheduleId;requiredHours
1;160  
2;160  
3;160

- **RCP_OUT/** – generated text reports for employees are saved here.

## What does the program do?

- Loads data from files in the corresponding folders.
- Allows viewing employee data.
- Generates reports with worked hours, overtime, absences, and comparisons with required hours.
- Supports various work shift types: 7–14, 14–22, and flexible.

## Tests

The project includes a set of unit tests to verify the correct operation of the main modules.
Tests are located in the `tests/` folder. To run them:

- Make sure you have `mingw32-make` installed.

In the terminal, run:

```bash
mingw32-make test
```
This will build the `bin/test_runner` file, which will execute all tests.  
Each test will print to the console whether it passed (OK) or failed (FAILED).

## Authors

- Konrad Biały  
- Kamil Celadyn  
- Misha Bondar  
- Filip Kasprzycki
