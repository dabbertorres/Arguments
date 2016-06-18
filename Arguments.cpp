#include "Arguments.hpp"

#include <regex>
#include <iomanip>

namespace dbr
{
	namespace util
	{
		static const std::regex argsRegex("(?:(?:-(\\w)(?:\\s(\\w+))?)|(?:--(\\w{2,})(?:=(\\w+))?))", std::regex_constants::optimize);

		Arguments::Arguments(const std::string& helpTitleMsg)
			: helpTitle(helpTitleMsg),
			showHelp(false),
			longestFlag(0)
		{
			add([&](auto) { return showHelp = true; }, "help", "Displays this help message.");
			add([&](auto) { return showHelp = true; }, "h", "Displays this help message.");
		}

		void Arguments::add(Receiver&& receive, const std::string& name, const std::string& helpMsg)
		{
			flags.emplace(name, Flag{receive, helpMsg});

			if(name.length() > longestFlag)
				longestFlag = name.length();
		}

		bool Arguments::run(int argc, char** argv, std::ostream& out)
		{
			// indices of capture groups in regex
			constexpr auto fullMatch = 0;
			constexpr auto shortName = 1;
			constexpr auto shortValue = 2;
			constexpr auto longName = 3;
			constexpr auto longValue = 4;

			// combine args into single string for regex
			std::string args;
			for(auto i = 1; i < argc; ++i)
			{
				args += argv[i];
				args += ' ';
			}
			
			std::sregex_iterator resultsIt{args.begin(), args.end(), argsRegex, std::regex_constants::match_not_null};
			std::sregex_iterator resultsEnd;

			for(auto it = resultsIt; it != resultsEnd; ++it)
			{
				std::string flag;
				std::string value;

				// short arg
				if(it->length(shortName) != 0)
				{
					flag = it->str(shortName);
					value = it->str(shortValue);
				}
				// long arg
				else if(it->length(longName) != 0)
				{
					flag = it->str(longName);
					value = it->str(longValue);
				}
				else
				{
					// exit fast, something weird happened
					out << "No arguments found?\n";
					return false;
				}

				if(!checkFlag(flag, value, out))
					return false;
			}
			
			if(showHelp)
			{
				displayHelp(out);
				return false;
			}
			else
			{
				return true;
			}
		}

		bool Arguments::checkFlag(const std::string& flag, const std::string& value, std::ostream& out)
		{
			auto it = flags.find(flag);

			if(it != flags.end())
			{
				if(!it->second.receiver(value))
				{
					out << "Invalid value '" << value << "' for '" << flag << "'\n";
					return false;
				}
			}
			else
			{
				out << "Unknown flag '" << flag << "'. Use '-h' or '--help' for help.\n";
				return false;
			}

			return true;
		}

		void Arguments::displayHelp(std::ostream& out)
		{
			out << helpTitle << "\n\n";
			for(auto& f : flags)
			{
				// minimum of 10 spaces between flags and descriptions
				out << '\t' << std::left << std::setw(longestFlag + 10) << (f.first.length() > 1 ? "--" : "-") + f.first << std::right << f.second.help << '\n';
			}
			out << '\n';
		}
	}
}
