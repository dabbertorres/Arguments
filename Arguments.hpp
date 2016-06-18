#ifndef DBR_UTIL_ARGUMENTS_HPP
#define DBR_UTIL_ARGUMENTS_HPP

#include <string>
#include <unordered_map>
#include <memory>
#include <functional>

namespace dbr
{
	namespace util
	{
		class Arguments
		{
		public:
			// A function that recieves the string value a flag was given (or empty if no value, but flag present)
			// returns true/false signifying success/failure
			using Receiver = std::function<bool(const std::string&)>;

			Arguments(const std::string& helpTitleMsg = "");
			~Arguments() = default;

			void add(Receiver&& receive, const std::string& name, const std::string& helpMsg = "");

			// returns true if program execution should continue as normal, false otherwise (example: help message was displayed or there was an error)
			bool run(int argc, char** argv, std::ostream& out);

		private:
			bool checkFlag(const std::string& flag, const std::string& value, std::ostream& out);

			void displayHelp(std::ostream& out);

			struct Flag
			{
				Receiver receiver;
				std::string help;
			};

			std::unordered_map<std::string, Flag> flags;

			std::string helpTitle;
			bool showHelp;
			std::size_t longestFlag;
		};
	}
}

#endif