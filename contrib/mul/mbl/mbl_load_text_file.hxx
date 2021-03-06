#ifndef mbl_load_text_file_hxx_
#define mbl_load_text_file_hxx_
//:
// \file
// \brief Functions to load objects from text file
// \author dac

#include "mbl_load_text_file.h"
#include <mbl/mbl_exception.h>
#include <vcl_fstream.h>
#include <vcl_iterator.h>
#include <vcl_algorithm.h>
#include <vcl_cerrno.h>

//: Load vector from file with format "v1 v2 .. vn"
// \throws on error, or returns false if exceptions are disabled.
template <class T>
bool mbl_load_text_file(vcl_vector<T>& v, const vcl_string& path)
{
  vcl_ifstream ifs(path.c_str());
  if (!ifs)
    mbl_exception_throw_os_error(path, "Whilst trying to open data file for reading.");

  try
  {
    bool rv = mbl_load_text_file( v, ifs );
    if (!rv && errno)
      mbl_exception_throw_os_error(path, "Whilst trying to read data file.");
  }
  catch (const mbl_exception_parse_error& e)
  {
    mbl_exception_warning(  mbl_exception_parse_file_error(e.what(), path));
    return false;
  }

  return true;
}

//: Load vector from file with format "v1 v2 .. vn"
// \throws on error, or returns false if exceptions are disabled.
template <class T>
bool mbl_load_text_file(vcl_vector<T>& v, vcl_istream& is)
{
  v.resize(0);

  if (!is)
  {
    mbl_exception_warning( mbl_exception_parse_error( "mbl_load_text_file: IO error" ));
    return false;
  }

  vcl_copy(vcl_istream_iterator<T> (is), vcl_istream_iterator<T>(),
           vcl_back_insert_iterator< vcl_vector<T> > (v) );
  if (!is.eof())
  {
    mbl_exception_warning( mbl_exception_parse_error( "mbl_load_text_file: failed to finished loading" ));
    return false;
  }

  if (v.empty())
  {
    mbl_exception_warning( mbl_exception_parse_error("Could not parse indices file."));
    return false;
  }

  return true;
}

#undef MBL_LOAD_TEXT_FILE_INSTANTIATE_PATH
#define MBL_LOAD_TEXT_FILE_INSTANTIATE_PATH(T ) \
template bool mbl_load_text_file(vcl_vector<T >& v, const vcl_string& path)
#undef MBL_LOAD_TEXT_FILE_INSTANTIATE_STREAM
#define MBL_LOAD_TEXT_FILE_INSTANTIATE_STREAM(T ) \
template bool mbl_load_text_file(vcl_vector<T >& v, vcl_istream& is)

#endif //mbl_load_text_file_hxx_
