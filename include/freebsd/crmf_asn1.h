/* Generated from /usr/src/crypto/heimdal/lib/hx509/crmf.asn1 */
/* Do not edit */

#ifndef __crmf_asn1_h__
#define __crmf_asn1_h__

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
CRMFRDNSequence ::= SEQUENCE OF RelativeDistinguishedName
*/

typedef struct CRMFRDNSequence {
  unsigned int len;
  RelativeDistinguishedName *val;
} CRMFRDNSequence;

ASN1EXP int    ASN1CALL decode_CRMFRDNSequence(const unsigned char *, size_t, CRMFRDNSequence *, size_t *);
ASN1EXP int    ASN1CALL encode_CRMFRDNSequence(unsigned char *, size_t, const CRMFRDNSequence *, size_t *);
ASN1EXP size_t ASN1CALL length_CRMFRDNSequence(const CRMFRDNSequence *);
ASN1EXP int    ASN1CALL copy_CRMFRDNSequence  (const CRMFRDNSequence *, CRMFRDNSequence *);
ASN1EXP void   ASN1CALL free_CRMFRDNSequence  (CRMFRDNSequence *);


/*
Controls ::= SEQUENCE OF AttributeTypeAndValue
*/

typedef struct Controls {
  unsigned int len;
  AttributeTypeAndValue *val;
} Controls;

ASN1EXP int    ASN1CALL decode_Controls(const unsigned char *, size_t, Controls *, size_t *);
ASN1EXP int    ASN1CALL encode_Controls(unsigned char *, size_t, const Controls *, size_t *);
ASN1EXP size_t ASN1CALL length_Controls(const Controls *);
ASN1EXP int    ASN1CALL copy_Controls  (const Controls *, Controls *);
ASN1EXP void   ASN1CALL free_Controls  (Controls *);


/*
POPOSigningKey ::= SEQUENCE {
  poposkInput           [0] IMPLICIT POPOSigningKeyInput OPTIONAL,
  algorithmIdentifier   AlgorithmIdentifier,
  signature               BIT STRING {
  },
}
*/

typedef struct POPOSigningKey {
  POPOSigningKeyInput *poposkInput;
  AlgorithmIdentifier algorithmIdentifier;
  heim_bit_string signature;
} POPOSigningKey;

ASN1EXP int    ASN1CALL decode_POPOSigningKey(const unsigned char *, size_t, POPOSigningKey *, size_t *);
ASN1EXP int    ASN1CALL encode_POPOSigningKey(unsigned char *, size_t, const POPOSigningKey *, size_t *);
ASN1EXP size_t ASN1CALL length_POPOSigningKey(const POPOSigningKey *);
ASN1EXP int    ASN1CALL copy_POPOSigningKey  (const POPOSigningKey *, POPOSigningKey *);
ASN1EXP void   ASN1CALL free_POPOSigningKey  (POPOSigningKey *);


/*
PKMACValue ::= SEQUENCE {
  algId           AlgorithmIdentifier,
  value             BIT STRING {
  },
}
*/

typedef struct PKMACValue {
  AlgorithmIdentifier algId;
  heim_bit_string value;
} PKMACValue;

ASN1EXP int    ASN1CALL decode_PKMACValue(const unsigned char *, size_t, PKMACValue *, size_t *);
ASN1EXP int    ASN1CALL encode_PKMACValue(unsigned char *, size_t, const PKMACValue *, size_t *);
ASN1EXP size_t ASN1CALL length_PKMACValue(const PKMACValue *);
ASN1EXP int    ASN1CALL copy_PKMACValue  (const PKMACValue *, PKMACValue *);
ASN1EXP void   ASN1CALL free_PKMACValue  (PKMACValue *);


/*
POPOSigningKeyInput ::= SEQUENCE {
  authInfo        CHOICE {
    sender          [0] IMPLICIT GeneralName,
    publicKeyMAC    PKMACValue,
  },
  publicKey       SubjectPublicKeyInfo,
}
*/

typedef struct POPOSigningKeyInput {
  struct POPOSigningKeyInput_authInfo {
    enum {
      choice_POPOSigningKeyInput_authInfo_sender = 1,
      choice_POPOSigningKeyInput_authInfo_publicKeyMAC
    } element;
    union {
      GeneralName sender;
      PKMACValue publicKeyMAC;
    } u;
  } authInfo;
  SubjectPublicKeyInfo publicKey;
} POPOSigningKeyInput;

ASN1EXP int    ASN1CALL decode_POPOSigningKeyInput(const unsigned char *, size_t, POPOSigningKeyInput *, size_t *);
ASN1EXP int    ASN1CALL encode_POPOSigningKeyInput(unsigned char *, size_t, const POPOSigningKeyInput *, size_t *);
ASN1EXP size_t ASN1CALL length_POPOSigningKeyInput(const POPOSigningKeyInput *);
ASN1EXP int    ASN1CALL copy_POPOSigningKeyInput  (const POPOSigningKeyInput *, POPOSigningKeyInput *);
ASN1EXP void   ASN1CALL free_POPOSigningKeyInput  (POPOSigningKeyInput *);


/*
PBMParameter ::= SEQUENCE {
  salt             OCTET STRING,
  owf              AlgorithmIdentifier,
  iterationCount   INTEGER,
  mac              AlgorithmIdentifier,
}
*/

typedef struct PBMParameter {
  heim_octet_string salt;
  AlgorithmIdentifier owf;
  heim_integer iterationCount;
  AlgorithmIdentifier mac;
} PBMParameter;

ASN1EXP int    ASN1CALL decode_PBMParameter(const unsigned char *, size_t, PBMParameter *, size_t *);
ASN1EXP int    ASN1CALL encode_PBMParameter(unsigned char *, size_t, const PBMParameter *, size_t *);
ASN1EXP size_t ASN1CALL length_PBMParameter(const PBMParameter *);
ASN1EXP int    ASN1CALL copy_PBMParameter  (const PBMParameter *, PBMParameter *);
ASN1EXP void   ASN1CALL free_PBMParameter  (PBMParameter *);


/*
SubsequentMessage ::= INTEGER {
  encrCert(0),
  challengeResp(1)
}
*/

typedef enum SubsequentMessage {
  encrCert = 0,
  challengeResp = 1
} SubsequentMessage;

ASN1EXP int    ASN1CALL decode_SubsequentMessage(const unsigned char *, size_t, SubsequentMessage *, size_t *);
ASN1EXP int    ASN1CALL encode_SubsequentMessage(unsigned char *, size_t, const SubsequentMessage *, size_t *);
ASN1EXP size_t ASN1CALL length_SubsequentMessage(const SubsequentMessage *);
ASN1EXP int    ASN1CALL copy_SubsequentMessage  (const SubsequentMessage *, SubsequentMessage *);
ASN1EXP void   ASN1CALL free_SubsequentMessage  (SubsequentMessage *);


/*
POPOPrivKey ::= CHOICE {
  thisMessage         [0]   BIT STRING {
  },
  subsequentMessage   [1] IMPLICIT SubsequentMessage,
  dhMAC               [2]   BIT STRING {
  },
  agreeMAC            [3] IMPLICIT PKMACValue,
  encryptedKey        [4] heim_any,
}
*/

typedef struct POPOPrivKey {
  enum {
    choice_POPOPrivKey_thisMessage = 1,
    choice_POPOPrivKey_subsequentMessage,
    choice_POPOPrivKey_dhMAC,
    choice_POPOPrivKey_agreeMAC,
    choice_POPOPrivKey_encryptedKey
  } element;
  union {
    heim_bit_string thisMessage;
    SubsequentMessage subsequentMessage;
    heim_bit_string dhMAC;
    PKMACValue agreeMAC;
    heim_any encryptedKey;
  } u;
} POPOPrivKey;

ASN1EXP int    ASN1CALL decode_POPOPrivKey(const unsigned char *, size_t, POPOPrivKey *, size_t *);
ASN1EXP int    ASN1CALL encode_POPOPrivKey(unsigned char *, size_t, const POPOPrivKey *, size_t *);
ASN1EXP size_t ASN1CALL length_POPOPrivKey(const POPOPrivKey *);
ASN1EXP int    ASN1CALL copy_POPOPrivKey  (const POPOPrivKey *, POPOPrivKey *);
ASN1EXP void   ASN1CALL free_POPOPrivKey  (POPOPrivKey *);


/*
ProofOfPossession ::= CHOICE {
  raVerified        [0]   NULL,
  signature         [1] POPOSigningKey,
  keyEncipherment   [2] POPOPrivKey,
  keyAgreement      [3] POPOPrivKey,
}
*/

typedef struct ProofOfPossession {
  enum {
    choice_ProofOfPossession_raVerified = 1,
    choice_ProofOfPossession_signature,
    choice_ProofOfPossession_keyEncipherment,
    choice_ProofOfPossession_keyAgreement
  } element;
  union {
    int raVerified;
    POPOSigningKey signature;
    POPOPrivKey keyEncipherment;
    POPOPrivKey keyAgreement;
  } u;
} ProofOfPossession;

ASN1EXP int    ASN1CALL decode_ProofOfPossession(const unsigned char *, size_t, ProofOfPossession *, size_t *);
ASN1EXP int    ASN1CALL encode_ProofOfPossession(unsigned char *, size_t, const ProofOfPossession *, size_t *);
ASN1EXP size_t ASN1CALL length_ProofOfPossession(const ProofOfPossession *);
ASN1EXP int    ASN1CALL copy_ProofOfPossession  (const ProofOfPossession *, ProofOfPossession *);
ASN1EXP void   ASN1CALL free_ProofOfPossession  (ProofOfPossession *);


/*
CertTemplate ::= SEQUENCE {
  version         [0] INTEGER OPTIONAL,
  serialNumber    [1] INTEGER OPTIONAL,
  signingAlg      [2] SEQUENCE {
    algorithm           OBJECT IDENTIFIER,
    parameters      heim_any OPTIONAL,
  } OPTIONAL,
  issuer          [3] IMPLICIT CHOICE {
    rdnSequence     CRMFRDNSequence,
  } OPTIONAL,
  validity        [4] SEQUENCE {
    notBefore       [0] Time OPTIONAL,
    notAfter        [1] Time OPTIONAL,
  } OPTIONAL,
  subject         [5] IMPLICIT CHOICE {
    rdnSequence     CRMFRDNSequence,
  } OPTIONAL,
  publicKey       [6] IMPLICIT SEQUENCE {
    algorithm          AlgorithmIdentifier,
    subjectPublicKey       BIT STRING {
    } OPTIONAL,
  } OPTIONAL,
  issuerUID       [7] IMPLICIT   BIT STRING {
  } OPTIONAL,
  subjectUID      [8] IMPLICIT   BIT STRING {
  } OPTIONAL,
  extensions      [9] IMPLICIT SEQUENCE OF Extension OPTIONAL,
}
*/

typedef struct CertTemplate {
  heim_integer *version;
  heim_integer *serialNumber;
  struct CertTemplate_signingAlg {
    heim_oid algorithm;
    heim_any *parameters;
  } *signingAlg;
  struct CertTemplate_issuer {
    enum {
      choice_CertTemplate_issuer_rdnSequence = 1
    } element;
    union {
      CRMFRDNSequence rdnSequence;
    } u;
  } *issuer;
  struct CertTemplate_validity {
    Time *notBefore;
    Time *notAfter;
  } *validity;
  struct CertTemplate_subject {
    enum {
      choice_CertTemplate_subject_rdnSequence = 1
    } element;
    union {
      CRMFRDNSequence rdnSequence;
    } u;
  } *subject;
  struct CertTemplate_publicKey {
    AlgorithmIdentifier algorithm;
    heim_bit_string *subjectPublicKey;
  } *publicKey;
  heim_bit_string *issuerUID;
  heim_bit_string *subjectUID;
  struct CertTemplate_extensions {
    unsigned int len;
    Extension *val;
  } *extensions;
} CertTemplate;

ASN1EXP int    ASN1CALL decode_CertTemplate(const unsigned char *, size_t, CertTemplate *, size_t *);
ASN1EXP int    ASN1CALL encode_CertTemplate(unsigned char *, size_t, const CertTemplate *, size_t *);
ASN1EXP size_t ASN1CALL length_CertTemplate(const CertTemplate *);
ASN1EXP int    ASN1CALL copy_CertTemplate  (const CertTemplate *, CertTemplate *);
ASN1EXP void   ASN1CALL free_CertTemplate  (CertTemplate *);


/*
CertRequest ::= SEQUENCE {
  certReqId       INTEGER,
  certTemplate    CertTemplate,
  controls        Controls OPTIONAL,
}
*/

typedef struct CertRequest {
  heim_integer certReqId;
  CertTemplate certTemplate;
  Controls *controls;
} CertRequest;

ASN1EXP int    ASN1CALL decode_CertRequest(const unsigned char *, size_t, CertRequest *, size_t *);
ASN1EXP int    ASN1CALL encode_CertRequest(unsigned char *, size_t, const CertRequest *, size_t *);
ASN1EXP size_t ASN1CALL length_CertRequest(const CertRequest *);
ASN1EXP int    ASN1CALL copy_CertRequest  (const CertRequest *, CertRequest *);
ASN1EXP void   ASN1CALL free_CertRequest  (CertRequest *);


/*
CertReqMsg ::= SEQUENCE {
  certReq         CertRequest,
  popo            ProofOfPossession OPTIONAL,
  regInfo         SEQUENCE OF AttributeTypeAndValue OPTIONAL,
}
*/

typedef struct CertReqMsg {
  CertRequest certReq;
  ProofOfPossession *popo;
  struct CertReqMsg_regInfo {
    unsigned int len;
    AttributeTypeAndValue *val;
  } *regInfo;
} CertReqMsg;

ASN1EXP int    ASN1CALL decode_CertReqMsg(const unsigned char *, size_t, CertReqMsg *, size_t *);
ASN1EXP int    ASN1CALL encode_CertReqMsg(unsigned char *, size_t, const CertReqMsg *, size_t *);
ASN1EXP size_t ASN1CALL length_CertReqMsg(const CertReqMsg *);
ASN1EXP int    ASN1CALL copy_CertReqMsg  (const CertReqMsg *, CertReqMsg *);
ASN1EXP void   ASN1CALL free_CertReqMsg  (CertReqMsg *);


/*
CertReqMessages ::= SEQUENCE OF CertReqMsg
*/

typedef struct CertReqMessages {
  unsigned int len;
  CertReqMsg *val;
} CertReqMessages;

ASN1EXP int    ASN1CALL decode_CertReqMessages(const unsigned char *, size_t, CertReqMessages *, size_t *);
ASN1EXP int    ASN1CALL encode_CertReqMessages(unsigned char *, size_t, const CertReqMessages *, size_t *);
ASN1EXP size_t ASN1CALL length_CertReqMessages(const CertReqMessages *);
ASN1EXP int    ASN1CALL copy_CertReqMessages  (const CertReqMessages *, CertReqMessages *);
ASN1EXP void   ASN1CALL free_CertReqMessages  (CertReqMessages *);


#endif /* __crmf_asn1_h__ */
