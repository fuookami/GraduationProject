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
			*	\函数名:   	generateKey
			*	\参数: 		unsigned int keyLength						密钥长度
			*	\参数: 		const std::string & seed					种子，用于构造随机数池（生成引擎），生成随机数
			*	\返回值:   	std::pair<std::string, std::string>	RSA公钥和私钥对
			*	\说明: 		生成RSA公钥和私钥对，用于验证器、激活码生成器生成请求码、激活
			*/
			std::pair<std::string, std::string> generateKey(unsigned int keyLength, const std::string &seed = DataUtils::toString(DataUtils::generateRandomBlock()));

			/*!
			*	\函数名:   	encrypt
			*	\参数: 		const std::string & publicKey	RSA公钥，用于加密信息
			*	\参数: 		const std::string & origin		待加密信息
			*	\参数: 		const std::string seed			种子，用于构造随机数池（生成引擎），生成随机数
			*	\返回值:   	std::string						密文
			*	\说明: 		使用RSA公钥对信息进行加密
			*/
			std::string encrypt(const std::string &publicKey, const std::string &origin, const std::string &seed = DataUtils::toString(DataUtils::generateRandomBlock()));

			struct encrypter
			{
				encrypter(const std::string &_publicKey, const std::string &_seed = DataUtils::toString(DataUtils::generateRandomBlock()));
				encrypter(const encrypter &ano) = default;
				encrypter(encrypter &&ano) = default;
				~encrypter(void) = default;

				inline std::string operator()(const std::string &origin);

				std::string publicKey;
				std::string seed;
			};

			/*!
			*	\函数名:   	decrypt
			*	\参数: 		const std::string & privateKey	RSA私钥，用于解密密文
			*	\参数: 		const std::string & cipher		密文
			*	\返回值:   	std::string						解密后明文
			*	\说明: 		使用RSA私钥对密文进行解密
			*/
			std::string decrypt(const std::string &privateKey, const std::string &cipher);

			struct decrypter
			{
				decrypter(const std::string &_privateKey);
				decrypter(const decrypter &ano) = default;
				decrypter(decrypter &&ano) = default;
				~decrypter(void) = default;

				inline std::string operator()(const std::string &cipher);

				std::string privateKey;
			};

			/*!
			*	\函数名:   	sign
			*	\参数: 		const std::string & privateKey	RSA私钥
			*	\参数: 		const std::string & msg			原始数据
			*	\返回值:   	std::string						已签名数据
			*	\说明: 		使用RSA私钥签名文件
			*/
			std::string sign(const std::string &privateKey, const std::string &msg);

			struct signer
			{
				signer(const std::string &_privateKey);
				signer(const signer &ano) = default;
				signer(signer &&ano) = default;
				~signer(void) = default;

				inline std::string operator()(const std::string &msg);

				std::string privateKey;
			};

			/*!
			*	\函数名:   	verify
			*	\参数: 		const std::string & publicKey	RSA公钥
			*	\参数: 		const std::string & msg			原始数据
			*	\参数: 		const std::string & signature	已签名数据
			*	\返回值:   	const bool						是否匹配，true表示匹配，false表示不匹配
			*	\说明: 		使用RSA公钥验证文件签名
			*/
			const bool verify(const std::string &publicKey, const std::string &msg, const std::string &signature);

			struct verifier
			{
				verifier(const std::string &_publicKey);
				verifier(const verifier &ano) = default;
				verifier(verifier &&ano) = default;
				~verifier(void) = default;

				inline const bool operator()(const std::string &msg, const std::string &signature);

				std::string publicKey;
			};
		};
	};
};
