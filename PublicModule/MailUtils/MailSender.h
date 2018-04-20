#pragma once

#include "_pri_mail_global.h"
#include "StringUtils.h"
#include <memory>

namespace SSUtils
{
	namespace Mail
	{
		struct MailSender
		{
			std::string senderMail;
			std::string senderPassword;
			std::string senderServer;
			std::vector<std::string> receiverMails;

			MailSender(const std::string &_senderMail, const std::string &_senderPassword, const std::string &_senderServer, const std::string _receiverMail);
			MailSender(const std::string &_senderMail, const std::string &_senderPassword, const std::string &_senderServer, const std::vector<std::string> &_receiverMails);
			MailSender(const MailSender &ano) = default;
			MailSender(MailSender &&ano) = default;
			MailSender &operator=(const MailSender &rhs) = default;
			MailSender &operator=(MailSender &&rhs) = default;
			~MailSender(void) = default;

			std::pair<bool, std::string> operator()(const MessageType type, const std::string & title, const std::string & content, const CharType charType = String::LocalCharType);
		};
	};
};
