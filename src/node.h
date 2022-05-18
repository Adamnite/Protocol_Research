#pragma once


#include <asio.hpp>
#include <asio/ts/buffer.hpp>
#include <asio/ts/internet.hpp>
#include <memory>
#include <utility>
#include <thread>

using asio::ip::tcp;


namespace adamnite
{
	class TimeChain;
	class PendingTransactions;

	
	class Server;

	uint32_t max_output_connections;
	uint32_t max_input_connections;
	enum peer_commands {
		Start = 0,
		Disconnect,
		Ping,
		Pong,
		GetPeerList = 0x15,
		GetPeers,
		GetTransactions,
		GetBlocks,
		GetChain


	};

	struct basic_peer_data
	{
		std::string Version;
		std::string host;
		int id;
		uint32_t random_seed;
		int current_connections;
		short portNumber;
		std::chrono::steady_clock::duration lastMessage;
		
	};


	class Session :
	{
		friend class Server;

	public:
		void start;
		void stop;
		asio::ip::tcp::endpoint endpoint;

	private:
		void dropped;
		void read;
		void write;
		bool interpeted(serlialize);
		bool matched_up(peers); //for light nodes that depend on internal gossip to get data from full node peers
		//Probably implement an optimistic push, where altrustic nodes push data to paired light nodes. Works directly into DPOS
		//as nodes who do this will be more likely to get elected.

		void Send(Serialized_Byte_Steam);
		asio::ip::tcp::socket csocket;
		PeerHeader cheader;
		static PeerList& prep(PeerList& _s);

		bytes cexternal;
		uint cnetwork_id;
		short c_listenport;

		std::chrono::steady_clock::time_point cping;
		std::chrono::steady_clock::time_point cconnect;
		std::chrono::steady_clock::time_point cdisconnect;

		std::set known_blocks;
		std::setbuf cknowntransactions;

	};


	enum class NodeStatus {
		Light,
		Server,
		Full
	};

	class Server
	{
		friend class Session;

	public:
		Server(std::string const& _client
	};
		
