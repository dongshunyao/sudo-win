#include <Windows.h>
#include <system_error>
#include <iostream>

using namespace std;


WCHAR parameters[65536];

int main()
try
{
	auto argc = 0;
	const auto argv = CommandLineToArgvW(GetCommandLineW(), &argc);

	for (auto i = 2; i < argc; i++)
	{
		wcscat_s(parameters, argv[i]);
		wcscat_s(parameters, TEXT(" "));
	}

	SHELLEXECUTEINFO info;
	info.cbSize = sizeof(SHELLEXECUTEINFO);
	info.lpVerb = TEXT("runas");
	info.lpFile = (argc == 1) ? TEXT("cmd") : argv[1];
	info.lpParameters = parameters;
	info.nShow = SW_SHOWNORMAL;


	if (!ShellExecuteEx(&info))
		throw system_error(GetLastError(), system_category());


	return 0;
}
catch (exception& e)
{
	cerr << e.what() << endl;
	return 0;
}
