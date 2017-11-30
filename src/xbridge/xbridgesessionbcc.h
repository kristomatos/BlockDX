//*****************************************************************************
//*****************************************************************************

#ifndef XBRIDGESESSIONBCC_H
#define XBRIDGESESSIONBCC_H

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

enum
{
    SIGHASH_FORKID = 0x40,
};

//*****************************************************************************
//*****************************************************************************
/**
 * @brief The XBridgeSessionBcc class
 */
class XBridgeSessionBcc
        : public XBridgeSession
{
public:
    /**
     * @brief XBridgeSessionBcc
     */
    XBridgeSessionBcc();

    /**
     * @brief XBridgeSessionBcc
     * @param wallet
     */
    XBridgeSessionBcc(const WalletParam &wallet);

    /**
     * @brief ~XBridgeSessionBcc
     */
    virtual ~XBridgeSessionBcc();

public:
    /**
     * @brief shared_from_this
     * @return
     */
    std::shared_ptr<XBridgeSessionBcc> shared_from_this()
    {
        return std::static_pointer_cast<XBridgeSessionBcc>(XBridgeSession::shared_from_this());
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
};//class XBridgeSessionBcc

/**
 * @brief XBridgeSessionBccPtr
 */
typedef std::shared_ptr<XBridgeSessionBcc> XBridgeSessionBccPtr;

#endif // XBRIDGESESSIONBCC_H
