# Symbol Tally: Easy CD Take Offs

**Symbol Tally** is a desktop application being built for construction professionals or estimators to quickly tally material on blueprint PDFs. This app allows you to load a PDF, mark up symbols, and export the counts to a text file for bidding purposes. 

> Inspired by real-world take off workflows this tool streamlines manual pen and paper counting with a simple, keyboard-driven interface.

---

## OpenCV

```console
cd build/_deps
git clone https://github.com/opencv/opencv.git
cmake -DCMAKE_INSTALL_PREFIX=../build/_deps/opencv/install ..
sudo make install -j$(nproc)
```
