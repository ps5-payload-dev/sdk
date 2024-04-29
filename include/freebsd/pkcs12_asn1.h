/* Generated from /usr/src/crypto/heimdal/lib/asn1/pkcs12.asn1 */
/* Do not edit */

#ifndef __pkcs12_asn1_h__
#define __pkcs12_asn1_h__

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

#include <cms_asn1.h>
#include <rfc2459_asn1.h>
#include <heim_asn1.h>
/* OBJECT IDENTIFIER id-pkcs-12 ::= { iso(1) member-body(2) us(840) rsadsi(113549) pkcs(1) pkcs-12(12) } */
extern ASN1EXP const heim_oid asn1_oid_id_pkcs_12;
#define ASN1_OID_ID_PKCS_12 (&asn1_oid_id_pkcs_12)

/* OBJECT IDENTIFIER id-pkcs-12PbeIds ::= { iso(1) member-body(2) us(840) rsadsi(113549) pkcs(1) pkcs-12(12) label-less(1) } */
extern ASN1EXP const heim_oid asn1_oid_id_pkcs_12PbeIds;
#define ASN1_OID_ID_PKCS_12PBEIDS (&asn1_oid_id_pkcs_12PbeIds)

/* OBJECT IDENTIFIER id-pbeWithSHAAnd128BitRC4 ::= { iso(1) member-body(2) us(840) rsadsi(113549) pkcs(1) pkcs-12(12) label-less(1) label-less(1) } */
extern ASN1EXP const heim_oid asn1_oid_id_pbeWithSHAAnd128BitRC4;
#define ASN1_OID_ID_PBEWITHSHAAND128BITRC4 (&asn1_oid_id_pbeWithSHAAnd128BitRC4)

/* OBJECT IDENTIFIER id-pbeWithSHAAnd40BitRC4 ::= { iso(1) member-body(2) us(840) rsadsi(113549) pkcs(1) pkcs-12(12) label-less(1) label-less(2) } */
extern ASN1EXP const heim_oid asn1_oid_id_pbeWithSHAAnd40BitRC4;
#define ASN1_OID_ID_PBEWITHSHAAND40BITRC4 (&asn1_oid_id_pbeWithSHAAnd40BitRC4)

/* OBJECT IDENTIFIER id-pbeWithSHAAnd3-KeyTripleDES-CBC ::= { iso(1) member-body(2) us(840) rsadsi(113549) pkcs(1) pkcs-12(12) label-less(1) label-less(3) } */
extern ASN1EXP const heim_oid asn1_oid_id_pbeWithSHAAnd3_KeyTripleDES_CBC;
#define ASN1_OID_ID_PBEWITHSHAAND3_KEYTRIPLEDES_CBC (&asn1_oid_id_pbeWithSHAAnd3_KeyTripleDES_CBC)

/* OBJECT IDENTIFIER id-pbeWithSHAAnd2-KeyTripleDES-CBC ::= { iso(1) member-body(2) us(840) rsadsi(113549) pkcs(1) pkcs-12(12) label-less(1) label-less(4) } */
extern ASN1EXP const heim_oid asn1_oid_id_pbeWithSHAAnd2_KeyTripleDES_CBC;
#define ASN1_OID_ID_PBEWITHSHAAND2_KEYTRIPLEDES_CBC (&asn1_oid_id_pbeWithSHAAnd2_KeyTripleDES_CBC)

/* OBJECT IDENTIFIER id-pbeWithSHAAnd128BitRC2-CBC ::= { iso(1) member-body(2) us(840) rsadsi(113549) pkcs(1) pkcs-12(12) label-less(1) label-less(5) } */
extern ASN1EXP const heim_oid asn1_oid_id_pbeWithSHAAnd128BitRC2_CBC;
#define ASN1_OID_ID_PBEWITHSHAAND128BITRC2_CBC (&asn1_oid_id_pbeWithSHAAnd128BitRC2_CBC)

/* OBJECT IDENTIFIER id-pbewithSHAAnd40BitRC2-CBC ::= { iso(1) member-body(2) us(840) rsadsi(113549) pkcs(1) pkcs-12(12) label-less(1) label-less(6) } */
extern ASN1EXP const heim_oid asn1_oid_id_pbewithSHAAnd40BitRC2_CBC;
#define ASN1_OID_ID_PBEWITHSHAAND40BITRC2_CBC (&asn1_oid_id_pbewithSHAAnd40BitRC2_CBC)

/* OBJECT IDENTIFIER id-pkcs12-bagtypes ::= { iso(1) member-body(2) us(840) rsadsi(113549) pkcs(1) pkcs-12(12) label-less(10) label-less(1) } */
extern ASN1EXP const heim_oid asn1_oid_id_pkcs12_bagtypes;
#define ASN1_OID_ID_PKCS12_BAGTYPES (&asn1_oid_id_pkcs12_bagtypes)

/* OBJECT IDENTIFIER id-pkcs12-keyBag ::= { iso(1) member-body(2) us(840) rsadsi(113549) pkcs(1) pkcs-12(12) label-less(10) label-less(1) label-less(1) } */
extern ASN1EXP const heim_oid asn1_oid_id_pkcs12_keyBag;
#define ASN1_OID_ID_PKCS12_KEYBAG (&asn1_oid_id_pkcs12_keyBag)

/* OBJECT IDENTIFIER id-pkcs12-pkcs8ShroudedKeyBag ::= { iso(1) member-body(2) us(840) rsadsi(113549) pkcs(1) pkcs-12(12) label-less(10) label-less(1) label-less(2) } */
extern ASN1EXP const heim_oid asn1_oid_id_pkcs12_pkcs8ShroudedKeyBag;
#define ASN1_OID_ID_PKCS12_PKCS8SHROUDEDKEYBAG (&asn1_oid_id_pkcs12_pkcs8ShroudedKeyBag)

/* OBJECT IDENTIFIER id-pkcs12-certBag ::= { iso(1) member-body(2) us(840) rsadsi(113549) pkcs(1) pkcs-12(12) label-less(10) label-less(1) label-less(3) } */
extern ASN1EXP const heim_oid asn1_oid_id_pkcs12_certBag;
#define ASN1_OID_ID_PKCS12_CERTBAG (&asn1_oid_id_pkcs12_certBag)

/* OBJECT IDENTIFIER id-pkcs12-crlBag ::= { iso(1) member-body(2) us(840) rsadsi(113549) pkcs(1) pkcs-12(12) label-less(10) label-less(1) label-less(4) } */
extern ASN1EXP const heim_oid asn1_oid_id_pkcs12_crlBag;
#define ASN1_OID_ID_PKCS12_CRLBAG (&asn1_oid_id_pkcs12_crlBag)

/* OBJECT IDENTIFIER id-pkcs12-secretBag ::= { iso(1) member-body(2) us(840) rsadsi(113549) pkcs(1) pkcs-12(12) label-less(10) label-less(1) label-less(5) } */
extern ASN1EXP const heim_oid asn1_oid_id_pkcs12_secretBag;
#define ASN1_OID_ID_PKCS12_SECRETBAG (&asn1_oid_id_pkcs12_secretBag)

/* OBJECT IDENTIFIER id-pkcs12-safeContentsBag ::= { iso(1) member-body(2) us(840) rsadsi(113549) pkcs(1) pkcs-12(12) label-less(10) label-less(1) label-less(6) } */
extern ASN1EXP const heim_oid asn1_oid_id_pkcs12_safeContentsBag;
#define ASN1_OID_ID_PKCS12_SAFECONTENTSBAG (&asn1_oid_id_pkcs12_safeContentsBag)

/*
PKCS12-MacData ::= SEQUENCE {
  mac             DigestInfo,
  macSalt         OCTET STRING,
  iterations      INTEGER OPTIONAL,
}
*/

typedef struct PKCS12_MacData {
  DigestInfo mac;
  heim_octet_string macSalt;
  heim_integer *iterations;
} PKCS12_MacData;

ASN1EXP int    ASN1CALL decode_PKCS12_MacData(const unsigned char *, size_t, PKCS12_MacData *, size_t *);
ASN1EXP int    ASN1CALL encode_PKCS12_MacData(unsigned char *, size_t, const PKCS12_MacData *, size_t *);
ASN1EXP size_t ASN1CALL length_PKCS12_MacData(const PKCS12_MacData *);
ASN1EXP int    ASN1CALL copy_PKCS12_MacData  (const PKCS12_MacData *, PKCS12_MacData *);
ASN1EXP void   ASN1CALL free_PKCS12_MacData  (PKCS12_MacData *);


/*
PKCS12-PFX ::= SEQUENCE {
  version         INTEGER,
  authSafe        ContentInfo,
  macData         PKCS12-MacData OPTIONAL,
}
*/

typedef struct PKCS12_PFX {
  heim_integer version;
  ContentInfo authSafe;
  PKCS12_MacData *macData;
} PKCS12_PFX;

ASN1EXP int    ASN1CALL decode_PKCS12_PFX(const unsigned char *, size_t, PKCS12_PFX *, size_t *);
ASN1EXP int    ASN1CALL encode_PKCS12_PFX(unsigned char *, size_t, const PKCS12_PFX *, size_t *);
ASN1EXP size_t ASN1CALL length_PKCS12_PFX(const PKCS12_PFX *);
ASN1EXP int    ASN1CALL copy_PKCS12_PFX  (const PKCS12_PFX *, PKCS12_PFX *);
ASN1EXP void   ASN1CALL free_PKCS12_PFX  (PKCS12_PFX *);


/*
PKCS12-AuthenticatedSafe ::= SEQUENCE OF ContentInfo
*/

typedef struct PKCS12_AuthenticatedSafe {
  unsigned int len;
  ContentInfo *val;
} PKCS12_AuthenticatedSafe;

ASN1EXP int    ASN1CALL decode_PKCS12_AuthenticatedSafe(const unsigned char *, size_t, PKCS12_AuthenticatedSafe *, size_t *);
ASN1EXP int    ASN1CALL encode_PKCS12_AuthenticatedSafe(unsigned char *, size_t, const PKCS12_AuthenticatedSafe *, size_t *);
ASN1EXP size_t ASN1CALL length_PKCS12_AuthenticatedSafe(const PKCS12_AuthenticatedSafe *);
ASN1EXP int    ASN1CALL copy_PKCS12_AuthenticatedSafe  (const PKCS12_AuthenticatedSafe *, PKCS12_AuthenticatedSafe *);
ASN1EXP void   ASN1CALL free_PKCS12_AuthenticatedSafe  (PKCS12_AuthenticatedSafe *);


/*
PKCS12-Attribute ::= SEQUENCE {
  attrId            OBJECT IDENTIFIER,
  attrValues      heim_any_set,
}
*/

typedef struct PKCS12_Attribute {
  heim_oid attrId;
  heim_any_set attrValues;
} PKCS12_Attribute;

ASN1EXP int    ASN1CALL decode_PKCS12_Attribute(const unsigned char *, size_t, PKCS12_Attribute *, size_t *);
ASN1EXP int    ASN1CALL encode_PKCS12_Attribute(unsigned char *, size_t, const PKCS12_Attribute *, size_t *);
ASN1EXP size_t ASN1CALL length_PKCS12_Attribute(const PKCS12_Attribute *);
ASN1EXP int    ASN1CALL copy_PKCS12_Attribute  (const PKCS12_Attribute *, PKCS12_Attribute *);
ASN1EXP void   ASN1CALL free_PKCS12_Attribute  (PKCS12_Attribute *);


/*
PKCS12-Attributes ::= SET OF PKCS12-Attribute
*/

typedef struct PKCS12_Attributes {
  unsigned int len;
  PKCS12_Attribute *val;
} PKCS12_Attributes;

ASN1EXP int    ASN1CALL decode_PKCS12_Attributes(const unsigned char *, size_t, PKCS12_Attributes *, size_t *);
ASN1EXP int    ASN1CALL encode_PKCS12_Attributes(unsigned char *, size_t, const PKCS12_Attributes *, size_t *);
ASN1EXP size_t ASN1CALL length_PKCS12_Attributes(const PKCS12_Attributes *);
ASN1EXP int    ASN1CALL copy_PKCS12_Attributes  (const PKCS12_Attributes *, PKCS12_Attributes *);
ASN1EXP void   ASN1CALL free_PKCS12_Attributes  (PKCS12_Attributes *);


/*
PKCS12-SafeBag ::= SEQUENCE {
  bagId             OBJECT IDENTIFIER,
  bagValue        [0] heim_any,
  bagAttributes   PKCS12-Attributes OPTIONAL,
}
*/

typedef struct PKCS12_SafeBag {
  heim_oid bagId;
  heim_any bagValue;
  PKCS12_Attributes *bagAttributes;
} PKCS12_SafeBag;

ASN1EXP int    ASN1CALL decode_PKCS12_SafeBag(const unsigned char *, size_t, PKCS12_SafeBag *, size_t *);
ASN1EXP int    ASN1CALL encode_PKCS12_SafeBag(unsigned char *, size_t, const PKCS12_SafeBag *, size_t *);
ASN1EXP size_t ASN1CALL length_PKCS12_SafeBag(const PKCS12_SafeBag *);
ASN1EXP int    ASN1CALL copy_PKCS12_SafeBag  (const PKCS12_SafeBag *, PKCS12_SafeBag *);
ASN1EXP void   ASN1CALL free_PKCS12_SafeBag  (PKCS12_SafeBag *);


/*
PKCS12-SafeContents ::= SEQUENCE OF PKCS12-SafeBag
*/

typedef struct PKCS12_SafeContents {
  unsigned int len;
  PKCS12_SafeBag *val;
} PKCS12_SafeContents;

ASN1EXP int    ASN1CALL decode_PKCS12_SafeContents(const unsigned char *, size_t, PKCS12_SafeContents *, size_t *);
ASN1EXP int    ASN1CALL encode_PKCS12_SafeContents(unsigned char *, size_t, const PKCS12_SafeContents *, size_t *);
ASN1EXP size_t ASN1CALL length_PKCS12_SafeContents(const PKCS12_SafeContents *);
ASN1EXP int    ASN1CALL copy_PKCS12_SafeContents  (const PKCS12_SafeContents *, PKCS12_SafeContents *);
ASN1EXP void   ASN1CALL free_PKCS12_SafeContents  (PKCS12_SafeContents *);


/*
PKCS12-CertBag ::= SEQUENCE {
  certType          OBJECT IDENTIFIER,
  certValue       [0] heim_any,
}
*/

typedef struct PKCS12_CertBag {
  heim_oid certType;
  heim_any certValue;
} PKCS12_CertBag;

ASN1EXP int    ASN1CALL decode_PKCS12_CertBag(const unsigned char *, size_t, PKCS12_CertBag *, size_t *);
ASN1EXP int    ASN1CALL encode_PKCS12_CertBag(unsigned char *, size_t, const PKCS12_CertBag *, size_t *);
ASN1EXP size_t ASN1CALL length_PKCS12_CertBag(const PKCS12_CertBag *);
ASN1EXP int    ASN1CALL copy_PKCS12_CertBag  (const PKCS12_CertBag *, PKCS12_CertBag *);
ASN1EXP void   ASN1CALL free_PKCS12_CertBag  (PKCS12_CertBag *);


/*
PKCS12-PBEParams ::= SEQUENCE {
  salt            OCTET STRING,
  iterations      INTEGER (0..-1) OPTIONAL,
}
*/

typedef struct PKCS12_PBEParams {
  heim_octet_string salt;
  unsigned int *iterations;
} PKCS12_PBEParams;

ASN1EXP int    ASN1CALL decode_PKCS12_PBEParams(const unsigned char *, size_t, PKCS12_PBEParams *, size_t *);
ASN1EXP int    ASN1CALL encode_PKCS12_PBEParams(unsigned char *, size_t, const PKCS12_PBEParams *, size_t *);
ASN1EXP size_t ASN1CALL length_PKCS12_PBEParams(const PKCS12_PBEParams *);
ASN1EXP int    ASN1CALL copy_PKCS12_PBEParams  (const PKCS12_PBEParams *, PKCS12_PBEParams *);
ASN1EXP void   ASN1CALL free_PKCS12_PBEParams  (PKCS12_PBEParams *);


/*
PKCS12-OctetString ::= OCTET STRING
*/

typedef heim_octet_string PKCS12_OctetString;

ASN1EXP int    ASN1CALL decode_PKCS12_OctetString(const unsigned char *, size_t, PKCS12_OctetString *, size_t *);
ASN1EXP int    ASN1CALL encode_PKCS12_OctetString(unsigned char *, size_t, const PKCS12_OctetString *, size_t *);
ASN1EXP size_t ASN1CALL length_PKCS12_OctetString(const PKCS12_OctetString *);
ASN1EXP int    ASN1CALL copy_PKCS12_OctetString  (const PKCS12_OctetString *, PKCS12_OctetString *);
ASN1EXP void   ASN1CALL free_PKCS12_OctetString  (PKCS12_OctetString *);


#endif /* __pkcs12_asn1_h__ */
