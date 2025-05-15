# Symbol Tally: Easy CD Take Offs

**Symbol Tally** is a desktop application being built for construction professionals or estimators to quickly tally material on blueprint PDFs. This app allows you to load a PDF, mark up symbols, and export the counts to a text file for bidding purposes. 

> Inspired by real-world take off workflows this tool streamlines manual pen and paper counting with a simple, keyboard-driven interface.

---

## Features

- View and pan large blueprint images.
- Zoom in/out using the mouse wheel.
- Start multiple named take offs.
- Mark and tally symbols with right-click.
- Template matching support (symbol recognition).
- Export counted take offs to a `.txt` file.

---

## Getting Started

### Dependencies

- C++23 or higher
- CMake
- [Poppler](https://anongit.freedesktop.org/git/poppler/poppler.git)
- [SFML](https://www.sfml-dev.org/)
- [OpenCV](https://github.com/opencv/opencv)

### Clone the Repository

```bash
git clone https://github.com/rubengmeza/symbol-tally.git
cd symbol-tally
```

This project uses SFML, Poppler, and OpenCV — all vendored in external/. Follow the steps below to install them properly before building.
**For Windows usage: Poppler can be tricky to get working. The example will run without needing to try to install Poppler. All code involving Poppler has been commented out.**

1. SFML

```bash
cd external
git clone https://github.com/SFML/SFML.git
```

2. Poppler

```bash
cd external
git clone https://gitlab.freedesktop.org/poppler/poppler.git
cd poppler
mkdir build && cd build
cmake .. \
  -DCMAKE_INSTALL_PREFIX=../install \
  -DENABLE_UNSTABLE_API_ABI_HEADERS=ON \
  -DENABLE_QT5=OFF \
  -DENABLE_QT6=OFF \
  -DENABLE_GLIB=OFF
make -j
make install
```

3. OpenCV

Make sure you are in the project root (/symbol-tally) before running the following. 
All dependencies MUST be in `symbol-tally/external`.

```bash
cd external
git clone https://github.com/opencv/opencv.git
cd opencv
mkdir build && cd build
cmake .. \
  -DCMAKE_BUILD_TYPE=Release \
  -DBUILD_TESTS=OFF \
  -DBUILD_PERF_TESTS=OFF \
  -DBUILD_EXAMPLES=OFF \
  -DBUILD_DOCS=OFF \
  -DBUILD_opencv_apps=OFF \
  -DBUILD_opencv_java=OFF \
  -DBUILD_opencv_python=OFF

make -j$(nproc)
```


### Building the Project

Again, make sure you are in the project root.

```bash
cd symbol-tally
mkdir build && cd build
cmake ..
make
```


### Run the Project:

```bash
./run
```

Before running, you may need to enter this command with the path like so:

Replace /path/to/project/ with the full path to where you cloned symbol-tally.
For me it was /home/roobz/fun/

```bash
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/path/to/project/symbol-tally/external/poppler/install/lib:/path/to/project/symbol-tally/external/opencv/build/lib
```


### Usage

- You can move the view with a click and drag motion. You can also zoom with the mouse scroll wheel.

- To begin counting material, press 'N'. This will create a new take off.

- You will be prompted to enter a name for the take off. It is common practice to use the name found on the legend for clarity.

- You can then begin counting the symbols for the specified material. Once all symbols have been marked, you can then press 'N' again to begin on the next take off.

- When you have finished all your take offs, press 'E' to save and export your counted materials to the file.

To use the symbol search, you must already have a take off created. Then push the 'S' key.
