# Product Catalog Manager

A C++ application for managing a typed product catalog, featuring both a command-line interface and a Qt-based graphical interface. Products are organized into a polymorphic hierarchy with strict contract-based validation.

---

## Features

- **Polymorphic product model** — base `Product` class extended by `Electronics` and `Clothing` with type-specific attributes
- **Contract programming** — pre/post-condition and invariant enforcement via a custom exception hierarchy
- **Product code validation** — checksum-verified code format (`PRD-XXXX-YY`)
- **Deep-copy catalog** — catalog manages product ownership via `std::unique_ptr` with correct copy semantics
- **Qt GUI** — graphical interface to add, remove, and browse catalog entries
- **Console interface** — interactive CLI for catalog management
- **Unit tests** — Google Test suite covering all core classes
- **Doxygen documentation** — fully documented API

---

## Project Structure

```
.
├── TP3Sources/        # Core library — product classes, catalog, date, exceptions, validation
├── TP3Principal/      # Console application
├── TP3QT/             # Qt GUI application
├── Documentation/     # Doxygen-generated HTML documentation
└── Doxyfile           # Doxygen configuration
```

---

## Requirements

| Dependency     | Version  |
|----------------|----------|
| C++ compiler   | g++ / clang++ with C++11 support |
| Qt             | 5.x      |
| Google Test    | 1.10+    |
| Doxygen        | 1.9+ (optional, for docs) |
| NetBeans IDE   | 12+ (optional, project files included) |

---

## Building

### Core Library (`TP3Sources`)

```bash
cd TP3Sources
make
```

This produces `dist/Debug/GNU-Linux/libtp3sources.a`.

### Console Application (`TP3Principal`)

Build the core library first, then:

```bash
cd TP3Principal
make
./dist/Debug/GNU-Linux/TP3Principal
```

### Qt GUI Application (`TP3QT`)

Build the core library first, then:

```bash
cd TP3QT
qmake nbproject/qt-Debug.pro
make
./dist/Debug/GNU-Linux/TP3QT
```

### Unit Tests

Unit tests are located in `TP3Sources/` alongside the source files (`*Testeur.cpp`). Run them after building the core library:

```bash
cd TP3Sources
make test
```

---

## Usage

### GUI Application

Launch the Qt application. From the **Operations** menu you can:

- **Add Electronics** — enter product description, price, code, warranty (months), and refurbished status
- **Add Clothing** — enter description, price, code, size (XS–XXL), and color
- **Remove Product** — remove an entry by product code
- **Load Catalog** — import a catalog from a text file

### Console Application

The CLI walks through creating a catalog, adding products interactively, and printing the result.

### Catalog File Format

```
<catalog name>
<DD MM YYYY>
<Type>,<Description>,<Price>,<Code>,<type-specific fields...>
```

Example:

```
My Catalog
21 08 2025
Electronique,Galaxy Smartphone,499.90,PRD-SMAR-60,24,0
Vetement,Cotton T-Shirt,19.95,PRD-TSHI-70,M,White
Electronique,Bluetooth Headset,89.99,PRD-CASQ-58,12,1
```

### Product Code Format

Codes follow the pattern `PRD-XXXX-YY` where:
- `XXXX` — 4-letter product identifier (A–Z)
- `YY` — 2-digit checksum computed from the identifier

---

## Product Model

```
Produit  (abstract base)
├── Electronique   — adds: warranty (months), refurbished flag
└── Vetement       — adds: size (XS/S/M/L/XL/XXL), color
```

Key design decisions:
- `clone()` enables polymorphic copying without slicing
- `std::unique_ptr` manages lifetime inside `Catalogue`
- `ContratException` hierarchy enforces class invariants at runtime

---

## Documentation

Generate the HTML documentation with:

```bash
doxygen Doxyfile
```

Output is written to `Documentation/html/`. Open `Documentation/html/index.html` in a browser.

---

## License

MIT License — see [LICENSE](LICENSE) for details.

---

## Author

Nour Belghazi
