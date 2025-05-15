#ifndef __VoiceChatSocket_H__
#define __VoiceChatSocket_H__

#include "Socket.h"
#include "VoiceChatDefines.h"
#include <boost/asio/ip/tcp.hpp>

using boost::asio::ip::tcp;

class VoiceChatSocket : public Socket<VoiceChatSocket> {

public:
  explicit VoiceChatSocket(tcp::socket &&socket);

  void Start() override;
  bool Update() override;
  // void SendPacket(ByteBuffer &packet);
  void SendPacket(VoiceChatServerPacket pct);

protected:
  void ReadHandler() override;

private:
  bool HandlePing();
  bool ProcessIncomingData();
  // bool HandleChannelCreated();
  // Add other handlers as needed
};

#endif
