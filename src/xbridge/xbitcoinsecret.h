#ifndef XBITCOINSECRET_H
#define XBITCOINSECRET_H

#include "base58.h"
#include "xkey.h"

namespace xbridge
{

//******************************************************************************
//******************************************************************************
/**
 * @brief The CBitcoinSecret class
 */
class CBitcoinSecret : public CBase58Data
{
public:
    /**
     * @brief SetKey
     * @param vchSecret
     */
    void SetKey(const CKey& vchSecret);

    /**
     * @brief GetKey
     * @return
     */
    CKey GetKey();

    /**
     * @brief IsValid
     * @return
     */
    bool IsValid() const;

    /**
     * @brief SetString
     * @param pszSecret
     * @return
     */
    bool SetString(const char* pszSecret);

    /**
     * @brief SetString
     * @param strSecret
     * @return
     */
    bool SetString(const std::string& strSecret);

    /**
     * @brief CBitcoinSecret
     * @param vchSecret
     */
    CBitcoinSecret(const CKey& vchSecret) { SetKey(vchSecret); }
    /**
      * @brief CBitcoinSecret
      *
      */
    CBitcoinSecret() = default;
};

} // namespace xbridge

#endif // XBITCOINSECRET_H
