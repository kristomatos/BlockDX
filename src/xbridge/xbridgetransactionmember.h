//*****************************************************************************
//*****************************************************************************

#ifndef XBRIDGETRANSACTIONMEMBER_H
#define XBRIDGETRANSACTIONMEMBER_H

#include "uint256.h"

#include <string>
#include <vector>

#include <boost/cstdint.hpp>

//*****************************************************************************
//*****************************************************************************
/**
 * @brief The XBridgeTransactionMember class
 */
class XBridgeTransactionMember
{
public:
    /**
     * @brief XBridgeTransactionMember
     */
    XBridgeTransactionMember() {}

    /**
     * @brief XBridgeTransactionMember
     * @param id
     */
    XBridgeTransactionMember(const uint256 &id) : m_id(id) {}

    /**
     * @brief isEmpty
     * @return
     */
    bool isEmpty() const { return m_sourceAddr.empty() || m_destAddr.empty(); }

    /**
     * @brief id
     * @return
     */
    const uint256 id() const { return m_id; }

    /**
     * @brief source
     * @return
     */
    const std::string &source() const { return m_sourceAddr; }

    /**
     * @brief xsource
     * @return
     */
    const std::vector<unsigned char> &xsource() const { return m_sourceXAddr; }

    /**
     * @brief setSource
     * @param addr
     * @param xaddr
     */
    void setSource(const std::string &addr, const std::vector<unsigned char> &xaddr)
    {
        m_sourceAddr  = addr;
        m_sourceXAddr = xaddr;
    }

    /**
     * @brief dest
     * @return
     */
    const std::string &dest() const { return m_destAddr; }

    /**
     * @brief xdest
     * @return
     */
    const std::vector<unsigned char> &xdest() const   { return m_destXAddr; }

    /**
     * @brief setDest
     * @param addr
     * @param xaddr
     */
    void setDest(const std::string &addr, const std::vector<unsigned char> &xaddr)
    {
        m_destAddr  = addr;
        m_destXAddr = xaddr;
    }

private:
    /**
     * @brief m_id
     */
    uint256 m_id;

    /**
     * @brief m_sourceAddr
     */
    std::string m_sourceAddr;

    /**
     * @brief m_sourceXAddr
     */
    std::vector<unsigned char> m_sourceXAddr;

    /**
     * @brief m_destAddr
     */
    std::string m_destAddr;

    /**
     * @brief m_destXAddr
     */
    std::vector<unsigned char> m_destXAddr;

    /**
     * @brief m_transactionHash
     */
    uint256 m_transactionHash;
};//class XBridgeTransactionMember

#endif // XBRIDGETRANSACTIONMEMBER_H
