# Map Generation for Roguelike Games from Textual Descriptions Using Large Language Models

LaTeX source code for the Undergraduate Thesis (B.Sc. in Computer Science) presented at Universidade Federal do Ceará (UFC), Campus Quixadá.

## Project Details

* **Author:** Gustavo Gurgel Medeiros
* **Advisor:** Prof. Dr. Cristiano Bacelar de Oliveira
* **Institution:** Universidade Federal do Ceará (UFC) - Campus Quixadá
* **Year:** 2026

## Directory Structure

| Directory/File | Description |
| --- | --- |
| `document.tex` | Main LaTeX file containing the document configuration and structure. |
| `1-pre-textuais/` | Pre-textual elements (Abstract, Dedication, Acknowledgements, etc.). |
| `2-textuais/` | Main chapters (Introduction, Theoretical Foundation, Related Works, Methodology, Results, Conclusion). |
| `3-pos-textuais/` | Post-textual elements (References, Appendices). |
| `lib/` | Formatting packages and classes (`ufcTex.sty`, `abntex2.cls`). |

## Compilation

This project is structured for LaTeX environments such as Overleaf, TeX Live, or MiKTeX.

1. Set `document.tex` as the main document.
2. Compile using `pdflatex`.
3. Run `bibtex` to generate the bibliography.
4. Compile using `pdflatex` twice to update cross-references and lists.

## Credits and Licenses

This project relies on the following templates and classes, distributed under the [LaTeX Project Public License (LPPL) v1.3](http://www.latex-project.org/lppl.txt):

* **UFC Template (`ufcTex.sty`):** Developed by Ednardo Moreira Rodrigues, Alan Batista de Oliveira, and the UFC Library System (adapted from the UECE template by Thiago Nascimento).
* **abnTeX2 (`abntex2.cls`):** Maintained by the abnTeX2 group for Brazilian ABNT academic formatting standards.
