#include <atomic>
#include <csignal>
#include <cstdlib>
#include <fmt/color.h>
#include <fmt/core.h>
#include <fstream>
#include <iostream>
#include <iterator>
#include <string>

std::atomic<int> g_sigint_count{ 0 };
void RunFile( const std::string& );
void RunPrompt();
void Run( const std::string& );
void SigintCallbackHandler( int );

int main( int argc, char* argv[] )
{
	std::signal( SIGINT, SigintCallbackHandler );
	if ( argc > 2 ) {
		fmt::println( "Usage: clox [script]" );
		std::exit( 64 );
	} else if ( argc == 2 ) {
		RunFile( argv[ 1 ] );
	} else {
		fmt::println( "Welcome to Clox v0.0.1" );
		fmt::println( "Type \".help\" for more information" );
		RunPrompt();
	}
	return EXIT_SUCCESS;
}

void SigintCallbackHandler( int signal )
{
	++g_sigint_count;
}

void RunFile( const std::string& path )
{
	std::ifstream file{ path, std::ios::binary };
	if ( !file ) {
		throw std::runtime_error( fmt::format( "Can not open file {}.", path ) );
	}
	const std::string content{
		( std::istreambuf_iterator<char>{ file } ),
		std::istreambuf_iterator<char>{}
	};
	Run( content );
}

void RunPrompt()
{
	std::string line;
	while ( true ) {
		fmt::print( fg( fmt::color::crimson ), "> " );
		if ( !std::getline( std::cin >> std::ws, line ) ) {
			if ( g_sigint_count.load() == 0 ) {
				fmt::println( "\n(To exit, press Ctrl+C again or Ctrl+D or type .exit)" );
				std::cin.clear();
				continue;
			} else {
				std::exit( 0 );
			}
		}
		Run( line );
	}
}

void Run( const std::string& line )
{
	fmt::println( line );
}