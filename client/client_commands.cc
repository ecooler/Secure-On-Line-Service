#include <cassert>
#include <cstring>
#include <iostream>
#include <openssl/rand.h>
#include <openssl/rsa.h>
#include <string>

#include "../common/contextmanager.h"
#include "../common/crypto.h"
#include "../common/file.h"
#include "../common/net.h"
#include "../common/protocol.h"
#include "../common/vec.h"

#include "client_commands.h"

using namespace std;

/// client_key() writes a request for the server's key on a socket descriptor.
/// When it gets it, it writes it to a file.
///
/// @param sd      An open socket
/// @param keyfile The name of the file to which the key should be written
void client_key(int sd, const string &keyfile) {
  cerr << "client_key is not implemented\n";
}

/// client_reg() sends the REG command to register a new user
///
/// @param sd      The socket descriptor for communicating with the server
/// @param pubkey  The public key of the server
/// @param user    The name of the user doing the request
/// @param pass    The password of the user doing the request
void client_reg(int sd, RSA *pubkey, const string &user, const string &pass,
                const string &, const string &) {
  cerr << "client_reg is not implemented\n";
}

/// client_bye() writes a request for the server to exit.
///
/// @param sd An open socket
/// @param pubkey  The public key of the server
/// @param user    The name of the user doing the request
/// @param pass    The password of the user doing the request
void client_bye(int sd, RSA *pubkey, const string &user, const string &pass,
                const string &, const string &) {
  cerr << "client_bye is not implemented\n";
}

/// client_sav() writes a request for the server to save its contents
///
/// @param sd An open socket
/// @param pubkey  The public key of the server
/// @param user The name of the user doing the request
/// @param pass The password of the user doing the request
void client_sav(int sd, RSA *pubkey, const string &user, const string &pass,
                const string &, const string &) {
  cerr << "client_sav is not implemented\n";
}

/// client_set() sends the SET command to set the content for a user
///
/// @param sd      The socket descriptor for communicating with the server
/// @param pubkey  The public key of the server
/// @param user    The name of the user doing the request
/// @param pass    The password of the user doing the request
/// @param setfile The file whose contents should be sent
void client_set(int sd, RSA *pubkey, const string &user, const string &pass,
                const string &setfile, const string &) {
  cerr << "client_set is not implemented\n";
}

/// client_get() requests the content associated with a user, and saves it to a
/// file called <user>.file.dat.
///
/// @param sd      The socket descriptor for communicating with the server
/// @param pubkey  The public key of the server
/// @param user    The name of the user doing the request
/// @param pass    The password of the user doing the request
/// @param getname The name of the user whose content should be fetched
void client_get(int sd, RSA *pubkey, const string &user, const string &pass,
                const string &getname, const string &) {
  cerr << "client_get is not implemented\n";
}

/// client_all() sends the ALL command to get a listing of all users, formatted
/// as text with one entry per line.
///
/// @param sd The socket descriptor for communicating with the server
/// @param pubkey  The public key of the server
/// @param user The name of the user doing the request
/// @param pass The password of the user doing the request
/// @param allfile The file where the result should go
void client_all(int sd, RSA *pubkey, const string &user, const string &pass,
                const string &allfile, const string &) {
  cerr << "client_all is not implemented\n";
}
