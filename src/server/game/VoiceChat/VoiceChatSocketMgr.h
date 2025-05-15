#ifndef VoiceChatSocketMgr_h__
#define VoiceChatSocketMgr_h__

// #include "VoiceChatSocket.h"
#include "Config.h"
#include "SocketMgr.h"
#include "VoiceChatSocket.h"

class VoiceChatSocketMgr : public SocketMgr<VoiceChatSocket>
{
    typedef SocketMgr<VoiceChatSocket> BaseSocketMgr;

public:
    static VoiceChatSocketMgr& Instance()
    {
        static VoiceChatSocketMgr instance;
        return instance;
    }

    bool StartNetwork(Acore::Asio::IoContext& ioContext, std::string const& bindIp, uint16 port, int threadCount = 1) override
    {
        if (!BaseSocketMgr::StartNetwork(ioContext, bindIp, port, threadCount))
            return false;

        _acceptor->AsyncAcceptWithCallback<&VoiceChatSocketMgr::OnSocketAccept>();
        return true;
    }

protected:
    NetworkThread<VoiceChatSocket>* CreateThreads() const override
    {
        NetworkThread<VoiceChatSocket>* threads = new NetworkThread<VoiceChatSocket>[1];
        return threads;
    }

    static void OnSocketAccept(tcp::socket&& sock, uint32 threadIndex)
    {
        Instance().OnSocketOpen(std::forward<tcp::socket>(sock), threadIndex);
    }
};

#define sVoiceChatSocketMgr VoiceChatSocketMgr::Instance()

#endif // VoiceChatSocketMgr_h__
