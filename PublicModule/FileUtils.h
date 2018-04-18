#pragma once

#include "Global.h"
#include "DataUtils/DataTranslator.h"
#include "DataUtils.h"
#include <string>
#include <iterator>
#include <fstream>
#include <algorithm>
#include <type_traits>

namespace SSUtils
{
	namespace File
	{
		extern const std::string PathSeperator;
		extern const std::string ExtensionSeperator;
		extern const std::string InitailPath;

		const bool checkFileExist(const std::string &targetUrl);
		void createFile(const std::string &targetUrl);
		const bool removeFile(const std::string &targetUrl);

		std::string getPathOfUrl(const std::string &targetUrl);
		std::string getFileNameOfUrl(const std::string &targetUrl);
		std::string getFileMainNameOfUrl(const std::string &targetUrl);
		std::string getFileExtensionOfUrl(const std::string &targetUrl);
		std::vector<std::string> getAllFilesUrlsOfPath(const std::string &targetPath);
		std::vector<std::string> getAllDirectoryPathsOfPath(const std::string &targetPath);

		Block loadFile(const std::string &targetUrl);
		std::vector<std::string> loadFileByLine(const std::string &targetUrl);

		template<typename T, uint32 DataLength = sizeof(T)>
		struct FileSaver
		{
			FileSaver(void) = default;
			FileSaver(const FileSaver &ano) = delete;
			FileSaver(FileSaver &&ano) = delete;
			FileSaver &operator=(const FileSaver &rhs) = delete;
			FileSaver &operator=(FileSaver &&rhs) = delete;
			~FileSaver(void) = default;

			template<typename iter>
			void operator()(const std::string &targetUrl, const iter bgIt, const iter edIt) const
			{
				static_assert(std::is_same_v<iter::value_type, T>, "FileSaver::operator(), the value type of iterator is not the same of the type");

				static const Data::DataTranslator<T> translator;
				static const FileSaver<byte> saver;
				Block buff(translator.fromDataIterator(bgIt, edIt));
				saver(targetUrl, buff.cbegin(), buff.cend());
			}
			template<typename container>
			void operator()(const std::string &targetUrl, const container &datas) const
			{
				static_assert(std::is_same_v<container::value_type, T>, "FileSaver::operator(), the value type of container is not the same of the type");

				operator()(targetUrl, datas.cbegin(), datas.cend());
			}
		};
		template<typename T>
		struct FileSaver<T, 1>
		{
			typedef typename std::enable_if<Data::ConversionChecker<T, byte>::value, T>::type value_type;

			FileSaver(void) = default;
			FileSaver(const FileSaver &ano) = delete;
			FileSaver(FileSaver &&ano) = delete;
			FileSaver &operator=(const FileSaver &rhs) = delete;
			FileSaver &operator=(FileSaver &&rhs) = delete;
			~FileSaver(void) = default;

			template<typename iter>
			void operator()(const std::string &targetUrl, const iter bgIt, const iter edIt) const
			{
				static_assert(std::is_same_v<iter::value_type, T>, "FileSaver::operator(), the value type of iterator is not the same of the type");

				std::ofstream fout(targetUrl);
				std::ostream_iterator<byte> outIt(fout);
				std::copy(bgIt, edIt, outIt);
				fout.close();
			}
			template<typename container>
			void operator()(const std::string &targetUrl, const container &datas) const
			{
				static_assert(std::is_same_v<container::value_type, T>, "FileSaver::operator(), the value type of container is not the same of the type");

				std::ofstream fout(targetUrl);
				std::ostream_iterator<byte> outIt(fout);
				std::copy(datas.cbegin(), datas.cend(), outIt);
				fout.close();
			}
		};
		void saveFile(const std::string &targetUrl, const Block &fileData);
		void saveFile(const std::string &targetUrl, const std::string &fileData);
		template<typename iter>
		void saveFile(const std::string &targetUrl, const iter bgIt, const iter edIt)
		{
			static const FileSaver<iter::value_type> saver;
			saver(targetUrl, bgIt, edIt);
		}
		template<typename container>
		void saveFile(const std::string &targetUrl, const container &fileData)
		{
			static const FileSaver<container::value_type> saver;
			saver(targetUrl, fileData);
		}

		const bool checkPathExist(const std::string &targetPath);
		const bool insurePathExist(const std::string &targetPath);
		const bool removePath(const std::string &targetPath);
		std::string getSystemNativePath(const std::string &targetPath);
	};
};
