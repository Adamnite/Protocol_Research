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
		//Start a basic connection
		Server(std::string const& _client, TimeChain const& _ch, short _portNumber, int peerid, NodeStatus: full)

			void connect(std::string const id, uint portnumber = 30303) { connect(asio::ip::tcp::endpoint(asio::ip::address::from_string(_addr), _portnumber)) };
	}		void connect(asio::ip::tcp::endpoint const& _ep);
			
	bool process(TimeChain& _bc, PendingTransactions&, Overlay& _o);
	bool process(TimeChain& _bc);



	//Implement whitelist/graylist methodlogy used by Monero. We can get a quasi BAR Gossip Protocol that incentivizes full nodes to act altrustically and push data to half nodes.
	

	//Set Peer Count (maximum of 15, although can be less) Implement error if it goes over 15
	void setCount(unsigned _n) { m_Count = _n };
	//Set the maximum POM (Proof of Misbehavior) that a node will accept 
	void setProofCount(unsigned _m) { m_ProofCount = _m };

	void setStatus(NodeStatus _m) {
		m_mode = _m;
	}

	void setVerbosity(unsigned _i) { m_verbosity = _i; }
	
	std::vector<BasicPeerData> whitelist() const;
	std::vector<BasicPeerData> greylist() const;

	unsigned peerCount() const {
		return m_whitelist.size();
	}

	//Get extra peers from greylist if needed (total number of peers is less than ideal peer count for node)
	//Only add peers that have a POM less than the accepted amount for the peer
	if (peerCount() < setCount()) {
		a = peerCount();
		for (int i = 0; i < greylist.size(); greylist++) {
			if(greylist[i].POM() < setProofCount()){
				m_whitelist.push(greylist[i]);
		}
	}

	void pingAll();
	//Implement logic to automatically move unresponsive peers to greylist from the whitelist
	short listenPort() const { return m_public.port(); }

private:
	void seal(bytes& _b);
	void populateIds();
	void matchRandomly(std::string const& _RandomSeed, bool _accep);
	void AcceptingNew();

	std::vector<asio::ip::tcp::endpoint> newPeers();


	//The remainder of the public class should be standard code defining vectors analyzing bytestreams of transactions, blocks, etc.

	

	std::chrono::steady_clock::time_point m_PeersRequest;
	//Implement code to push peers who have not responsded to the greylist.


	
	
	};
		








} 
		
