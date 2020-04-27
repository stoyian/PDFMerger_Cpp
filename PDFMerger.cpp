// PDFMaker.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "podofo.h"
#include <iostream>
#include <vector>

void printUsage() {
	std::cout << "Wrong usage of the program. Please see the following\n";
	std::cout << "Usage:\nmergePDF  file1.pdf file2.pdf....fileN.pdf  outputfile.pdf\n";
}


int main(int argc, char** argv){
	if (argc < 4) {
		printUsage();
		exit(EXIT_FAILURE);
	}
	PoDoFo::PdfError::EnableDebug(false);
	
	std::vector<char*> inputPDFs;
	char* outputPDF = argv[argc - 1];
	for (int i = 1; i < argc - 1; i++)
		inputPDFs.push_back(argv[i]);

	std::cout << "PDF merging begins" << std::endl;
	try{
		printf("Reading file: %s\n", inputPDFs[0]);
		PoDoFo::PdfMemDocument doc1;
		doc1.Load(inputPDFs[0]);

		printf("Merging the rest of PDFs!");

		for (char* pdf : inputPDFs) {
			PoDoFo::PdfMemDocument doc;
			doc.Load(pdf);

			doc1.Append(doc);
		}
		printf("Writing files to %s\n ", outputPDF);
		doc1.Write(outputPDF);
	}
	catch (const PoDoFo::PdfError& e) {
		std::cerr << "An error has occured!\n";
		e.PrintErrorMsg();
		return e.GetError();
	}
	exit(EXIT_SUCCESS);
}	
