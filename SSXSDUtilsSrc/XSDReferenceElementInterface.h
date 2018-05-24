#pragma once

#include "XSDGlobal.h"
#include <string>
#include <memory>

namespace XSDFrontend
{
	namespace XSDElementUtils
	{
		template <typename T>
		class IXSDReferenceElementInterface abstract
		{
		protected:
			IXSDReferenceElementInterface(void) = default;
			IXSDReferenceElementInterface(const std::string &refName, const std::shared_ptr<T> &spRef = nullptr);
			IXSDReferenceElementInterface(std::string &&refName, const std::shared_ptr<T> &spRef = nullptr);
			IXSDReferenceElementInterface(const IXSDReferenceElementInterface &ano) = default;
			IXSDReferenceElementInterface(IXSDReferenceElementInterface &&ano);
			IXSDReferenceElementInterface &operator=(const IXSDReferenceElementInterface &rhs) = default;
			IXSDReferenceElementInterface &operator=(IXSDReferenceElementInterface &&rhs);
		public:
			virtual ~IXSDReferenceElementInterface(void) = default;

			inline void setRef(const std::string &ref, const std::shared_ptr<T> &spRef = nullptr) { m_ref.assign(ref); m_refElement = spRef; }
			inline void setRef(std::string &&ref, const std::shared_ptr<T> &spRef = nullptr) { m_ref.assign(ref); m_refElement = spRef; }
			inline const bool hasRef(void) const { return !m_ref.empty(); }
			inline const std::string &getRefName(void) const { return m_ref; }
			inline const std::shared_ptr<T> getRef(void) const { return m_refElement; }

		private:
			std::string m_ref;
			std::shared_ptr<T> m_refElement;
		};

		template<typename T>
		inline IXSDReferenceElementInterface<T>::IXSDReferenceElementInterface(const std::string & refName, const std::shared_ptr<T>& spRef)
			: m_ref(refName), m_refElement(spRef)
		{
		}

		template<typename T>
		inline IXSDReferenceElementInterface<T>::IXSDReferenceElementInterface(std::string && refName, const std::shared_ptr<T>& spRef)
			: m_ref(std::move(refName)), m_refElement(spRef)
		{
		}

		template<typename T>
		inline IXSDReferenceElementInterface<T>::IXSDReferenceElementInterface(IXSDReferenceElementInterface && ano)
			: m_ref(std::move(ano.m_ref)), m_refElement(ano.m_refElement)
		{
		}

		template<typename T>
		inline IXSDReferenceElementInterface<T> & IXSDReferenceElementInterface<T>::operator=(IXSDReferenceElementInterface && rhs)
		{
			m_ref.assign(std::move(rhs.m_ref));
			m_refElement = rhs.m_refElement;

			return *this;
		}
	};
};
