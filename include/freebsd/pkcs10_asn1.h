/* Generated from /usr/src/crypto/heimdal/lib/hx509/pkcs10.asn1 */
/* Do not edit */

#ifndef __pkcs10_asn1_h__
#define __pkcs10_asn1_h__

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
/*
CertificationRequestInfo ::= SEQUENCE {
  version         INTEGER {
    pkcs10_v1(0)
  },
  subject         Name,
  subjectPKInfo   SubjectPublicKeyInfo,
  attributes      [0] IMPLICIT SET OF Attribute OPTIONAL,
}
*/

typedef struct CertificationRequestInfo {
  heim_octet_string _save;
  enum  {
    pkcs10_v1 = 0
} version;
  Name subject;
  SubjectPublicKeyInfo subjectPKInfo;
  struct CertificationRequestInfo_attributes {
    unsigned int len;
    Attribute *val;
  } *attributes;
} CertificationRequestInfo;

ASN1EXP int    ASN1CALL decode_CertificationRequestInfo(const unsigned char *, size_t, CertificationRequestInfo *, size_t *);
ASN1EXP int    ASN1CALL encode_CertificationRequestInfo(unsigned char *, size_t, const CertificationRequestInfo *, size_t *);
ASN1EXP size_t ASN1CALL length_CertificationRequestInfo(const CertificationRequestInfo *);
ASN1EXP int    ASN1CALL copy_CertificationRequestInfo  (const CertificationRequestInfo *, CertificationRequestInfo *);
ASN1EXP void   ASN1CALL free_CertificationRequestInfo  (CertificationRequestInfo *);


/*
CertificationRequest ::= SEQUENCE {
  certificationRequestInfo   CertificationRequestInfo,
  signatureAlgorithm         AlgorithmIdentifier,
  signature                    BIT STRING {
  },
}
*/

typedef struct CertificationRequest {
  CertificationRequestInfo certificationRequestInfo;
  AlgorithmIdentifier signatureAlgorithm;
  heim_bit_string signature;
} CertificationRequest;

ASN1EXP int    ASN1CALL decode_CertificationRequest(const unsigned char *, size_t, CertificationRequest *, size_t *);
ASN1EXP int    ASN1CALL encode_CertificationRequest(unsigned char *, size_t, const CertificationRequest *, size_t *);
ASN1EXP size_t ASN1CALL length_CertificationRequest(const CertificationRequest *);
ASN1EXP int    ASN1CALL copy_CertificationRequest  (const CertificationRequest *, CertificationRequest *);
ASN1EXP void   ASN1CALL free_CertificationRequest  (CertificationRequest *);


#endif /* __pkcs10_asn1_h__ */
