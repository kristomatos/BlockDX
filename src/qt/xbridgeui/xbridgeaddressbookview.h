//******************************************************************************
//******************************************************************************

#ifndef XBRIDGEADDRESSBOOKVIEW_H
#define XBRIDGEADDRESSBOOKVIEW_H

#include "xbridgeaddressbookmodel.h"

#include <QDialog>
#include <QTableView>

//******************************************************************************
//******************************************************************************
/**
 * @brief The XBridgeAddressBookView class
 */
class XBridgeAddressBookView : public QDialog
{
    Q_OBJECT
public:
    /**
     * @brief XBridgeAddressBookView
     * @param parent
     */
    explicit XBridgeAddressBookView(QWidget *parent = 0);
    /**
      * ~XBridgeAddressBookView
      * */
    ~XBridgeAddressBookView();

    /**
     * @brief selectedAddress
     * @return
     */
    std::string selectedAddress() const { return m_selectedAddress; }
    /**
     * @brief selectedCurrency
     * @return
     */
    std::string selectedCurrency() const { return m_selectedCurrency; }


private slots:
    /**
     * @brief onAddressSelect
     * @param index
     */
    void onAddressSelect(QModelIndex index);

private:
    /**
     * @brief setupUi
     */
    void setupUi();

private:
    /**
     * @brief m_selectedAddress
     */
    std::string m_selectedAddress;
    /**
     * @brief m_selectedCurrency
     */
    std::string m_selectedCurrency;

    /**
     * @brief m_model
     */
    XBridgeAddressBookModel m_model;

    /**
     * @brief m_entryList
     */
    QTableView  * m_entryList;
};

#endif // XBRIDGEADDRESSBOOKVIEW_H
