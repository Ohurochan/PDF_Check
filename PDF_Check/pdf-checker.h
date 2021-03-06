/* 
* A check unit 
*/

#ifndef DETECT_PDF_CHECKER_H_
#define DETECT_PDF_CHECKER_H_

#include <iostream>
#include <memory>
#include "pdf.h"

namespace PDF_CHECK {

	class PdfAnalyzeReport;

	class PdfChecker {
	public:
		PdfChecker();
		~PdfChecker() = default;

		explicit PdfChecker(const std::wstring& path);
		PdfChecker(const PdfChecker&) = delete;
		PdfChecker(PdfChecker&&) = delete;
		PdfChecker& operator = (const PdfChecker&) = delete;
		PdfChecker& operator = (PdfChecker&&) = delete;

		PdfAnalyzeReport GetReport(const std::wstring& path);
		bool ReadPdf(const std::wstring& path);
		void ShowPdfData() const;

		Bytes get_pdf_data(unsigned int, unsigned int) const;

	private:
		std::unique_ptr<Pdf> pdf_;
	};
}

#endif /* end of DETECT_PDF_CHECKER_H_ */