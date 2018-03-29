#pragma once

#include "DataUtils.h"

#include <string>
#include <utility>

namespace FuUtils
{
	namespace Encryption
	{
		namespace RSA
		{
			/*!
			*	\������:   	generateKey
			*	\����: 		unsigned int keyLength						��Կ����
			*	\����: 		const std::string & seed					���ӣ����ڹ���������أ��������棩�����������
			*	\����ֵ:   	std::pair<std::string, std::string>	RSA��Կ��˽Կ��
			*	\˵��: 		����RSA��Կ��˽Կ�ԣ�������֤�������������������������롢����
			*/
			std::pair<std::string, std::string> generateKey(unsigned int keyLength, const std::string &seed = DataUtils::toString(DataUtils::generateRandomBlock()));

			/*!
			*	\������:   	encryptStringRSA
			*	\����: 		const std::string & publicKey	RSA��Կ�����ڼ�����Ϣ
			*	\����: 		const std::string & origin		��������Ϣ
			*	\����: 		const std::string seed			���ӣ����ڹ���������أ��������棩�����������
			*	\����ֵ:   	std::string				����
			*	\˵��: 		ʹ��RSA��Կ����Ϣ���м���
			*/
			std::string encryptStringRSA(const std::string &publicKey, const std::string &origin, const std::string &seed = DataUtils::toString(DataUtils::generateRandomBlock()));

			/*!
			*	\������:   	decryptStringRSA
			*	\����: 		const std::string & privateKey	RSA˽Կ�����ڽ�������
			*	\����: 		const std::string & cipher		����
			*	\����ֵ:   	std::string				���ܺ�����
			*	\˵��: 		ʹ��RSA˽Կ�����Ľ��н���
			*/
			std::string decryptStringRSA(const std::string &privateKey, const std::string &cipher);

			/*!
			*	\������:   	signFileRSA
			*	\����: 		const std::string & privateKey	RSA˽Կ
			*	\����: 		const std::string & msg			ԭʼ����
			*	\����ֵ:   	std::string				��ǩ������
			*	\˵��: 		ʹ��RSA˽Կǩ���ļ�
			*/
			std::string signFileRSA(const std::string &privateKey, const std::string &msg);
			/*!
			*	\������:   	verifyFileRSA
			*	\����: 		const std::string & publicKey	RSA��Կ
			*	\����: 		const std::string & msg			ԭʼ����
			*	\����: 		const std::string & signature	��ǩ������
			*	\����ֵ:   	const bool						�Ƿ�ƥ�䣬true��ʾƥ�䣬false��ʾ��ƥ��
			*	\˵��: 		ʹ��RSA��Կ��֤�ļ�ǩ��
			*/
			const bool verifyFileRSA(const std::string &publicKey, const std::string &msg, const std::string &signature);
		};
	};
};
