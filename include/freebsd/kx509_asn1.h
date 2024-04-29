/* Generated from /usr/src/crypto/heimdal/lib/asn1/kx509.asn1 */
/* Do not edit */

#ifndef __kx509_asn1_h__
#define __kx509_asn1_h__

#include <stddef.h>
#include <time.h>

#ifndef __asn1_common_definitions__
#define __asn1_common_definitions__

typedef struct heim_integer {
  size_t length;
  void *data;
  int negative;
} heim_integer;

typedef struct heim_octet_string {
  size_t length;
  void *data;
} heim_octet_string;

typedef char *heim_general_string;

typedef char *heim_utf8_string;

typedef struct heim_octet_string heim_printable_string;

typedef struct heim_octet_string heim_ia5_string;

typedef struct heim_bmp_string {
  size_t length;
  uint16_t *data;
} heim_bmp_string;

typedef struct heim_universal_string {
  size_t length;
  uint32_t *data;
} heim_universal_string;

typedef char *heim_visible_string;

typedef struct heim_oid {
  size_t length;
  unsigned *components;
} heim_oid;

typedef struct heim_bit_string {
  size_t length;
  void *data;
} heim_bit_string;

typedef struct heim_octet_string heim_any;
typedef struct heim_octet_string heim_any_set;

#define ASN1_MALLOC_ENCODE(T, B, BL, S, L, R)                  \
  do {                                                         \
    (BL) = length_##T((S));                                    \
    (B) = malloc((BL));                                        \
    if((B) == NULL) {                                          \
      (R) = ENOMEM;                                            \
    } else {                                                   \
      (R) = encode_##T(((unsigned char*)(B)) + (BL) - 1, (BL), \
                       (S), (L));                              \
      if((R) != 0) {                                           \
        free((B));                                             \
        (B) = NULL;                                            \
      }                                                        \
    }                                                          \
  } while (0)

#ifdef _WIN32
#ifndef ASN1_LIB
#define ASN1EXP  __declspec(dllimport)
#else
#define ASN1EXP
#endif
#define ASN1CALL __stdcall
#else
#define ASN1EXP
#define ASN1CALL
#endif
struct units;

#endif

/*
KX509-ERROR-CODE ::= INTEGER {
  KX509_STATUS_GOOD(0),
  KX509_STATUS_CLIENT_BAD(1),
  KX509_STATUS_CLIENT_FIX(2),
  KX509_STATUS_CLIENT_TEMP(3),
  KX509_STATUS_SERVER_BAD(4),
  KX509_STATUS_SERVER_TEMP(5),
  KX509_STATUS_SERVER_KEY(7)
}
*/

typedef enum KX509_ERROR_CODE {
  KX509_STATUS_GOOD = 0,
  KX509_STATUS_CLIENT_BAD = 1,
  KX509_STATUS_CLIENT_FIX = 2,
  KX509_STATUS_CLIENT_TEMP = 3,
  KX509_STATUS_SERVER_BAD = 4,
  KX509_STATUS_SERVER_TEMP = 5,
  KX509_STATUS_SERVER_KEY = 7
} KX509_ERROR_CODE;

ASN1EXP int    ASN1CALL decode_KX509_ERROR_CODE(const unsigned char *, size_t, KX509_ERROR_CODE *, size_t *);
ASN1EXP int    ASN1CALL encode_KX509_ERROR_CODE(unsigned char *, size_t, const KX509_ERROR_CODE *, size_t *);
ASN1EXP size_t ASN1CALL length_KX509_ERROR_CODE(const KX509_ERROR_CODE *);
ASN1EXP int    ASN1CALL copy_KX509_ERROR_CODE  (const KX509_ERROR_CODE *, KX509_ERROR_CODE *);
ASN1EXP void   ASN1CALL free_KX509_ERROR_CODE  (KX509_ERROR_CODE *);


/*
Kx509Request ::= SEQUENCE {
  authenticator   OCTET STRING,
  pk-hash         OCTET STRING,
  pk-key          OCTET STRING,
}
*/

typedef struct Kx509Request {
  heim_octet_string authenticator;
  heim_octet_string pk_hash;
  heim_octet_string pk_key;
} Kx509Request;

ASN1EXP int    ASN1CALL decode_Kx509Request(const unsigned char *, size_t, Kx509Request *, size_t *);
ASN1EXP int    ASN1CALL encode_Kx509Request(unsigned char *, size_t, const Kx509Request *, size_t *);
ASN1EXP size_t ASN1CALL length_Kx509Request(const Kx509Request *);
ASN1EXP int    ASN1CALL copy_Kx509Request  (const Kx509Request *, Kx509Request *);
ASN1EXP void   ASN1CALL free_Kx509Request  (Kx509Request *);


/*
Kx509Response ::= SEQUENCE {
  error-code      [0] INTEGER (-2147483648..2147483647) OPTIONAL,
  hash            [1] OCTET STRING OPTIONAL,
  certificate     [2] OCTET STRING OPTIONAL,
  e-text          [3]   VisibleString OPTIONAL,
}
*/

typedef struct Kx509Response {
  int *error_code;
  heim_octet_string *hash;
  heim_octet_string *certificate;
  heim_visible_string *e_text;
} Kx509Response;

ASN1EXP int    ASN1CALL decode_Kx509Response(const unsigned char *, size_t, Kx509Response *, size_t *);
ASN1EXP int    ASN1CALL encode_Kx509Response(unsigned char *, size_t, const Kx509Response *, size_t *);
ASN1EXP size_t ASN1CALL length_Kx509Response(const Kx509Response *);
ASN1EXP int    ASN1CALL copy_Kx509Response  (const Kx509Response *, Kx509Response *);
ASN1EXP void   ASN1CALL free_Kx509Response  (Kx509Response *);


#endif /* __kx509_asn1_h__ */
