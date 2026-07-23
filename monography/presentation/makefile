filename=document

all: compile

compile:
	pdflatex $(filename).tex
	bibtex $(filename)
	pdflatex $(filename).tex
	pdflatex $(filename).tex
	@echo "Processo finalizado com sucesso!"


clear:
	@echo -n "Limpando arquivos auxiliares...\n"
	@rm -f *.out *.aux *.alg *.acr *.dvi *.gls *.log *.bbl *.blg *.ntn *.not *.lof *.lot *.toc *.loa *.lsg *.nlo *.nls *.ilg *.ind *.ist *.glg *.glo *.xdy *.acn *.idx *.loq *~
	@rm -f $(filename).pdf
	@echo "Processo finalizado com sucesso!"
