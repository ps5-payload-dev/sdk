/* Generated from /usr/src/crypto/heimdal/lib/asn1/pkcs8.asn1 */
/* Do not edit */

#ifndef __pkcs8_asn1_h__
#define __pkcs8_asn1_h__

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

#include <rfc2459_asn1.h>
#include <heim_asn1.h>
/*
PKCS8PrivateKeyAlgorithmIdentifier ::= AlgorithmIdentifier
*/

typedef AlgorithmIdentifier PKCS8PrivateKeyAlgorithmIdentifier;

ASN1EXP int    ASN1CALL decode_PKCS8PrivateKeyAlgorithmIdentifier(const unsigned char *, size_t, PKCS8PrivateKeyAlgorithmIdentifier *, size_t *);
ASN1EXP int    ASN1CALL encode_PKCS8PrivateKeyAlgorithmIdentifier(unsigned char *, size_t, const PKCS8PrivateKeyAlgorithmIdentifier *, size_t *);
ASN1EXP size_t ASN1CALL length_PKCS8PrivateKeyAlgorithmIdentifier(const PKCS8PrivateKeyAlgorithmIdentifier *);
ASN1EXP int    ASN1CALL copy_PKCS8PrivateKeyAlgorithmIdentifier  (const PKCS8PrivateKeyAlgorithmIdentifier *, PKCS8PrivateKeyAlgorithmIdentifier *);
ASN1EXP void   ASN1CALL free_PKCS8PrivateKeyAlgorithmIdentifier  (PKCS8PrivateKeyAlgorithmIdentifier *);


/*
PKCS8PrivateKey ::= OCTET STRING
*/

typedef heim_octet_string PKCS8PrivateKey;

ASN1EXP int    ASN1CALL decode_PKCS8PrivateKey(const unsigned char *, size_t, PKCS8PrivateKey *, size_t *);
ASN1EXP int    ASN1CALL encode_PKCS8PrivateKey(unsigned char *, size_t, const PKCS8PrivateKey *, size_t *);
ASN1EXP size_t ASN1CALL length_PKCS8PrivateKey(const PKCS8PrivateKey *);
ASN1EXP int    ASN1CALL copy_PKCS8PrivateKey  (const PKCS8PrivateKey *, PKCS8PrivateKey *);
ASN1EXP void   ASN1CALL free_PKCS8PrivateKey  (PKCS8PrivateKey *);


/*
PKCS8Attributes ::= SET OF Attribute
*/

typedef struct PKCS8Attributes {
  unsigned int len;
  Attribute *val;
} PKCS8Attributes;

ASN1EXP int    ASN1CALL decode_PKCS8Attributes(const unsigned char *, size_t, PKCS8Attributes *, size_t *);
ASN1EXP int    ASN1CALL encode_PKCS8Attributes(unsigned char *, size_t, const PKCS8Attributes *, size_t *);
ASN1EXP size_t ASN1CALL length_PKCS8Attributes(const PKCS8Attributes *);
ASN1EXP int    ASN1CALL copy_PKCS8Attributes  (const PKCS8Attributes *, PKCS8Attributes *);
ASN1EXP void   ASN1CALL free_PKCS8Attributes  (PKCS8Attributes *);


/*
PKCS8PrivateKeyInfo ::= SEQUENCE {
  version               INTEGER,
  privateKeyAlgorithm   PKCS8PrivateKeyAlgorithmIdentifier,
  privateKey            PKCS8PrivateKey,
  attributes            [0] IMPLICIT SET OF Attribute OPTIONAL,
}
*/

typedef struct PKCS8PrivateKeyInfo {
  heim_integer version;
  PKCS8PrivateKeyAlgorithmIdentifier privateKeyAlgorithm;
  PKCS8PrivateKey privateKey;
  struct PKCS8PrivateKeyInfo_attributes {
    unsigned int len;
    Attribute *val;
  } *attributes;
} PKCS8PrivateKeyInfo;

ASN1EXP int    ASN1CALL decode_PKCS8PrivateKeyInfo(const unsigned char *, size_t, PKCS8PrivateKeyInfo *, size_t *);
ASN1EXP int    ASN1CALL encode_PKCS8PrivateKeyInfo(unsigned char *, size_t, const PKCS8PrivateKeyInfo *, size_t *);
ASN1EXP size_t ASN1CALL length_PKCS8PrivateKeyInfo(const PKCS8PrivateKeyInfo *);
ASN1EXP int    ASN1CALL copy_PKCS8PrivateKeyInfo  (const PKCS8PrivateKeyInfo *, PKCS8PrivateKeyInfo *);
ASN1EXP void   ASN1CALL free_PKCS8PrivateKeyInfo  (PKCS8PrivateKeyInfo *);


/*
PKCS8EncryptedData ::= OCTET STRING
*/

typedef heim_octet_string PKCS8EncryptedData;

ASN1EXP int    ASN1CALL decode_PKCS8EncryptedData(const unsigned char *, size_t, PKCS8EncryptedData *, size_t *);
ASN1EXP int    ASN1CALL encode_PKCS8EncryptedData(unsigned char *, size_t, const PKCS8EncryptedData *, size_t *);
ASN1EXP size_t ASN1CALL length_PKCS8EncryptedData(const PKCS8EncryptedData *);
ASN1EXP int    ASN1CALL copy_PKCS8EncryptedData  (const PKCS8EncryptedData *, PKCS8EncryptedData *);
ASN1EXP void   ASN1CALL free_PKCS8EncryptedData  (PKCS8EncryptedData *);


/*
PKCS8EncryptedPrivateKeyInfo ::= SEQUENCE {
  encryptionAlgorithm   AlgorithmIdentifier,
  encryptedData         PKCS8EncryptedData,
}
*/

typedef struct PKCS8EncryptedPrivateKeyInfo {
  AlgorithmIdentifier encryptionAlgorithm;
  PKCS8EncryptedData encryptedData;
} PKCS8EncryptedPrivateKeyInfo;

ASN1EXP int    ASN1CALL decode_PKCS8EncryptedPrivateKeyInfo(const unsigned char *, size_t, PKCS8EncryptedPrivateKeyInfo *, size_t *);
ASN1EXP int    ASN1CALL encode_PKCS8EncryptedPrivateKeyInfo(unsigned char *, size_t, const PKCS8EncryptedPrivateKeyInfo *, size_t *);
ASN1EXP size_t ASN1CALL length_PKCS8EncryptedPrivateKeyInfo(const PKCS8EncryptedPrivateKeyInfo *);
ASN1EXP int    ASN1CALL copy_PKCS8EncryptedPrivateKeyInfo  (const PKCS8EncryptedPrivateKeyInfo *, PKCS8EncryptedPrivateKeyInfo *);
ASN1EXP void   ASN1CALL free_PKCS8EncryptedPrivateKeyInfo  (PKCS8EncryptedPrivateKeyInfo *);


#endif /* __pkcs8_asn1_h__ */
