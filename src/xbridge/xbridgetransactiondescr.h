#ifndef XBRIDGETRANSACTIONDESCR
#define XBRIDGETRANSACTIONDESCR

// #include "uint256.h"
#include "base58.h"
#include "xbridgepacket.h"
#include "xkey.h"
#include "xbitcoinsecret.h"

#include <string>
#include <boost/cstdint.hpp>
#include <boost/date_time/posix_time/ptime.hpp>
#include <boost/date_time/posix_time/posix_time_types.hpp>

//*****************************************************************************
//*****************************************************************************
struct XBridgeTransactionDescr;
/**
 * @brief XBridgeTransactionDescrPtr
 */
typedef boost::shared_ptr<XBridgeTransactionDescr> XBridgeTransactionDescrPtr;

//******************************************************************************
//******************************************************************************
/**
 * @brief The XBridgeTransactionDescr struct
 */
struct XBridgeTransactionDescr
{
    enum
    {
        COIN = 1000000
    };

    /**
     * @brief The State enum
     */
    enum State
    {
        trExpired = -1,
        trNew = 0,
        trOffline,
        trPending,
        trAccepting,
        trHold,
        trInitialized,
        trCreated,
        trSigned,
        trCommited,
        trFinished,
        trRollback,
        trRollbackFailed,
        trDropped,
        trCancelled,
        trInvalid
    };

    /**
     * @brief id
     */
    uint256 id;

    /**
     * @brief role
     */
    char role;

    /**
     * @brief hubAddress
     */
    std::vector<unsigned char> hubAddress;

    /**
     * @brief confirmAddress
     */
    std::vector<unsigned char> confirmAddress;

    /**
     * @brief from
     */
    std::string from;

    /**
     * @brief fromCurrency
     */
    std::string fromCurrency;

    /**
     * @brief fromAmount
     */
    uint64_t fromAmount;

    /**
     * @brief to
     */
    std::string to;

    /**
     * @brief toCurrency
     */
    std::string toCurrency;

    /**
     * @brief toAmount
     */
    uint64_t toAmount;

    /**
     * @brief tax
     */
    uint32_t tax;

    /**
     * @brief lockTimeTx1
     */
    uint32_t lockTimeTx1;

    /**
     * @brief lockTimeTx2
     */
    uint32_t lockTimeTx2;

    /**
     * @brief state
     */
    State state;

    /**
     * @brief reason
     */
    uint32_t reason;

    /**
     * @brief created
     */
    boost::posix_time::ptime   created;

    /**
     * @brief txtime
     */
    boost::posix_time::ptime   txtime;

    // raw bitcoin transactions
    /**
     * @brief binTxId
     */
    std::string binTxId;

    /**
     * @brief binTx
     */
    std::string binTx;

    /**
     * @brief payTxId
     */
    std::string payTxId;

    /**
     * @brief payTx
     */
    std::string payTx;

    /**
     * @brief refTxId
     */
    std::string refTxId;

    /**
     * @brief refTx
     */
    std::string refTx;

    // multisig address and redeem script

    /**
     * @brief multisig
     */
    std::string multisig;

    /**
     * @brief innerScript
     */
    std::string innerScript;

    // prevtxs for signrawtransaction
    // std::string                prevtxs;

    /**
     * @brief packet
     */
    XBridgePacketPtr packet;

    // multisig key
    /**
     * @brief mPubKey
     */
    xbridge::CPubKey mPubKey;

    /**
     * @brief mSecret
     */
    xbridge::CBitcoinSecret mSecret;

    // X key

    /**
     * @brief xPubKey
     */
    xbridge::CPubKey xPubKey;

    /**
     * @brief xSecret
     */
    xbridge::CBitcoinSecret xSecret;

    /**
     * @brief XBridgeTransactionDescr
     */
    XBridgeTransactionDescr()
        : role(0)
        , tax(0)
        , lockTimeTx1(0)
        , lockTimeTx2(0)
        , state(trNew)
        , reason(0)
        , created(boost::posix_time::second_clock::universal_time())
        , txtime(boost::posix_time::second_clock::universal_time())
    {}

//    bool operator == (const XBridgeTransactionDescr & d) const
//    {
//        return id == d.id;
//    }

    /**
     * @brief operator <
     * @param d
     * @return
     */
    bool operator < (const XBridgeTransactionDescr &d) const
    {
        return created < d.created;
    }

    /**
     * @brief operator >
     * @param d
     * @return
     */
    bool operator > (const XBridgeTransactionDescr &d) const
    {
        return created > d.created;
    }

    XBridgeTransactionDescr &operator = (const XBridgeTransactionDescr &d)
    {
        if (this == &d)
        {
            return *this;
        }

        copyFrom(d);

        return *this;
    }

    /**
     * @brief XBridgeTransactionDescr
     * @param d
     */
    XBridgeTransactionDescr(const XBridgeTransactionDescr &d)
    {
        state   = trNew;
        created = boost::posix_time::second_clock::universal_time();
        txtime  = boost::posix_time::second_clock::universal_time();

        copyFrom(d);
    }

    /**
     * @brief updateTimestamp
     * @param d
     */
    void updateTimestamp(const XBridgeTransactionDescr &d)
    {
        txtime = boost::posix_time::second_clock::universal_time();
        if (created > d.created)
        {
            created = d.created;
        }
    }

    /**
     * @brief isLocal
     * @return
     */
    bool isLocal() const
    {
        return from.size() != 0 && to.size() != 0;
    }

    /**
     * @brief strState
     * @return
     */
    std::string strState() const
    {
        switch (state)
        {
            case trInvalid:   return std::string("Invalid");
            case trNew:       return std::string("New");
            case trPending:   return std::string("Open");
            case trAccepting: return std::string("Accepting");
            case trHold:      return std::string("Hold");
            case trCreated:   return std::string("Created");
            case trSigned:    return std::string("Signed");
            case trCommited:  return std::string("Commited");
            case trFinished:  return std::string("Finished");
            case trCancelled: return std::string("Cancelled");
            case trRollback:  return std::string("Rolled Back");
            case trDropped:   return std::string("Dropped");
            case trExpired:   return std::string("Expired");
            case trOffline:   return std::string("Offline");
            default:          return std::string("Unknown");
        }
    }

private:

    /**
     * @brief copyFrom
     * @param d
     */
    void copyFrom(const XBridgeTransactionDescr &d)
    {
        id           = d.id;
        role         = d.role;
        from         = d.from;
        fromCurrency = d.fromCurrency;
        fromAmount   = d.fromAmount;
        to           = d.to;
        toCurrency   = d.toCurrency;
        toAmount     = d.toAmount;
        tax          = d.tax;
        lockTimeTx1  = d.lockTimeTx1;
        lockTimeTx2  = d.lockTimeTx2;
        state        = d.state;
        reason       = d.reason;
        payTx        = d.payTx;
        refTx        = d.refTx;

        binTxId      = d.binTxId;
        binTx        = d.binTx;
        payTxId      = d.payTxId;
        payTx        = d.payTx;
        refTxId      = d.refTxId;
        refTx        = d.refTx;

        // multisig address and redeem script
        multisig     = d.multisig;
        innerScript       = d.innerScript;

        // prevtxs for signrawtransaction
        // prevtxs      = d.prevtxs;

        // multisig key
        mPubKey      = d.mPubKey;
        mSecret      = d.mSecret;

        // X key
        xPubKey      = d.xPubKey;
        xSecret      = d.xSecret;

        hubAddress     = d.hubAddress;
        confirmAddress = d.confirmAddress;

        updateTimestamp(d);
    }
};//struct XBridgeTransactionDescr

#endif // XBRIDGETRANSACTIONDESCR

