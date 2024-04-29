/* Generated from /usr/src/crypto/heimdal/lib/asn1/rfc2459.asn1 */
/* Do not edit */

#ifndef __rfc2459_asn1_h__
#define __rfc2459_asn1_h__

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

#include <heim_asn1.h>
/*
Version ::= INTEGER {
  rfc3280_version_1(0),
  rfc3280_version_2(1),
  rfc3280_version_3(2)
}
*/

typedef enum Version {
  rfc3280_version_1 = 0,
  rfc3280_version_2 = 1,
  rfc3280_version_3 = 2
} Version;

ASN1EXP int    ASN1CALL decode_Version(const unsigned char *, size_t, Version *, size_t *);
ASN1EXP int    ASN1CALL encode_Version(unsigned char *, size_t, const Version *, size_t *);
ASN1EXP size_t ASN1CALL length_Version(const Version *);
ASN1EXP int    ASN1CALL copy_Version  (const Version *, Version *);
ASN1EXP void   ASN1CALL free_Version  (Version *);


/* OBJECT IDENTIFIER id-pkcs-1 ::= { iso(1) member-body(2) us(840) rsadsi(113549) pkcs(1) label-less(1) } */
extern ASN1EXP const heim_oid asn1_oid_id_pkcs_1;
#define ASN1_OID_ID_PKCS_1 (&asn1_oid_id_pkcs_1)

/* OBJECT IDENTIFIER id-pkcs1-rsaEncryption ::= { iso(1) member-body(2) us(840) rsadsi(113549) pkcs(1) label-less(1) label-less(1) } */
extern ASN1EXP const heim_oid asn1_oid_id_pkcs1_rsaEncryption;
#define ASN1_OID_ID_PKCS1_RSAENCRYPTION (&asn1_oid_id_pkcs1_rsaEncryption)

/* OBJECT IDENTIFIER id-pkcs1-md2WithRSAEncryption ::= { iso(1) member-body(2) us(840) rsadsi(113549) pkcs(1) label-less(1) label-less(2) } */
extern ASN1EXP const heim_oid asn1_oid_id_pkcs1_md2WithRSAEncryption;
#define ASN1_OID_ID_PKCS1_MD2WITHRSAENCRYPTION (&asn1_oid_id_pkcs1_md2WithRSAEncryption)

/* OBJECT IDENTIFIER id-pkcs1-md5WithRSAEncryption ::= { iso(1) member-body(2) us(840) rsadsi(113549) pkcs(1) label-less(1) label-less(4) } */
extern ASN1EXP const heim_oid asn1_oid_id_pkcs1_md5WithRSAEncryption;
#define ASN1_OID_ID_PKCS1_MD5WITHRSAENCRYPTION (&asn1_oid_id_pkcs1_md5WithRSAEncryption)

/* OBJECT IDENTIFIER id-pkcs1-sha1WithRSAEncryption ::= { iso(1) member-body(2) us(840) rsadsi(113549) pkcs(1) label-less(1) label-less(5) } */
extern ASN1EXP const heim_oid asn1_oid_id_pkcs1_sha1WithRSAEncryption;
#define ASN1_OID_ID_PKCS1_SHA1WITHRSAENCRYPTION (&asn1_oid_id_pkcs1_sha1WithRSAEncryption)

/* OBJECT IDENTIFIER id-pkcs1-sha256WithRSAEncryption ::= { iso(1) member-body(2) us(840) rsadsi(113549) pkcs(1) label-less(1) label-less(11) } */
extern ASN1EXP const heim_oid asn1_oid_id_pkcs1_sha256WithRSAEncryption;
#define ASN1_OID_ID_PKCS1_SHA256WITHRSAENCRYPTION (&asn1_oid_id_pkcs1_sha256WithRSAEncryption)

/* OBJECT IDENTIFIER id-pkcs1-sha384WithRSAEncryption ::= { iso(1) member-body(2) us(840) rsadsi(113549) pkcs(1) label-less(1) label-less(12) } */
extern ASN1EXP const heim_oid asn1_oid_id_pkcs1_sha384WithRSAEncryption;
#define ASN1_OID_ID_PKCS1_SHA384WITHRSAENCRYPTION (&asn1_oid_id_pkcs1_sha384WithRSAEncryption)

/* OBJECT IDENTIFIER id-pkcs1-sha512WithRSAEncryption ::= { iso(1) member-body(2) us(840) rsadsi(113549) pkcs(1) label-less(1) label-less(13) } */
extern ASN1EXP const heim_oid asn1_oid_id_pkcs1_sha512WithRSAEncryption;
#define ASN1_OID_ID_PKCS1_SHA512WITHRSAENCRYPTION (&asn1_oid_id_pkcs1_sha512WithRSAEncryption)

/* OBJECT IDENTIFIER id-heim-rsa-pkcs1-x509 ::= { label-less(1) label-less(2) label-less(752) label-less(43) label-less(16) label-less(1) } */
extern ASN1EXP const heim_oid asn1_oid_id_heim_rsa_pkcs1_x509;
#define ASN1_OID_ID_HEIM_RSA_PKCS1_X509 (&asn1_oid_id_heim_rsa_pkcs1_x509)

/* OBJECT IDENTIFIER id-pkcs-2 ::= { iso(1) member-body(2) us(840) rsadsi(113549) pkcs(1) label-less(2) } */
extern ASN1EXP const heim_oid asn1_oid_id_pkcs_2;
#define ASN1_OID_ID_PKCS_2 (&asn1_oid_id_pkcs_2)

/* OBJECT IDENTIFIER id-pkcs2-md2 ::= { iso(1) member-body(2) us(840) rsadsi(113549) pkcs(1) label-less(2) label-less(2) } */
extern ASN1EXP const heim_oid asn1_oid_id_pkcs2_md2;
#define ASN1_OID_ID_PKCS2_MD2 (&asn1_oid_id_pkcs2_md2)

/* OBJECT IDENTIFIER id-pkcs2-md4 ::= { iso(1) member-body(2) us(840) rsadsi(113549) pkcs(1) label-less(2) label-less(4) } */
extern ASN1EXP const heim_oid asn1_oid_id_pkcs2_md4;
#define ASN1_OID_ID_PKCS2_MD4 (&asn1_oid_id_pkcs2_md4)

/* OBJECT IDENTIFIER id-pkcs2-md5 ::= { iso(1) member-body(2) us(840) rsadsi(113549) pkcs(1) label-less(2) label-less(5) } */
extern ASN1EXP const heim_oid asn1_oid_id_pkcs2_md5;
#define ASN1_OID_ID_PKCS2_MD5 (&asn1_oid_id_pkcs2_md5)

/* OBJECT IDENTIFIER id-rsa-digestAlgorithm ::= { iso(1) member-body(2) us(840) rsadsi(113549) label-less(2) } */
extern ASN1EXP const heim_oid asn1_oid_id_rsa_digestAlgorithm;
#define ASN1_OID_ID_RSA_DIGESTALGORITHM (&asn1_oid_id_rsa_digestAlgorithm)

/* OBJECT IDENTIFIER id-rsa-digest-md2 ::= { iso(1) member-body(2) us(840) rsadsi(113549) label-less(2) label-less(2) } */
extern ASN1EXP const heim_oid asn1_oid_id_rsa_digest_md2;
#define ASN1_OID_ID_RSA_DIGEST_MD2 (&asn1_oid_id_rsa_digest_md2)

/* OBJECT IDENTIFIER id-rsa-digest-md4 ::= { iso(1) member-body(2) us(840) rsadsi(113549) label-less(2) label-less(4) } */
extern ASN1EXP const heim_oid asn1_oid_id_rsa_digest_md4;
#define ASN1_OID_ID_RSA_DIGEST_MD4 (&asn1_oid_id_rsa_digest_md4)

/* OBJECT IDENTIFIER id-rsa-digest-md5 ::= { iso(1) member-body(2) us(840) rsadsi(113549) label-less(2) label-less(5) } */
extern ASN1EXP const heim_oid asn1_oid_id_rsa_digest_md5;
#define ASN1_OID_ID_RSA_DIGEST_MD5 (&asn1_oid_id_rsa_digest_md5)

/* OBJECT IDENTIFIER id-pkcs-3 ::= { iso(1) member-body(2) us(840) rsadsi(113549) pkcs(1) label-less(3) } */
extern ASN1EXP const heim_oid asn1_oid_id_pkcs_3;
#define ASN1_OID_ID_PKCS_3 (&asn1_oid_id_pkcs_3)

/* OBJECT IDENTIFIER id-pkcs3-rc2-cbc ::= { iso(1) member-body(2) us(840) rsadsi(113549) pkcs(1) label-less(3) label-less(2) } */
extern ASN1EXP const heim_oid asn1_oid_id_pkcs3_rc2_cbc;
#define ASN1_OID_ID_PKCS3_RC2_CBC (&asn1_oid_id_pkcs3_rc2_cbc)

/* OBJECT IDENTIFIER id-pkcs3-rc4 ::= { iso(1) member-body(2) us(840) rsadsi(113549) pkcs(1) label-less(3) label-less(4) } */
extern ASN1EXP const heim_oid asn1_oid_id_pkcs3_rc4;
#define ASN1_OID_ID_PKCS3_RC4 (&asn1_oid_id_pkcs3_rc4)

/* OBJECT IDENTIFIER id-pkcs3-des-ede3-cbc ::= { iso(1) member-body(2) us(840) rsadsi(113549) pkcs(1) label-less(3) label-less(7) } */
extern ASN1EXP const heim_oid asn1_oid_id_pkcs3_des_ede3_cbc;
#define ASN1_OID_ID_PKCS3_DES_EDE3_CBC (&asn1_oid_id_pkcs3_des_ede3_cbc)

/* OBJECT IDENTIFIER id-rsadsi-encalg ::= { iso(1) member-body(2) us(840) rsadsi(113549) label-less(3) } */
extern ASN1EXP const heim_oid asn1_oid_id_rsadsi_encalg;
#define ASN1_OID_ID_RSADSI_ENCALG (&asn1_oid_id_rsadsi_encalg)

/* OBJECT IDENTIFIER id-rsadsi-rc2-cbc ::= { iso(1) member-body(2) us(840) rsadsi(113549) label-less(3) label-less(2) } */
extern ASN1EXP const heim_oid asn1_oid_id_rsadsi_rc2_cbc;
#define ASN1_OID_ID_RSADSI_RC2_CBC (&asn1_oid_id_rsadsi_rc2_cbc)

/* OBJECT IDENTIFIER id-rsadsi-des-ede3-cbc ::= { iso(1) member-body(2) us(840) rsadsi(113549) label-less(3) label-less(7) } */
extern ASN1EXP const heim_oid asn1_oid_id_rsadsi_des_ede3_cbc;
#define ASN1_OID_ID_RSADSI_DES_EDE3_CBC (&asn1_oid_id_rsadsi_des_ede3_cbc)

/* OBJECT IDENTIFIER id-secsig-sha-1 ::= { iso(1) identified-organization(3) oiw(14) secsig(3) algorithm(2) label-less(26) } */
extern ASN1EXP const heim_oid asn1_oid_id_secsig_sha_1;
#define ASN1_OID_ID_SECSIG_SHA_1 (&asn1_oid_id_secsig_sha_1)

/* OBJECT IDENTIFIER id-secsig-sha-1WithRSAEncryption ::= { iso(1) identified-organization(3) oiw(14) secsig(3) algorithm(2) label-less(29) } */
extern ASN1EXP const heim_oid asn1_oid_id_secsig_sha_1WithRSAEncryption;
#define ASN1_OID_ID_SECSIG_SHA_1WITHRSAENCRYPTION (&asn1_oid_id_secsig_sha_1WithRSAEncryption)

/* OBJECT IDENTIFIER id-nistAlgorithm ::= { joint-iso-itu-t(2) country(16) us(840) organization(1) gov(101) csor(3) label-less(4) } */
extern ASN1EXP const heim_oid asn1_oid_id_nistAlgorithm;
#define ASN1_OID_ID_NISTALGORITHM (&asn1_oid_id_nistAlgorithm)

/* OBJECT IDENTIFIER id-nist-aes-algs ::= { joint-iso-itu-t(2) country(16) us(840) organization(1) gov(101) csor(3) label-less(4) label-less(1) } */
extern ASN1EXP const heim_oid asn1_oid_id_nist_aes_algs;
#define ASN1_OID_ID_NIST_AES_ALGS (&asn1_oid_id_nist_aes_algs)

/* OBJECT IDENTIFIER id-aes-128-cbc ::= { joint-iso-itu-t(2) country(16) us(840) organization(1) gov(101) csor(3) label-less(4) label-less(1) label-less(2) } */
extern ASN1EXP const heim_oid asn1_oid_id_aes_128_cbc;
#define ASN1_OID_ID_AES_128_CBC (&asn1_oid_id_aes_128_cbc)

/* OBJECT IDENTIFIER id-aes-192-cbc ::= { joint-iso-itu-t(2) country(16) us(840) organization(1) gov(101) csor(3) label-less(4) label-less(1) label-less(22) } */
extern ASN1EXP const heim_oid asn1_oid_id_aes_192_cbc;
#define ASN1_OID_ID_AES_192_CBC (&asn1_oid_id_aes_192_cbc)

/* OBJECT IDENTIFIER id-aes-256-cbc ::= { joint-iso-itu-t(2) country(16) us(840) organization(1) gov(101) csor(3) label-less(4) label-less(1) label-less(42) } */
extern ASN1EXP const heim_oid asn1_oid_id_aes_256_cbc;
#define ASN1_OID_ID_AES_256_CBC (&asn1_oid_id_aes_256_cbc)

/* OBJECT IDENTIFIER id-nist-sha-algs ::= { joint-iso-itu-t(2) country(16) us(840) organization(1) gov(101) csor(3) label-less(4) label-less(2) } */
extern ASN1EXP const heim_oid asn1_oid_id_nist_sha_algs;
#define ASN1_OID_ID_NIST_SHA_ALGS (&asn1_oid_id_nist_sha_algs)

/* OBJECT IDENTIFIER id-sha256 ::= { joint-iso-itu-t(2) country(16) us(840) organization(1) gov(101) csor(3) label-less(4) label-less(2) label-less(1) } */
extern ASN1EXP const heim_oid asn1_oid_id_sha256;
#define ASN1_OID_ID_SHA256 (&asn1_oid_id_sha256)

/* OBJECT IDENTIFIER id-sha224 ::= { joint-iso-itu-t(2) country(16) us(840) organization(1) gov(101) csor(3) label-less(4) label-less(2) label-less(4) } */
extern ASN1EXP const heim_oid asn1_oid_id_sha224;
#define ASN1_OID_ID_SHA224 (&asn1_oid_id_sha224)

/* OBJECT IDENTIFIER id-sha384 ::= { joint-iso-itu-t(2) country(16) us(840) organization(1) gov(101) csor(3) label-less(4) label-less(2) label-less(2) } */
extern ASN1EXP const heim_oid asn1_oid_id_sha384;
#define ASN1_OID_ID_SHA384 (&asn1_oid_id_sha384)

/* OBJECT IDENTIFIER id-sha512 ::= { joint-iso-itu-t(2) country(16) us(840) organization(1) gov(101) csor(3) label-less(4) label-less(2) label-less(3) } */
extern ASN1EXP const heim_oid asn1_oid_id_sha512;
#define ASN1_OID_ID_SHA512 (&asn1_oid_id_sha512)

/* OBJECT IDENTIFIER id-dhpublicnumber ::= { iso(1) member-body(2) us(840) ansi-x942(10046) number-type(2) label-less(1) } */
extern ASN1EXP const heim_oid asn1_oid_id_dhpublicnumber;
#define ASN1_OID_ID_DHPUBLICNUMBER (&asn1_oid_id_dhpublicnumber)

/* OBJECT IDENTIFIER id-ecPublicKey ::= { iso(1) member-body(2) us(840) ansi-X9-62(10045) keyType(2) label-less(1) } */
extern ASN1EXP const heim_oid asn1_oid_id_ecPublicKey;
#define ASN1_OID_ID_ECPUBLICKEY (&asn1_oid_id_ecPublicKey)

/* OBJECT IDENTIFIER id-ecDH ::= { iso(1) identified-organization(3) certicom(132) schemes(1) ecdh(12) } */
extern ASN1EXP const heim_oid asn1_oid_id_ecDH;
#define ASN1_OID_ID_ECDH (&asn1_oid_id_ecDH)

/* OBJECT IDENTIFIER id-ecMQV ::= { iso(1) identified-organization(3) certicom(132) schemes(1) ecmqv(13) } */
extern ASN1EXP const heim_oid asn1_oid_id_ecMQV;
#define ASN1_OID_ID_ECMQV (&asn1_oid_id_ecMQV)

/* OBJECT IDENTIFIER id-ecdsa-with-SHA256 ::= { iso(1) member-body(2) us(840) ansi-X9-62(10045) signatures(4) ecdsa-with-SHA2(3) label-less(2) } */
extern ASN1EXP const heim_oid asn1_oid_id_ecdsa_with_SHA256;
#define ASN1_OID_ID_ECDSA_WITH_SHA256 (&asn1_oid_id_ecdsa_with_SHA256)

/* OBJECT IDENTIFIER id-ecdsa-with-SHA1 ::= { iso(1) member-body(2) us(840) ansi-X9-62(10045) signatures(4) label-less(1) } */
extern ASN1EXP const heim_oid asn1_oid_id_ecdsa_with_SHA1;
#define ASN1_OID_ID_ECDSA_WITH_SHA1 (&asn1_oid_id_ecdsa_with_SHA1)

/* OBJECT IDENTIFIER id-ec-group-secp256r1 ::= { iso(1) member-body(2) us(840) ansi-X9-62(10045) curves(3) prime(1) label-less(7) } */
extern ASN1EXP const heim_oid asn1_oid_id_ec_group_secp256r1;
#define ASN1_OID_ID_EC_GROUP_SECP256R1 (&asn1_oid_id_ec_group_secp256r1)

/* OBJECT IDENTIFIER id-ec-group-secp160r1 ::= { iso(1) identified-organization(3) certicom(132) label-less(0) label-less(8) } */
extern ASN1EXP const heim_oid asn1_oid_id_ec_group_secp160r1;
#define ASN1_OID_ID_EC_GROUP_SECP160R1 (&asn1_oid_id_ec_group_secp160r1)

/* OBJECT IDENTIFIER id-ec-group-secp160r2 ::= { iso(1) identified-organization(3) certicom(132) label-less(0) label-less(30) } */
extern ASN1EXP const heim_oid asn1_oid_id_ec_group_secp160r2;
#define ASN1_OID_ID_EC_GROUP_SECP160R2 (&asn1_oid_id_ec_group_secp160r2)

/* OBJECT IDENTIFIER id-x9-57 ::= { iso(1) member-body(2) us(840) ansi-x942(10046) label-less(4) } */
extern ASN1EXP const heim_oid asn1_oid_id_x9_57;
#define ASN1_OID_ID_X9_57 (&asn1_oid_id_x9_57)

/* OBJECT IDENTIFIER id-dsa ::= { iso(1) member-body(2) us(840) ansi-x942(10046) label-less(4) label-less(1) } */
extern ASN1EXP const heim_oid asn1_oid_id_dsa;
#define ASN1_OID_ID_DSA (&asn1_oid_id_dsa)

/* OBJECT IDENTIFIER id-dsa-with-sha1 ::= { iso(1) member-body(2) us(840) ansi-x942(10046) label-less(4) label-less(3) } */
extern ASN1EXP const heim_oid asn1_oid_id_dsa_with_sha1;
#define ASN1_OID_ID_DSA_WITH_SHA1 (&asn1_oid_id_dsa_with_sha1)

/* OBJECT IDENTIFIER id-x520-at ::= { joint-iso-ccitt(2) ds(5) label-less(4) } */
extern ASN1EXP const heim_oid asn1_oid_id_x520_at;
#define ASN1_OID_ID_X520_AT (&asn1_oid_id_x520_at)

/* OBJECT IDENTIFIER id-at-commonName ::= { joint-iso-ccitt(2) ds(5) label-less(4) label-less(3) } */
extern ASN1EXP const heim_oid asn1_oid_id_at_commonName;
#define ASN1_OID_ID_AT_COMMONNAME (&asn1_oid_id_at_commonName)

/* OBJECT IDENTIFIER id-at-surname ::= { joint-iso-ccitt(2) ds(5) label-less(4) label-less(4) } */
extern ASN1EXP const heim_oid asn1_oid_id_at_surname;
#define ASN1_OID_ID_AT_SURNAME (&asn1_oid_id_at_surname)

/* OBJECT IDENTIFIER id-at-serialNumber ::= { joint-iso-ccitt(2) ds(5) label-less(4) label-less(5) } */
extern ASN1EXP const heim_oid asn1_oid_id_at_serialNumber;
#define ASN1_OID_ID_AT_SERIALNUMBER (&asn1_oid_id_at_serialNumber)

/* OBJECT IDENTIFIER id-at-countryName ::= { joint-iso-ccitt(2) ds(5) label-less(4) label-less(6) } */
extern ASN1EXP const heim_oid asn1_oid_id_at_countryName;
#define ASN1_OID_ID_AT_COUNTRYNAME (&asn1_oid_id_at_countryName)

/* OBJECT IDENTIFIER id-at-localityName ::= { joint-iso-ccitt(2) ds(5) label-less(4) label-less(7) } */
extern ASN1EXP const heim_oid asn1_oid_id_at_localityName;
#define ASN1_OID_ID_AT_LOCALITYNAME (&asn1_oid_id_at_localityName)

/* OBJECT IDENTIFIER id-at-stateOrProvinceName ::= { joint-iso-ccitt(2) ds(5) label-less(4) label-less(8) } */
extern ASN1EXP const heim_oid asn1_oid_id_at_stateOrProvinceName;
#define ASN1_OID_ID_AT_STATEORPROVINCENAME (&asn1_oid_id_at_stateOrProvinceName)

/* OBJECT IDENTIFIER id-at-streetAddress ::= { joint-iso-ccitt(2) ds(5) label-less(4) label-less(9) } */
extern ASN1EXP const heim_oid asn1_oid_id_at_streetAddress;
#define ASN1_OID_ID_AT_STREETADDRESS (&asn1_oid_id_at_streetAddress)

/* OBJECT IDENTIFIER id-at-organizationName ::= { joint-iso-ccitt(2) ds(5) label-less(4) label-less(10) } */
extern ASN1EXP const heim_oid asn1_oid_id_at_organizationName;
#define ASN1_OID_ID_AT_ORGANIZATIONNAME (&asn1_oid_id_at_organizationName)

/* OBJECT IDENTIFIER id-at-organizationalUnitName ::= { joint-iso-ccitt(2) ds(5) label-less(4) label-less(11) } */
extern ASN1EXP const heim_oid asn1_oid_id_at_organizationalUnitName;
#define ASN1_OID_ID_AT_ORGANIZATIONALUNITNAME (&asn1_oid_id_at_organizationalUnitName)

/* OBJECT IDENTIFIER id-at-name ::= { joint-iso-ccitt(2) ds(5) label-less(4) label-less(41) } */
extern ASN1EXP const heim_oid asn1_oid_id_at_name;
#define ASN1_OID_ID_AT_NAME (&asn1_oid_id_at_name)

/* OBJECT IDENTIFIER id-at-givenName ::= { joint-iso-ccitt(2) ds(5) label-less(4) label-less(42) } */
extern ASN1EXP const heim_oid asn1_oid_id_at_givenName;
#define ASN1_OID_ID_AT_GIVENNAME (&asn1_oid_id_at_givenName)

/* OBJECT IDENTIFIER id-at-initials ::= { joint-iso-ccitt(2) ds(5) label-less(4) label-less(43) } */
extern ASN1EXP const heim_oid asn1_oid_id_at_initials;
#define ASN1_OID_ID_AT_INITIALS (&asn1_oid_id_at_initials)

/* OBJECT IDENTIFIER id-at-generationQualifier ::= { joint-iso-ccitt(2) ds(5) label-less(4) label-less(44) } */
extern ASN1EXP const heim_oid asn1_oid_id_at_generationQualifier;
#define ASN1_OID_ID_AT_GENERATIONQUALIFIER (&asn1_oid_id_at_generationQualifier)

/* OBJECT IDENTIFIER id-at-pseudonym ::= { joint-iso-ccitt(2) ds(5) label-less(4) label-less(65) } */
extern ASN1EXP const heim_oid asn1_oid_id_at_pseudonym;
#define ASN1_OID_ID_AT_PSEUDONYM (&asn1_oid_id_at_pseudonym)

/* OBJECT IDENTIFIER id-Userid ::= { label-less(0) label-less(9) label-less(2342) label-less(19200300) label-less(100) label-less(1) label-less(1) } */
extern ASN1EXP const heim_oid asn1_oid_id_Userid;
#define ASN1_OID_ID_USERID (&asn1_oid_id_Userid)

/* OBJECT IDENTIFIER id-domainComponent ::= { label-less(0) label-less(9) label-less(2342) label-less(19200300) label-less(100) label-less(1) label-less(25) } */
extern ASN1EXP const heim_oid asn1_oid_id_domainComponent;
#define ASN1_OID_ID_DOMAINCOMPONENT (&asn1_oid_id_domainComponent)

/* OBJECT IDENTIFIER id-x509-ce ::= { joint-iso-ccitt(2) ds(5) label-less(29) } */
extern ASN1EXP const heim_oid asn1_oid_id_x509_ce;
#define ASN1_OID_ID_X509_CE (&asn1_oid_id_x509_ce)

/*
AlgorithmIdentifier ::= SEQUENCE {
  algorithm         OBJECT IDENTIFIER,
  parameters      heim_any OPTIONAL,
}
*/

typedef struct AlgorithmIdentifier {
  heim_oid algorithm;
  heim_any *parameters;
} AlgorithmIdentifier;

ASN1EXP int    ASN1CALL decode_AlgorithmIdentifier(const unsigned char *, size_t, AlgorithmIdentifier *, size_t *);
ASN1EXP int    ASN1CALL encode_AlgorithmIdentifier(unsigned char *, size_t, const AlgorithmIdentifier *, size_t *);
ASN1EXP size_t ASN1CALL length_AlgorithmIdentifier(const AlgorithmIdentifier *);
ASN1EXP int    ASN1CALL copy_AlgorithmIdentifier  (const AlgorithmIdentifier *, AlgorithmIdentifier *);
ASN1EXP void   ASN1CALL free_AlgorithmIdentifier  (AlgorithmIdentifier *);


/*
AttributeType ::= OBJECT IDENTIFIER
*/

typedef heim_oid AttributeType;

ASN1EXP int    ASN1CALL decode_AttributeType(const unsigned char *, size_t, AttributeType *, size_t *);
ASN1EXP int    ASN1CALL encode_AttributeType(unsigned char *, size_t, const AttributeType *, size_t *);
ASN1EXP size_t ASN1CALL length_AttributeType(const AttributeType *);
ASN1EXP int    ASN1CALL copy_AttributeType  (const AttributeType *, AttributeType *);
ASN1EXP void   ASN1CALL free_AttributeType  (AttributeType *);


/*
AttributeValue ::= heim_any
*/

typedef heim_any AttributeValue;

ASN1EXP int    ASN1CALL decode_AttributeValue(const unsigned char *, size_t, AttributeValue *, size_t *);
ASN1EXP int    ASN1CALL encode_AttributeValue(unsigned char *, size_t, const AttributeValue *, size_t *);
ASN1EXP size_t ASN1CALL length_AttributeValue(const AttributeValue *);
ASN1EXP int    ASN1CALL copy_AttributeValue  (const AttributeValue *, AttributeValue *);
ASN1EXP void   ASN1CALL free_AttributeValue  (AttributeValue *);


/*
DirectoryString ::= CHOICE {
  ia5String           IA5String,
  teletexString     TeletexString,
  printableString     PrintableString,
  universalString     UniversalString,
  utf8String          UTF8String,
  bmpString           BMPString,
}
*/

typedef struct DirectoryString {
  enum {
    choice_DirectoryString_ia5String = 1,
    choice_DirectoryString_teletexString,
    choice_DirectoryString_printableString,
    choice_DirectoryString_universalString,
    choice_DirectoryString_utf8String,
    choice_DirectoryString_bmpString
  } element;
  union {
    heim_ia5_string ia5String;
    heim_general_string teletexString;
    heim_printable_string printableString;
    heim_universal_string universalString;
    heim_utf8_string utf8String;
    heim_bmp_string bmpString;
  } u;
} DirectoryString;

ASN1EXP int    ASN1CALL decode_DirectoryString(const unsigned char *, size_t, DirectoryString *, size_t *);
ASN1EXP int    ASN1CALL encode_DirectoryString(unsigned char *, size_t, const DirectoryString *, size_t *);
ASN1EXP size_t ASN1CALL length_DirectoryString(const DirectoryString *);
ASN1EXP int    ASN1CALL copy_DirectoryString  (const DirectoryString *, DirectoryString *);
ASN1EXP void   ASN1CALL free_DirectoryString  (DirectoryString *);


/*
Attribute ::= SEQUENCE {
  type            AttributeType,
  value           SET OF heim_any,
}
*/

typedef struct Attribute {
  AttributeType type;
  struct Attribute_value {
    unsigned int len;
    heim_any *val;
  } value;
} Attribute;

ASN1EXP int    ASN1CALL decode_Attribute(const unsigned char *, size_t, Attribute *, size_t *);
ASN1EXP int    ASN1CALL encode_Attribute(unsigned char *, size_t, const Attribute *, size_t *);
ASN1EXP size_t ASN1CALL length_Attribute(const Attribute *);
ASN1EXP int    ASN1CALL copy_Attribute  (const Attribute *, Attribute *);
ASN1EXP void   ASN1CALL free_Attribute  (Attribute *);


/*
AttributeTypeAndValue ::= SEQUENCE {
  type            AttributeType,
  value           DirectoryString,
}
*/

typedef struct AttributeTypeAndValue {
  AttributeType type;
  DirectoryString value;
} AttributeTypeAndValue;

ASN1EXP int    ASN1CALL decode_AttributeTypeAndValue(const unsigned char *, size_t, AttributeTypeAndValue *, size_t *);
ASN1EXP int    ASN1CALL encode_AttributeTypeAndValue(unsigned char *, size_t, const AttributeTypeAndValue *, size_t *);
ASN1EXP size_t ASN1CALL length_AttributeTypeAndValue(const AttributeTypeAndValue *);
ASN1EXP int    ASN1CALL copy_AttributeTypeAndValue  (const AttributeTypeAndValue *, AttributeTypeAndValue *);
ASN1EXP void   ASN1CALL free_AttributeTypeAndValue  (AttributeTypeAndValue *);


/*
RelativeDistinguishedName ::= SET OF AttributeTypeAndValue
*/

typedef struct RelativeDistinguishedName {
  unsigned int len;
  AttributeTypeAndValue *val;
} RelativeDistinguishedName;

ASN1EXP int    ASN1CALL decode_RelativeDistinguishedName(const unsigned char *, size_t, RelativeDistinguishedName *, size_t *);
ASN1EXP int    ASN1CALL encode_RelativeDistinguishedName(unsigned char *, size_t, const RelativeDistinguishedName *, size_t *);
ASN1EXP size_t ASN1CALL length_RelativeDistinguishedName(const RelativeDistinguishedName *);
ASN1EXP int    ASN1CALL copy_RelativeDistinguishedName  (const RelativeDistinguishedName *, RelativeDistinguishedName *);
ASN1EXP void   ASN1CALL free_RelativeDistinguishedName  (RelativeDistinguishedName *);


/*
RDNSequence ::= SEQUENCE OF RelativeDistinguishedName
*/

typedef struct RDNSequence {
  unsigned int len;
  RelativeDistinguishedName *val;
} RDNSequence;

ASN1EXP int    ASN1CALL decode_RDNSequence(const unsigned char *, size_t, RDNSequence *, size_t *);
ASN1EXP int    ASN1CALL encode_RDNSequence(unsigned char *, size_t, const RDNSequence *, size_t *);
ASN1EXP size_t ASN1CALL length_RDNSequence(const RDNSequence *);
ASN1EXP int    ASN1CALL copy_RDNSequence  (const RDNSequence *, RDNSequence *);
ASN1EXP void   ASN1CALL free_RDNSequence  (RDNSequence *);


/*
Name ::= CHOICE {
  rdnSequence     RDNSequence,
}
*/

typedef struct Name {
  heim_octet_string _save;
  enum {
    choice_Name_rdnSequence = 1
  } element;
  union {
    RDNSequence rdnSequence;
  } u;
} Name;

ASN1EXP int    ASN1CALL decode_Name(const unsigned char *, size_t, Name *, size_t *);
ASN1EXP int    ASN1CALL encode_Name(unsigned char *, size_t, const Name *, size_t *);
ASN1EXP size_t ASN1CALL length_Name(const Name *);
ASN1EXP int    ASN1CALL copy_Name  (const Name *, Name *);
ASN1EXP void   ASN1CALL free_Name  (Name *);


/*
CertificateSerialNumber ::= INTEGER
*/

typedef heim_integer CertificateSerialNumber;

ASN1EXP int    ASN1CALL decode_CertificateSerialNumber(const unsigned char *, size_t, CertificateSerialNumber *, size_t *);
ASN1EXP int    ASN1CALL encode_CertificateSerialNumber(unsigned char *, size_t, const CertificateSerialNumber *, size_t *);
ASN1EXP size_t ASN1CALL length_CertificateSerialNumber(const CertificateSerialNumber *);
ASN1EXP int    ASN1CALL copy_CertificateSerialNumber  (const CertificateSerialNumber *, CertificateSerialNumber *);
ASN1EXP void   ASN1CALL free_CertificateSerialNumber  (CertificateSerialNumber *);


/*
Time ::= CHOICE {
  utcTime         UTCTime,
  generalTime     GeneralizedTime,
}
*/

typedef struct Time {
  enum {
    choice_Time_utcTime = 1,
    choice_Time_generalTime
  } element;
  union {
    time_t utcTime;
    time_t generalTime;
  } u;
} Time;

ASN1EXP int    ASN1CALL decode_Time(const unsigned char *, size_t, Time *, size_t *);
ASN1EXP int    ASN1CALL encode_Time(unsigned char *, size_t, const Time *, size_t *);
ASN1EXP size_t ASN1CALL length_Time(const Time *);
ASN1EXP int    ASN1CALL copy_Time  (const Time *, Time *);
ASN1EXP void   ASN1CALL free_Time  (Time *);


/*
Validity ::= SEQUENCE {
  notBefore       Time,
  notAfter        Time,
}
*/

typedef struct Validity {
  Time notBefore;
  Time notAfter;
} Validity;

ASN1EXP int    ASN1CALL decode_Validity(const unsigned char *, size_t, Validity *, size_t *);
ASN1EXP int    ASN1CALL encode_Validity(unsigned char *, size_t, const Validity *, size_t *);
ASN1EXP size_t ASN1CALL length_Validity(const Validity *);
ASN1EXP int    ASN1CALL copy_Validity  (const Validity *, Validity *);
ASN1EXP void   ASN1CALL free_Validity  (Validity *);


/*
UniqueIdentifier ::= BIT STRING {
}
*/

typedef heim_bit_string UniqueIdentifier;

ASN1EXP int    ASN1CALL decode_UniqueIdentifier(const unsigned char *, size_t, UniqueIdentifier *, size_t *);
ASN1EXP int    ASN1CALL encode_UniqueIdentifier(unsigned char *, size_t, const UniqueIdentifier *, size_t *);
ASN1EXP size_t ASN1CALL length_UniqueIdentifier(const UniqueIdentifier *);
ASN1EXP int    ASN1CALL copy_UniqueIdentifier  (const UniqueIdentifier *, UniqueIdentifier *);
ASN1EXP void   ASN1CALL free_UniqueIdentifier  (UniqueIdentifier *);


/*
SubjectPublicKeyInfo ::= SEQUENCE {
  algorithm          AlgorithmIdentifier,
  subjectPublicKey     BIT STRING {
  },
}
*/

typedef struct SubjectPublicKeyInfo {
  AlgorithmIdentifier algorithm;
  heim_bit_string subjectPublicKey;
} SubjectPublicKeyInfo;

ASN1EXP int    ASN1CALL decode_SubjectPublicKeyInfo(const unsigned char *, size_t, SubjectPublicKeyInfo *, size_t *);
ASN1EXP int    ASN1CALL encode_SubjectPublicKeyInfo(unsigned char *, size_t, const SubjectPublicKeyInfo *, size_t *);
ASN1EXP size_t ASN1CALL length_SubjectPublicKeyInfo(const SubjectPublicKeyInfo *);
ASN1EXP int    ASN1CALL copy_SubjectPublicKeyInfo  (const SubjectPublicKeyInfo *, SubjectPublicKeyInfo *);
ASN1EXP void   ASN1CALL free_SubjectPublicKeyInfo  (SubjectPublicKeyInfo *);


/*
Extension ::= SEQUENCE {
  extnID            OBJECT IDENTIFIER,
  critical        BOOLEAN OPTIONAL,
  extnValue       OCTET STRING,
}
*/

typedef struct Extension {
  heim_oid extnID;
  int *critical;
  heim_octet_string extnValue;
} Extension;

ASN1EXP int    ASN1CALL decode_Extension(const unsigned char *, size_t, Extension *, size_t *);
ASN1EXP int    ASN1CALL encode_Extension(unsigned char *, size_t, const Extension *, size_t *);
ASN1EXP size_t ASN1CALL length_Extension(const Extension *);
ASN1EXP int    ASN1CALL copy_Extension  (const Extension *, Extension *);
ASN1EXP void   ASN1CALL free_Extension  (Extension *);


/*
Extensions ::= SEQUENCE OF Extension
*/

typedef struct Extensions {
  unsigned int len;
  Extension *val;
} Extensions;

ASN1EXP int   ASN1CALL add_Extensions  (Extensions *, const Extension *);
ASN1EXP int   ASN1CALL remove_Extensions  (Extensions *, unsigned int);
ASN1EXP int    ASN1CALL decode_Extensions(const unsigned char *, size_t, Extensions *, size_t *);
ASN1EXP int    ASN1CALL encode_Extensions(unsigned char *, size_t, const Extensions *, size_t *);
ASN1EXP size_t ASN1CALL length_Extensions(const Extensions *);
ASN1EXP int    ASN1CALL copy_Extensions  (const Extensions *, Extensions *);
ASN1EXP void   ASN1CALL free_Extensions  (Extensions *);


/*
TBSCertificate ::= SEQUENCE {
  version                [0] Version OPTIONAL,
  serialNumber           CertificateSerialNumber,
  signature              AlgorithmIdentifier,
  issuer                 Name,
  validity               Validity,
  subject                Name,
  subjectPublicKeyInfo   SubjectPublicKeyInfo,
  issuerUniqueID         [1] IMPLICIT   BIT STRING {
  } OPTIONAL,
  subjectUniqueID        [2] IMPLICIT   BIT STRING {
  } OPTIONAL,
  extensions             [3] Extensions OPTIONAL,
}
*/

typedef struct TBSCertificate {
  heim_octet_string _save;
  Version *version;
  CertificateSerialNumber serialNumber;
  AlgorithmIdentifier signature;
  Name issuer;
  Validity validity;
  Name subject;
  SubjectPublicKeyInfo subjectPublicKeyInfo;
  heim_bit_string *issuerUniqueID;
  heim_bit_string *subjectUniqueID;
  Extensions *extensions;
} TBSCertificate;

ASN1EXP int    ASN1CALL decode_TBSCertificate(const unsigned char *, size_t, TBSCertificate *, size_t *);
ASN1EXP int    ASN1CALL encode_TBSCertificate(unsigned char *, size_t, const TBSCertificate *, size_t *);
ASN1EXP size_t ASN1CALL length_TBSCertificate(const TBSCertificate *);
ASN1EXP int    ASN1CALL copy_TBSCertificate  (const TBSCertificate *, TBSCertificate *);
ASN1EXP void   ASN1CALL free_TBSCertificate  (TBSCertificate *);


/*
Certificate ::= SEQUENCE {
  tbsCertificate       TBSCertificate,
  signatureAlgorithm   AlgorithmIdentifier,
  signatureValue         BIT STRING {
  },
}
*/

typedef struct Certificate {
  TBSCertificate tbsCertificate;
  AlgorithmIdentifier signatureAlgorithm;
  heim_bit_string signatureValue;
} Certificate;

ASN1EXP int    ASN1CALL decode_Certificate(const unsigned char *, size_t, Certificate *, size_t *);
ASN1EXP int    ASN1CALL encode_Certificate(unsigned char *, size_t, const Certificate *, size_t *);
ASN1EXP size_t ASN1CALL length_Certificate(const Certificate *);
ASN1EXP int    ASN1CALL copy_Certificate  (const Certificate *, Certificate *);
ASN1EXP void   ASN1CALL free_Certificate  (Certificate *);


/*
Certificates ::= SEQUENCE OF Certificate
*/

typedef struct Certificates {
  unsigned int len;
  Certificate *val;
} Certificates;

ASN1EXP int    ASN1CALL decode_Certificates(const unsigned char *, size_t, Certificates *, size_t *);
ASN1EXP int    ASN1CALL encode_Certificates(unsigned char *, size_t, const Certificates *, size_t *);
ASN1EXP size_t ASN1CALL length_Certificates(const Certificates *);
ASN1EXP int    ASN1CALL copy_Certificates  (const Certificates *, Certificates *);
ASN1EXP void   ASN1CALL free_Certificates  (Certificates *);


/*
ValidationParms ::= SEQUENCE {
  seed              BIT STRING {
  },
  pgenCounter     INTEGER,
}
*/

typedef struct ValidationParms {
  heim_bit_string seed;
  heim_integer pgenCounter;
} ValidationParms;

ASN1EXP int    ASN1CALL decode_ValidationParms(const unsigned char *, size_t, ValidationParms *, size_t *);
ASN1EXP int    ASN1CALL encode_ValidationParms(unsigned char *, size_t, const ValidationParms *, size_t *);
ASN1EXP size_t ASN1CALL length_ValidationParms(const ValidationParms *);
ASN1EXP int    ASN1CALL copy_ValidationParms  (const ValidationParms *, ValidationParms *);
ASN1EXP void   ASN1CALL free_ValidationParms  (ValidationParms *);


/*
DomainParameters ::= SEQUENCE {
  p                 INTEGER,
  g                 INTEGER,
  q                 INTEGER,
  j                 INTEGER OPTIONAL,
  validationParms   ValidationParms OPTIONAL,
}
*/

typedef struct DomainParameters {
  heim_integer p;
  heim_integer g;
  heim_integer q;
  heim_integer *j;
  ValidationParms *validationParms;
} DomainParameters;

ASN1EXP int    ASN1CALL decode_DomainParameters(const unsigned char *, size_t, DomainParameters *, size_t *);
ASN1EXP int    ASN1CALL encode_DomainParameters(unsigned char *, size_t, const DomainParameters *, size_t *);
ASN1EXP size_t ASN1CALL length_DomainParameters(const DomainParameters *);
ASN1EXP int    ASN1CALL copy_DomainParameters  (const DomainParameters *, DomainParameters *);
ASN1EXP void   ASN1CALL free_DomainParameters  (DomainParameters *);


/*
DHParameter ::= SEQUENCE {
  prime                INTEGER,
  base                 INTEGER,
  privateValueLength   INTEGER OPTIONAL,
}
*/

typedef struct DHParameter {
  heim_integer prime;
  heim_integer base;
  heim_integer *privateValueLength;
} DHParameter;

ASN1EXP int    ASN1CALL decode_DHParameter(const unsigned char *, size_t, DHParameter *, size_t *);
ASN1EXP int    ASN1CALL encode_DHParameter(unsigned char *, size_t, const DHParameter *, size_t *);
ASN1EXP size_t ASN1CALL length_DHParameter(const DHParameter *);
ASN1EXP int    ASN1CALL copy_DHParameter  (const DHParameter *, DHParameter *);
ASN1EXP void   ASN1CALL free_DHParameter  (DHParameter *);


/*
DHPublicKey ::= INTEGER
*/

typedef heim_integer DHPublicKey;

ASN1EXP int    ASN1CALL decode_DHPublicKey(const unsigned char *, size_t, DHPublicKey *, size_t *);
ASN1EXP int    ASN1CALL encode_DHPublicKey(unsigned char *, size_t, const DHPublicKey *, size_t *);
ASN1EXP size_t ASN1CALL length_DHPublicKey(const DHPublicKey *);
ASN1EXP int    ASN1CALL copy_DHPublicKey  (const DHPublicKey *, DHPublicKey *);
ASN1EXP void   ASN1CALL free_DHPublicKey  (DHPublicKey *);


/*
OtherName ::= SEQUENCE {
  type-id           OBJECT IDENTIFIER,
  value           [0] heim_any,
}
*/

typedef struct OtherName {
  heim_oid type_id;
  heim_any value;
} OtherName;

ASN1EXP int    ASN1CALL decode_OtherName(const unsigned char *, size_t, OtherName *, size_t *);
ASN1EXP int    ASN1CALL encode_OtherName(unsigned char *, size_t, const OtherName *, size_t *);
ASN1EXP size_t ASN1CALL length_OtherName(const OtherName *);
ASN1EXP int    ASN1CALL copy_OtherName  (const OtherName *, OtherName *);
ASN1EXP void   ASN1CALL free_OtherName  (OtherName *);


/*
GeneralName ::= CHOICE {
  otherName                   [0] IMPLICIT SEQUENCE {
    type-id             OBJECT IDENTIFIER,
    value           [0] heim_any,
  },
  rfc822Name                  [1] IMPLICIT   IA5String,
  dNSName                     [2] IMPLICIT   IA5String,
  directoryName               [4] IMPLICIT CHOICE {
    rdnSequence     RDNSequence,
  },
  uniformResourceIdentifier   [6] IMPLICIT   IA5String,
  iPAddress                   [7] IMPLICIT OCTET STRING,
  registeredID                [8] IMPLICIT   OBJECT IDENTIFIER,
}
*/

typedef struct GeneralName {
  enum {
    choice_GeneralName_otherName = 1,
    choice_GeneralName_rfc822Name,
    choice_GeneralName_dNSName,
    choice_GeneralName_directoryName,
    choice_GeneralName_uniformResourceIdentifier,
    choice_GeneralName_iPAddress,
    choice_GeneralName_registeredID
  } element;
  union {
    struct GeneralName_otherName {
      heim_oid type_id;
      heim_any value;
    } otherName;
    heim_ia5_string rfc822Name;
    heim_ia5_string dNSName;
    struct GeneralName_directoryName {
      enum {
        choice_GeneralName_directoryName_rdnSequence = 1
      } element;
      union {
        RDNSequence rdnSequence;
      } u;
    } directoryName;
    heim_ia5_string uniformResourceIdentifier;
    heim_octet_string iPAddress;
    heim_oid registeredID;
  } u;
} GeneralName;

ASN1EXP int    ASN1CALL decode_GeneralName(const unsigned char *, size_t, GeneralName *, size_t *);
ASN1EXP int    ASN1CALL encode_GeneralName(unsigned char *, size_t, const GeneralName *, size_t *);
ASN1EXP size_t ASN1CALL length_GeneralName(const GeneralName *);
ASN1EXP int    ASN1CALL copy_GeneralName  (const GeneralName *, GeneralName *);
ASN1EXP void   ASN1CALL free_GeneralName  (GeneralName *);


/*
GeneralNames ::= SEQUENCE OF GeneralName
*/

typedef struct GeneralNames {
  unsigned int len;
  GeneralName *val;
} GeneralNames;

ASN1EXP int   ASN1CALL add_GeneralNames  (GeneralNames *, const GeneralName *);
ASN1EXP int   ASN1CALL remove_GeneralNames  (GeneralNames *, unsigned int);
ASN1EXP int    ASN1CALL decode_GeneralNames(const unsigned char *, size_t, GeneralNames *, size_t *);
ASN1EXP int    ASN1CALL encode_GeneralNames(unsigned char *, size_t, const GeneralNames *, size_t *);
ASN1EXP size_t ASN1CALL length_GeneralNames(const GeneralNames *);
ASN1EXP int    ASN1CALL copy_GeneralNames  (const GeneralNames *, GeneralNames *);
ASN1EXP void   ASN1CALL free_GeneralNames  (GeneralNames *);


/* OBJECT IDENTIFIER id-x509-ce-keyUsage ::= { joint-iso-ccitt(2) ds(5) label-less(29) label-less(15) } */
extern ASN1EXP const heim_oid asn1_oid_id_x509_ce_keyUsage;
#define ASN1_OID_ID_X509_CE_KEYUSAGE (&asn1_oid_id_x509_ce_keyUsage)

/*
KeyUsage ::= BIT STRING {
  digitalSignature(0),
  nonRepudiation(1),
  keyEncipherment(2),
  dataEncipherment(3),
  keyAgreement(4),
  keyCertSign(5),
  cRLSign(6),
  encipherOnly(7),
  decipherOnly(8)
}
*/

typedef struct KeyUsage {
  unsigned int digitalSignature:1;
  unsigned int nonRepudiation:1;
  unsigned int keyEncipherment:1;
  unsigned int dataEncipherment:1;
  unsigned int keyAgreement:1;
  unsigned int keyCertSign:1;
  unsigned int cRLSign:1;
  unsigned int encipherOnly:1;
  unsigned int decipherOnly:1;
  unsigned int _unused9:1;
  unsigned int _unused10:1;
  unsigned int _unused11:1;
  unsigned int _unused12:1;
  unsigned int _unused13:1;
  unsigned int _unused14:1;
  unsigned int _unused15:1;
  unsigned int _unused16:1;
  unsigned int _unused17:1;
  unsigned int _unused18:1;
  unsigned int _unused19:1;
  unsigned int _unused20:1;
  unsigned int _unused21:1;
  unsigned int _unused22:1;
  unsigned int _unused23:1;
  unsigned int _unused24:1;
  unsigned int _unused25:1;
  unsigned int _unused26:1;
  unsigned int _unused27:1;
  unsigned int _unused28:1;
  unsigned int _unused29:1;
  unsigned int _unused30:1;
  unsigned int _unused31:1;
} KeyUsage;


unsigned KeyUsage2int(KeyUsage);
KeyUsage int2KeyUsage(unsigned);
const struct units * asn1_KeyUsage_units(void);
ASN1EXP int    ASN1CALL decode_KeyUsage(const unsigned char *, size_t, KeyUsage *, size_t *);
ASN1EXP int    ASN1CALL encode_KeyUsage(unsigned char *, size_t, const KeyUsage *, size_t *);
ASN1EXP size_t ASN1CALL length_KeyUsage(const KeyUsage *);
ASN1EXP int    ASN1CALL copy_KeyUsage  (const KeyUsage *, KeyUsage *);
ASN1EXP void   ASN1CALL free_KeyUsage  (KeyUsage *);


/* OBJECT IDENTIFIER id-x509-ce-authorityKeyIdentifier ::= { joint-iso-ccitt(2) ds(5) label-less(29) label-less(35) } */
extern ASN1EXP const heim_oid asn1_oid_id_x509_ce_authorityKeyIdentifier;
#define ASN1_OID_ID_X509_CE_AUTHORITYKEYIDENTIFIER (&asn1_oid_id_x509_ce_authorityKeyIdentifier)

/*
KeyIdentifier ::= OCTET STRING
*/

typedef heim_octet_string KeyIdentifier;

ASN1EXP int    ASN1CALL decode_KeyIdentifier(const unsigned char *, size_t, KeyIdentifier *, size_t *);
ASN1EXP int    ASN1CALL encode_KeyIdentifier(unsigned char *, size_t, const KeyIdentifier *, size_t *);
ASN1EXP size_t ASN1CALL length_KeyIdentifier(const KeyIdentifier *);
ASN1EXP int    ASN1CALL copy_KeyIdentifier  (const KeyIdentifier *, KeyIdentifier *);
ASN1EXP void   ASN1CALL free_KeyIdentifier  (KeyIdentifier *);


/*
AuthorityKeyIdentifier ::= SEQUENCE {
  keyIdentifier               [0] IMPLICIT OCTET STRING OPTIONAL,
  authorityCertIssuer         [1] IMPLICIT SEQUENCE OF GeneralName OPTIONAL,
  authorityCertSerialNumber   [2] IMPLICIT INTEGER OPTIONAL,
}
*/

typedef struct AuthorityKeyIdentifier {
  heim_octet_string *keyIdentifier;
  struct AuthorityKeyIdentifier_authorityCertIssuer {
    unsigned int len;
    GeneralName *val;
  } *authorityCertIssuer;
  heim_integer *authorityCertSerialNumber;
} AuthorityKeyIdentifier;

ASN1EXP int    ASN1CALL decode_AuthorityKeyIdentifier(const unsigned char *, size_t, AuthorityKeyIdentifier *, size_t *);
ASN1EXP int    ASN1CALL encode_AuthorityKeyIdentifier(unsigned char *, size_t, const AuthorityKeyIdentifier *, size_t *);
ASN1EXP size_t ASN1CALL length_AuthorityKeyIdentifier(const AuthorityKeyIdentifier *);
ASN1EXP int    ASN1CALL copy_AuthorityKeyIdentifier  (const AuthorityKeyIdentifier *, AuthorityKeyIdentifier *);
ASN1EXP void   ASN1CALL free_AuthorityKeyIdentifier  (AuthorityKeyIdentifier *);


/* OBJECT IDENTIFIER id-x509-ce-subjectKeyIdentifier ::= { joint-iso-ccitt(2) ds(5) label-less(29) label-less(14) } */
extern ASN1EXP const heim_oid asn1_oid_id_x509_ce_subjectKeyIdentifier;
#define ASN1_OID_ID_X509_CE_SUBJECTKEYIDENTIFIER (&asn1_oid_id_x509_ce_subjectKeyIdentifier)

/*
SubjectKeyIdentifier ::= KeyIdentifier
*/

typedef KeyIdentifier SubjectKeyIdentifier;

ASN1EXP int    ASN1CALL decode_SubjectKeyIdentifier(const unsigned char *, size_t, SubjectKeyIdentifier *, size_t *);
ASN1EXP int    ASN1CALL encode_SubjectKeyIdentifier(unsigned char *, size_t, const SubjectKeyIdentifier *, size_t *);
ASN1EXP size_t ASN1CALL length_SubjectKeyIdentifier(const SubjectKeyIdentifier *);
ASN1EXP int    ASN1CALL copy_SubjectKeyIdentifier  (const SubjectKeyIdentifier *, SubjectKeyIdentifier *);
ASN1EXP void   ASN1CALL free_SubjectKeyIdentifier  (SubjectKeyIdentifier *);


/* OBJECT IDENTIFIER id-x509-ce-basicConstraints ::= { joint-iso-ccitt(2) ds(5) label-less(29) label-less(19) } */
extern ASN1EXP const heim_oid asn1_oid_id_x509_ce_basicConstraints;
#define ASN1_OID_ID_X509_CE_BASICCONSTRAINTS (&asn1_oid_id_x509_ce_basicConstraints)

/*
BasicConstraints ::= SEQUENCE {
  cA                  BOOLEAN OPTIONAL,
  pathLenConstraint   INTEGER (0..-1) OPTIONAL,
}
*/

typedef struct BasicConstraints {
  int *cA;
  unsigned int *pathLenConstraint;
} BasicConstraints;

ASN1EXP int    ASN1CALL decode_BasicConstraints(const unsigned char *, size_t, BasicConstraints *, size_t *);
ASN1EXP int    ASN1CALL encode_BasicConstraints(unsigned char *, size_t, const BasicConstraints *, size_t *);
ASN1EXP size_t ASN1CALL length_BasicConstraints(const BasicConstraints *);
ASN1EXP int    ASN1CALL copy_BasicConstraints  (const BasicConstraints *, BasicConstraints *);
ASN1EXP void   ASN1CALL free_BasicConstraints  (BasicConstraints *);


/* OBJECT IDENTIFIER id-x509-ce-nameConstraints ::= { joint-iso-ccitt(2) ds(5) label-less(29) label-less(30) } */
extern ASN1EXP const heim_oid asn1_oid_id_x509_ce_nameConstraints;
#define ASN1_OID_ID_X509_CE_NAMECONSTRAINTS (&asn1_oid_id_x509_ce_nameConstraints)

/*
BaseDistance ::= INTEGER
*/

typedef heim_integer BaseDistance;

ASN1EXP int    ASN1CALL decode_BaseDistance(const unsigned char *, size_t, BaseDistance *, size_t *);
ASN1EXP int    ASN1CALL encode_BaseDistance(unsigned char *, size_t, const BaseDistance *, size_t *);
ASN1EXP size_t ASN1CALL length_BaseDistance(const BaseDistance *);
ASN1EXP int    ASN1CALL copy_BaseDistance  (const BaseDistance *, BaseDistance *);
ASN1EXP void   ASN1CALL free_BaseDistance  (BaseDistance *);


/*
GeneralSubtree ::= SEQUENCE {
  base            GeneralName,
  minimum         [0] IMPLICIT INTEGER OPTIONAL,
  maximum         [1] IMPLICIT INTEGER OPTIONAL,
}
*/

typedef struct GeneralSubtree {
  GeneralName base;
  heim_integer *minimum;
  heim_integer *maximum;
} GeneralSubtree;

ASN1EXP int    ASN1CALL decode_GeneralSubtree(const unsigned char *, size_t, GeneralSubtree *, size_t *);
ASN1EXP int    ASN1CALL encode_GeneralSubtree(unsigned char *, size_t, const GeneralSubtree *, size_t *);
ASN1EXP size_t ASN1CALL length_GeneralSubtree(const GeneralSubtree *);
ASN1EXP int    ASN1CALL copy_GeneralSubtree  (const GeneralSubtree *, GeneralSubtree *);
ASN1EXP void   ASN1CALL free_GeneralSubtree  (GeneralSubtree *);


/*
GeneralSubtrees ::= SEQUENCE OF GeneralSubtree
*/

typedef struct GeneralSubtrees {
  unsigned int len;
  GeneralSubtree *val;
} GeneralSubtrees;

ASN1EXP int    ASN1CALL decode_GeneralSubtrees(const unsigned char *, size_t, GeneralSubtrees *, size_t *);
ASN1EXP int    ASN1CALL encode_GeneralSubtrees(unsigned char *, size_t, const GeneralSubtrees *, size_t *);
ASN1EXP size_t ASN1CALL length_GeneralSubtrees(const GeneralSubtrees *);
ASN1EXP int    ASN1CALL copy_GeneralSubtrees  (const GeneralSubtrees *, GeneralSubtrees *);
ASN1EXP void   ASN1CALL free_GeneralSubtrees  (GeneralSubtrees *);


/*
NameConstraints ::= SEQUENCE {
  permittedSubtrees   [0] IMPLICIT SEQUENCE OF GeneralSubtree OPTIONAL,
  excludedSubtrees    [1] IMPLICIT SEQUENCE OF GeneralSubtree OPTIONAL,
}
*/

typedef struct NameConstraints {
  struct NameConstraints_permittedSubtrees {
    unsigned int len;
    GeneralSubtree *val;
  } *permittedSubtrees;
  struct NameConstraints_excludedSubtrees {
    unsigned int len;
    GeneralSubtree *val;
  } *excludedSubtrees;
} NameConstraints;

ASN1EXP int    ASN1CALL decode_NameConstraints(const unsigned char *, size_t, NameConstraints *, size_t *);
ASN1EXP int    ASN1CALL encode_NameConstraints(unsigned char *, size_t, const NameConstraints *, size_t *);
ASN1EXP size_t ASN1CALL length_NameConstraints(const NameConstraints *);
ASN1EXP int    ASN1CALL copy_NameConstraints  (const NameConstraints *, NameConstraints *);
ASN1EXP void   ASN1CALL free_NameConstraints  (NameConstraints *);


/* OBJECT IDENTIFIER id-x509-ce-privateKeyUsagePeriod ::= { joint-iso-ccitt(2) ds(5) label-less(29) label-less(16) } */
extern ASN1EXP const heim_oid asn1_oid_id_x509_ce_privateKeyUsagePeriod;
#define ASN1_OID_ID_X509_CE_PRIVATEKEYUSAGEPERIOD (&asn1_oid_id_x509_ce_privateKeyUsagePeriod)

/* OBJECT IDENTIFIER id-x509-ce-certificatePolicies ::= { joint-iso-ccitt(2) ds(5) label-less(29) label-less(32) } */
extern ASN1EXP const heim_oid asn1_oid_id_x509_ce_certificatePolicies;
#define ASN1_OID_ID_X509_CE_CERTIFICATEPOLICIES (&asn1_oid_id_x509_ce_certificatePolicies)

/* OBJECT IDENTIFIER id-x509-ce-policyMappings ::= { joint-iso-ccitt(2) ds(5) label-less(29) label-less(33) } */
extern ASN1EXP const heim_oid asn1_oid_id_x509_ce_policyMappings;
#define ASN1_OID_ID_X509_CE_POLICYMAPPINGS (&asn1_oid_id_x509_ce_policyMappings)

/* OBJECT IDENTIFIER id-x509-ce-subjectAltName ::= { joint-iso-ccitt(2) ds(5) label-less(29) label-less(17) } */
extern ASN1EXP const heim_oid asn1_oid_id_x509_ce_subjectAltName;
#define ASN1_OID_ID_X509_CE_SUBJECTALTNAME (&asn1_oid_id_x509_ce_subjectAltName)

/* OBJECT IDENTIFIER id-x509-ce-issuerAltName ::= { joint-iso-ccitt(2) ds(5) label-less(29) label-less(18) } */
extern ASN1EXP const heim_oid asn1_oid_id_x509_ce_issuerAltName;
#define ASN1_OID_ID_X509_CE_ISSUERALTNAME (&asn1_oid_id_x509_ce_issuerAltName)

/* OBJECT IDENTIFIER id-x509-ce-subjectDirectoryAttributes ::= { joint-iso-ccitt(2) ds(5) label-less(29) label-less(9) } */
extern ASN1EXP const heim_oid asn1_oid_id_x509_ce_subjectDirectoryAttributes;
#define ASN1_OID_ID_X509_CE_SUBJECTDIRECTORYATTRIBUTES (&asn1_oid_id_x509_ce_subjectDirectoryAttributes)

/* OBJECT IDENTIFIER id-x509-ce-policyConstraints ::= { joint-iso-ccitt(2) ds(5) label-less(29) label-less(36) } */
extern ASN1EXP const heim_oid asn1_oid_id_x509_ce_policyConstraints;
#define ASN1_OID_ID_X509_CE_POLICYCONSTRAINTS (&asn1_oid_id_x509_ce_policyConstraints)

/* OBJECT IDENTIFIER id-x509-ce-extKeyUsage ::= { joint-iso-ccitt(2) ds(5) label-less(29) label-less(37) } */
extern ASN1EXP const heim_oid asn1_oid_id_x509_ce_extKeyUsage;
#define ASN1_OID_ID_X509_CE_EXTKEYUSAGE (&asn1_oid_id_x509_ce_extKeyUsage)

/*
ExtKeyUsage ::= SEQUENCE OF OBJECT IDENTIFIER
*/

typedef struct ExtKeyUsage {
  unsigned int len;
  heim_oid *val;
} ExtKeyUsage;

ASN1EXP int    ASN1CALL decode_ExtKeyUsage(const unsigned char *, size_t, ExtKeyUsage *, size_t *);
ASN1EXP int    ASN1CALL encode_ExtKeyUsage(unsigned char *, size_t, const ExtKeyUsage *, size_t *);
ASN1EXP size_t ASN1CALL length_ExtKeyUsage(const ExtKeyUsage *);
ASN1EXP int    ASN1CALL copy_ExtKeyUsage  (const ExtKeyUsage *, ExtKeyUsage *);
ASN1EXP void   ASN1CALL free_ExtKeyUsage  (ExtKeyUsage *);


/* OBJECT IDENTIFIER id-x509-ce-cRLDistributionPoints ::= { joint-iso-ccitt(2) ds(5) label-less(29) label-less(31) } */
extern ASN1EXP const heim_oid asn1_oid_id_x509_ce_cRLDistributionPoints;
#define ASN1_OID_ID_X509_CE_CRLDISTRIBUTIONPOINTS (&asn1_oid_id_x509_ce_cRLDistributionPoints)

/* OBJECT IDENTIFIER id-x509-ce-deltaCRLIndicator ::= { joint-iso-ccitt(2) ds(5) label-less(29) label-less(27) } */
extern ASN1EXP const heim_oid asn1_oid_id_x509_ce_deltaCRLIndicator;
#define ASN1_OID_ID_X509_CE_DELTACRLINDICATOR (&asn1_oid_id_x509_ce_deltaCRLIndicator)

/* OBJECT IDENTIFIER id-x509-ce-issuingDistributionPoint ::= { joint-iso-ccitt(2) ds(5) label-less(29) label-less(28) } */
extern ASN1EXP const heim_oid asn1_oid_id_x509_ce_issuingDistributionPoint;
#define ASN1_OID_ID_X509_CE_ISSUINGDISTRIBUTIONPOINT (&asn1_oid_id_x509_ce_issuingDistributionPoint)

/* OBJECT IDENTIFIER id-x509-ce-holdInstructionCode ::= { joint-iso-ccitt(2) ds(5) label-less(29) label-less(23) } */
extern ASN1EXP const heim_oid asn1_oid_id_x509_ce_holdInstructionCode;
#define ASN1_OID_ID_X509_CE_HOLDINSTRUCTIONCODE (&asn1_oid_id_x509_ce_holdInstructionCode)

/* OBJECT IDENTIFIER id-x509-ce-invalidityDate ::= { joint-iso-ccitt(2) ds(5) label-less(29) label-less(24) } */
extern ASN1EXP const heim_oid asn1_oid_id_x509_ce_invalidityDate;
#define ASN1_OID_ID_X509_CE_INVALIDITYDATE (&asn1_oid_id_x509_ce_invalidityDate)

/* OBJECT IDENTIFIER id-x509-ce-certificateIssuer ::= { joint-iso-ccitt(2) ds(5) label-less(29) label-less(29) } */
extern ASN1EXP const heim_oid asn1_oid_id_x509_ce_certificateIssuer;
#define ASN1_OID_ID_X509_CE_CERTIFICATEISSUER (&asn1_oid_id_x509_ce_certificateIssuer)

/* OBJECT IDENTIFIER id-x509-ce-inhibitAnyPolicy ::= { joint-iso-ccitt(2) ds(5) label-less(29) label-less(54) } */
extern ASN1EXP const heim_oid asn1_oid_id_x509_ce_inhibitAnyPolicy;
#define ASN1_OID_ID_X509_CE_INHIBITANYPOLICY (&asn1_oid_id_x509_ce_inhibitAnyPolicy)

/*
DistributionPointReasonFlags ::= BIT STRING {
  unused(0),
  keyCompromise(1),
  cACompromise(2),
  affiliationChanged(3),
  superseded(4),
  cessationOfOperation(5),
  certificateHold(6),
  privilegeWithdrawn(7),
  aACompromise(8)
}
*/

typedef struct DistributionPointReasonFlags {
  unsigned int unused:1;
  unsigned int keyCompromise:1;
  unsigned int cACompromise:1;
  unsigned int affiliationChanged:1;
  unsigned int superseded:1;
  unsigned int cessationOfOperation:1;
  unsigned int certificateHold:1;
  unsigned int privilegeWithdrawn:1;
  unsigned int aACompromise:1;
  unsigned int _unused9:1;
  unsigned int _unused10:1;
  unsigned int _unused11:1;
  unsigned int _unused12:1;
  unsigned int _unused13:1;
  unsigned int _unused14:1;
  unsigned int _unused15:1;
  unsigned int _unused16:1;
  unsigned int _unused17:1;
  unsigned int _unused18:1;
  unsigned int _unused19:1;
  unsigned int _unused20:1;
  unsigned int _unused21:1;
  unsigned int _unused22:1;
  unsigned int _unused23:1;
  unsigned int _unused24:1;
  unsigned int _unused25:1;
  unsigned int _unused26:1;
  unsigned int _unused27:1;
  unsigned int _unused28:1;
  unsigned int _unused29:1;
  unsigned int _unused30:1;
  unsigned int _unused31:1;
} DistributionPointReasonFlags;


unsigned DistributionPointReasonFlags2int(DistributionPointReasonFlags);
DistributionPointReasonFlags int2DistributionPointReasonFlags(unsigned);
const struct units * asn1_DistributionPointReasonFlags_units(void);
ASN1EXP int    ASN1CALL decode_DistributionPointReasonFlags(const unsigned char *, size_t, DistributionPointReasonFlags *, size_t *);
ASN1EXP int    ASN1CALL encode_DistributionPointReasonFlags(unsigned char *, size_t, const DistributionPointReasonFlags *, size_t *);
ASN1EXP size_t ASN1CALL length_DistributionPointReasonFlags(const DistributionPointReasonFlags *);
ASN1EXP int    ASN1CALL copy_DistributionPointReasonFlags  (const DistributionPointReasonFlags *, DistributionPointReasonFlags *);
ASN1EXP void   ASN1CALL free_DistributionPointReasonFlags  (DistributionPointReasonFlags *);


/*
DistributionPointName ::= CHOICE {
  fullName                  [0] IMPLICIT SEQUENCE OF GeneralName,
  nameRelativeToCRLIssuer   [1] RelativeDistinguishedName,
}
*/

typedef struct DistributionPointName {
  enum {
    choice_DistributionPointName_fullName = 1,
    choice_DistributionPointName_nameRelativeToCRLIssuer
  } element;
  union {
    struct DistributionPointName_fullName {
      unsigned int len;
      GeneralName *val;
    } fullName;
    RelativeDistinguishedName nameRelativeToCRLIssuer;
  } u;
} DistributionPointName;

ASN1EXP int    ASN1CALL decode_DistributionPointName(const unsigned char *, size_t, DistributionPointName *, size_t *);
ASN1EXP int    ASN1CALL encode_DistributionPointName(unsigned char *, size_t, const DistributionPointName *, size_t *);
ASN1EXP size_t ASN1CALL length_DistributionPointName(const DistributionPointName *);
ASN1EXP int    ASN1CALL copy_DistributionPointName  (const DistributionPointName *, DistributionPointName *);
ASN1EXP void   ASN1CALL free_DistributionPointName  (DistributionPointName *);


/*
DistributionPoint ::= SEQUENCE {
  distributionPoint   [0] IMPLICIT heim_any OPTIONAL,
  reasons             [1] IMPLICIT heim_any OPTIONAL,
  cRLIssuer           [2] IMPLICIT heim_any OPTIONAL,
}
*/

typedef struct DistributionPoint {
  heim_any *distributionPoint;
  heim_any *reasons;
  heim_any *cRLIssuer;
} DistributionPoint;

ASN1EXP int    ASN1CALL decode_DistributionPoint(const unsigned char *, size_t, DistributionPoint *, size_t *);
ASN1EXP int    ASN1CALL encode_DistributionPoint(unsigned char *, size_t, const DistributionPoint *, size_t *);
ASN1EXP size_t ASN1CALL length_DistributionPoint(const DistributionPoint *);
ASN1EXP int    ASN1CALL copy_DistributionPoint  (const DistributionPoint *, DistributionPoint *);
ASN1EXP void   ASN1CALL free_DistributionPoint  (DistributionPoint *);


/*
CRLDistributionPoints ::= SEQUENCE OF DistributionPoint
*/

typedef struct CRLDistributionPoints {
  unsigned int len;
  DistributionPoint *val;
} CRLDistributionPoints;

ASN1EXP int   ASN1CALL add_CRLDistributionPoints  (CRLDistributionPoints *, const DistributionPoint *);
ASN1EXP int   ASN1CALL remove_CRLDistributionPoints  (CRLDistributionPoints *, unsigned int);
ASN1EXP int    ASN1CALL decode_CRLDistributionPoints(const unsigned char *, size_t, CRLDistributionPoints *, size_t *);
ASN1EXP int    ASN1CALL encode_CRLDistributionPoints(unsigned char *, size_t, const CRLDistributionPoints *, size_t *);
ASN1EXP size_t ASN1CALL length_CRLDistributionPoints(const CRLDistributionPoints *);
ASN1EXP int    ASN1CALL copy_CRLDistributionPoints  (const CRLDistributionPoints *, CRLDistributionPoints *);
ASN1EXP void   ASN1CALL free_CRLDistributionPoints  (CRLDistributionPoints *);


/*
DSASigValue ::= SEQUENCE {
  r               INTEGER,
  s               INTEGER,
}
*/

typedef struct DSASigValue {
  heim_integer r;
  heim_integer s;
} DSASigValue;

ASN1EXP int    ASN1CALL decode_DSASigValue(const unsigned char *, size_t, DSASigValue *, size_t *);
ASN1EXP int    ASN1CALL encode_DSASigValue(unsigned char *, size_t, const DSASigValue *, size_t *);
ASN1EXP size_t ASN1CALL length_DSASigValue(const DSASigValue *);
ASN1EXP int    ASN1CALL copy_DSASigValue  (const DSASigValue *, DSASigValue *);
ASN1EXP void   ASN1CALL free_DSASigValue  (DSASigValue *);


/*
DSAPublicKey ::= INTEGER
*/

typedef heim_integer DSAPublicKey;

ASN1EXP int    ASN1CALL decode_DSAPublicKey(const unsigned char *, size_t, DSAPublicKey *, size_t *);
ASN1EXP int    ASN1CALL encode_DSAPublicKey(unsigned char *, size_t, const DSAPublicKey *, size_t *);
ASN1EXP size_t ASN1CALL length_DSAPublicKey(const DSAPublicKey *);
ASN1EXP int    ASN1CALL copy_DSAPublicKey  (const DSAPublicKey *, DSAPublicKey *);
ASN1EXP void   ASN1CALL free_DSAPublicKey  (DSAPublicKey *);


/*
DSAParams ::= SEQUENCE {
  p               INTEGER,
  q               INTEGER,
  g               INTEGER,
}
*/

typedef struct DSAParams {
  heim_integer p;
  heim_integer q;
  heim_integer g;
} DSAParams;

ASN1EXP int    ASN1CALL decode_DSAParams(const unsigned char *, size_t, DSAParams *, size_t *);
ASN1EXP int    ASN1CALL encode_DSAParams(unsigned char *, size_t, const DSAParams *, size_t *);
ASN1EXP size_t ASN1CALL length_DSAParams(const DSAParams *);
ASN1EXP int    ASN1CALL copy_DSAParams  (const DSAParams *, DSAParams *);
ASN1EXP void   ASN1CALL free_DSAParams  (DSAParams *);


/*
ECPoint ::= OCTET STRING
*/

typedef heim_octet_string ECPoint;

ASN1EXP int    ASN1CALL decode_ECPoint(const unsigned char *, size_t, ECPoint *, size_t *);
ASN1EXP int    ASN1CALL encode_ECPoint(unsigned char *, size_t, const ECPoint *, size_t *);
ASN1EXP size_t ASN1CALL length_ECPoint(const ECPoint *);
ASN1EXP int    ASN1CALL copy_ECPoint  (const ECPoint *, ECPoint *);
ASN1EXP void   ASN1CALL free_ECPoint  (ECPoint *);


/*
ECParameters ::= CHOICE {
  namedCurve        OBJECT IDENTIFIER,
}
*/

typedef struct ECParameters {
  enum {
    choice_ECParameters_namedCurve = 1
  } element;
  union {
    heim_oid namedCurve;
  } u;
} ECParameters;

ASN1EXP int    ASN1CALL decode_ECParameters(const unsigned char *, size_t, ECParameters *, size_t *);
ASN1EXP int    ASN1CALL encode_ECParameters(unsigned char *, size_t, const ECParameters *, size_t *);
ASN1EXP size_t ASN1CALL length_ECParameters(const ECParameters *);
ASN1EXP int    ASN1CALL copy_ECParameters  (const ECParameters *, ECParameters *);
ASN1EXP void   ASN1CALL free_ECParameters  (ECParameters *);


/*
ECDSA-Sig-Value ::= SEQUENCE {
  r               INTEGER,
  s               INTEGER,
}
*/

typedef struct ECDSA_Sig_Value {
  heim_integer r;
  heim_integer s;
} ECDSA_Sig_Value;

ASN1EXP int    ASN1CALL decode_ECDSA_Sig_Value(const unsigned char *, size_t, ECDSA_Sig_Value *, size_t *);
ASN1EXP int    ASN1CALL encode_ECDSA_Sig_Value(unsigned char *, size_t, const ECDSA_Sig_Value *, size_t *);
ASN1EXP size_t ASN1CALL length_ECDSA_Sig_Value(const ECDSA_Sig_Value *);
ASN1EXP int    ASN1CALL copy_ECDSA_Sig_Value  (const ECDSA_Sig_Value *, ECDSA_Sig_Value *);
ASN1EXP void   ASN1CALL free_ECDSA_Sig_Value  (ECDSA_Sig_Value *);


/*
RSAPublicKey ::= SEQUENCE {
  modulus          INTEGER,
  publicExponent   INTEGER,
}
*/

typedef struct RSAPublicKey {
  heim_integer modulus;
  heim_integer publicExponent;
} RSAPublicKey;

ASN1EXP int    ASN1CALL decode_RSAPublicKey(const unsigned char *, size_t, RSAPublicKey *, size_t *);
ASN1EXP int    ASN1CALL encode_RSAPublicKey(unsigned char *, size_t, const RSAPublicKey *, size_t *);
ASN1EXP size_t ASN1CALL length_RSAPublicKey(const RSAPublicKey *);
ASN1EXP int    ASN1CALL copy_RSAPublicKey  (const RSAPublicKey *, RSAPublicKey *);
ASN1EXP void   ASN1CALL free_RSAPublicKey  (RSAPublicKey *);


/*
RSAPrivateKey ::= SEQUENCE {
  version           INTEGER (0..-1),
  modulus           INTEGER,
  publicExponent    INTEGER,
  privateExponent   INTEGER,
  prime1            INTEGER,
  prime2            INTEGER,
  exponent1         INTEGER,
  exponent2         INTEGER,
  coefficient       INTEGER,
}
*/

typedef struct RSAPrivateKey {
  unsigned int version;
  heim_integer modulus;
  heim_integer publicExponent;
  heim_integer privateExponent;
  heim_integer prime1;
  heim_integer prime2;
  heim_integer exponent1;
  heim_integer exponent2;
  heim_integer coefficient;
} RSAPrivateKey;

ASN1EXP int    ASN1CALL decode_RSAPrivateKey(const unsigned char *, size_t, RSAPrivateKey *, size_t *);
ASN1EXP int    ASN1CALL encode_RSAPrivateKey(unsigned char *, size_t, const RSAPrivateKey *, size_t *);
ASN1EXP size_t ASN1CALL length_RSAPrivateKey(const RSAPrivateKey *);
ASN1EXP int    ASN1CALL copy_RSAPrivateKey  (const RSAPrivateKey *, RSAPrivateKey *);
ASN1EXP void   ASN1CALL free_RSAPrivateKey  (RSAPrivateKey *);


/*
DigestInfo ::= SEQUENCE {
  digestAlgorithm   AlgorithmIdentifier,
  digest            OCTET STRING,
}
*/

typedef struct DigestInfo {
  AlgorithmIdentifier digestAlgorithm;
  heim_octet_string digest;
} DigestInfo;

ASN1EXP int    ASN1CALL decode_DigestInfo(const unsigned char *, size_t, DigestInfo *, size_t *);
ASN1EXP int    ASN1CALL encode_DigestInfo(unsigned char *, size_t, const DigestInfo *, size_t *);
ASN1EXP size_t ASN1CALL length_DigestInfo(const DigestInfo *);
ASN1EXP int    ASN1CALL copy_DigestInfo  (const DigestInfo *, DigestInfo *);
ASN1EXP void   ASN1CALL free_DigestInfo  (DigestInfo *);


/*
TBSCRLCertList ::= SEQUENCE {
  version               Version OPTIONAL,
  signature             AlgorithmIdentifier,
  issuer                Name,
  thisUpdate            Time,
  nextUpdate            Time OPTIONAL,
  revokedCertificates   SEQUENCE OF SEQUENCE {
  userCertificate      CertificateSerialNumber,
  revocationDate       Time,
  crlEntryExtensions   Extensions OPTIONAL,
} OPTIONAL,
  crlExtensions         [0] Extensions OPTIONAL,
}
*/

typedef struct TBSCRLCertList {
  heim_octet_string _save;
  Version *version;
  AlgorithmIdentifier signature;
  Name issuer;
  Time thisUpdate;
  Time *nextUpdate;
  struct TBSCRLCertList_revokedCertificates {
    unsigned int len;
    struct TBSCRLCertList_revokedCertificates_val {
      CertificateSerialNumber userCertificate;
      Time revocationDate;
      Extensions *crlEntryExtensions;
    } *val;
  } *revokedCertificates;
  Extensions *crlExtensions;
} TBSCRLCertList;

ASN1EXP int    ASN1CALL decode_TBSCRLCertList(const unsigned char *, size_t, TBSCRLCertList *, size_t *);
ASN1EXP int    ASN1CALL encode_TBSCRLCertList(unsigned char *, size_t, const TBSCRLCertList *, size_t *);
ASN1EXP size_t ASN1CALL length_TBSCRLCertList(const TBSCRLCertList *);
ASN1EXP int    ASN1CALL copy_TBSCRLCertList  (const TBSCRLCertList *, TBSCRLCertList *);
ASN1EXP void   ASN1CALL free_TBSCRLCertList  (TBSCRLCertList *);


/*
CRLCertificateList ::= SEQUENCE {
  tbsCertList          TBSCRLCertList,
  signatureAlgorithm   AlgorithmIdentifier,
  signatureValue         BIT STRING {
  },
}
*/

typedef struct CRLCertificateList {
  TBSCRLCertList tbsCertList;
  AlgorithmIdentifier signatureAlgorithm;
  heim_bit_string signatureValue;
} CRLCertificateList;

ASN1EXP int    ASN1CALL decode_CRLCertificateList(const unsigned char *, size_t, CRLCertificateList *, size_t *);
ASN1EXP int    ASN1CALL encode_CRLCertificateList(unsigned char *, size_t, const CRLCertificateList *, size_t *);
ASN1EXP size_t ASN1CALL length_CRLCertificateList(const CRLCertificateList *);
ASN1EXP int    ASN1CALL copy_CRLCertificateList  (const CRLCertificateList *, CRLCertificateList *);
ASN1EXP void   ASN1CALL free_CRLCertificateList  (CRLCertificateList *);


/* OBJECT IDENTIFIER id-x509-ce-cRLNumber ::= { joint-iso-ccitt(2) ds(5) label-less(29) label-less(20) } */
extern ASN1EXP const heim_oid asn1_oid_id_x509_ce_cRLNumber;
#define ASN1_OID_ID_X509_CE_CRLNUMBER (&asn1_oid_id_x509_ce_cRLNumber)

/* OBJECT IDENTIFIER id-x509-ce-freshestCRL ::= { joint-iso-ccitt(2) ds(5) label-less(29) label-less(46) } */
extern ASN1EXP const heim_oid asn1_oid_id_x509_ce_freshestCRL;
#define ASN1_OID_ID_X509_CE_FRESHESTCRL (&asn1_oid_id_x509_ce_freshestCRL)

/* OBJECT IDENTIFIER id-x509-ce-cRLReason ::= { joint-iso-ccitt(2) ds(5) label-less(29) label-less(21) } */
extern ASN1EXP const heim_oid asn1_oid_id_x509_ce_cRLReason;
#define ASN1_OID_ID_X509_CE_CRLREASON (&asn1_oid_id_x509_ce_cRLReason)

/*
CRLReason ::= INTEGER {
  unspecified(0),
  keyCompromise(1),
  cACompromise(2),
  affiliationChanged(3),
  superseded(4),
  cessationOfOperation(5),
  certificateHold(6),
  removeFromCRL(8),
  privilegeWithdrawn(9),
  aACompromise(10)
}
*/

typedef enum CRLReason {
  unspecified = 0,
  keyCompromise = 1,
  cACompromise = 2,
  affiliationChanged = 3,
  superseded = 4,
  cessationOfOperation = 5,
  certificateHold = 6,
  removeFromCRL = 8,
  privilegeWithdrawn = 9,
  aACompromise = 10
} CRLReason;

ASN1EXP int    ASN1CALL decode_CRLReason(const unsigned char *, size_t, CRLReason *, size_t *);
ASN1EXP int    ASN1CALL encode_CRLReason(unsigned char *, size_t, const CRLReason *, size_t *);
ASN1EXP size_t ASN1CALL length_CRLReason(const CRLReason *);
ASN1EXP int    ASN1CALL copy_CRLReason  (const CRLReason *, CRLReason *);
ASN1EXP void   ASN1CALL free_CRLReason  (CRLReason *);


/*
PKIXXmppAddr ::= UTF8String
*/

typedef heim_utf8_string PKIXXmppAddr;

ASN1EXP int    ASN1CALL decode_PKIXXmppAddr(const unsigned char *, size_t, PKIXXmppAddr *, size_t *);
ASN1EXP int    ASN1CALL encode_PKIXXmppAddr(unsigned char *, size_t, const PKIXXmppAddr *, size_t *);
ASN1EXP size_t ASN1CALL length_PKIXXmppAddr(const PKIXXmppAddr *);
ASN1EXP int    ASN1CALL copy_PKIXXmppAddr  (const PKIXXmppAddr *, PKIXXmppAddr *);
ASN1EXP void   ASN1CALL free_PKIXXmppAddr  (PKIXXmppAddr *);


/* OBJECT IDENTIFIER id-pkix ::= { iso(1) identified-organization(3) dod(6) internet(1) security(5) mechanisms(5) pkix(7) } */
extern ASN1EXP const heim_oid asn1_oid_id_pkix;
#define ASN1_OID_ID_PKIX (&asn1_oid_id_pkix)

/* OBJECT IDENTIFIER id-pkix-on ::= { iso(1) identified-organization(3) dod(6) internet(1) security(5) mechanisms(5) pkix(7) label-less(8) } */
extern ASN1EXP const heim_oid asn1_oid_id_pkix_on;
#define ASN1_OID_ID_PKIX_ON (&asn1_oid_id_pkix_on)

/* OBJECT IDENTIFIER id-pkix-on-xmppAddr ::= { iso(1) identified-organization(3) dod(6) internet(1) security(5) mechanisms(5) pkix(7) label-less(8) label-less(5) } */
extern ASN1EXP const heim_oid asn1_oid_id_pkix_on_xmppAddr;
#define ASN1_OID_ID_PKIX_ON_XMPPADDR (&asn1_oid_id_pkix_on_xmppAddr)

/* OBJECT IDENTIFIER id-pkix-on-dnsSRV ::= { iso(1) identified-organization(3) dod(6) internet(1) security(5) mechanisms(5) pkix(7) label-less(8) label-less(7) } */
extern ASN1EXP const heim_oid asn1_oid_id_pkix_on_dnsSRV;
#define ASN1_OID_ID_PKIX_ON_DNSSRV (&asn1_oid_id_pkix_on_dnsSRV)

/* OBJECT IDENTIFIER id-pkix-kp ::= { iso(1) identified-organization(3) dod(6) internet(1) security(5) mechanisms(5) pkix(7) label-less(3) } */
extern ASN1EXP const heim_oid asn1_oid_id_pkix_kp;
#define ASN1_OID_ID_PKIX_KP (&asn1_oid_id_pkix_kp)

/* OBJECT IDENTIFIER id-pkix-kp-serverAuth ::= { iso(1) identified-organization(3) dod(6) internet(1) security(5) mechanisms(5) pkix(7) label-less(3) label-less(1) } */
extern ASN1EXP const heim_oid asn1_oid_id_pkix_kp_serverAuth;
#define ASN1_OID_ID_PKIX_KP_SERVERAUTH (&asn1_oid_id_pkix_kp_serverAuth)

/* OBJECT IDENTIFIER id-pkix-kp-clientAuth ::= { iso(1) identified-organization(3) dod(6) internet(1) security(5) mechanisms(5) pkix(7) label-less(3) label-less(2) } */
extern ASN1EXP const heim_oid asn1_oid_id_pkix_kp_clientAuth;
#define ASN1_OID_ID_PKIX_KP_CLIENTAUTH (&asn1_oid_id_pkix_kp_clientAuth)

/* OBJECT IDENTIFIER id-pkix-kp-emailProtection ::= { iso(1) identified-organization(3) dod(6) internet(1) security(5) mechanisms(5) pkix(7) label-less(3) label-less(4) } */
extern ASN1EXP const heim_oid asn1_oid_id_pkix_kp_emailProtection;
#define ASN1_OID_ID_PKIX_KP_EMAILPROTECTION (&asn1_oid_id_pkix_kp_emailProtection)

/* OBJECT IDENTIFIER id-pkix-kp-timeStamping ::= { iso(1) identified-organization(3) dod(6) internet(1) security(5) mechanisms(5) pkix(7) label-less(3) label-less(8) } */
extern ASN1EXP const heim_oid asn1_oid_id_pkix_kp_timeStamping;
#define ASN1_OID_ID_PKIX_KP_TIMESTAMPING (&asn1_oid_id_pkix_kp_timeStamping)

/* OBJECT IDENTIFIER id-pkix-kp-OCSPSigning ::= { iso(1) identified-organization(3) dod(6) internet(1) security(5) mechanisms(5) pkix(7) label-less(3) label-less(9) } */
extern ASN1EXP const heim_oid asn1_oid_id_pkix_kp_OCSPSigning;
#define ASN1_OID_ID_PKIX_KP_OCSPSIGNING (&asn1_oid_id_pkix_kp_OCSPSigning)

/* OBJECT IDENTIFIER id-pkix-pe ::= { iso(1) identified-organization(3) dod(6) internet(1) security(5) mechanisms(5) pkix(7) label-less(1) } */
extern ASN1EXP const heim_oid asn1_oid_id_pkix_pe;
#define ASN1_OID_ID_PKIX_PE (&asn1_oid_id_pkix_pe)

/* OBJECT IDENTIFIER id-pkix-pe-authorityInfoAccess ::= { iso(1) identified-organization(3) dod(6) internet(1) security(5) mechanisms(5) pkix(7) label-less(1) label-less(1) } */
extern ASN1EXP const heim_oid asn1_oid_id_pkix_pe_authorityInfoAccess;
#define ASN1_OID_ID_PKIX_PE_AUTHORITYINFOACCESS (&asn1_oid_id_pkix_pe_authorityInfoAccess)

/*
AccessDescription ::= SEQUENCE {
  accessMethod       OBJECT IDENTIFIER,
  accessLocation   GeneralName,
}
*/

typedef struct AccessDescription {
  heim_oid accessMethod;
  GeneralName accessLocation;
} AccessDescription;

ASN1EXP int    ASN1CALL decode_AccessDescription(const unsigned char *, size_t, AccessDescription *, size_t *);
ASN1EXP int    ASN1CALL encode_AccessDescription(unsigned char *, size_t, const AccessDescription *, size_t *);
ASN1EXP size_t ASN1CALL length_AccessDescription(const AccessDescription *);
ASN1EXP int    ASN1CALL copy_AccessDescription  (const AccessDescription *, AccessDescription *);
ASN1EXP void   ASN1CALL free_AccessDescription  (AccessDescription *);


/*
AuthorityInfoAccessSyntax ::= SEQUENCE OF AccessDescription
*/

typedef struct AuthorityInfoAccessSyntax {
  unsigned int len;
  AccessDescription *val;
} AuthorityInfoAccessSyntax;

ASN1EXP int    ASN1CALL decode_AuthorityInfoAccessSyntax(const unsigned char *, size_t, AuthorityInfoAccessSyntax *, size_t *);
ASN1EXP int    ASN1CALL encode_AuthorityInfoAccessSyntax(unsigned char *, size_t, const AuthorityInfoAccessSyntax *, size_t *);
ASN1EXP size_t ASN1CALL length_AuthorityInfoAccessSyntax(const AuthorityInfoAccessSyntax *);
ASN1EXP int    ASN1CALL copy_AuthorityInfoAccessSyntax  (const AuthorityInfoAccessSyntax *, AuthorityInfoAccessSyntax *);
ASN1EXP void   ASN1CALL free_AuthorityInfoAccessSyntax  (AuthorityInfoAccessSyntax *);


/* OBJECT IDENTIFIER id-pkix-pe-proxyCertInfo ::= { iso(1) identified-organization(3) dod(6) internet(1) security(5) mechanisms(5) pkix(7) label-less(1) label-less(14) } */
extern ASN1EXP const heim_oid asn1_oid_id_pkix_pe_proxyCertInfo;
#define ASN1_OID_ID_PKIX_PE_PROXYCERTINFO (&asn1_oid_id_pkix_pe_proxyCertInfo)

/* OBJECT IDENTIFIER id-pkix-ppl ::= { iso(1) identified-organization(3) dod(6) internet(1) security(5) mechanisms(5) pkix(7) label-less(21) } */
extern ASN1EXP const heim_oid asn1_oid_id_pkix_ppl;
#define ASN1_OID_ID_PKIX_PPL (&asn1_oid_id_pkix_ppl)

/* OBJECT IDENTIFIER id-pkix-ppl-anyLanguage ::= { iso(1) identified-organization(3) dod(6) internet(1) security(5) mechanisms(5) pkix(7) label-less(21) label-less(0) } */
extern ASN1EXP const heim_oid asn1_oid_id_pkix_ppl_anyLanguage;
#define ASN1_OID_ID_PKIX_PPL_ANYLANGUAGE (&asn1_oid_id_pkix_ppl_anyLanguage)

/* OBJECT IDENTIFIER id-pkix-ppl-inheritAll ::= { iso(1) identified-organization(3) dod(6) internet(1) security(5) mechanisms(5) pkix(7) label-less(21) label-less(1) } */
extern ASN1EXP const heim_oid asn1_oid_id_pkix_ppl_inheritAll;
#define ASN1_OID_ID_PKIX_PPL_INHERITALL (&asn1_oid_id_pkix_ppl_inheritAll)

/* OBJECT IDENTIFIER id-pkix-ppl-independent ::= { iso(1) identified-organization(3) dod(6) internet(1) security(5) mechanisms(5) pkix(7) label-less(21) label-less(2) } */
extern ASN1EXP const heim_oid asn1_oid_id_pkix_ppl_independent;
#define ASN1_OID_ID_PKIX_PPL_INDEPENDENT (&asn1_oid_id_pkix_ppl_independent)

/*
ProxyPolicy ::= SEQUENCE {
  policyLanguage     OBJECT IDENTIFIER,
  policy           OCTET STRING OPTIONAL,
}
*/

typedef struct ProxyPolicy {
  heim_oid policyLanguage;
  heim_octet_string *policy;
} ProxyPolicy;

ASN1EXP int    ASN1CALL decode_ProxyPolicy(const unsigned char *, size_t, ProxyPolicy *, size_t *);
ASN1EXP int    ASN1CALL encode_ProxyPolicy(unsigned char *, size_t, const ProxyPolicy *, size_t *);
ASN1EXP size_t ASN1CALL length_ProxyPolicy(const ProxyPolicy *);
ASN1EXP int    ASN1CALL copy_ProxyPolicy  (const ProxyPolicy *, ProxyPolicy *);
ASN1EXP void   ASN1CALL free_ProxyPolicy  (ProxyPolicy *);


/*
ProxyCertInfo ::= SEQUENCE {
  pCPathLenConstraint   INTEGER (0..-1) OPTIONAL,
  proxyPolicy           ProxyPolicy,
}
*/

typedef struct ProxyCertInfo {
  unsigned int *pCPathLenConstraint;
  ProxyPolicy proxyPolicy;
} ProxyCertInfo;

ASN1EXP int    ASN1CALL decode_ProxyCertInfo(const unsigned char *, size_t, ProxyCertInfo *, size_t *);
ASN1EXP int    ASN1CALL encode_ProxyCertInfo(unsigned char *, size_t, const ProxyCertInfo *, size_t *);
ASN1EXP size_t ASN1CALL length_ProxyCertInfo(const ProxyCertInfo *);
ASN1EXP int    ASN1CALL copy_ProxyCertInfo  (const ProxyCertInfo *, ProxyCertInfo *);
ASN1EXP void   ASN1CALL free_ProxyCertInfo  (ProxyCertInfo *);


/* OBJECT IDENTIFIER id-uspkicommon-card-id ::= { label-less(2) label-less(16) label-less(840) label-less(1) label-less(101) label-less(3) label-less(6) label-less(6) } */
extern ASN1EXP const heim_oid asn1_oid_id_uspkicommon_card_id;
#define ASN1_OID_ID_USPKICOMMON_CARD_ID (&asn1_oid_id_uspkicommon_card_id)

/* OBJECT IDENTIFIER id-uspkicommon-piv-interim ::= { label-less(2) label-less(16) label-less(840) label-less(1) label-less(101) label-less(3) label-less(6) label-less(9) label-less(1) } */
extern ASN1EXP const heim_oid asn1_oid_id_uspkicommon_piv_interim;
#define ASN1_OID_ID_USPKICOMMON_PIV_INTERIM (&asn1_oid_id_uspkicommon_piv_interim)

/* OBJECT IDENTIFIER id-netscape ::= { joint-iso-itu-t(2) country(16) us(840) organization(1) netscape(113730) } */
extern ASN1EXP const heim_oid asn1_oid_id_netscape;
#define ASN1_OID_ID_NETSCAPE (&asn1_oid_id_netscape)

/* OBJECT IDENTIFIER id-netscape-cert-comment ::= { joint-iso-itu-t(2) country(16) us(840) organization(1) netscape(113730) label-less(1) label-less(13) } */
extern ASN1EXP const heim_oid asn1_oid_id_netscape_cert_comment;
#define ASN1_OID_ID_NETSCAPE_CERT_COMMENT (&asn1_oid_id_netscape_cert_comment)

/* OBJECT IDENTIFIER id-ms-cert-enroll-domaincontroller ::= { label-less(1) label-less(3) label-less(6) label-less(1) label-less(4) label-less(1) label-less(311) label-less(20) label-less(2) } */
extern ASN1EXP const heim_oid asn1_oid_id_ms_cert_enroll_domaincontroller;
#define ASN1_OID_ID_MS_CERT_ENROLL_DOMAINCONTROLLER (&asn1_oid_id_ms_cert_enroll_domaincontroller)

/* OBJECT IDENTIFIER id-ms-client-authentication ::= { label-less(1) label-less(3) label-less(6) label-less(1) label-less(5) label-less(5) label-less(7) label-less(3) label-less(2) } */
extern ASN1EXP const heim_oid asn1_oid_id_ms_client_authentication;
#define ASN1_OID_ID_MS_CLIENT_AUTHENTICATION (&asn1_oid_id_ms_client_authentication)

#endif /* __rfc2459_asn1_h__ */
