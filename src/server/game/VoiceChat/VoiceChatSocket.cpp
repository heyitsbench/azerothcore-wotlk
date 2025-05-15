#include "VoiceChatSocket.h"
#include "Log.h"
#include "VoiceChatDefines.h"
#include "VoiceChatMgr.h"

struct VoiceChatServerPktHeader {
  uint16 cmd;
  uint16 size;

  const char *data() const { return reinterpret_cast<const char *>(this); }

  std::size_t headerSize() const { return sizeof(VoiceChatServerPktHeader); }
};

// ~VoiceChatSocket::VoiceChatSocket()
// {
//     LOG_DEBUG("voice.chat", "VoiceChatSocket destructor called");
//     if (IsOpen())
//     {
//         LOG_DEBUG("voice.chat", "Socket was still open during destruction");
//     }
// }

VoiceChatSocket::VoiceChatSocket(tcp::socket &&socket)
    : Socket<VoiceChatSocket>(std::move(socket)) {}

void VoiceChatSocket::Start() {
  // Initialize connection
  std::string ip_address = GetRemoteIpAddress().to_string();
  // LOG_TRACE("session", "Accepted connection from {}", ip_address);
  LOG_ERROR("sql.sql", "Accepted connection from {}", ip_address);
  LOG_DEBUG("session", "Accepted connection from {}", ip_address);
  AsyncRead();
}

bool VoiceChatSocket::Update() {
  if (!Socket<VoiceChatSocket>::Update())
    return false;

  // _queryProcessor.ProcessReadyCallbacks();
    // Process any queued packets in parent class

  // Add session-specific update logic
  return true;
}

void VoiceChatSocket::SendPacket(VoiceChatServerPacket pct)
{
    if (!IsOpen())
        return;

    VoiceChatServerPktHeader header;
    header.cmd = pct.GetOpcode();
    header.size = static_cast<uint8>(pct.size());

    // Create MessageBuffer with total size (header + payload)
    MessageBuffer buffer(header.headerSize() + pct.size());

    // Write header
    buffer.Write(header.data(), header.headerSize());

    // Write payload if any
    if (pct.size() > 0)
        buffer.Write(pct.contents(), pct.size());

    LOG_ERROR("sql.sql", "Sending packet: opcode={}, size={}", header.cmd, header.size);

    // Log the raw packet data
    std::stringstream ss;
    const uint8* data = (const uint8*)buffer.GetReadPointer();
    for (size_t i = 0; i < buffer.GetActiveSize(); ++i)
        ss << std::hex << std::setw(2) << std::setfill('0') << (int)data[i] << " ";
    LOG_ERROR("sql.sql", "Packet data: {}", ss.str());

    // Queue the packet using Socket's QueuePacket method
    QueuePacket(std::move(buffer));
}

bool VoiceChatSocket::HandlePing() {
  // Handle ping packet
  return true;
}

bool VoiceChatSocket::ProcessIncomingData() {
  LOG_INFO("sql.sql", "VoiceChatSocket::ProcessIncomingData() Read Pong packet "
                      "sent from server"); // Log info for pong packets
  // Structured similar to VoiceChatServerSocket
  if (!IsOpen())
    return false;

  // Read header
  if (GetReadBuffer().GetActiveSize() < sizeof(VoiceChatServerPktHeader)) {
    LOG_ERROR("sql.sql", "Not enough data for header ({} < {})",
              GetReadBuffer().GetActiveSize(),
              sizeof(VoiceChatServerPktHeader));
    return false;
  }

  VoiceChatServerPktHeader header;
  std::memcpy(&header, GetReadBuffer().GetReadPointer(), sizeof(header));
  GetReadBuffer().ReadCompleted(sizeof(header));

  LOG_ERROR("sql.sql", "Processing packet: cmd={}, size={}", header.cmd,
            header.size);

  if (header.size < 2 || header.size > 0x2800) {
    // //actual error\nLOG_ERROR("sql.sql", "VoiceChatServerSocket::ProcessIncomingData: client sent
    // malformed packet size = %u , cmd = %u", header->size, header->cmd);
    CloseSocket();
    return false;
  }

  // Read payload
  if (GetReadBuffer().GetActiveSize() < header.size)
    return false;

  std::vector<uint8> payload(header.size);
  std::memcpy(payload.data(), GetReadBuffer().GetReadPointer(), header.size);
  GetReadBuffer().ReadCompleted(header.size);

  // Pass to VoiceChatMgr
  auto packet = std::make_unique<VoiceChatServerPacket>(
      (VoiceChatServerOpcodes)header.cmd, header.size);
  packet->append(payload.data(), payload.size());
  sVoiceChatMgr.QueuePacket(std::move(packet));

  return true;
}

void VoiceChatSocket::ReadHandler() {
  LOG_ERROR("sql.sql", "ReadHandler called with {} bytes available",
            GetReadBuffer().GetActiveSize());

  MessageBuffer &packet = GetReadBuffer();
  while (packet.GetActiveSize() > 0) // Loop while there's data in the buffer
  {
    if (!ProcessIncomingData()) // Process data until buffer is exhausted
      break;                    // Break if processing fails
  }

  AsyncRead(); // Queue the next async read
}