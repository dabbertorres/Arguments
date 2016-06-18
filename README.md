# Arguments
Command line argument handling for C++

# Usage
Create an instance of ```dbr::util::Arguments```, providing a help message title if desired.

Add all desired arguments using ```dbr::util::Arguments::add```.
	Parameters:
	1. ```dbr::util::Arguments::Receiver``` is an alias for ```std::function<bool(const std::string&)```. The parsed value is provided, and is expected to return true/false signifying success/failure for that particular argument (conversion to numbers, value ranges, etc).
	2. Desired flag name for a user to use.
	3. Optional help message for this argument.

Then, call ```dbr::util::Arguments::run```, providing ```argc```, ```argv```, and an ```std::ostream``` to write to.

Your functions provided in calls to ```dbr::util::Arguments::add``` will be called for each found argument. Use these to set any variables for your program, etc.

Done!
