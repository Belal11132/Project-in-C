# 🌌 Space Travel Simulation in C

This is a modular C project that simulates space travel between planets using different types of spacecraft. It is developed for a university-level assignment and demonstrates file reading, memory management, object-oriented structure in C, and formatted simulation output.

## 📁 Project Structure

- `Main.c`: Main simulation controller.
- `src/`: Contains the implementation files for:
  - `gezegen.c` – Planet base class
  - `kayac_gezegen.c`, `gaz_devi_gezegen.c`, etc. – Subclasses of planets
  - `uzay_araci.c` – Spacecraft behavior and transitions
  - `kisi.c` – Person class
- `include/`: Header files for each module
- `lib/`: Compiled object files
- `veriler/`: Input files (`Gezegenler.txt`, `Araclar.txt`, `Kisiler.txt`)
- `Makefile`: Used to compile and run the simulation.

## 🚀 Features

- Reads input from structured text files.
- Supports different types of planets (rocky, gas giants, ice planets, etc.).
- Simulates population migration using spacecrafts.
- Tracks simulation time, outputs detailed per-planet and per-vehicle status.
- Outputs are formatted to match assignment specifications.
- Turkish localization for simulation output (e.g., `"VARDI"`, `"YOLDA"`).

## 🛠️ How to Build

```bash
make
```

## ▶️ How to Run

```bash
make run
```

## 📊 Output Format

Simulation results are printed in a detailed table including:

- Planet names
- Current date and population per planet
- Spacecraft name, status, departure & arrival planets, hours left, arrival date

## 📌 Notes

- Ensure input files are located correctly inside the project directory.
- The simulation uses a fast-forwarded time multiplier to progress the simulation quickly.
- Developed and tested in Linux.

## 📄 Report

A detailed report in Turkish is included in the project:
- `Odev2_RAPOR_FINAL_TARIHLI.docx`

---

🧑‍💻 Developed by **Bilal Alhamid**

Feel free to use this project as a learning resource. Contributions and suggestions are welcome.
