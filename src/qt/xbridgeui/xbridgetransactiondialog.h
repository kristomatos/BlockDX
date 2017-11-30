//******************************************************************************
//******************************************************************************

#ifndef XBRIDGETRANSACTIONDIALOG_H
#define XBRIDGETRANSACTIONDIALOG_H

#include "xbridgetransactionsmodel.h"
#include "xbridgeaddressbookview.h"

// #include "../walletmodel.h"

#include <QDialog>
#include <QStringList>
#include <QStringListModel>

#include <boost/signals2.hpp>

class QLineEdit;
class QComboBox;
class QPushButton;
class QLabel;

//******************************************************************************
//******************************************************************************
/**
 * @brief The XBridgeTransactionDialog class
 */
class XBridgeTransactionDialog : public QDialog
{
    Q_OBJECT
public:
    /**
     * @brief XBridgeTransactionDialog
     * @param model
     * @param parent
     */
    explicit XBridgeTransactionDialog(XBridgeTransactionsModel &model, QWidget *parent = 0);
    ~XBridgeTransactionDialog();

public:
    // void setWalletModel(WalletModel * model);

    /**
     * @brief setPendingId
     * @param id
     * @param hubAddress
     */
    void setPendingId(const uint256 &id, const std::vector<unsigned char> &hubAddress);

    /**
     * @brief setFromAmount
     * @param amount
     */
    void setFromAmount(double amount);

    /**
     * @brief setFromCurrency
     * @param currency
     */
    void setFromCurrency(const QString &currency);

    /**
     * @brief setToAmount
     * @param amount
     */
    void setToAmount(double amount);

    /**
     * @brief setToCurrency
     * @param currency
     */
    void setToCurrency(const QString &currency);

signals:

private:
    /**
     * @brief setupUI
     */
    void setupUI();

    /**
     * @brief onWalletListReceived
     * @param wallets
     */
    void onWalletListReceived(const std::vector<string> &wallets);

private slots:
    /**
     * @brief onWalletListReceivedHandler
     * @param wallets
     */
    void onWalletListReceivedHandler(const QStringList &wallets);

    /**
     * @brief onSendTransaction
     */
    void onSendTransaction();

    /**
     * @brief onPasteFrom
     */
    void onPasteFrom();

    /**
     * @brief onAddressBookFrom
     */
    void onAddressBookFrom();

    /**
     * @brief onPasteTo
     */
    void onPasteTo();

    /**
     * @brief onAddressBookTo
     */
    void onAddressBookTo();
    
    /**
     * @brief accountBalance
     * @param currency
     * @return
     */
    double accountBalance(const std::string &currency);

private:
    // WalletModel              * m_walletModel;

    /**
     * @brief m_model
     */
    XBridgeTransactionsModel &m_model;

    /**
     * @brief m_pendingId
     */
    uint256 m_pendingId;

    /**
     * @brief m_hubAddress
     */
    std::vector<unsigned char> m_hubAddress;

    /**
     * @brief m_addressFrom
     */
    QLineEdit *m_addressFrom;

    /**
     * @brief m_addressTo
     */
    QLineEdit *m_addressTo;

    /**
     * @brief m_amountFrom
     */
    QLineEdit *m_amountFrom;

    /**
     * @brief m_amountTo
     */
    QLineEdit *m_amountTo;

    /**
     * @brief m_currencyFrom
     */
    QComboBox *m_currencyFrom;

    /**
     * @brief m_currencyTo
     */
    QComboBox *m_currencyTo;

    /**
     * @brief m_balanceFrom
     */
    QLabel *m_balanceFrom;

    /**
     * @brief m_balanceTo
     */
    QLabel *m_balanceTo;

    /**
     * @brief m_btnSend
     */
    QPushButton *m_btnSend;

    /**
     * @brief m_addressBook
     */

    XBridgeAddressBookView m_addressBook;

    /**
     * @brief m_thisWallets
     */
    QStringList m_thisWallets;

    /**
     * @brief m_thisWalletsModel
     */
    QStringListModel m_thisWalletsModel;

    /**
     * @brief m_wallets
     */
    QStringList m_wallets;

    /**
     * @brief m_walletsModel
     */
    QStringListModel m_walletsModel;

    /**
     * @brief m_walletsNotifier
     */
    boost::signals2::connection m_walletsNotifier;
};

#endif // XBRIDGETRANSACTIONDIALOG_H
