#pragma once

#include "SimpleTypeAnalyzer.h"

#include <set>

namespace XSDAnalyzer
{
	class XSDAnalyzer
	{
	public:
		XSDAnalyzer(void);
		XSDAnalyzer(const XSDAnalyzer &ano) = delete;
		XSDAnalyzer(const XSDAnalyzer &&ano) = delete;
		XSDAnalyzer &operator=(const XSDAnalyzer &rhs) = delete;
		XSDAnalyzer &operator=(const XSDAnalyzer &&rhs) = delete;
		~XSDAnalyzer(void);

		const bool scan(const std::string &fileUrl);

	private:
		std::set<std::string> m_scanedFiles;

		SimpleTypeAnalyzer m_simpleTypeAnalyzer;
	};
};
