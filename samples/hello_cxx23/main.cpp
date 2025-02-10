/* Copyright (C) 2025 cragson

This program is free software; you can redistribute it and/or modify it
under the terms of the GNU General Public License as published by the
Free Software Foundation; either version 3, or (at your option) any
later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; see the file COPYING. If not, see
<http://www.gnu.org/licenses/>.  */

#include <algorithm>
#include <thread>
#include <vector>
#include <print>
#include <ranges>
#include <string_view>

void task( const std::string_view prefix ) 
{
  std::vector< int32_t > vec = { 4, 2, 3, 1, 5 };

  std::ranges::sort( vec );

  std::print( "[+] sorted vec: " );

  std::ranges::for_each( vec, []( const auto elem ){ std::print("{} ", elem ); } );

  std::print( "\n" );

  try 
  {
    throw int32_t( 1337 );
  }
  catch( int e ) 
  {
    std::println( "[!] Caught exception: {}", e );
  }
}


int main() 
{
  std::println( "[+] Hello, libcxx!" );
  std::thread t( task, __FILE__ );
  t.join();

  return 0;
}
