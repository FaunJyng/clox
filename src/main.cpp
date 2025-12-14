#include <chrono>
#include <csignal>
#include <cstdlib>
#include <fmt/color.h>
#include <fmt/core.h>
#include <fstream>
#include <iostream>
#include <iterator>
#include <string>
#include <thread>

void RunFile( const std::string& );
void RunPrompt();
void Run( const std::string& );
void SIGINTHandler( int );

int main( int argc, char* argv[] )
{
	std::signal( SIGINT, SIGINTHandler );
	if ( argc > 2 ) {
		fmt::println( "Usage: clox [script]" );
		std::exit( 64 );
	} else if ( argc == 2 ) {
		RunFile( argv[ 1 ] );
	} else {
		fmt::print( "Welcome to Clox v0.0.1\n" );
		fmt::print( "Type \".help\" for more information\n" );
		RunPrompt();
	}
	return EXIT_SUCCESS;
}

void SIGINTHandler( int signal )
{
	if ( signal == SIGINT ) {
		fmt::print( fg( fmt::color::dim_gray ), "\nKeyboardInterupt\n" );
	}
	std::signal( SIGINT, SIGINTHandler );
};

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
		fmt::print( "> " );
		if ( !std::getline( std::cin, line ) ) {
			std::cin.clear();
			std::this_thread::sleep_for( std::chrono::milliseconds( 1 ) );
			continue;
		}
		if ( line == ".exit" || line == ".e" )
			break;
		Run( line );
	}
}

void Run( const std::string& line )
{
	if ( line.empty() || line.length() == 0 ) {
		fmt::print( "" );
	} else {
		fmt::print( fg( fmt::color::yellow ), "{}\n", line );
	}
}