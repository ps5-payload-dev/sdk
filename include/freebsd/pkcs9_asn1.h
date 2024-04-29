/* Generated from /usr/src/crypto/heimdal/lib/asn1/pkcs9.asn1 */
/* Do not edit */

#ifndef __pkcs9_asn1_h__
#define __pkcs9_asn1_h__

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

/* OBJECT IDENTIFIER id-pkcs-9 ::= { iso(1) member-body(2) us(840) rsadsi(113549) pkcs(1) pkcs-9(9) } */
extern ASN1EXP const heim_oid asn1_oid_id_pkcs_9;
#define ASN1_OID_ID_PKCS_9 (&asn1_oid_id_pkcs_9)

/* OBJECT IDENTIFIER id-pkcs9-emailAddress ::= { iso(1) member-body(2) us(840) rsadsi(113549) pkcs(1) pkcs-9(9) label-less(1) } */
extern ASN1EXP const heim_oid asn1_oid_id_pkcs9_emailAddress;
#define ASN1_OID_ID_PKCS9_EMAILADDRESS (&asn1_oid_id_pkcs9_emailAddress)

/* OBJECT IDENTIFIER id-pkcs9-contentType ::= { iso(1) member-body(2) us(840) rsadsi(113549) pkcs(1) pkcs-9(9) label-less(3) } */
extern ASN1EXP const heim_oid asn1_oid_id_pkcs9_contentType;
#define ASN1_OID_ID_PKCS9_CONTENTTYPE (&asn1_oid_id_pkcs9_contentType)

/* OBJECT IDENTIFIER id-pkcs9-messageDigest ::= { iso(1) member-body(2) us(840) rsadsi(113549) pkcs(1) pkcs-9(9) label-less(4) } */
extern ASN1EXP const heim_oid asn1_oid_id_pkcs9_messageDigest;
#define ASN1_OID_ID_PKCS9_MESSAGEDIGEST (&asn1_oid_id_pkcs9_messageDigest)

/* OBJECT IDENTIFIER id-pkcs9-signingTime ::= { iso(1) member-body(2) us(840) rsadsi(113549) pkcs(1) pkcs-9(9) label-less(5) } */
extern ASN1EXP const heim_oid asn1_oid_id_pkcs9_signingTime;
#define ASN1_OID_ID_PKCS9_SIGNINGTIME (&asn1_oid_id_pkcs9_signingTime)

/* OBJECT IDENTIFIER id-pkcs9-countersignature ::= { iso(1) member-body(2) us(840) rsadsi(113549) pkcs(1) pkcs-9(9) label-less(6) } */
extern ASN1EXP const heim_oid asn1_oid_id_pkcs9_countersignature;
#define ASN1_OID_ID_PKCS9_COUNTERSIGNATURE (&asn1_oid_id_pkcs9_countersignature)

/* OBJECT IDENTIFIER id-pkcs-9-at-friendlyName ::= { iso(1) member-body(2) us(840) rsadsi(113549) pkcs(1) pkcs-9(9) label-less(20) } */
extern ASN1EXP const heim_oid asn1_oid_id_pkcs_9_at_friendlyName;
#define ASN1_OID_ID_PKCS_9_AT_FRIENDLYNAME (&asn1_oid_id_pkcs_9_at_friendlyName)

/* OBJECT IDENTIFIER id-pkcs-9-at-localKeyId ::= { iso(1) member-body(2) us(840) rsadsi(113549) pkcs(1) pkcs-9(9) label-less(21) } */
extern ASN1EXP const heim_oid asn1_oid_id_pkcs_9_at_localKeyId;
#define ASN1_OID_ID_PKCS_9_AT_LOCALKEYID (&asn1_oid_id_pkcs_9_at_localKeyId)

/* OBJECT IDENTIFIER id-pkcs-9-at-certTypes ::= { iso(1) member-body(2) us(840) rsadsi(113549) pkcs(1) pkcs-9(9) label-less(22) } */
extern ASN1EXP const heim_oid asn1_oid_id_pkcs_9_at_certTypes;
#define ASN1_OID_ID_PKCS_9_AT_CERTTYPES (&asn1_oid_id_pkcs_9_at_certTypes)

/* OBJECT IDENTIFIER id-pkcs-9-at-certTypes-x509 ::= { iso(1) member-body(2) us(840) rsadsi(113549) pkcs(1) pkcs-9(9) label-less(22) label-less(1) } */
extern ASN1EXP const heim_oid asn1_oid_id_pkcs_9_at_certTypes_x509;
#define ASN1_OID_ID_PKCS_9_AT_CERTTYPES_X509 (&asn1_oid_id_pkcs_9_at_certTypes_x509)

/*
PKCS9-BMPString ::= BMPString
*/

typedef heim_bmp_string PKCS9_BMPString;

ASN1EXP int    ASN1CALL decode_PKCS9_BMPString(const unsigned char *, size_t, PKCS9_BMPString *, size_t *);
ASN1EXP int    ASN1CALL encode_PKCS9_BMPString(unsigned char *, size_t, const PKCS9_BMPString *, size_t *);
ASN1EXP size_t ASN1CALL length_PKCS9_BMPString(const PKCS9_BMPString *);
ASN1EXP int    ASN1CALL copy_PKCS9_BMPString  (const PKCS9_BMPString *, PKCS9_BMPString *);
ASN1EXP void   ASN1CALL free_PKCS9_BMPString  (PKCS9_BMPString *);


/*
PKCS9-friendlyName ::= SET OF PKCS9-BMPString
*/

typedef struct PKCS9_friendlyName {
  unsigned int len;
  PKCS9_BMPString *val;
} PKCS9_friendlyName;

ASN1EXP int    ASN1CALL decode_PKCS9_friendlyName(const unsigned char *, size_t, PKCS9_friendlyName *, size_t *);
ASN1EXP int    ASN1CALL encode_PKCS9_friendlyName(unsigned char *, size_t, const PKCS9_friendlyName *, size_t *);
ASN1EXP size_t ASN1CALL length_PKCS9_friendlyName(const PKCS9_friendlyName *);
ASN1EXP int    ASN1CALL copy_PKCS9_friendlyName  (const PKCS9_friendlyName *, PKCS9_friendlyName *);
ASN1EXP void   ASN1CALL free_PKCS9_friendlyName  (PKCS9_friendlyName *);


#endif /* __pkcs9_asn1_h__ */
