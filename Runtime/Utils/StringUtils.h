#pragma once


namespace Helianthus::Runtime
{
	namespace Utils
	{
		class StringUtils
		{
		public:
			static std::string Trim(const std::string& S)
			{
				auto StartPos = S.find_first_not_of(" \t\n\r");
				auto EndPos = S.find_last_not_of(" \t\n\r");
				if (StartPos == std::string::npos)
				{
					return "";
				}
				return S.substr(StartPos, EndPos - StartPos + 1);
			}
		};
	} // namespace Utils
}  // namespace Helianthus::Runtime