#include <cstring>
#include <iostream>

using namespace std;

/// Print an error message that combines some application-specific text with the
/// standard unix error message that accompanies errno.
///
/// @param err    The error code that was generated by the program
/// @param prefix The text to display before the error message
void sys_error(int err, const char *prefix) {
  char buf[1024];
  cerr << prefix << " " << strerror_r(err, buf, sizeof(buf)) << endl;
}