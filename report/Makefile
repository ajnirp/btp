all: report

report: report.tex
	xelatex report.tex 1>/dev/null
	bibtex report 1>/dev/null
	xelatex report.tex 1>/dev/null
	xelatex report.tex 1>/dev/null

clean:
	rm -f *.log *.out *.dvi *.toc *.bbl *.blg *.brf