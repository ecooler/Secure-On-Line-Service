#include <iostream>
#include <openssl/md5.h>
#include <unordered_map>
#include <utility>

#include "../common/contextmanager.h"
#include "../common/err.h"
#include "../common/protocol.h"
#include "../common/vec.h"

#include "server_storage.h"

using namespace std;

/// Storage::Internal is the private struct that holds all of the fields of the
/// Storage object.  Organizing the fields as an Internal is part of the PIMPL
/// pattern.
struct Storage::Internal {
  /// AuthTableEntry represents one user stored in the authentication table
  struct AuthTableEntry {
    /// The name of the user; max 64 characters
    string username;

    /// The hashed password.  Note that the password is a max of 128 chars
    string pass_hash;

    /// The user's content
    vec content;
  };

  /// A unique 8-byte code to use as a prefix each time an AuthTable Entry is
  /// written to disk.
  ///
  /// NB: this isn't needed in assignment 1, but will be useful for backwards
  ///     compatibility later on.
  inline static const string AUTHENTRY = "AUTHAUTH";

  /// The map of authentication information, indexed by username
  unordered_map<string, AuthTableEntry> auth_table;

  /// filename is the name of the file from which the Storage object was loaded,
  /// and to which we persist the Storage object every time it changes
  string filename = "";

  /// Construct the Storage::Internal object by setting the filename
  ///
  /// @param fname The name of the file that should be used to load/store the
  ///              data
  Internal(const string &fname) : filename(fname) {}
};

/// Construct an empty object and specify the file from which it should be
/// loaded.  To avoid exceptions and errors in the constructor, the act of
/// loading data is separate from construction.
///
/// @param fname The name of the file that should be used to load/store the
///              data
Storage::Storage(const string &fname) : fields(new Internal(fname)) {}

/// Destructor for the storage object.
///
/// NB: The compiler doesn't know that it can create the default destructor in
///     the .h file, because PIMPL prevents it from knowing the size of
///     Storage::Internal.  Now that we have reified Storage::Internal, the
///     compiler can make a destructor for us.
Storage::~Storage() = default;

/// Populate the Storage object by loading an auth_table from this.filename.
/// Note that load() begins by clearing the auth_table, so that when the call
/// is complete, exactly and only the contents of the file are in the
/// auth_table.
///
/// @returns false if any error is encountered in the file, and true
///          otherwise.  Note that a non-existent file is not an error.
bool Storage::load() {
  cerr << "load is not implemented\n";
  return false;
}

/// Create a new entry in the Auth table.  If the user_name already exists, we
/// should return an error.  Otherwise, hash the password, and then save an
/// entry with the username, hashed password, and a zero-byte content.
///
/// @param user_name The user name to register
/// @param pass      The password to associate with that user name
///
/// @returns False if the username already exists, true otherwise
bool Storage::add_user(const string &user_name, const string &pass) {
  cerr << "add_user is not implemented\n";
  return false;
}

/// Set the data bytes for a user, but do so if and only if the password
/// matches
///
/// @param user_name The name of the user whose content is being set
/// @param pass      The password for the user, used to authenticate
/// @param content   The data to set for this user
///
/// @returns A pair with a bool to indicate error, and a vector indicating the
///          message (possibly an error message) that is the result of the
///          attempt
vec Storage::set_user_data(const string &user_name, const string &pass,
                           const vec &content) {
  cerr << "set_user_data is not implemented\n";
  return vec_from_string(RES_ERR_XMIT);
}

/// Return a copy of the user data for a user, but do so only if the password
/// matches
///
/// @param user_name The name of the user who made the request
/// @param pass      The password for the user, used to authenticate
/// @param who       The name of the user whose content is being fetched
///
/// @returns A pair with a bool to indicate error, and a vector indicating the
///          data (possibly an error message) that is the result of the
///          attempt.  Note that "no data" is an error
pair<bool, vec> Storage::get_user_data(const string &user_name,
                                       const string &pass, const string &who) {
  cerr << "get_user_data is not implemented\n";
  return {true, vec_from_string(RES_ERR_XMIT)};
}

/// Return a newline-delimited string containing all of the usernames in the
/// auth table
///
/// @param user_name The name of the user who made the request
/// @param pass      The password for the user, used to authenticate
///
/// @returns A vector with the data, or a vector with an error message
pair<bool, vec> Storage::get_all_users(const string &user_name,
                                       const string &pass) {
  cerr << "get_all_users is not implemented\n";
  return {true, vec_from_string(RES_ERR_XMIT)};
}

/// Authenticate a user
///
/// @param user_name The name of the user who made the request
/// @param pass      The password for the user, used to authenticate
///
/// @returns True if the user and password are valid, false otherwise
bool Storage::auth(const string &user_name, const string &pass) {
  cerr << "auth is not implemented\n";
  return false;
}

/// Write the entire Storage object (right now just the Auth table) to the
/// file specified by this.filename.  To ensure durability, Storage must be
/// persisted in two steps.  First, it must be written to a temporary file
/// (this.filename.tmp).  Then the temporary file can be renamed to replace
/// the older version of the Storage object.
void Storage::persist() { cerr << "persist is not implemented\n"; }

/// Shut down the storage when the server stops.
///
/// NB: this is only called when all threads have stopped accessing the
///     Storage object.  As a result, there's nothing left to do, so it's a
///     no-op.
void Storage::shutdown() {}
