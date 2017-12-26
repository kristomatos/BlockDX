#ifndef XBRIDGETRANSACTIONDESCR
#define XBRIDGETRANSACTIONDESCR

// #include "uint256.h"
#include "base58.h"
#include "xbridgepacket.h"
#include "xkey.h"
#include "xbitcoinsecret.h"
#include "xbridgewalletconnector.h"

#include <string>
#include <boost/cstdint.hpp>
#include <boost/date_time/posix_time/ptime.hpp>
#include <boost/date_time/posix_time/posix_time_types.hpp>

//******************************************************************************
//******************************************************************************
namespace xbridge
{

//******************************************************************************
//******************************************************************************
struct TransactionDescr
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
    uint256                    id;

    /**
     * @brief role
     */
    char                       role;

    /**
     * @brief hubAddress
     */
    std::vector<unsigned char> hubAddress;
    /**
     * @brief confirmAddress
     */
    std::vector<unsigned char> confirmAddress;

    /**
     * @brief from - from address
     */
    std::vector<unsigned char> from;
    /**
     * @brief fromCurrency - from currency
     */
    std::string                fromCurrency;
    /**
     * @brief fromAmount - from amount
     */
    uint64_t                   fromAmount;
    /**
     * @brief to - to address
     */
    std::vector<unsigned char> to;
    /**
     * @brief toCurrency - to currency
     */
    std::string                toCurrency;
    /**
     * @brief toAmount - to amount
     */
    uint64_t                   toAmount;

    /**
     * @brief tax
     */
    uint32_t                   tax;

    /**
     * @brief lockTimeTx1 - time of lock
     */
    uint32_t                   lockTimeTx1;
    /**
     * @brief lockTimeTx2
     */
    uint32_t                   lockTimeTx2;

    /**
     * @brief state - status of transaction
     */
    State                      state;
    /**
     * @brief reason
     */
    uint32_t                   reason;

    /**
     * @brief created - time of creation transaction
     */
    boost::posix_time::ptime   created;
    /**
     * @brief txtime - time of last transaction update
     */
    boost::posix_time::ptime   txtime;


    /**
     * @brief binTxId raw bitcoin transactions
     */
    std::string                binTxId;
    /**
     * @brief binTx
     */
    std::string                binTx;
    /**
     * @brief payTxId
     */
    std::string                payTxId;
    /**
     * @brief payTx
     */
    std::string                payTx;
    /**
     * @brief refTxId
     */
    std::string                refTxId;
    /**
     * @brief refTx
     */
    std::string                refTx;


    /**
     * @brief depositP2SH multisig address and redeem script
     */
    std::string                depositP2SH;
    /**
     * @brief innerScript
     */
    std::vector<unsigned char> innerScript;

    // prevtxs for signrawtransaction
    // std::string                prevtxs;

    /**
     * @brief packet
     */
    XBridgePacketPtr           packet;

    //
    /**
     * @brief mPubKey local created key (for exchange)
     */
    std::vector<unsigned char>    mPubKey;
    /**
     * @brief mPrivKey
     */
    std::vector<unsigned char>    mPrivKey;


    /**
     * @brief xPubKey X key (secret data)
     */
    std::vector<unsigned char>    xPubKey;
    /**
     * @brief xPrivKey
     */
    std::vector<unsigned char>    xPrivKey;

    // used coins in transaction
    /**
     * @brief usedCoins
     */
    std::vector<xbridge::wallet::UtxoEntry> usedCoins;

    /**
     * @brief TransactionDescr  - default constructor
     */
    TransactionDescr()
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

    bool operator < (const TransactionDescr & d) const
    {
        return created < d.created;
    }

    bool operator > (const TransactionDescr & d) const
    {
        return created > d.created;
    }

    TransactionDescr & operator = (const TransactionDescr & d)
    {
        if (this == &d)
        {
            return *this;
        }

        copyFrom(d);

        return *this;
    }

    /**
     * @brief TransactionDescr - copy constructor
     * @param d
     */
    TransactionDescr(const TransactionDescr & d)
    {
        state   = trNew;
        created = boost::posix_time::second_clock::universal_time();
        txtime  = boost::posix_time::second_clock::universal_time();

        copyFrom(d);
    }

    /**
     * @brief updateTimestamp - update timestamp of transaction
     */
    void updateTimestamp()
    {
        txtime       = boost::posix_time::second_clock::universal_time();
    }

    /**
     * @brief updateTimestamp - update timestamp of transaction
     * @param d - other transaction
     */
    void updateTimestamp(const TransactionDescr & d)
    {
        txtime       = boost::posix_time::second_clock::universal_time();
        if (created > d.created)
        {
            created = d.created;
        }
    }

    /**
     * @brief isLocal
     * @return true, if client is owner of transaction
     */
    bool isLocal() const
    {
        return from.size() != 0 && to.size() != 0;
    }

    /**
     * @brief strState
     * @return string description  transaction status
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
    void copyFrom(const TransactionDescr & d)
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
        depositP2SH     = d.depositP2SH;
        innerScript       = d.innerScript;

        // prevtxs for signrawtransaction
        // prevtxs      = d.prevtxs;

        // multisig key
        mPubKey      = d.mPubKey;
        mPrivKey      = d.mPrivKey;

        // X key
        xPubKey      = d.xPubKey;
        xPrivKey      = d.xPrivKey;

        hubAddress     = d.hubAddress;
        confirmAddress = d.confirmAddress;

        updateTimestamp(d);
    }
};

} // namespace xbridge

#endif // XBRIDGETRANSACTIONDESCR

