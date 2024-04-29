/* Generated from /usr/src/crypto/heimdal/lib/hx509/ocsp.asn1 */
/* Do not edit */

#ifndef __ocsp_asn1_h__
#define __ocsp_asn1_h__

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
OCSPVersion ::= INTEGER {
  ocsp_v1(0)
}
*/

typedef enum OCSPVersion {
  ocsp_v1 = 0
} OCSPVersion;

ASN1EXP int    ASN1CALL decode_OCSPVersion(const unsigned char *, size_t, OCSPVersion *, size_t *);
ASN1EXP int    ASN1CALL encode_OCSPVersion(unsigned char *, size_t, const OCSPVersion *, size_t *);
ASN1EXP size_t ASN1CALL length_OCSPVersion(const OCSPVersion *);
ASN1EXP int    ASN1CALL copy_OCSPVersion  (const OCSPVersion *, OCSPVersion *);
ASN1EXP void   ASN1CALL free_OCSPVersion  (OCSPVersion *);


/*
OCSPCertStatus ::= CHOICE {
  good            [0] IMPLICIT   NULL,
  revoked         [1] IMPLICIT SEQUENCE {
    revocationTime     GeneralizedTime,
    revocationReason   [0] CRLReason OPTIONAL,
  },
  unknown         [2] IMPLICIT   NULL,
}
*/

typedef struct OCSPCertStatus {
  enum {
    choice_OCSPCertStatus_good = 1,
    choice_OCSPCertStatus_revoked,
    choice_OCSPCertStatus_unknown
  } element;
  union {
    int good;
    struct OCSPCertStatus_revoked {
      time_t revocationTime;
      CRLReason *revocationReason;
    } revoked;
    int unknown;
  } u;
} OCSPCertStatus;

ASN1EXP int    ASN1CALL decode_OCSPCertStatus(const unsigned char *, size_t, OCSPCertStatus *, size_t *);
ASN1EXP int    ASN1CALL encode_OCSPCertStatus(unsigned char *, size_t, const OCSPCertStatus *, size_t *);
ASN1EXP size_t ASN1CALL length_OCSPCertStatus(const OCSPCertStatus *);
ASN1EXP int    ASN1CALL copy_OCSPCertStatus  (const OCSPCertStatus *, OCSPCertStatus *);
ASN1EXP void   ASN1CALL free_OCSPCertStatus  (OCSPCertStatus *);


/*
OCSPCertID ::= SEQUENCE {
  hashAlgorithm    AlgorithmIdentifier,
  issuerNameHash   OCTET STRING,
  issuerKeyHash    OCTET STRING,
  serialNumber     CertificateSerialNumber,
}
*/

typedef struct OCSPCertID {
  AlgorithmIdentifier hashAlgorithm;
  heim_octet_string issuerNameHash;
  heim_octet_string issuerKeyHash;
  CertificateSerialNumber serialNumber;
} OCSPCertID;

ASN1EXP int    ASN1CALL decode_OCSPCertID(const unsigned char *, size_t, OCSPCertID *, size_t *);
ASN1EXP int    ASN1CALL encode_OCSPCertID(unsigned char *, size_t, const OCSPCertID *, size_t *);
ASN1EXP size_t ASN1CALL length_OCSPCertID(const OCSPCertID *);
ASN1EXP int    ASN1CALL copy_OCSPCertID  (const OCSPCertID *, OCSPCertID *);
ASN1EXP void   ASN1CALL free_OCSPCertID  (OCSPCertID *);


/*
OCSPSingleResponse ::= SEQUENCE {
  certID             OCSPCertID,
  certStatus         OCSPCertStatus,
  thisUpdate         GeneralizedTime,
  nextUpdate         [0] GeneralizedTime OPTIONAL,
  singleExtensions   [1] Extensions OPTIONAL,
}
*/

typedef struct OCSPSingleResponse {
  OCSPCertID certID;
  OCSPCertStatus certStatus;
  time_t thisUpdate;
  time_t *nextUpdate;
  Extensions *singleExtensions;
} OCSPSingleResponse;

ASN1EXP int    ASN1CALL decode_OCSPSingleResponse(const unsigned char *, size_t, OCSPSingleResponse *, size_t *);
ASN1EXP int    ASN1CALL encode_OCSPSingleResponse(unsigned char *, size_t, const OCSPSingleResponse *, size_t *);
ASN1EXP size_t ASN1CALL length_OCSPSingleResponse(const OCSPSingleResponse *);
ASN1EXP int    ASN1CALL copy_OCSPSingleResponse  (const OCSPSingleResponse *, OCSPSingleResponse *);
ASN1EXP void   ASN1CALL free_OCSPSingleResponse  (OCSPSingleResponse *);


/*
OCSPInnerRequest ::= SEQUENCE {
  reqCert                   OCSPCertID,
  singleRequestExtensions   [0] Extensions OPTIONAL,
}
*/

typedef struct OCSPInnerRequest {
  OCSPCertID reqCert;
  Extensions *singleRequestExtensions;
} OCSPInnerRequest;

ASN1EXP int    ASN1CALL decode_OCSPInnerRequest(const unsigned char *, size_t, OCSPInnerRequest *, size_t *);
ASN1EXP int    ASN1CALL encode_OCSPInnerRequest(unsigned char *, size_t, const OCSPInnerRequest *, size_t *);
ASN1EXP size_t ASN1CALL length_OCSPInnerRequest(const OCSPInnerRequest *);
ASN1EXP int    ASN1CALL copy_OCSPInnerRequest  (const OCSPInnerRequest *, OCSPInnerRequest *);
ASN1EXP void   ASN1CALL free_OCSPInnerRequest  (OCSPInnerRequest *);


/*
OCSPTBSRequest ::= SEQUENCE {
  version             [0] OCSPVersion OPTIONAL,
  requestorName       [1] GeneralName OPTIONAL,
  requestList         SEQUENCE OF OCSPInnerRequest,
  requestExtensions   [2] Extensions OPTIONAL,
}
*/

typedef struct OCSPTBSRequest {
  heim_octet_string _save;
  OCSPVersion *version;
  GeneralName *requestorName;
  struct OCSPTBSRequest_requestList {
    unsigned int len;
    OCSPInnerRequest *val;
  } requestList;
  Extensions *requestExtensions;
} OCSPTBSRequest;

ASN1EXP int    ASN1CALL decode_OCSPTBSRequest(const unsigned char *, size_t, OCSPTBSRequest *, size_t *);
ASN1EXP int    ASN1CALL encode_OCSPTBSRequest(unsigned char *, size_t, const OCSPTBSRequest *, size_t *);
ASN1EXP size_t ASN1CALL length_OCSPTBSRequest(const OCSPTBSRequest *);
ASN1EXP int    ASN1CALL copy_OCSPTBSRequest  (const OCSPTBSRequest *, OCSPTBSRequest *);
ASN1EXP void   ASN1CALL free_OCSPTBSRequest  (OCSPTBSRequest *);


/*
OCSPSignature ::= SEQUENCE {
  signatureAlgorithm   AlgorithmIdentifier,
  signature              BIT STRING {
  },
  certs                [0] SEQUENCE OF Certificate OPTIONAL,
}
*/

typedef struct OCSPSignature {
  AlgorithmIdentifier signatureAlgorithm;
  heim_bit_string signature;
  struct OCSPSignature_certs {
    unsigned int len;
    Certificate *val;
  } *certs;
} OCSPSignature;

ASN1EXP int    ASN1CALL decode_OCSPSignature(const unsigned char *, size_t, OCSPSignature *, size_t *);
ASN1EXP int    ASN1CALL encode_OCSPSignature(unsigned char *, size_t, const OCSPSignature *, size_t *);
ASN1EXP size_t ASN1CALL length_OCSPSignature(const OCSPSignature *);
ASN1EXP int    ASN1CALL copy_OCSPSignature  (const OCSPSignature *, OCSPSignature *);
ASN1EXP void   ASN1CALL free_OCSPSignature  (OCSPSignature *);


/*
OCSPRequest ::= SEQUENCE {
  tbsRequest          OCSPTBSRequest,
  optionalSignature   [0] OCSPSignature OPTIONAL,
}
*/

typedef struct OCSPRequest {
  OCSPTBSRequest tbsRequest;
  OCSPSignature *optionalSignature;
} OCSPRequest;

ASN1EXP int    ASN1CALL decode_OCSPRequest(const unsigned char *, size_t, OCSPRequest *, size_t *);
ASN1EXP int    ASN1CALL encode_OCSPRequest(unsigned char *, size_t, const OCSPRequest *, size_t *);
ASN1EXP size_t ASN1CALL length_OCSPRequest(const OCSPRequest *);
ASN1EXP int    ASN1CALL copy_OCSPRequest  (const OCSPRequest *, OCSPRequest *);
ASN1EXP void   ASN1CALL free_OCSPRequest  (OCSPRequest *);


/*
OCSPResponseBytes ::= SEQUENCE {
  responseType      OBJECT IDENTIFIER,
  response        OCTET STRING,
}
*/

typedef struct OCSPResponseBytes {
  heim_oid responseType;
  heim_octet_string response;
} OCSPResponseBytes;

ASN1EXP int    ASN1CALL decode_OCSPResponseBytes(const unsigned char *, size_t, OCSPResponseBytes *, size_t *);
ASN1EXP int    ASN1CALL encode_OCSPResponseBytes(unsigned char *, size_t, const OCSPResponseBytes *, size_t *);
ASN1EXP size_t ASN1CALL length_OCSPResponseBytes(const OCSPResponseBytes *);
ASN1EXP int    ASN1CALL copy_OCSPResponseBytes  (const OCSPResponseBytes *, OCSPResponseBytes *);
ASN1EXP void   ASN1CALL free_OCSPResponseBytes  (OCSPResponseBytes *);


/*
OCSPResponseStatus ::= INTEGER {
  successful(0),
  malformedRequest(1),
  internalError(2),
  tryLater(3),
  sigRequired(5),
  unauthorized(6)
}
*/

typedef enum OCSPResponseStatus {
  successful = 0,
  malformedRequest = 1,
  internalError = 2,
  tryLater = 3,
  sigRequired = 5,
  unauthorized = 6
} OCSPResponseStatus;

ASN1EXP int    ASN1CALL decode_OCSPResponseStatus(const unsigned char *, size_t, OCSPResponseStatus *, size_t *);
ASN1EXP int    ASN1CALL encode_OCSPResponseStatus(unsigned char *, size_t, const OCSPResponseStatus *, size_t *);
ASN1EXP size_t ASN1CALL length_OCSPResponseStatus(const OCSPResponseStatus *);
ASN1EXP int    ASN1CALL copy_OCSPResponseStatus  (const OCSPResponseStatus *, OCSPResponseStatus *);
ASN1EXP void   ASN1CALL free_OCSPResponseStatus  (OCSPResponseStatus *);


/*
OCSPResponse ::= SEQUENCE {
  responseStatus   OCSPResponseStatus,
  responseBytes    [0] OCSPResponseBytes OPTIONAL,
}
*/

typedef struct OCSPResponse {
  OCSPResponseStatus responseStatus;
  OCSPResponseBytes *responseBytes;
} OCSPResponse;

ASN1EXP int    ASN1CALL decode_OCSPResponse(const unsigned char *, size_t, OCSPResponse *, size_t *);
ASN1EXP int    ASN1CALL encode_OCSPResponse(unsigned char *, size_t, const OCSPResponse *, size_t *);
ASN1EXP size_t ASN1CALL length_OCSPResponse(const OCSPResponse *);
ASN1EXP int    ASN1CALL copy_OCSPResponse  (const OCSPResponse *, OCSPResponse *);
ASN1EXP void   ASN1CALL free_OCSPResponse  (OCSPResponse *);


/*
OCSPKeyHash ::= OCTET STRING
*/

typedef heim_octet_string OCSPKeyHash;

ASN1EXP int    ASN1CALL decode_OCSPKeyHash(const unsigned char *, size_t, OCSPKeyHash *, size_t *);
ASN1EXP int    ASN1CALL encode_OCSPKeyHash(unsigned char *, size_t, const OCSPKeyHash *, size_t *);
ASN1EXP size_t ASN1CALL length_OCSPKeyHash(const OCSPKeyHash *);
ASN1EXP int    ASN1CALL copy_OCSPKeyHash  (const OCSPKeyHash *, OCSPKeyHash *);
ASN1EXP void   ASN1CALL free_OCSPKeyHash  (OCSPKeyHash *);


/*
OCSPResponderID ::= CHOICE {
  byName          [1] Name,
  byKey           [2] OCSPKeyHash,
}
*/

typedef struct OCSPResponderID {
  enum {
    choice_OCSPResponderID_byName = 1,
    choice_OCSPResponderID_byKey
  } element;
  union {
    Name byName;
    OCSPKeyHash byKey;
  } u;
} OCSPResponderID;

ASN1EXP int    ASN1CALL decode_OCSPResponderID(const unsigned char *, size_t, OCSPResponderID *, size_t *);
ASN1EXP int    ASN1CALL encode_OCSPResponderID(unsigned char *, size_t, const OCSPResponderID *, size_t *);
ASN1EXP size_t ASN1CALL length_OCSPResponderID(const OCSPResponderID *);
ASN1EXP int    ASN1CALL copy_OCSPResponderID  (const OCSPResponderID *, OCSPResponderID *);
ASN1EXP void   ASN1CALL free_OCSPResponderID  (OCSPResponderID *);


/*
OCSPResponseData ::= SEQUENCE {
  version              [0] OCSPVersion OPTIONAL,
  responderID          OCSPResponderID,
  producedAt           GeneralizedTime,
  responses            SEQUENCE OF OCSPSingleResponse,
  responseExtensions   [1] Extensions OPTIONAL,
}
*/

typedef struct OCSPResponseData {
  heim_octet_string _save;
  OCSPVersion *version;
  OCSPResponderID responderID;
  time_t producedAt;
  struct OCSPResponseData_responses {
    unsigned int len;
    OCSPSingleResponse *val;
  } responses;
  Extensions *responseExtensions;
} OCSPResponseData;

ASN1EXP int    ASN1CALL decode_OCSPResponseData(const unsigned char *, size_t, OCSPResponseData *, size_t *);
ASN1EXP int    ASN1CALL encode_OCSPResponseData(unsigned char *, size_t, const OCSPResponseData *, size_t *);
ASN1EXP size_t ASN1CALL length_OCSPResponseData(const OCSPResponseData *);
ASN1EXP int    ASN1CALL copy_OCSPResponseData  (const OCSPResponseData *, OCSPResponseData *);
ASN1EXP void   ASN1CALL free_OCSPResponseData  (OCSPResponseData *);


/*
OCSPBasicOCSPResponse ::= SEQUENCE {
  tbsResponseData      OCSPResponseData,
  signatureAlgorithm   AlgorithmIdentifier,
  signature              BIT STRING {
  },
  certs                [0] SEQUENCE OF Certificate OPTIONAL,
}
*/

typedef struct OCSPBasicOCSPResponse {
  OCSPResponseData tbsResponseData;
  AlgorithmIdentifier signatureAlgorithm;
  heim_bit_string signature;
  struct OCSPBasicOCSPResponse_certs {
    unsigned int len;
    Certificate *val;
  } *certs;
} OCSPBasicOCSPResponse;

ASN1EXP int    ASN1CALL decode_OCSPBasicOCSPResponse(const unsigned char *, size_t, OCSPBasicOCSPResponse *, size_t *);
ASN1EXP int    ASN1CALL encode_OCSPBasicOCSPResponse(unsigned char *, size_t, const OCSPBasicOCSPResponse *, size_t *);
ASN1EXP size_t ASN1CALL length_OCSPBasicOCSPResponse(const OCSPBasicOCSPResponse *);
ASN1EXP int    ASN1CALL copy_OCSPBasicOCSPResponse  (const OCSPBasicOCSPResponse *, OCSPBasicOCSPResponse *);
ASN1EXP void   ASN1CALL free_OCSPBasicOCSPResponse  (OCSPBasicOCSPResponse *);


/* OBJECT IDENTIFIER id-pkix-ocsp ::= { iso(1) identified-organization(3) dod(6) internet(1) security(5) mechanisms(5) pkix(7) pkix-ad(48) label-less(1) } */
extern ASN1EXP const heim_oid asn1_oid_id_pkix_ocsp;
#define ASN1_OID_ID_PKIX_OCSP (&asn1_oid_id_pkix_ocsp)

/* OBJECT IDENTIFIER id-pkix-ocsp-basic ::= { iso(1) identified-organization(3) dod(6) internet(1) security(5) mechanisms(5) pkix(7) pkix-ad(48) label-less(1) label-less(1) } */
extern ASN1EXP const heim_oid asn1_oid_id_pkix_ocsp_basic;
#define ASN1_OID_ID_PKIX_OCSP_BASIC (&asn1_oid_id_pkix_ocsp_basic)

/* OBJECT IDENTIFIER id-pkix-ocsp-nonce ::= { iso(1) identified-organization(3) dod(6) internet(1) security(5) mechanisms(5) pkix(7) pkix-ad(48) label-less(1) label-less(2) } */
extern ASN1EXP const heim_oid asn1_oid_id_pkix_ocsp_nonce;
#define ASN1_OID_ID_PKIX_OCSP_NONCE (&asn1_oid_id_pkix_ocsp_nonce)

#endif /* __ocsp_asn1_h__ */
