#include "../includes/Game.hpp"

int	systemFailed(const bool value, const string message)
{
	if (value == true)
		cout << "\033[1A" << ERASE_LINE << endl << ERASE_LINE;

	cerr << "System failed: " << message << endl;
	cerr << "Closing the game..." << endl;

	return (1);
}

int	memoryFailed(const bool value)
{
	if (value == true)
		cout << "\033[1A" << ERASE_LINE << endl << ERASE_LINE;

	cerr << "Memory allocation failed. Closing the game..." << endl;

	return (1);
}
