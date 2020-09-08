#pragma once

#include <string>

/// protocol.h defines the messages that a client may send, and the responses a
/// server will provide.  Note that the entire request is a single byte stream,
/// as is the entire response.  The entire communication between client and
/// server should consist of just two messages.  First, the client sends a
/// message (the request), and then the server sends a reply message (the
/// response).
///
/// Different parts of a message may be encrypted in different ways.  We
/// indicate this with the 'enc()' function.  The expression 'enc(x, y)'
/// indicates that y should be encrypted using key x.  Both RSA and AES
/// encryption are used.  A unique AES key (aeskey) should be generated each
/// time the client sends an AES-encrypted message to the server.  An RSA key
/// (rsakey) is generated by the server once.
///
/// A request always begins with a fixed-size RSA-encrypted block of bytes
/// (@rblock), followed by a variable-size AES-encrypted block of bytes
/// (@ablock).  The only exception to this is the KEY request, which consists of
/// a fixed-size unencrypted block of bytes (@kblock). The @kblock or @rblock
/// will always be LEN_MSG_MIN bytes, regardless of whether it is an
/// RSA-encrypted block, or the "KEY" message.  KEY messages are padded with
/// '\0' characters. In the discussion below, this padding is represented by the
/// function pad0(). RSA-encrypted blocks should be padded with random bytes by
/// the RSA library.
///
/// When there is an AES block, its length will be given as part of the RSA
/// block.  Note that this is the length of the *encrypted* @ablock.
///
/// In describing message formats, we use the dot ('.') to indicate
/// concatenation.  So "ABC"."DEF" will consist of 6 bytes, and will be the
/// characters "ABCDEF".  When 'len()' appears in a description, this indicates
/// that a 4-byte *binary* value will be provided as a length.  You are allowed
/// to assume that only x86 machines will be used (little endian).
///
/// Finally, note that some error messages do not correspond directly to any
/// specific message, but are possible nonetheless (i.e., RES_ERR_INV_CMD).

/// Maximum length of a user name
const int LEN_UNAME = 64;

/// Maximum length of a password
const int LEN_PASS = 128;

/// Maximum length of a user's content field
const int LEN_CONTENT = 1048576;

/// Length of an rblock or kblock
const int LEN_RKBLOCK = 256;

/// Length of an RSA public key
const int LEN_RSA_PUBKEY = 426;

/// Length of pre-encryption rblock content
const int LEN_RBLOCK_CONTENT = 128;

/// Request the server's public key (@pubkey), to use for subsequent interaction
/// with the server by the client
///
/// @kblock   pad0("KEY")
/// @response @pubkey<EOF>
/// @errors   None
const std::string REQ_KEY = "KEY";

/// Request the creation of a new user, with null content.  The user name must
/// not already exist.
///
/// The user name (@u) and user password (@p) must conform to LEN_UNAME and
/// LEN_PASS.
///
/// @rblock   enc(pubkey, "REG".aeskey.length(@ablock))
/// @ablock   enc(aeskey, len(@u).@u.len(@p).@p)
/// @response enc(aeskey, "OK").<EOF>       -- Success
///           enc(aeskey, error_code).<EOF> -- Error (see @errors)
///           ERR_CRYPTO.<EOF>              -- Error (see @errors)
/// @errors   ERR_USER_EXISTS -- @u already exists as a user
///           ERR_MSG_FMT     -- Server unable to extract @u or @p
///           ERR_CRYPTO      -- Server could not decrypt @ablock
const std::string REQ_REG = "REG";

/// Force the server to stop.  @u and @p represent a valid user's username and
/// password.
///
/// The user name (@u) and user password (@p) must conform to LEN_UNAME and
/// LEN_PASS.
///
/// Note that a real server should never let a client cause it to stop.  This is
/// a convenience request to help the professor and TAs grade your assignment.
///
/// @rblock   enc(pubkey, "BYE".aeskey.length(@ablock))
/// @ablock   enc(aeskey, len(@u).@u.len(@p).@p)
/// @response enc(aeskey, "OK").<EOF>       -- Success
///           enc(aeskey, error_code).<EOF> -- Error (see @errors)
///           ERR_CRYPTO.<EOF>              -- Error (see @errors)
/// @errors   ERR_LOGIN       -- @u is not a valid user
///           ERR_LOGIN       -- @p is not @u's password
///           ERR_MSG_FMT     -- Server unable to extract @u or @p
///           ERR_CRYPTO      -- Server could not decrypt @ablock
const std::string REQ_BYE = "BYE";

/// Force the server to send all its data to disk.  @u and @p represent a valid
/// user's username and password.
///
/// The user name (@u) and user password (@p) must conform to LEN_UNAME and
/// LEN_PASS.
///
/// Note that a real server should never let a client cause it to do this.  This
/// is a convenience request to help the professor and TAs grade your
/// assignment.
///
/// @rblock   enc(pubkey, "SAV".aeskey.length(@ablock))
/// @ablock   enc(aeskey, len(@u).@u.len(@p).@p)
/// @response enc(aeskey, "OK").<EOF>       -- Success
///           enc(aeskey, error_code).<EOF> -- Error (see @errors)
///           ERR_CRYPTO.<EOF>              -- Error (see @errors)
/// @errors   ERR_LOGIN       -- @u is not a valid user
///           ERR_LOGIN       -- @p is not @u's password
///           ERR_MSG_FMT     -- Server unable to extract @u or @p
///           ERR_CRYPTO      -- Server could not decrypt @ablock
const std::string REQ_SAV = "SAV";

/// Allow user @u (with password @p) to set her profile content to the byte
/// stream @b.
///
/// The user name (@u) and user password (@p) must conform to LEN_UNAME and
/// LEN_PASS.  @b must be no more than LEN_CONTENT bytes.
///
/// @rblock   enc(pubkey, "SET".aeskey.length(@ablock))
/// @ablock   enc(aeskey, len(@u).@u.len(@p).@p.len(@b).@b)
/// @response enc(aeskey, "OK").<EOF>       -- Success
///           enc(aeskey, error_code).<EOF> -- Error (see @errors)
///           ERR_CRYPTO.<EOF>              -- Error (see @errors)
/// @errors   ERR_LOGIN       -- @u is not a valid user
///           ERR_LOGIN       -- @p is not @u's password
///           ERR_MSG_FMT     -- Server unable to extract @u or @p or @b
///           ERR_CRYPTO      -- Server could not decrypt @ablock
const std::string REQ_SET = "SET";

/// Allow user @u (with password @p) to fetch the profile content @c associated
/// with user @w.
///
/// The user name (@u) and user password (@p) must conform to LEN_UNAME and
/// LEN_PASS.  @w must be no more than LEN_UNAME bytes.
///
/// @rblock   enc(pubkey, "GET".aeskey.length(@ablock))
/// @ablock   enc(aeskey, len(@u).@u.len(@p).@p.len(@w).@w)
/// @response enc(aeskey, "OK".len(@c).@c).<EOF>    -- Success
///           enc(aeskey, error_code).<EOF>         -- Error (see @errors)
///           ERR_CRYPTO.<EOF>                      -- Error (see @errors)
/// @errors   ERR_LOGIN       -- @u is not a valid user
///           ERR_LOGIN       -- @p is not @u's password
///           ERR_NO_USER     -- @w is not a valid user
///           ERR_NO_DATA     -- @w has a null profile content
///           ERR_MSG_FMT     -- Server unable to extract @u or @p or @w
///           ERR_CRYPTO      -- Server could not decrypt @ablock
const std::string REQ_GET = "GET";

/// Allow user @u (with password @p) to get a newline-separated list (@l) of the
/// names of all the users.  @u will appear in @l, @l will not be sorted, and @l
/// will not have a trailing newline.
///
/// The user name (@u) and user password (@p) must conform to LEN_UNAME and
/// LEN_PASS.
///
/// @rblock   enc(pubkey, "ALL".aeskey.length(@ablock))
/// @ablock   enc(aeskey, len(@u).@u.len(@p).@p)
/// @response enc(aeskey, "OK".len(@l).@l).<EOF>    -- Success
///           enc(aeskey, error_code).<EOF>         -- Error (see @errors)
///           ERR_CRYPTO.<EOF>                      -- Error (see @errors)
/// @errors   ERR_LOGIN       -- @u is not a valid user
///           ERR_LOGIN       -- @p is not @u's password
///           ERR_MSG_FMT     -- Server unable to extract @u or @p or @w
///           ERR_CRYPTO      -- Server could not decrypt @ablock
const std::string REQ_ALL = "ALL";

/// Response code to indicate that the command was successful
const std::string RES_OK = "OK";

/// Response code to indicate that registered user already exists
const std::string RES_ERR_USER_EXISTS = "ERR_USER_EXISTS";

/// Response code to indicate that the client gave a bad username or password
const std::string RES_ERR_LOGIN = "ERR_LOGIN";

/// Response code to indicate that the client request was improperly formatted
const std::string RES_ERR_MSG_FMT = "ERR_MSG_FMT";

/// Response code to indicate that there is no data to send back
const std::string RES_ERR_NO_DATA = "ERR_NO_DATA";

/// Response code to indicate that the user being looked up is invalid
const std::string RES_ERR_NO_USER = "ERR_NO_USER";

/// Response code to indicate that the requested command doesn't exist
const std::string RES_ERR_INV_CMD = "ERR_INVALID_COMMAND";

/// Response code to indicate that the client didn't get as much data as
/// expected
const std::string RES_ERR_XMIT = "ERR_XMIT";

/// Response code to indicate that the client data can't be decrypted with the
/// provided AES key
const std::string RES_ERR_CRYPTO = "ERR_CRYPTO";