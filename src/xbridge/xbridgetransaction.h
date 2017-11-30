//*****************************************************************************
//*****************************************************************************

#ifndef XBRIDGETRANSACTION_H
#define XBRIDGETRANSACTION_H

#include "uint256.h"
#include "xbridgetransactionmember.h"
#include "xkey.h"

#include <vector>
#include <string>

#include <boost/cstdint.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/date_time/posix_time/ptime.hpp>

//*****************************************************************************
//*****************************************************************************
class XBridgeTransaction;
typedef boost::shared_ptr<XBridgeTransaction> XBridgeTransactionPtr;

//*****************************************************************************
//*****************************************************************************
/**
 * @brief The XBridgeTransaction class
 */
class XBridgeTransaction
{
public:
    // see strState when editing
    /**
     * @brief The State enum
     */
    enum State
    {
        trInvalid = 0,
        trNew,
        trJoined,
        trHold,
        trInitialized,
        trCreated,
        trSigned,
        trCommited,

        trConfirmed,
        trFinished,
        trCancelled,
        trDropped
    };

    enum
    {
        // transaction lock time base, in seconds, 10 min
        lockTime = 600,

        // pending transaction ttl in seconds, 72 hours
        pendingTTL = 259200,

        // transaction ttl in seconds, 60 min
        TTL = 3600
    };

public:
    /**
     * @brief XBridgeTransaction
     */
    XBridgeTransaction();

    /**
     * @brief XBridgeTransaction
     * @param id
     * @param sourceAddr
     * @param sourceXAddr
     * @param sourceCurrency
     * @param sourceAmount
     * @param destAddr
     * @param destXAddr
     * @param destCurrency
     * @param destAmount
     */
    XBridgeTransaction(const uint256 &id,
                       const std::string &sourceAddr,
                       const std::vector<unsigned char> &sourceXAddr,
                       const std::string &sourceCurrency,
                       const uint64_t &sourceAmount,
                       const std::string &destAddr,
                       const std::vector<unsigned char> &destXAddr,
                       const std::string &destCurrency,
                       const uint64_t &destAmount);

    /**
      *
      * */
    ~XBridgeTransaction();

    /**
     * @brief id
     * @return
     */
    uint256 id() const;


    /**
     * @brief state state of transaction
     * @return
     */
    State state() const;


    /**
     * @brief increaseStateCounter update state counter and update state
     * @param state
     * @param from
     * @return
     */
    State increaseStateCounter(State state, const std::string &from);

    /**
     * @brief strState
     * @param state
     * @return
     */
    static std::string strState(const State state);

    /**
     * @brief strState
     * @return
     */
    std::string strState() const;

    /**
     * @brief updateTimestamp
     */
    void updateTimestamp();

    /**
     * @brief createdTime
     * @return
     */
    boost::posix_time::ptime createdTime() const;

    /**
     * @brief isFinished
     * @return
     */
    bool isFinished() const;

    /**
     * @brief isValid
     * @return
     */
    bool isValid() const;

    /**
     * @brief isExpired
     * @return
     */
    bool isExpired() const;

    /**
     * @brief cancel
     */
    void cancel();

    /**
     * @brief drop
     */
    void drop();

    /**
     * @brief finish
     */
    void finish();

    /**
     * @brief confirm
     * @param id
     * @return
     */
    bool confirm(const std::string &id);

    // hash of transaction
    /**
     * @brief hash1
     * @return
     */
    uint256 hash1() const;

    /**
     * @brief hash2
     * @return
     */
    uint256 hash2() const;

    // uint256                    firstId() const;
    /**
     * @brief a_address
     * @return
     */
    std::string a_address() const;

    /**
     * @brief a_xaddress
     * @return
     */
    std::vector<unsigned char> a_xaddress() const;

    /**
     * @brief a_destination
     * @return
     */
    std::string a_destination() const;

    /**
     * @brief a_xdestination
     * @return
     */
    std::vector<unsigned char> a_xdestination() const;

    /**
     * @brief a_currency
     * @return
     */
    std::string a_currency() const;

    /**
     * @brief a_amount
     * @return
     */
    uint64_t a_amount() const;

    /**
     * @brief a_payTx
     * @return
     */
    std::string a_payTx() const;

    /**
     * @brief a_refTx
     * @return
     */
    std::string a_refTx() const;

    /**
     * @brief a_bintxid
     * @return
     */
    std::string a_bintxid() const;

    /**
     * @brief a_innerScript
     * @return
     */
    std::string a_innerScript() const;

    /**
     * @brief a_datatxid
     * @return
     */
    uint256 a_datatxid() const;

    /**
     * @brief a_pk1
     * @return
     */
    xbridge::CPubKey a_pk1() const;

    // uint256                    secondId() const;

    /**
     * @brief b_address
     * @return
     */
    std::string b_address() const;

    /**
     * @brief b_xaddress
     * @return
     */
    std::vector<unsigned char> b_xaddress() const;

    /**
     * @brief b_destination
     * @return
     */
    std::string b_destination() const;

    /**
     * @brief b_xdestination
     * @return
     */
    std::vector<unsigned char> b_xdestination() const;

    /**
     * @brief b_currency
     * @return
     */
    std::string b_currency() const;

    /**
     * @brief b_amount
     * @return
     */
    uint64_t b_amount() const;

    /**
     * @brief b_payTx
     * @return
     */
    std::string b_payTx() const;

    /**
     * @brief b_refTx
     * @return
     */
    std::string b_refTx() const;

    /**
     * @brief b_bintxid
     * @return
     */
    std::string b_bintxid() const;

    /**
     * @brief b_innerScript
     * @return
     */
    std::string b_innerScript() const;

    // uint256                    b_datatxid() const;

    /**
     * @brief b_pk1
     * @return
     */
    xbridge::CPubKey b_pk1() const;

    /**
     * @brief tryJoin
     * @param other
     * @return
     */
    bool tryJoin(const XBridgeTransactionPtr other);

    /**
     * @brief setKeys
     * @param addr
     * @param datatxid
     * @param pk
     * @return
     */
    bool setKeys(const std::string &addr,
                 const uint256 &datatxid,
                 const xbridge::CPubKey &pk);

    /**
     * @brief setBinTxId
     * @param addr
     * @param id
     * @param innerScript
     * @return
     */
    bool setBinTxId(const std::string &addr,
                    const std::string &id,
                    const std::string &innerScript);

public:
    /**
     * @brief m_lock
     */
    boost::mutex m_lock;

private:
    /**
     * @brief m_id
     */
    uint256 m_id;

    /**
     * @brief m_created
     */
    boost::posix_time::ptime m_created;

    /**
     * @brief m_state
     */
    State m_state;

    /**
     * @brief m_a_stateChanged
     */
    bool m_a_stateChanged;

    /**
     * @brief m_b_stateChanged
     */
    bool m_b_stateChanged;

    /**
     * @brief m_confirmationCounter
     */
    unsigned int m_confirmationCounter;

    /**
     * @brief m_sourceCurrency
     */
    std::string m_sourceCurrency;

    /**
     * @brief m_destCurrency
     */
    std::string m_destCurrency;

    /**
     * @brief m_sourceAmount
     */
    uint64_t m_sourceAmount;

    /**
     * @brief m_destAmount
     */
    uint64_t m_destAmount;

    /**
     * @brief m_bintxid1
     */
    std::string m_bintxid1;

    /**
     * @brief m_bintxid2
     */
    std::string m_bintxid2;

    /**
     * @brief m_innerScript1
     */
    std::string m_innerScript1;

    /**
     * @brief m_innerScript2
     */
    std::string m_innerScript2;

    /**
     * @brief m_a
     */
    XBridgeTransactionMember m_a;

    /**
     * @brief m_b
     */
    XBridgeTransactionMember m_b;

    /**
     * @brief m_a_datatxid
     */
    uint256 m_a_datatxid;

    /**
     * @brief m_b_datatxid
     */
    uint256 m_b_datatxid;

    /**
     * @brief m_a_pk1
     */
    xbridge::CPubKey m_a_pk1;

    /**
     * @brief m_b_pk1
     */
    xbridge::CPubKey m_b_pk1;
};//class XBridgeTransaction

#endif // XBRIDGETRANSACTION_H
