# Statistical Tools

A simple **C++ statistical analysis tool** for single-variable or two-variable datasets.
It can calculate statistics, regression line, correlation coefficients, and provide visualization-ready data output.

---

## Features

* Add raw data interactively (1 or 2 variables)
* Compute statistical metrics:

  * Minimum, Maximum, Range, Median, Average
  * Variance, Standard Deviation
  * Covariance, Correlation Coefficient
* Linear Regression:

  * Regression line (point-slope or slope-intercept form)
  * Residual Sum of Squares (RSS)
  * Root Mean Square Error (RMSE)
  * Coefficient of Determination (R²)
* Read from and write to files
* Color-coded console output for clarity
* Command support:

  * `!HELP` – Show help message
  * `!EXIT` – Exit program
  * `!CLEAR` – Reset data
  * `!PRINTALLDATA` – Print raw + statistics
  * `!PRINTRAWDATA` – Print raw data only
  * `!PRINTSTADATA` – Print statistics only
  * `!PRINTLINE` – Print regression line
  * `!PRINTR2` – Print R²
  * `!PRINTRSS` – Print RSS
  * `!PRINTRMSE` – Print RMSE
  * `!WRITEIN` – Load data from file
  * `!WRITEOUT` – Save data to file

---

## Requirements

* C++17 or later
* Compatible with Linux, Windows, or WSL
* Standard library only (no external dependencies)

---

## Build Instructions

Using `g++` or `clang++`:

```bash
g++ -std=c++17 main.cpp -o statistical_tools
./statistical_tools
```

Or on Windows PowerShell / CMD:

```powershell
clang++ -std=c++17 main.cpp -o statistical_tools.exe
.\statistical_tools.exe
```

---

## Usage

1. Run the program:

```bash
./statistical_tools
```

2. Follow the prompts:

* Enter `y` to load a file, or `n` to input new data
* Enter numbers interactively or from a file
* Use commands starting with `!` to control the program

3. Example of file format (`WriteIn` compatible):

```text
##Raw Data
2
1.0 2.0
2.0 3.5
3.0 5.0
```

---

## Example Commands

```text
>!HELP
>!PRINTALLDATA
>!WRITEOUT
>!EXIT
```

---

## File Input/Output

* **Output (`WriteOut`)** includes:

  * Raw data
  * Statistical analysis
  * Machine-readable block (`##Raw Data`) for re-import

* **Input (`WriteIn`)** parses the `##Raw Data` block only.

* Comments (lines starting with `#`) are ignored.

---

## Notes

* Maximum 2 variables supported
* Commands are case-insensitive
* Supports decimal numbers and signed numbers

---

## License

MIT License © 2026 111999yes
