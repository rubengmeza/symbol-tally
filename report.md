Writing my own pdf parser not an option. 
- PDF standard over 1000 pages long. Probably not enough time to implement by deadline.

Will need pdf parser dependency. 
- Must make it portable for ease of building for the professor. He shouldnt have find the dependencies for my project.
    - Immediately difficult process. 
    - Will use CMake to simplify. Will handle PoDoFo when he builds the project. 

PoDoFo examples suck! and dont even compile anymore with recent PoDoFo version.

Architectural drawings created in some sort of CAD software. Plans exported to PDF format and line work is saved as vector data.
- Stored in content streams? 
    - Use [PdfContentsTokenizer](https://stackoverflow.com/questions/11715561/pdf-parsing-in-c-podofo?rq=3) ????
    - Couldnt get these functions to work. 

Found this instead. 
[comment from this post gave me a hint](https://stackoverflow.com/questions/73746836/extract-geometric-objects-lines-circles-from-a-pdf-using-pdfmm)
```
PoDoFo::PdfContentStreamReader reader(sample_page);
PoDoFo::PdfContent data;
```
- Can use `PdfContent` to switch on `PdfOperator`.
- Specifically looking for graphic operators per [cheat sheet](https://pdfa.org/download-area/cheat-sheets/OperatorsAndOperands.pdf)

Would be much simpler to convert to image and display as image.
- Found [Poppler](https://gitlab.freedesktop.org/poppler/poppler) for rendering pdf as image.
- Can display with SFML for markups.
- Opencv for symbol search.     

The Plan!
1. Load a PDF

2. Extract pages as images

3. Load a symbol legend image

4. Search and count matches using OpenCV

5. Output counts

Problems linking poppler.
- Was an absolute nightmare. Even with cmake. 
- Still needed to run with: 
`export LD_LIBRARY_PATH=external/poppler/install/lib:$LD_LIBRARY_PATH`


OpenCV Template Matching
- [Example](https://stackoverflow.com/questions/23180630/using-opencv-matchtemplate-for-blister-pack-inspection)
- Will try implementing OpenCV example: 
