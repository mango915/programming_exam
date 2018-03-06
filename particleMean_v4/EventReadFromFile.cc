#include "EventReadFromFile.h"

#include "Event.h"

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// read data from file "name"
EventReadFromFile::EventReadFromFile( const string& name ) {
  file = new ifstream( name.c_str(), ios::binary );
}


EventReadFromFile::~EventReadFromFile() {
  delete file;
}


// get an event
const Event* EventReadFromFile::get() {
  return readFile();
}


// read an event
const Event* EventReadFromFile::readFile() {

  // event pointer and identifier
  Event* ev;
  int i;

  // try to read input file
  // on success create new event
  if ( file->read( reinterpret_cast<char*>( &i ),
                                    sizeof(  i ) ) ) ev = new Event( i );
  // on failure return null pointer
  else return 0;

  // read number of points
  int n;
  file->read( reinterpret_cast<char*>( &n ), sizeof( n ) );

  // read and store all points
  int e;
  for ( i = 0; i < n; ++i ) {
    file->read( reinterpret_cast<char*>( &e ), sizeof( e ) );
    ev->add( e );
  }

  return ev;

}

