/* Generated from /usr/src/crypto/heimdal/lib/asn1/cms.asn1 */
/* Do not edit */

#ifndef __cms_asn1_h__
#define __cms_asn1_h__

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
/* OBJECT IDENTIFIER id-pkcs7 ::= { iso(1) member-body(2) us(840) rsadsi(113549) pkcs(1) pkcs7(7) } */
extern ASN1EXP const heim_oid asn1_oid_id_pkcs7;
#define ASN1_OID_ID_PKCS7 (&asn1_oid_id_pkcs7)

/* OBJECT IDENTIFIER id-pkcs7-data ::= { iso(1) member-body(2) us(840) rsadsi(113549) pkcs(1) pkcs7(7) label-less(1) } */
extern ASN1EXP const heim_oid asn1_oid_id_pkcs7_data;
#define ASN1_OID_ID_PKCS7_DATA (&asn1_oid_id_pkcs7_data)

/* OBJECT IDENTIFIER id-pkcs7-signedData ::= { iso(1) member-body(2) us(840) rsadsi(113549) pkcs(1) pkcs7(7) label-less(2) } */
extern ASN1EXP const heim_oid asn1_oid_id_pkcs7_signedData;
#define ASN1_OID_ID_PKCS7_SIGNEDDATA (&asn1_oid_id_pkcs7_signedData)

/* OBJECT IDENTIFIER id-pkcs7-envelopedData ::= { iso(1) member-body(2) us(840) rsadsi(113549) pkcs(1) pkcs7(7) label-less(3) } */
extern ASN1EXP const heim_oid asn1_oid_id_pkcs7_envelopedData;
#define ASN1_OID_ID_PKCS7_ENVELOPEDDATA (&asn1_oid_id_pkcs7_envelopedData)

/* OBJECT IDENTIFIER id-pkcs7-signedAndEnvelopedData ::= { iso(1) member-body(2) us(840) rsadsi(113549) pkcs(1) pkcs7(7) label-less(4) } */
extern ASN1EXP const heim_oid asn1_oid_id_pkcs7_signedAndEnvelopedData;
#define ASN1_OID_ID_PKCS7_SIGNEDANDENVELOPEDDATA (&asn1_oid_id_pkcs7_signedAndEnvelopedData)

/* OBJECT IDENTIFIER id-pkcs7-digestedData ::= { iso(1) member-body(2) us(840) rsadsi(113549) pkcs(1) pkcs7(7) label-less(5) } */
extern ASN1EXP const heim_oid asn1_oid_id_pkcs7_digestedData;
#define ASN1_OID_ID_PKCS7_DIGESTEDDATA (&asn1_oid_id_pkcs7_digestedData)

/* OBJECT IDENTIFIER id-pkcs7-encryptedData ::= { iso(1) member-body(2) us(840) rsadsi(113549) pkcs(1) pkcs7(7) label-less(6) } */
extern ASN1EXP const heim_oid asn1_oid_id_pkcs7_encryptedData;
#define ASN1_OID_ID_PKCS7_ENCRYPTEDDATA (&asn1_oid_id_pkcs7_encryptedData)

/*
CMSVersion ::= INTEGER {
  CMSVersion_v0(0),
  CMSVersion_v1(1),
  CMSVersion_v2(2),
  CMSVersion_v3(3),
  CMSVersion_v4(4)
}
*/

typedef enum CMSVersion {
  CMSVersion_v0 = 0,
  CMSVersion_v1 = 1,
  CMSVersion_v2 = 2,
  CMSVersion_v3 = 3,
  CMSVersion_v4 = 4
} CMSVersion;

ASN1EXP int    ASN1CALL decode_CMSVersion(const unsigned char *, size_t, CMSVersion *, size_t *);
ASN1EXP int    ASN1CALL encode_CMSVersion(unsigned char *, size_t, const CMSVersion *, size_t *);
ASN1EXP size_t ASN1CALL length_CMSVersion(const CMSVersion *);
ASN1EXP int    ASN1CALL copy_CMSVersion  (const CMSVersion *, CMSVersion *);
ASN1EXP void   ASN1CALL free_CMSVersion  (CMSVersion *);


/*
DigestAlgorithmIdentifier ::= AlgorithmIdentifier
*/

typedef AlgorithmIdentifier DigestAlgorithmIdentifier;

ASN1EXP int    ASN1CALL decode_DigestAlgorithmIdentifier(const unsigned char *, size_t, DigestAlgorithmIdentifier *, size_t *);
ASN1EXP int    ASN1CALL encode_DigestAlgorithmIdentifier(unsigned char *, size_t, const DigestAlgorithmIdentifier *, size_t *);
ASN1EXP size_t ASN1CALL length_DigestAlgorithmIdentifier(const DigestAlgorithmIdentifier *);
ASN1EXP int    ASN1CALL copy_DigestAlgorithmIdentifier  (const DigestAlgorithmIdentifier *, DigestAlgorithmIdentifier *);
ASN1EXP void   ASN1CALL free_DigestAlgorithmIdentifier  (DigestAlgorithmIdentifier *);


/*
DigestAlgorithmIdentifiers ::= SET OF DigestAlgorithmIdentifier
*/

typedef struct DigestAlgorithmIdentifiers {
  unsigned int len;
  DigestAlgorithmIdentifier *val;
} DigestAlgorithmIdentifiers;

ASN1EXP int   ASN1CALL add_DigestAlgorithmIdentifiers  (DigestAlgorithmIdentifiers *, const DigestAlgorithmIdentifier *);
ASN1EXP int   ASN1CALL remove_DigestAlgorithmIdentifiers  (DigestAlgorithmIdentifiers *, unsigned int);
ASN1EXP int    ASN1CALL decode_DigestAlgorithmIdentifiers(const unsigned char *, size_t, DigestAlgorithmIdentifiers *, size_t *);
ASN1EXP int    ASN1CALL encode_DigestAlgorithmIdentifiers(unsigned char *, size_t, const DigestAlgorithmIdentifiers *, size_t *);
ASN1EXP size_t ASN1CALL length_DigestAlgorithmIdentifiers(const DigestAlgorithmIdentifiers *);
ASN1EXP int    ASN1CALL copy_DigestAlgorithmIdentifiers  (const DigestAlgorithmIdentifiers *, DigestAlgorithmIdentifiers *);
ASN1EXP void   ASN1CALL free_DigestAlgorithmIdentifiers  (DigestAlgorithmIdentifiers *);


/*
SignatureAlgorithmIdentifier ::= AlgorithmIdentifier
*/

typedef AlgorithmIdentifier SignatureAlgorithmIdentifier;

ASN1EXP int    ASN1CALL decode_SignatureAlgorithmIdentifier(const unsigned char *, size_t, SignatureAlgorithmIdentifier *, size_t *);
ASN1EXP int    ASN1CALL encode_SignatureAlgorithmIdentifier(unsigned char *, size_t, const SignatureAlgorithmIdentifier *, size_t *);
ASN1EXP size_t ASN1CALL length_SignatureAlgorithmIdentifier(const SignatureAlgorithmIdentifier *);
ASN1EXP int    ASN1CALL copy_SignatureAlgorithmIdentifier  (const SignatureAlgorithmIdentifier *, SignatureAlgorithmIdentifier *);
ASN1EXP void   ASN1CALL free_SignatureAlgorithmIdentifier  (SignatureAlgorithmIdentifier *);


/*
ContentType ::= OBJECT IDENTIFIER
*/

typedef heim_oid ContentType;

ASN1EXP int    ASN1CALL decode_ContentType(const unsigned char *, size_t, ContentType *, size_t *);
ASN1EXP int    ASN1CALL encode_ContentType(unsigned char *, size_t, const ContentType *, size_t *);
ASN1EXP size_t ASN1CALL length_ContentType(const ContentType *);
ASN1EXP int    ASN1CALL copy_ContentType  (const ContentType *, ContentType *);
ASN1EXP void   ASN1CALL free_ContentType  (ContentType *);


/*
MessageDigest ::= OCTET STRING
*/

typedef heim_octet_string MessageDigest;

ASN1EXP int    ASN1CALL decode_MessageDigest(const unsigned char *, size_t, MessageDigest *, size_t *);
ASN1EXP int    ASN1CALL encode_MessageDigest(unsigned char *, size_t, const MessageDigest *, size_t *);
ASN1EXP size_t ASN1CALL length_MessageDigest(const MessageDigest *);
ASN1EXP int    ASN1CALL copy_MessageDigest  (const MessageDigest *, MessageDigest *);
ASN1EXP void   ASN1CALL free_MessageDigest  (MessageDigest *);


/*
ContentInfo ::= SEQUENCE {
  contentType     ContentType,
  content         [0] heim_any OPTIONAL,
}
*/

typedef struct ContentInfo {
  ContentType contentType;
  heim_any *content;
} ContentInfo;

ASN1EXP int    ASN1CALL decode_ContentInfo(const unsigned char *, size_t, ContentInfo *, size_t *);
ASN1EXP int    ASN1CALL encode_ContentInfo(unsigned char *, size_t, const ContentInfo *, size_t *);
ASN1EXP size_t ASN1CALL length_ContentInfo(const ContentInfo *);
ASN1EXP int    ASN1CALL copy_ContentInfo  (const ContentInfo *, ContentInfo *);
ASN1EXP void   ASN1CALL free_ContentInfo  (ContentInfo *);


/*
EncapsulatedContentInfo ::= SEQUENCE {
  eContentType    ContentType,
  eContent        [0] OCTET STRING OPTIONAL,
}
*/

typedef struct EncapsulatedContentInfo {
  ContentType eContentType;
  heim_octet_string *eContent;
} EncapsulatedContentInfo;

ASN1EXP int    ASN1CALL decode_EncapsulatedContentInfo(const unsigned char *, size_t, EncapsulatedContentInfo *, size_t *);
ASN1EXP int    ASN1CALL encode_EncapsulatedContentInfo(unsigned char *, size_t, const EncapsulatedContentInfo *, size_t *);
ASN1EXP size_t ASN1CALL length_EncapsulatedContentInfo(const EncapsulatedContentInfo *);
ASN1EXP int    ASN1CALL copy_EncapsulatedContentInfo  (const EncapsulatedContentInfo *, EncapsulatedContentInfo *);
ASN1EXP void   ASN1CALL free_EncapsulatedContentInfo  (EncapsulatedContentInfo *);


/*
CertificateSet ::= SET OF heim_any
*/

typedef struct CertificateSet {
  unsigned int len;
  heim_any *val;
} CertificateSet;

ASN1EXP int    ASN1CALL decode_CertificateSet(const unsigned char *, size_t, CertificateSet *, size_t *);
ASN1EXP int    ASN1CALL encode_CertificateSet(unsigned char *, size_t, const CertificateSet *, size_t *);
ASN1EXP size_t ASN1CALL length_CertificateSet(const CertificateSet *);
ASN1EXP int    ASN1CALL copy_CertificateSet  (const CertificateSet *, CertificateSet *);
ASN1EXP void   ASN1CALL free_CertificateSet  (CertificateSet *);


/*
CertificateList ::= Certificate
*/

typedef Certificate CertificateList;

ASN1EXP int    ASN1CALL decode_CertificateList(const unsigned char *, size_t, CertificateList *, size_t *);
ASN1EXP int    ASN1CALL encode_CertificateList(unsigned char *, size_t, const CertificateList *, size_t *);
ASN1EXP size_t ASN1CALL length_CertificateList(const CertificateList *);
ASN1EXP int    ASN1CALL copy_CertificateList  (const CertificateList *, CertificateList *);
ASN1EXP void   ASN1CALL free_CertificateList  (CertificateList *);


/*
CertificateRevocationLists ::= SET OF CertificateList
*/

typedef struct CertificateRevocationLists {
  unsigned int len;
  CertificateList *val;
} CertificateRevocationLists;

ASN1EXP int    ASN1CALL decode_CertificateRevocationLists(const unsigned char *, size_t, CertificateRevocationLists *, size_t *);
ASN1EXP int    ASN1CALL encode_CertificateRevocationLists(unsigned char *, size_t, const CertificateRevocationLists *, size_t *);
ASN1EXP size_t ASN1CALL length_CertificateRevocationLists(const CertificateRevocationLists *);
ASN1EXP int    ASN1CALL copy_CertificateRevocationLists  (const CertificateRevocationLists *, CertificateRevocationLists *);
ASN1EXP void   ASN1CALL free_CertificateRevocationLists  (CertificateRevocationLists *);


/*
IssuerAndSerialNumber ::= SEQUENCE {
  issuer          Name,
  serialNumber    CertificateSerialNumber,
}
*/

typedef struct IssuerAndSerialNumber {
  Name issuer;
  CertificateSerialNumber serialNumber;
} IssuerAndSerialNumber;

ASN1EXP int    ASN1CALL decode_IssuerAndSerialNumber(const unsigned char *, size_t, IssuerAndSerialNumber *, size_t *);
ASN1EXP int    ASN1CALL encode_IssuerAndSerialNumber(unsigned char *, size_t, const IssuerAndSerialNumber *, size_t *);
ASN1EXP size_t ASN1CALL length_IssuerAndSerialNumber(const IssuerAndSerialNumber *);
ASN1EXP int    ASN1CALL copy_IssuerAndSerialNumber  (const IssuerAndSerialNumber *, IssuerAndSerialNumber *);
ASN1EXP void   ASN1CALL free_IssuerAndSerialNumber  (IssuerAndSerialNumber *);


/*
CMSIdentifier ::= CHOICE {
  issuerAndSerialNumber   IssuerAndSerialNumber,
  subjectKeyIdentifier    [0] SubjectKeyIdentifier,
}
*/

typedef struct CMSIdentifier {
  enum {
    choice_CMSIdentifier_issuerAndSerialNumber = 1,
    choice_CMSIdentifier_subjectKeyIdentifier
  } element;
  union {
    IssuerAndSerialNumber issuerAndSerialNumber;
    SubjectKeyIdentifier subjectKeyIdentifier;
  } u;
} CMSIdentifier;

ASN1EXP int    ASN1CALL decode_CMSIdentifier(const unsigned char *, size_t, CMSIdentifier *, size_t *);
ASN1EXP int    ASN1CALL encode_CMSIdentifier(unsigned char *, size_t, const CMSIdentifier *, size_t *);
ASN1EXP size_t ASN1CALL length_CMSIdentifier(const CMSIdentifier *);
ASN1EXP int    ASN1CALL copy_CMSIdentifier  (const CMSIdentifier *, CMSIdentifier *);
ASN1EXP void   ASN1CALL free_CMSIdentifier  (CMSIdentifier *);


/*
SignerIdentifier ::= CMSIdentifier
*/

typedef CMSIdentifier SignerIdentifier;

ASN1EXP int    ASN1CALL decode_SignerIdentifier(const unsigned char *, size_t, SignerIdentifier *, size_t *);
ASN1EXP int    ASN1CALL encode_SignerIdentifier(unsigned char *, size_t, const SignerIdentifier *, size_t *);
ASN1EXP size_t ASN1CALL length_SignerIdentifier(const SignerIdentifier *);
ASN1EXP int    ASN1CALL copy_SignerIdentifier  (const SignerIdentifier *, SignerIdentifier *);
ASN1EXP void   ASN1CALL free_SignerIdentifier  (SignerIdentifier *);


/*
RecipientIdentifier ::= CMSIdentifier
*/

typedef CMSIdentifier RecipientIdentifier;

ASN1EXP int    ASN1CALL decode_RecipientIdentifier(const unsigned char *, size_t, RecipientIdentifier *, size_t *);
ASN1EXP int    ASN1CALL encode_RecipientIdentifier(unsigned char *, size_t, const RecipientIdentifier *, size_t *);
ASN1EXP size_t ASN1CALL length_RecipientIdentifier(const RecipientIdentifier *);
ASN1EXP int    ASN1CALL copy_RecipientIdentifier  (const RecipientIdentifier *, RecipientIdentifier *);
ASN1EXP void   ASN1CALL free_RecipientIdentifier  (RecipientIdentifier *);


/*
CMSAttributes ::= SET OF Attribute
*/

typedef struct CMSAttributes {
  unsigned int len;
  Attribute *val;
} CMSAttributes;

ASN1EXP int    ASN1CALL decode_CMSAttributes(const unsigned char *, size_t, CMSAttributes *, size_t *);
ASN1EXP int    ASN1CALL encode_CMSAttributes(unsigned char *, size_t, const CMSAttributes *, size_t *);
ASN1EXP size_t ASN1CALL length_CMSAttributes(const CMSAttributes *);
ASN1EXP int    ASN1CALL copy_CMSAttributes  (const CMSAttributes *, CMSAttributes *);
ASN1EXP void   ASN1CALL free_CMSAttributes  (CMSAttributes *);


/*
SignatureValue ::= OCTET STRING
*/

typedef heim_octet_string SignatureValue;

ASN1EXP int    ASN1CALL decode_SignatureValue(const unsigned char *, size_t, SignatureValue *, size_t *);
ASN1EXP int    ASN1CALL encode_SignatureValue(unsigned char *, size_t, const SignatureValue *, size_t *);
ASN1EXP size_t ASN1CALL length_SignatureValue(const SignatureValue *);
ASN1EXP int    ASN1CALL copy_SignatureValue  (const SignatureValue *, SignatureValue *);
ASN1EXP void   ASN1CALL free_SignatureValue  (SignatureValue *);


/*
SignerInfo ::= SEQUENCE {
  version              CMSVersion,
  sid                  SignerIdentifier,
  digestAlgorithm      DigestAlgorithmIdentifier,
  signedAttrs          [0] IMPLICIT SET OF Attribute OPTIONAL,
  signatureAlgorithm   SignatureAlgorithmIdentifier,
  signature            SignatureValue,
  unsignedAttrs        [1] IMPLICIT SET OF Attribute OPTIONAL,
}
*/

typedef struct SignerInfo {
  CMSVersion version;
  SignerIdentifier sid;
  DigestAlgorithmIdentifier digestAlgorithm;
  struct SignerInfo_signedAttrs {
    unsigned int len;
    Attribute *val;
  } *signedAttrs;
  SignatureAlgorithmIdentifier signatureAlgorithm;
  SignatureValue signature;
  struct SignerInfo_unsignedAttrs {
    unsigned int len;
    Attribute *val;
  } *unsignedAttrs;
} SignerInfo;

ASN1EXP int    ASN1CALL decode_SignerInfo(const unsigned char *, size_t, SignerInfo *, size_t *);
ASN1EXP int    ASN1CALL encode_SignerInfo(unsigned char *, size_t, const SignerInfo *, size_t *);
ASN1EXP size_t ASN1CALL length_SignerInfo(const SignerInfo *);
ASN1EXP int    ASN1CALL copy_SignerInfo  (const SignerInfo *, SignerInfo *);
ASN1EXP void   ASN1CALL free_SignerInfo  (SignerInfo *);


/*
SignerInfos ::= SET OF SignerInfo
*/

typedef struct SignerInfos {
  unsigned int len;
  SignerInfo *val;
} SignerInfos;

ASN1EXP int    ASN1CALL decode_SignerInfos(const unsigned char *, size_t, SignerInfos *, size_t *);
ASN1EXP int    ASN1CALL encode_SignerInfos(unsigned char *, size_t, const SignerInfos *, size_t *);
ASN1EXP size_t ASN1CALL length_SignerInfos(const SignerInfos *);
ASN1EXP int    ASN1CALL copy_SignerInfos  (const SignerInfos *, SignerInfos *);
ASN1EXP void   ASN1CALL free_SignerInfos  (SignerInfos *);


/*
SignedData ::= SEQUENCE {
  version            CMSVersion,
  digestAlgorithms   DigestAlgorithmIdentifiers,
  encapContentInfo   EncapsulatedContentInfo,
  certificates       [0] IMPLICIT SET OF heim_any OPTIONAL,
  crls               [1] IMPLICIT heim_any OPTIONAL,
  signerInfos        SignerInfos,
}
*/

typedef struct SignedData {
  CMSVersion version;
  DigestAlgorithmIdentifiers digestAlgorithms;
  EncapsulatedContentInfo encapContentInfo;
  struct SignedData_certificates {
    unsigned int len;
    heim_any *val;
  } *certificates;
  heim_any *crls;
  SignerInfos signerInfos;
} SignedData;

ASN1EXP int    ASN1CALL decode_SignedData(const unsigned char *, size_t, SignedData *, size_t *);
ASN1EXP int    ASN1CALL encode_SignedData(unsigned char *, size_t, const SignedData *, size_t *);
ASN1EXP size_t ASN1CALL length_SignedData(const SignedData *);
ASN1EXP int    ASN1CALL copy_SignedData  (const SignedData *, SignedData *);
ASN1EXP void   ASN1CALL free_SignedData  (SignedData *);


/*
OriginatorInfo ::= SEQUENCE {
  certs           [0] IMPLICIT SET OF heim_any OPTIONAL,
  crls            [1] IMPLICIT heim_any OPTIONAL,
}
*/

typedef struct OriginatorInfo {
  struct OriginatorInfo_certs {
    unsigned int len;
    heim_any *val;
  } *certs;
  heim_any *crls;
} OriginatorInfo;

ASN1EXP int    ASN1CALL decode_OriginatorInfo(const unsigned char *, size_t, OriginatorInfo *, size_t *);
ASN1EXP int    ASN1CALL encode_OriginatorInfo(unsigned char *, size_t, const OriginatorInfo *, size_t *);
ASN1EXP size_t ASN1CALL length_OriginatorInfo(const OriginatorInfo *);
ASN1EXP int    ASN1CALL copy_OriginatorInfo  (const OriginatorInfo *, OriginatorInfo *);
ASN1EXP void   ASN1CALL free_OriginatorInfo  (OriginatorInfo *);


/*
KeyEncryptionAlgorithmIdentifier ::= AlgorithmIdentifier
*/

typedef AlgorithmIdentifier KeyEncryptionAlgorithmIdentifier;

ASN1EXP int    ASN1CALL decode_KeyEncryptionAlgorithmIdentifier(const unsigned char *, size_t, KeyEncryptionAlgorithmIdentifier *, size_t *);
ASN1EXP int    ASN1CALL encode_KeyEncryptionAlgorithmIdentifier(unsigned char *, size_t, const KeyEncryptionAlgorithmIdentifier *, size_t *);
ASN1EXP size_t ASN1CALL length_KeyEncryptionAlgorithmIdentifier(const KeyEncryptionAlgorithmIdentifier *);
ASN1EXP int    ASN1CALL copy_KeyEncryptionAlgorithmIdentifier  (const KeyEncryptionAlgorithmIdentifier *, KeyEncryptionAlgorithmIdentifier *);
ASN1EXP void   ASN1CALL free_KeyEncryptionAlgorithmIdentifier  (KeyEncryptionAlgorithmIdentifier *);


/*
ContentEncryptionAlgorithmIdentifier ::= AlgorithmIdentifier
*/

typedef AlgorithmIdentifier ContentEncryptionAlgorithmIdentifier;

ASN1EXP int    ASN1CALL decode_ContentEncryptionAlgorithmIdentifier(const unsigned char *, size_t, ContentEncryptionAlgorithmIdentifier *, size_t *);
ASN1EXP int    ASN1CALL encode_ContentEncryptionAlgorithmIdentifier(unsigned char *, size_t, const ContentEncryptionAlgorithmIdentifier *, size_t *);
ASN1EXP size_t ASN1CALL length_ContentEncryptionAlgorithmIdentifier(const ContentEncryptionAlgorithmIdentifier *);
ASN1EXP int    ASN1CALL copy_ContentEncryptionAlgorithmIdentifier  (const ContentEncryptionAlgorithmIdentifier *, ContentEncryptionAlgorithmIdentifier *);
ASN1EXP void   ASN1CALL free_ContentEncryptionAlgorithmIdentifier  (ContentEncryptionAlgorithmIdentifier *);


/*
EncryptedKey ::= OCTET STRING
*/

typedef heim_octet_string EncryptedKey;

ASN1EXP int    ASN1CALL decode_EncryptedKey(const unsigned char *, size_t, EncryptedKey *, size_t *);
ASN1EXP int    ASN1CALL encode_EncryptedKey(unsigned char *, size_t, const EncryptedKey *, size_t *);
ASN1EXP size_t ASN1CALL length_EncryptedKey(const EncryptedKey *);
ASN1EXP int    ASN1CALL copy_EncryptedKey  (const EncryptedKey *, EncryptedKey *);
ASN1EXP void   ASN1CALL free_EncryptedKey  (EncryptedKey *);


/*
KeyTransRecipientInfo ::= SEQUENCE {
  version                  CMSVersion,
  rid                      RecipientIdentifier,
  keyEncryptionAlgorithm   KeyEncryptionAlgorithmIdentifier,
  encryptedKey             EncryptedKey,
}
*/

typedef struct KeyTransRecipientInfo {
  CMSVersion version;
  RecipientIdentifier rid;
  KeyEncryptionAlgorithmIdentifier keyEncryptionAlgorithm;
  EncryptedKey encryptedKey;
} KeyTransRecipientInfo;

ASN1EXP int    ASN1CALL decode_KeyTransRecipientInfo(const unsigned char *, size_t, KeyTransRecipientInfo *, size_t *);
ASN1EXP int    ASN1CALL encode_KeyTransRecipientInfo(unsigned char *, size_t, const KeyTransRecipientInfo *, size_t *);
ASN1EXP size_t ASN1CALL length_KeyTransRecipientInfo(const KeyTransRecipientInfo *);
ASN1EXP int    ASN1CALL copy_KeyTransRecipientInfo  (const KeyTransRecipientInfo *, KeyTransRecipientInfo *);
ASN1EXP void   ASN1CALL free_KeyTransRecipientInfo  (KeyTransRecipientInfo *);


/*
RecipientInfo ::= KeyTransRecipientInfo
*/

typedef KeyTransRecipientInfo RecipientInfo;

ASN1EXP int    ASN1CALL decode_RecipientInfo(const unsigned char *, size_t, RecipientInfo *, size_t *);
ASN1EXP int    ASN1CALL encode_RecipientInfo(unsigned char *, size_t, const RecipientInfo *, size_t *);
ASN1EXP size_t ASN1CALL length_RecipientInfo(const RecipientInfo *);
ASN1EXP int    ASN1CALL copy_RecipientInfo  (const RecipientInfo *, RecipientInfo *);
ASN1EXP void   ASN1CALL free_RecipientInfo  (RecipientInfo *);


/*
RecipientInfos ::= SET OF RecipientInfo
*/

typedef struct RecipientInfos {
  unsigned int len;
  RecipientInfo *val;
} RecipientInfos;

ASN1EXP int    ASN1CALL decode_RecipientInfos(const unsigned char *, size_t, RecipientInfos *, size_t *);
ASN1EXP int    ASN1CALL encode_RecipientInfos(unsigned char *, size_t, const RecipientInfos *, size_t *);
ASN1EXP size_t ASN1CALL length_RecipientInfos(const RecipientInfos *);
ASN1EXP int    ASN1CALL copy_RecipientInfos  (const RecipientInfos *, RecipientInfos *);
ASN1EXP void   ASN1CALL free_RecipientInfos  (RecipientInfos *);


/*
EncryptedContent ::= OCTET STRING
*/

typedef heim_octet_string EncryptedContent;

ASN1EXP int    ASN1CALL decode_EncryptedContent(const unsigned char *, size_t, EncryptedContent *, size_t *);
ASN1EXP int    ASN1CALL encode_EncryptedContent(unsigned char *, size_t, const EncryptedContent *, size_t *);
ASN1EXP size_t ASN1CALL length_EncryptedContent(const EncryptedContent *);
ASN1EXP int    ASN1CALL copy_EncryptedContent  (const EncryptedContent *, EncryptedContent *);
ASN1EXP void   ASN1CALL free_EncryptedContent  (EncryptedContent *);


/*
EncryptedContentInfo ::= SEQUENCE {
  contentType                  ContentType,
  contentEncryptionAlgorithm   ContentEncryptionAlgorithmIdentifier,
  encryptedContent             [0] IMPLICIT OCTET STRING OPTIONAL,
}
*/

typedef struct EncryptedContentInfo {
  ContentType contentType;
  ContentEncryptionAlgorithmIdentifier contentEncryptionAlgorithm;
  heim_octet_string *encryptedContent;
} EncryptedContentInfo;

ASN1EXP int    ASN1CALL decode_EncryptedContentInfo(const unsigned char *, size_t, EncryptedContentInfo *, size_t *);
ASN1EXP int    ASN1CALL encode_EncryptedContentInfo(unsigned char *, size_t, const EncryptedContentInfo *, size_t *);
ASN1EXP size_t ASN1CALL length_EncryptedContentInfo(const EncryptedContentInfo *);
ASN1EXP int    ASN1CALL copy_EncryptedContentInfo  (const EncryptedContentInfo *, EncryptedContentInfo *);
ASN1EXP void   ASN1CALL free_EncryptedContentInfo  (EncryptedContentInfo *);


/*
UnprotectedAttributes ::= SET OF Attribute
*/

typedef struct UnprotectedAttributes {
  unsigned int len;
  Attribute *val;
} UnprotectedAttributes;

ASN1EXP int    ASN1CALL decode_UnprotectedAttributes(const unsigned char *, size_t, UnprotectedAttributes *, size_t *);
ASN1EXP int    ASN1CALL encode_UnprotectedAttributes(unsigned char *, size_t, const UnprotectedAttributes *, size_t *);
ASN1EXP size_t ASN1CALL length_UnprotectedAttributes(const UnprotectedAttributes *);
ASN1EXP int    ASN1CALL copy_UnprotectedAttributes  (const UnprotectedAttributes *, UnprotectedAttributes *);
ASN1EXP void   ASN1CALL free_UnprotectedAttributes  (UnprotectedAttributes *);


/*
CMSEncryptedData ::= SEQUENCE {
  version                CMSVersion,
  encryptedContentInfo   EncryptedContentInfo,
  unprotectedAttrs       [1] IMPLICIT heim_any OPTIONAL,
}
*/

typedef struct CMSEncryptedData {
  CMSVersion version;
  EncryptedContentInfo encryptedContentInfo;
  heim_any *unprotectedAttrs;
} CMSEncryptedData;

ASN1EXP int    ASN1CALL decode_CMSEncryptedData(const unsigned char *, size_t, CMSEncryptedData *, size_t *);
ASN1EXP int    ASN1CALL encode_CMSEncryptedData(unsigned char *, size_t, const CMSEncryptedData *, size_t *);
ASN1EXP size_t ASN1CALL length_CMSEncryptedData(const CMSEncryptedData *);
ASN1EXP int    ASN1CALL copy_CMSEncryptedData  (const CMSEncryptedData *, CMSEncryptedData *);
ASN1EXP void   ASN1CALL free_CMSEncryptedData  (CMSEncryptedData *);


/*
EnvelopedData ::= SEQUENCE {
  version                CMSVersion,
  originatorInfo         [0] IMPLICIT heim_any OPTIONAL,
  recipientInfos         RecipientInfos,
  encryptedContentInfo   EncryptedContentInfo,
  unprotectedAttrs       [1] IMPLICIT heim_any OPTIONAL,
}
*/

typedef struct EnvelopedData {
  CMSVersion version;
  heim_any *originatorInfo;
  RecipientInfos recipientInfos;
  EncryptedContentInfo encryptedContentInfo;
  heim_any *unprotectedAttrs;
} EnvelopedData;

ASN1EXP int    ASN1CALL decode_EnvelopedData(const unsigned char *, size_t, EnvelopedData *, size_t *);
ASN1EXP int    ASN1CALL encode_EnvelopedData(unsigned char *, size_t, const EnvelopedData *, size_t *);
ASN1EXP size_t ASN1CALL length_EnvelopedData(const EnvelopedData *);
ASN1EXP int    ASN1CALL copy_EnvelopedData  (const EnvelopedData *, EnvelopedData *);
ASN1EXP void   ASN1CALL free_EnvelopedData  (EnvelopedData *);


/*
CMSRC2CBCParameter ::= SEQUENCE {
  rc2ParameterVersion   INTEGER (0..-1),
  iv                    OCTET STRING,
}
*/

typedef struct CMSRC2CBCParameter {
  unsigned int rc2ParameterVersion;
  heim_octet_string iv;
} CMSRC2CBCParameter;

ASN1EXP int    ASN1CALL decode_CMSRC2CBCParameter(const unsigned char *, size_t, CMSRC2CBCParameter *, size_t *);
ASN1EXP int    ASN1CALL encode_CMSRC2CBCParameter(unsigned char *, size_t, const CMSRC2CBCParameter *, size_t *);
ASN1EXP size_t ASN1CALL length_CMSRC2CBCParameter(const CMSRC2CBCParameter *);
ASN1EXP int    ASN1CALL copy_CMSRC2CBCParameter  (const CMSRC2CBCParameter *, CMSRC2CBCParameter *);
ASN1EXP void   ASN1CALL free_CMSRC2CBCParameter  (CMSRC2CBCParameter *);


/*
CMSCBCParameter ::= OCTET STRING
*/

typedef heim_octet_string CMSCBCParameter;

ASN1EXP int    ASN1CALL decode_CMSCBCParameter(const unsigned char *, size_t, CMSCBCParameter *, size_t *);
ASN1EXP int    ASN1CALL encode_CMSCBCParameter(unsigned char *, size_t, const CMSCBCParameter *, size_t *);
ASN1EXP size_t ASN1CALL length_CMSCBCParameter(const CMSCBCParameter *);
ASN1EXP int    ASN1CALL copy_CMSCBCParameter  (const CMSCBCParameter *, CMSCBCParameter *);
ASN1EXP void   ASN1CALL free_CMSCBCParameter  (CMSCBCParameter *);


#endif /* __cms_asn1_h__ */
