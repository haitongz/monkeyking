#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <boost/algorithm/string.hpp>
#include <boost/range.hpp>

typedef boost::split_iterator<std::string::iterator> IteratorType;

int
Transform( std::string& str )
{
   std::string ret, tmp;
   IteratorType it;

   try {
      // assume message has a "-"
      for( it = boost::make_split_iterator( str, boost::last_finder( "-", boost::is_iequal() ) );
      it != IteratorType(); ++it ) {
         tmp = boost::copy_range<std::string>( *it );
         break;
      }

      if( tmp == str ) { //??
         std::cerr << "Invalid input: " << str << std::endl;
         return -1;
      }

      for( it = boost::make_split_iterator( tmp, boost::last_finder( "MQ", boost::is_iequal() ) );
      it != IteratorType(); ++it ) {
         ret = boost::copy_range<std::string>( *it );
      }

      if( tmp == ret ) { //??
         std::cerr << "Invalid input: " << str << std::endl;
         return -1;
      }

      boost::trim( ret );

      if( ret.length() <= 1 ) {
         std::cerr << "Invalid input: " << str << std::endl;
         return -1;
      }

      while( ::isdigit( *(ret.begin()) ) )
         ret.erase( ret.begin(), ret.begin()+1 );

      if( ret.length() <= 2 ) {
         std::cerr << "Invalid input: " << str << std::endl;
         return -1;
      }
      ret.insert( ret.begin()+2, ' ' );           // assume branch is always 2 chars

      if( ret.length() <= 6 ) {
         std::cerr << "Invalid input: " << str << std::endl;
         return -1;
      }
      ret.insert( ret.end()-6, ' ' );             // assume date is always 6 digits

      std::cout << "Transform transformed " << str << " to " << ret << std::endl;
   }
   catch( const std::exception& e ) {
      std::cerr << "Caught std::exception while transforming string: " << e.what() << std::endl;
      return -1;
   }
   catch( ... ) {
      std::cerr << "Caught unknown exception while transforming string." << std::endl;
      return -1;
   }
}

std::vector<std::string>&
split( const std::string& s, char delim, std::vector<std::string>& elems )
{
   std::stringstream ss( s );
   std::string item;
   while( std::getline( ss, item, delim ) ) {
      elems.push_back( item );
   }

   return elems;
}

std::vector<std::string>
split( const std::string& s, char delim )
{
   std::vector<std::string> elems;
   return split( s, delim, elems );
}

static int
Transform2( const std::string& str )
{
   try
   {
      std::vector<std::string> ss = split( str, '-' );
      if( ss[0] == str ) { //??
         std::cerr << "Cannot transform invalid string: " << str << std::endl;
         return -1;
      }

      if( ss[0].length() <= 2 || !::isdigit( *(ss[0].begin()+2) ) ) {
         std::cerr << "Cannot transform invalid string: " << str << std::endl;
         return -1;
      }
      ss[0].erase( ss[0].begin(), ss[0].begin()+2 );

      while( ::isdigit( *(ss[0].begin()) ) )
         ss[0].erase( ss[0].begin(), ss[0].begin()+1 );

      if( ss[0].length() <= 2 ) {
         std::cerr << "Cannot transform invalid string: " << str << std::endl;
         return -1;
      }
      ss[0].insert( ss[0].begin()+2, ' ' ); // assume branch is always 2 chars

      if( ss[0].length() <= 6 ) {
         std::cerr << "Cannot transform invalid string: " << str << std::endl;
         return -1;
      }
      ss[0].insert( ss[0].end()-6, ' ' );   // assume date is always 6 digits

      std::cout << "Transform2 transformed " << str << " to " << ss[0] << std::endl;
   }
   catch( const std::exception& e ) {
      std::cerr << "Caught std::exception while transforming string: " << e.what() << std::endl;
      return -1;
   }
   catch( ... ) {
      std::cerr << "Caught unknown exception while transforming string." << std::endl;
      return -1;
   }
}

int main( int argc, char** argv )
{
   std::string str = "MQ7XZ0221121203-1";
   std::string str1 = "MQ1XZ0221121203-89275934504";
   std::string str2 = "MQ10XZ0221121203-1";
   std::string str3 = "MQ1XZ0221121203";
   std::string str4 = "Q1XZ0221121203-1";
   std::string str5 = "MQ1XZ21121203-1";

   Transform( str );
   Transform( str1 );
   Transform( str2 );
   Transform( str3 );
   Transform( str4 );
   Transform( str5 );

   Transform2( str );
   Transform2( str1 );
   Transform2( str2 );
   Transform2( str3 );
   Transform2( str4 );
   Transform2( str5 );
}
