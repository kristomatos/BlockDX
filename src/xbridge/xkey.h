// Copyright (c) 2009-2010 Satoshi Nakamoto
// Copyright (c) 2009-2012 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef XBRIDGE_BITCOIN_KEY_H
#define XBRIDGE_BITCOIN_KEY_H

#include "xpubkey.h"
#include "serialize.h"
#include "allocators.h"
#include "uint256.h"

#include <stdexcept>
#include <vector>

/**
 * secp256k1:
 * const unsigned int PRIVATE_KEY_SIZE = 279;
 * const unsigned int PUBLIC_KEY_SIZE  = 65;
 * const unsigned int SIGNATURE_SIZE   = 72;
 *
 * see www.keylength.com
 * script supports up to 75 for single byte push
 */

namespace xbridge
{

/**
 * secure_allocator is defined in allocators.h
 * CPrivKey is a serialized private key, with all parameters included (279 bytes)
 */
typedef std::vector<unsigned char, secure_allocator<unsigned char> > CPrivKey;


/**
 * @brief The CKey class An encapsulated private key
 */
class CKey
{
private:
    //! Whether this private key is valid. We check for correctness when modifying the key


    /**
     * @brief fValid data, so fValid should always correspond to the actual state.
     */
    bool fValid;


    /**
     * @brief fCompressed Whether the public key corresponding to this private key is (to be) compressed.
     */
    bool fCompressed;


    /**
     * @brief vch  The actual byte data
     */
    unsigned char vch[32];

    // static_assert(sizeof(vch) == 32, "vch must be 32 bytes in length to not break serialization");


    /**
     * @brief Check Check whether the 32-byte array pointed to be vch is valid keydata.
     * @param vch
     * @return
     */
    bool static Check(const unsigned char* vch);

public:

    /**
     * @brief CKey Construct an invalid private key.
     */
    CKey() : fValid(false), fCompressed(false)
    {
        // LockObject(vch);
    }


    /**
     * @brief CKey Copy constructor. This is necessary because of memlocking.
     * @param secret
     */
    CKey(const CKey& secret) : fValid(secret.fValid), fCompressed(secret.fCompressed)
    {
        // LockObject(vch);
        memcpy(vch, secret.vch, sizeof(vch));
    }



    /**
      *Destructor (again necessary because of memlocking).
      * */
    ~CKey()
    {
        // UnlockObject(vch);
    }

    /**
     * @brief operator ==
     * @param a
     * @param b
     * @return
     */
    friend bool operator==(const CKey &a, const CKey &b)
    {
        return a.fCompressed == b.fCompressed &&
            a.size() == b.size() &&
            memcmp(&a.vch[0], &b.vch[0], a.size()) == 0;
    }


    /**
     * @brief Set Initialize using begin and end iterators to byte data.
     * @param pbegin
     * @param pend
     * @param fCompressedIn
     */
    template <typename T>
    void Set(const T pbegin, const T pend, bool fCompressedIn)
    {
        if (pend - pbegin != sizeof(vch)) {
            fValid = false;
        } else if (Check(&pbegin[0])) {
            memcpy(vch, (unsigned char*)&pbegin[0], sizeof(vch));
            fValid = true;
            fCompressed = fCompressedIn;
        } else {
            fValid = false;
        }
    }


    /**
     * @brief size Simple read-only vector-like interface.
     * @return
     */
    unsigned int size() const { return (fValid ? sizeof(vch) : 0); }
    /**
     * @brief begin
     * @return
     */
    const unsigned char* begin() const { return vch; }

    /**
     * @brief end
     * @return
     */
    const unsigned char* end() const { return vch + size(); }


    /**
     * @brief IsValid Check whether this private key is valid.
     * @return
     */
    bool IsValid() const { return fValid; }


    /**
     * @brief IsCompressed Check whether the public key corresponding to this private key is (to be) compressed.
     * @return
     */
    bool IsCompressed() const { return fCompressed; }



    /**
     * @brief SetPrivKey Initialize from a CPrivKey (serialized OpenSSL private key data).
     * @param vchPrivKey
     * @param fCompressed
     * @return
     */
    bool SetPrivKey(const CPrivKey& vchPrivKey, bool fCompressed);



    /**
     * @brief MakeNewKey Generate a new private key using a cryptographic PRNG.
     * @param fCompressed
     */
    void MakeNewKey(bool fCompressed);

    /**
     * @brief GetPrivKey Convert the private key to a CPrivKey (serialized OpenSSL private key data).
     * This is expensive.
     * @return
     */
    CPrivKey GetPrivKey() const;

    /**
     * @brief GetPubKey Compute the public key from a private key.
     * This is expensive.
     * @return
     */
    CPubKey GetPubKey() const;

    /**
     * @brief Sign Create a DER-serialized signature.
     * The test_case parameter tweaks the deterministic nonce.
     * @param hash
     * @param vchSig
     * @param test_case
     * @return
     */
    bool Sign(const uint256& hash, std::vector<unsigned char> &vchSig, uint32_t test_case = 0) const;




    /**
     * @brief SignCompact -  Create a compact signature (65 bytes), which allows reconstructing the used public key.
     * The format is one header byte, followed by two times 32 bytes for the serialized r and s values.
     * The header byte: 0x1B = first key with even y, 0x1C = first key with odd y,
     *                  0x1D = second key with even y, 0x1E = second key with odd y,
     *                  add 0x04 for compressed keys.
     * @param hash
     * @param vchSig
     * @return
     */
    bool SignCompact(const uint256 &hash, std::vector<unsigned char> &vchSig) const;


    /**
     * @brief Derive - Derive BIP32 child key.
     * @param keyChild
     * @param ccChild
     * @param nChild
     * @param cc
     * @return
     */
    bool Derive(CKey &keyChild, ChainCode &ccChild, unsigned int nChild, const ChainCode &cc) const;

    /**
     * @brief VerifyPubKey - Verify thoroughly whether a private key and a public key match.
     * This is done using a different mechanism than just regenerating it.
     * @param vchPubKey
     * @return
     */
    bool VerifyPubKey(const CPubKey &vchPubKey) const;


    /**
     * @brief Load Load private key and check that public key matches.
     * @param privkey
     * @param vchPubKey
     * @param fSkipCheck
     * @return
     */
    bool Load(CPrivKey &privkey, CPubKey &vchPubKey, bool fSkipCheck);
};

/**
 * @brief The CExtKey struct
 */
struct CExtKey {

    /**
     * @brief nDepth
     */
    unsigned char nDepth;

    /**
     * @brief vchFingerprint
     */
    unsigned char vchFingerprint[4];

    /**
     * @brief nChild
     */
    unsigned int nChild;

    /**
     * @brief chaincode
     */
    ChainCode chaincode;

    /**
     * @brief key
     */
    CKey key;

    /**
     * @brief operator ==
     * @param a
     * @param b
     * @return
     */
    friend bool operator==(const CExtKey &a, const CExtKey &b)
    {
        return a.nDepth == b.nDepth &&
            memcmp(&a.vchFingerprint[0], &b.vchFingerprint[0], sizeof(a.vchFingerprint)) == 0 &&
            a.nChild == b.nChild &&
            a.chaincode == b.chaincode &&
            a.key == b.key;
    }

    /**
     * @brief Encode
     * @param code
     */
    void Encode(unsigned char code[BIP32_EXTKEY_SIZE]) const;

    /**
     * @brief Decode
     * @param code
     */
    void Decode(const unsigned char code[BIP32_EXTKEY_SIZE]);

    /**
     * @brief Derive
     * @param out
     * @param nChild
     * @return
     */
    bool Derive(CExtKey& out, unsigned int nChild) const;

    /**
     * @brief Neuter
     * @return
     */
    CExtPubKey Neuter() const;

    /**
     * @brief SetMaster
     * @param seed
     * @param nSeedLen
     */
    void SetMaster(const unsigned char* seed, unsigned int nSeedLen);

    /**
     * @brief Serialize
     * @param s
     * @param nType
     * @param nVersion
     */
    template <typename Stream>
    void Serialize(Stream &s, int nType, int nVersion) const
    {
        unsigned int len = BIP32_EXTKEY_SIZE;
        ::WriteCompactSize(s, len);
        unsigned char code[BIP32_EXTKEY_SIZE];
        Encode(code);
        s.write((const char *)&code[0], len);
    }

    /**
     * @brief Unserialize
     * @param s
     * @param nType
     * @param nVersion
     */
    template <typename Stream>
    void Unserialize(Stream &s, int nType, int nVersion)
    {
        unsigned int len = ::ReadCompactSize(s);
        unsigned char code[BIP32_EXTKEY_SIZE];
        s.read((char *)&code[0], len);
        Decode(code);
    }
};


/**
 * @brief ECC_Start  Initialize the elliptic curve support. May not be called twice without calling ECC_Stop first.
 */
void ECC_Start(void);



/**
 * @brief ECC_Stop Deinitialize the elliptic curve support. No-op if ECC_Start wasn't called first.
 */
void ECC_Stop(void);



/**
 * @brief ECC_InitSanityCheck Check that required EC support is available at runtime.
 * @return
 */
bool ECC_InitSanityCheck(void);

} // namespace xbridge

#endif // XBRIDGE_BITCOIN_KEY_H
