#ifndef XBRIDGESESSIONDCR_H
#define XBRIDGESESSIONDCR_H

#include "xbridge.h"
#include "xbridgesession.h"
#include "xbridgepacket.h"
#include "xbridgetransaction.h"
#include "xbridgewallet.h"
#include "FastDelegate.h"
#include "uint256.h"

#include <memory>
#include <set>
#include <boost/thread/mutex.hpp>
#include <boost/noncopyable.hpp>

//*****************************************************************************
//*****************************************************************************
/**
 * @brief The XBridgeSessionDcr class
 */
class XBridgeSessionDcr
        : public XBridgeSession
{
public:
    /**
     * @brief XBridgeSessionDcr
     */
    XBridgeSessionDcr();

    /**
     * @brief XBridgeSessionDcr
     * @param wallet
     */
    XBridgeSessionDcr(const WalletParam &wallet);

    /**
     * @brief ~XBridgeSessionDcr
     */
    virtual ~XBridgeSessionDcr();

public:
    /**
     * @brief shared_from_this
     * @return
     */
    std::shared_ptr<XBridgeSessionDcr> shared_from_this()
    {
        return std::static_pointer_cast<XBridgeSessionDcr>(XBridgeSession::shared_from_this());
    }

protected:

    /**
     * @brief toXAddr
     * @param addr
     * @return
     */
    std::vector<unsigned char> toXAddr(const std::string &addr) const;

    /**
     * @brief lockTime
     * @param role
     * @return
     */
    virtual uint32_t lockTime(const char role) const;

    /**
     * @brief createTransaction
     * @return
     */
    virtual xbridge::CTransactionPtr createTransaction() const;

    /**
     * @brief createTransaction
     * @param inputs
     * @param outputs
     * @param lockTime
     * @return
     */
    virtual xbridge::CTransactionPtr createTransaction(const std::vector<std::pair<std::string, int> > &inputs,
                                                       const std::vector<std::pair<CScript, double> > &outputs,
                                                       const uint32_t lockTime = 0) const;

    /**
     * @brief signTransaction
     * @param key
     * @param transaction
     * @param inputIdx
     * @param unlockScript
     * @param signature
     * @return
     */
    virtual bool signTransaction(const xbridge::CKey &key,
                                 const xbridge::CTransactionPtr &transaction,
                                 const uint32_t inputIdx,
                                 const CScript &unlockScript,
                                 std::vector<unsigned char> &signature);

private:
    /**
     * @brief DecodeBase58Check
     * @param psz
     * @param vchRet
     * @return
     */
    bool DecodeBase58Check(const char* psz, std::vector<unsigned char> &vchRet) const;
};//class XBridgeSessionDcr

/**
 * @brief XBridgeSessionDecPtr
 */
typedef std::shared_ptr<XBridgeSessionDcr> XBridgeSessionDecPtr;

#endif // XBRIDGESESSIONDCR_H
