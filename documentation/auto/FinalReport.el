(TeX-add-style-hook
 "FinalReport"
 (lambda ()
   (TeX-add-to-alist 'LaTeX-provided-class-options
                     '(("IEEEtran" "12pt" "conference" "onecolumn" "titlepage")))
   (TeX-add-to-alist 'LaTeX-provided-package-options
                     '(("graphicx" "pdftex") ("inputenc" "utf8") ("biblatex" "backend=biber") ("fontenc" "T1") ("beramono" "scaled")))
   (add-to-list 'LaTeX-verbatim-environments-local "lstlisting")
   (add-to-list 'LaTeX-verbatim-macros-with-braces-local "lstinline")
   (add-to-list 'LaTeX-verbatim-macros-with-braces-local "hyperref")
   (add-to-list 'LaTeX-verbatim-macros-with-braces-local "hyperimage")
   (add-to-list 'LaTeX-verbatim-macros-with-braces-local "hyperbaseurl")
   (add-to-list 'LaTeX-verbatim-macros-with-braces-local "nolinkurl")
   (add-to-list 'LaTeX-verbatim-macros-with-braces-local "url")
   (add-to-list 'LaTeX-verbatim-macros-with-braces-local "path")
   (add-to-list 'LaTeX-verbatim-macros-with-delims-local "lstinline")
   (add-to-list 'LaTeX-verbatim-macros-with-delims-local "url")
   (add-to-list 'LaTeX-verbatim-macros-with-delims-local "path")
   (TeX-run-style-hooks
    "latex2e"
    "IEEEtran"
    "IEEEtran12"
    "graphicx"
    "wrapfig"
    "inputenc"
    "algorithmic"
    "pdflscape"
    "amssymb"
    "amsmath"
    "latexsym"
    "csquotes"
    "biblatex"
    "hyperref"
    "cleveref"
    "setspace"
    "parskip"
    "indentfirst"
    "verbatim"
    "adjustbox"
    "listings"
    "subcaption"
    "fontenc"
    "beramono")
   (TeX-add-symbols
    '("figuretitle" 1)
    '("mywrapfigure" 5)
    '("myfigure" 4)
    "Small"
    "LSTfont")
   (LaTeX-add-labels
    "#4"
    "#5"
    "sec:overview"
    "sec:hardware"
    "sec:electrical"
    "fig:cables"
    "sec:mechanical"
    "fig:motor2bearing"
    "sec:software"
    "sec:previous-iterations"
    "sec:ros-appl-arch"
    "sec:controls"
    "sec:results"
    "fig:balancing"
    "fig:pertandrec")
   (LaTeX-add-bibliographies
    "/home/ivan/Dropbox/Documents/Latex_Stuff/BibDB/AllEntries")))

