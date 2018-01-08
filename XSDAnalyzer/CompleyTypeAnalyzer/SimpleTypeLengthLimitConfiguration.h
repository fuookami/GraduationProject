#pragma once

namespace XSDFrontend
{
	namespace SimpleType
	{
		class LengthLimitConfiguration abstract
		{
		public:
			static const int NoLengthValidator = -1;

		protected:
			LengthLimitConfiguration(const int minLength = NoLengthValidator, const int maxLength = NoLengthValidator);
			LengthLimitConfiguration(const LengthLimitConfiguration &ano);
			LengthLimitConfiguration(const LengthLimitConfiguration &&ano);
			LengthLimitConfiguration &operator=(const LengthLimitConfiguration &rhs);
			LengthLimitConfiguration &operator=(const LengthLimitConfiguration &&rhs);
		public:
			virtual ~LengthLimitConfiguration(void);
			
		public:
			inline void setLengthValidator(const int lenth) { m_minLength = m_maxLength = lenth; }
			inline void removeLengthValidator(void) { setLengthValidator(NoLengthValidator); }
			inline const int getLengthValidator(void) const { return m_minLength == m_maxLength ? m_minLength : NoLengthValidator; }

			const bool setMinLengthValidator(const int minLength);
			inline void removeMinLengthValidator(void) { setMinLengthValidator(NoLengthValidator); }
			inline const int getMinLengthValidator(void) const { return m_minLength; }

			const bool setMaxLengthValidator(const int maxLength);
			inline void removeMaxLengthValidator(void) { setMaxLengthValidator(NoLengthValidator); }
			inline const int getMaxLengthValidator(void) const { return m_maxLength; }

		private:
			int m_minLength;
			int m_maxLength;
		};
	};
};
