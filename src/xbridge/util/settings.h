//******************************************************************************
//******************************************************************************
#ifndef SETTINGS_H
#define SETTINGS_H

#include "logger.h"

#include <vector>
#include <string>

#include <boost/property_tree/ptree.hpp>

#define TRY(_STMNT_) try { (_STMNT_); } catch(std::exception & e) { LOG() << e.what(); }

//******************************************************************************
/**
 * @brief The Settings class
 */
class Settings
{
    /**
     * @brief settings
     * @return
     */
    friend Settings & settings();

private:
    /**
     * @brief Settings
     */
    Settings();

public:
    /**
     * @brief parseCmdLine
     * @param argv
     * @return
     */
    bool parseCmdLine(int, char * argv[]);

    /**
     * @brief read
     * @param fileName
     * @return
     */
    bool read(const char* fileName = 0);

    /**
     * @brief write
     * @param fileName
     * @return
     */
    bool write(const char* fileName = 0);

public:
    /**
     * @brief isFullLog
     * @return
     */
    bool isFullLog() { return get<bool>("Main.FullLog", false); }

    /**
     * @brief isExchangeEnabled
     * @return
     */
    bool isExchangeEnabled() const { return m_isExchangeEnabled; }

    /**
     * @brief appPath
     * @return
     */
    std::string appPath() const    { return m_appPath; }

    /**
     * @brief logPath
     * @return
     */
    std::string logPath() const;

    /**
     * @brief peers
     * @return
     */
    std::vector<std::string> peers() const;

    /**
     * @brief exchangeWallets
     * @return
     */
    std::vector<std::string> exchangeWallets() const;

    /**
     * @brief rpcEnabled
     * @return
     */
    bool rpcEnabled() { return get<bool>("Rpc.Enable", false); }

    /**
     * @brief rpcPort
     * @param def
     * @return
     */
    uint32_t rpcPort(const uint32_t def) { return get<uint32_t>("Rpc.Port", def); }

    /**
     * @brief rpcServerUserName
     * @return
     */
    std::string rpcServerUserName() { return get<std::string>("Rpc.UserName"); }

    /**
     * @brief rpcServerPasswd
     * @return
     */
    std::string rpcServerPasswd() { return get<std::string>("Rpc.Password"); }

    /**
     * @brief rpcUseSsl
     * @return
     */
    bool rpcUseSsl() { return get<bool>("Rpc.UseSSL"); }

    /**
     * @brief rpcSertFile
     * @param def
     * @return
     */
    std::string rpcSertFile(const std::string def = std::string()) { return get<std::string>("Rpc.SertFile", def); }

    /**
     * @brief rpcPKeyFile
     * @param def
     * @return
     */
    std::string rpcPKeyFile(const std::string def = std::string()) { return get<std::string>("Rpc.PKeyFile", def); }

    /**
     * @brief rpcSslCiphers
     * @param def
     * @return
     */
    std::string rpcSslCiphers(const std::string def = std::string()) { return get<std::string>("Rpc.SslCiphers", def); }

public:
    /**
     * @brief get
     * @param param
     * @param def
     * @return
     */
    template <class _T>
    _T get(const std::string & param, _T def = _T())
    {
        return get<_T>(param.c_str(), def);
    }

    /**
     * @brief get
     * @param param
     * @param def
     * @return
     */
    template <class _T>
    _T get(const char * param, _T def = _T())
    {
        _T tmp = def;
        try
        {
            tmp = m_pt.get<_T>(param);
            return tmp;
        }
        catch (std::exception & e)
        {
            LOG() << e.what();
        }

        set(param, tmp);
        return tmp;
    }

    /**
     * @brief set
     * @param param
     * @param val
     * @return
     */
    template <class _T>
    bool set(const char * param, const _T & val)
    {
        try
        {
            m_pt.put<_T>(param, val);
            write();
        }
        catch (std::exception & e)
        {
            LOG() << e.what();
            return false;
        }
        return true;
    }

private:
    /**
     * @brief m_appPath
     */
    std::string m_appPath;

    /**
     * @brief m_fileName
     */
    std::string m_fileName;

    /**
     * @brief m_pt
     */
    boost::property_tree::ptree m_pt;

    /**
     * @brief m_peers
     */
    std::vector<std::string> m_peers;

    /**
     * @brief m_isExchangeEnabled
     */
    bool m_isExchangeEnabled;
}; //class Settings

Settings & settings();

#endif // SETTINGS_H
