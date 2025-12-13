#include <csignal>
#include <cstdlib>
#include <iostream>
#include <unistd.h>

using namespace std;
// Define the function to be called when ctrl-c (SIGINT) is sent to process
void signal_callback_handler( int signum )
{
	cout << "Caught signal " << signum << endl;
	// Terminate program
	std::exit( signum );
}
int main()
{
	// Register signal and signal handler
	std::signal( SIGINT, signal_callback_handler );
	while ( true ) {
		cout << "Program processing..." << endl;
		sleep( 1 );
	}
	return EXIT_SUCCESS;
}