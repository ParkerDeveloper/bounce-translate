/*
RakLite
@bartekdvd
Feel free to use it
*/

#define RAKNET_MAX_PACKET	256

#include "BitStream.h"
#include "../CGame/Types.h"

typedef unsigned int RakNetTime;
typedef long long RakNetTimeNS;

enum PacketPriority
{
	SYSTEM_PRIORITY,
	HIGH_PRIORITY,
	MEDIUM_PRIORITY,
	LOW_PRIORITY,
	NUMBER_OF_PRIORITIES
};

enum PacketReliability
{
	UNRELIABLE,
	UNRELIABLE_SEQUENCED,
	RELIABLE,
	RELIABLE_ORDERED,
	RELIABLE_SEQUENCED
};

typedef unsigned short PlayerIndex;

#pragma pack(push, 1)
struct PlayerID
{
	///The peer address from inet_addr.
	unsigned int binaryAddress;
	///The port number
	unsigned short port;

	PlayerID& operator = (const PlayerID& input)
	{
		binaryAddress = input.binaryAddress;
		port = input.port;
		return *this;
	}

	bool operator==(const PlayerID& right) const;
	bool operator!=(const PlayerID& right) const;
	bool operator > (const PlayerID& right) const;
	bool operator < (const PlayerID& right) const;
};

struct NetworkID
{
	bool peerToPeer;
	PlayerID playerId;
	unsigned short localSystemId;
};

/// This represents a user message from another system.
struct Packet
{
	/// Server only - this is the index into the player array that this playerId maps to
	PlayerIndex playerIndex;

	/// The system that send this packet.
	PlayerID playerId;

	/// The length of the data in bytes
	/// deprecated You should use bitSize.
	unsigned int length;

	/// The length of the data in bits
	unsigned int bitSize;

	/// The data from the sender
	unsigned char* data;

	/// @internal
	/// Indicates whether to delete the data, or to simply delete the packet.
	bool deleteData;
};

/// All RPC functions have the same parameter list - this structure.
struct RPCParameters
{
	/// The data from the remote system
	unsigned char *input;

	/// How many bits long a input is
	unsigned int numberOfBitsOfData;

	/// Which system called this RPC
	PlayerID sender;

	/// Which instance of RakPeer (or a derived RakServer or RakClient) got this call
	void *recipient;

	/// You can return values from RPC calls by writing them to this BitStream.
	/// This is only sent back if the RPC call originally passed a BitStream to receive the reply.
	/// If you do so and your send is reliable, it will block until you get a reply or you get disconnected from the system you are sending to, whichever is first.
	/// If your send is not reliable, it will block for triple the ping time, or until you are disconnected, or you get a reply, whichever is first.
	BitStream *replyToSender;
};

struct RPCNode
{
	uint8_t uniqueIdentifier;
	void(*staticFunctionPointer) (RPCParameters *rpcParms);
};

/// Store Statistics information related to network usage
struct RakNetStatisticsStruct
{
	///  Number of Messages in the send Buffer (high, medium, low priority)
	unsigned messageSendBuffer[NUMBER_OF_PRIORITIES];
	///  Number of messages sent (high, medium, low priority)
	unsigned messagesSent[NUMBER_OF_PRIORITIES];
	///  Number of data bits used for user messages
	unsigned messageDataBitsSent[NUMBER_OF_PRIORITIES];
	///  Number of total bits used for user messages, including headers
	unsigned messageTotalBitsSent[NUMBER_OF_PRIORITIES];

	///  Number of packets sent containing only acknowledgements
	unsigned packetsContainingOnlyAcknowlegements;
	///  Number of acknowledgements sent
	unsigned acknowlegementsSent;
	///  Number of acknowledgements waiting to be sent
	unsigned acknowlegementsPending;
	///  Number of acknowledgements bits sent
	unsigned acknowlegementBitsSent;

	///  Number of packets containing only acknowledgements and resends
	unsigned packetsContainingOnlyAcknowlegementsAndResends;

	///  Number of messages resent
	unsigned messageResends;
	///  Number of bits resent of actual data
	unsigned messageDataBitsResent;
	///  Total number of bits resent, including headers
	unsigned messagesTotalBitsResent;
	///  Number of messages waiting for ack (// TODO - rename this)
	unsigned messagesOnResendQueue;

	///  Number of messages not split for sending
	unsigned numberOfUnsplitMessages;
	///  Number of messages split for sending
	unsigned numberOfSplitMessages;
	///  Total number of splits done for sending
	unsigned totalSplits;

	///  Total packets sent
	unsigned packetsSent;

	///  Number of bits added by encryption
	unsigned encryptionBitsSent;
	///  total bits sent
	unsigned totalBitsSent;

	///  Number of sequenced messages arrived out of order
	unsigned sequencedMessagesOutOfOrder;
	///  Number of sequenced messages arrived in order
	unsigned sequencedMessagesInOrder;

	///  Number of ordered messages arrived out of order
	unsigned orderedMessagesOutOfOrder;
	///  Number of ordered messages arrived in order
	unsigned orderedMessagesInOrder;

	///  Packets with a good CRC received
	unsigned packetsReceived;
	///  Packets with a bad CRC received
	unsigned packetsWithBadCRCReceived;
	///  Bits with a good CRC received
	unsigned bitsReceived;
	///  Bits with a bad CRC received
	unsigned bitsWithBadCRCReceived;
	///  Number of acknowledgement messages received for packets we are resending
	unsigned acknowlegementsReceived;
	///  Number of acknowledgement messages received for packets we are not resending
	unsigned duplicateAcknowlegementsReceived;
	///  Number of data messages (anything other than an ack) received that are valid and not duplicate
	unsigned messagesReceived;
	///  Number of data messages (anything other than an ack) received that are invalid
	unsigned invalidMessagesReceived;
	///  Number of data messages (anything other than an ack) received that are duplicate
	unsigned duplicateMessagesReceived;
	///  Number of messages waiting for reassembly
	unsigned messagesWaitingForReassembly;
	///  Number of messages in reliability output queue
	unsigned internalOutputQueueSize;
	///  Current bits per second
	double bitsPerSecond;
	///  connection start time
	RakNetTime connectionStartTime;
};
#pragma pack(pop)

class RakClient
{
public:
	virtual void __destruct();
	virtual bool Connect(const char* host, unsigned short serverPort, unsigned short clientPort, unsigned int depreciated, int threadSleepTimer) = 0;
	virtual void Disconnect(unsigned int blockDuration, unsigned char orderingChannel = 0) = 0;
	virtual void InitializeSecurity(const char *privKeyP, const char *privKeyQ) = 0;
	virtual void SetPassword(const char *_password) = 0;
	virtual bool HasPassword(void) = 0;
	virtual bool Send(const char *data, const int length, PacketPriority priority, PacketReliability reliability, char orderingChannel) = 0;
	virtual bool Send(BitStream * bitStream, PacketPriority priority, PacketReliability reliability, char orderingChannel) = 0;
	virtual Packet* Receive(void) = 0;
	virtual void DeallocatePacket(Packet *packet) = 0;
	virtual void PingServer(void) = 0;
	virtual void PingServer(const char* host, unsigned short serverPort, unsigned short clientPort, bool onlyReplyOnAcceptingConnections) = 0;
	virtual int GetAveragePing(void) = 0;
	virtual int GetLastPing(void) = 0;
	virtual int GetLowestPing(void) = 0;
	virtual int GetPlayerPing(const PlayerID playerId) = 0;
	virtual void StartOccasionalPing(void) = 0;
	virtual void StopOccasionalPing(void) = 0;
	virtual bool IsConnected(void) = 0;
	virtual unsigned int GetSynchronizedRandomInteger(void) = 0;
	virtual bool GenerateCompressionLayer(unsigned int inputFrequencyTable[256], bool inputLayer) = 0;
	virtual bool DeleteCompressionLayer(bool inputLayer) = 0;
	virtual void RegisterAsRemoteProcedureCall(int* uniqueID, void(*functionPointer) (RPCParameters *rpcParms)) = 0;
	virtual void RegisterClassMemberRPC(int* uniqueID, void *functionPointer) = 0;
	virtual void UnregisterAsRemoteProcedureCall(int* uniqueID) = 0;
	virtual bool RPC(int* uniqueID, const char *data, unsigned int bitLength, PacketPriority priority, PacketReliability reliability, char orderingChannel, bool shiftTimestamp) = 0;
	virtual bool RPC(int* uniqueID, BitStream *bitStream, PacketPriority priority, PacketReliability reliability, char orderingChannel, bool shiftTimestamp) = 0;
	virtual bool RPC_(int* uniqueID, BitStream *bitStream, PacketPriority priority, PacketReliability reliability, char orderingChannel, bool shiftTimestamp, NetworkID networkID) = 0;
	virtual void SetTrackFrequencyTable(bool b) = 0;
	virtual bool GetSendFrequencyTable(unsigned int outputFrequencyTable[256]) = 0;
	virtual float GetCompressionRatio(void) = 0;
	virtual float GetDecompressionRatio(void) = 0;
	virtual void AttachPlugin(void *messageHandler) = 0;
	virtual void DetachPlugin(void *messageHandler) = 0;
	virtual BitStream * GetStaticServerData(void) = 0;
	virtual void SetStaticServerData(const char *data, const int length) = 0;
	virtual BitStream * GetStaticClientData(const PlayerID playerId) = 0;
	virtual void SetStaticClientData(const PlayerID playerId, const char *data, const int length) = 0;
	virtual void SendStaticClientDataToServer(void) = 0;
	virtual PlayerID GetServerID(void) = 0;
	virtual PlayerID GetPlayerID(void) = 0;
	virtual PlayerID GetInternalID(void) = 0;
	virtual const char* PlayerIDToDottedIP(const PlayerID playerId) = 0;
	virtual void PushBackPacket(Packet *packet, bool pushAtHead) = 0;
	virtual void SetRouterInterface(void *routerInterface) = 0;
	virtual void RemoveRouterInterface(void *routerInterface) = 0;
	virtual void SetTimeoutTime(RakNetTime timeMS) = 0;
	virtual bool SetMTUSize(int size) = 0;
	virtual int GetMTUSize(void) = 0;
	virtual void AllowConnectionResponseIPMigration(bool allow) = 0;
	virtual void AdvertiseSystem(const char *host, unsigned short remotePort, const char *data, int dataLength) = 0;
	virtual RakNetStatisticsStruct * GetStatistics(void) = 0;
	virtual void ApplyNetworkSimulator(double maxSendBPS, unsigned short minExtraPing, unsigned short extraPingVariance) = 0;
	virtual bool IsNetworkSimulatorActive(void) = 0;
	virtual PlayerIndex GetPlayerIndex(void) = 0;
};
