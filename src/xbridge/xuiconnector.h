#ifndef XUICONNECTOR_H
#define XUICONNECTOR_H

#include <string>
#include <boost/signals2/signal.hpp>

class uint256;
struct XBridgeTransactionDescr;
/**
 * @brief The XUIConnector class
 */
class XUIConnector
{
public:
    /**
     * @brief NotifyXBridgePendingTransactionReceived
     */
    boost::signals2::signal<void (const XBridgeTransactionDescr &tx)> NotifyXBridgePendingTransactionReceived;

    /**
     * @brief NotifyXBridgeTransactionStateChanged
     */
    boost::signals2::signal<void (const uint256 &id,
                                  const unsigned int state)> NotifyXBridgeTransactionStateChanged;

    /**
     * @brief NotifyXBridgeTransactionCancelled
     */
    boost::signals2::signal<void (const uint256 &id,
                                  const uint32_t state,
                                  const uint32_t reason)> NotifyXBridgeTransactionCancelled;

    /**
     * @brief NotifyXBridgeAddressBookEntryReceived
     */
    boost::signals2::signal<void (const std::string &currency,
                                  const std::string &name,
                                  const std::string &address)> NotifyXBridgeAddressBookEntryReceived;

    /**
     * @brief NotifyLogMessage
     */
    boost::signals2::signal<void (const std::string str)> NotifyLogMessage;
};

extern XUIConnector xuiConnector;

#endif // XUICONNECTOR_H

