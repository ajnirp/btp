all: report

report: report.tex
	xelatex report.tex
	bibtex report
	xelatex report.tex
	xelatex report.tex

clean:
	rm -f *.log *.out *.dvi *.toc *.bbl *.blg *.brf