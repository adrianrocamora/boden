#include <bdn/init.h>
#include <bdn/win32Util.h>

namespace bdn
{
namespace win32
{


/** Parses a wide character commandline string (as returned by the win32 API function
	GetCommandLineW.
	Returns an array (std::vector) with the individual arguments. The first element in the array
	will be the executable name that was included in the commandline.	
	*/
std::vector<String> parseWin32CommandLine(const String& commandLine)
{
	int argCount=0;
	wchar_t** argPtrs = ::CommandLineToArgvW(commandLine.asWidePtr(), &argCount);
	if( argPtrs==NULL )
	{
		BDN_throwLastSysError( ErrorFields().add("func", "CommandLineToArgvW")
											.add("context", "parseWin32CommandLine") );
	}

	std::vector<String> args;
	for(int i=0; i<argCount; i++)
		args.push_back( argPtrs[i] );

	::LocalFree(argPtrs);

	return args;
}


}
}


