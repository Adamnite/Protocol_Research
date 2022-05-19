#pragma once


#include <iosfwd>
#include <iterator>
#include <vector>



namespace adamnite
{
	struct peerlists {
		//Implement a protocol similar to Monero's, except with BAR-ressilency for a stronger gossip protocol.
		std::vector<peerlist> whitelist;
		std::vector<peerlist> greylist;
	};


	class peerlist_storage
	{
	public:
		peerlist_storage()
			: m_types{}
		{}

		static <peerlist_storage> open(std::istream& src, const bool new_format)

		peerlist_storage(peerlist_storage&&) = default;
		peerlist_storage(const peerlist_storage&) = delete;

		//Define how both peerlists may be stored in an optimal storage locally, either as a file or other storage method

		//Define how peerlists are returned via accessing a path

	private: 
		peerlist_types m_types;
	};
	


	class select_peer_manager
	{
	public:
		bool init(peerlist_types&& peers, bool allow_local_ip);
		size_t get_white_peers_count();
		size_t get_grey_peers_count();
		bool getpeerlist();
		bool update_peerlist(); //Update based on last activer peers
		//Add other functions as neccescary (nodes, eviction, indexing)
		//Also, proabably want to split the selection process, this is for brevity, and as is evident, not working code.
		void create_seed(PRNG, private_key_singnature);
		bool select_peer(seed, peerlist);
		//Seed a PRNG (Private Number Random Generator) with the private seed of the node, and then map that value to get the peer id of the peer.
		bool accept_peer(seed_external,message)
		//If a peer gets a request from another peer, accept only if the request checks out and the message is valid.
		//Add removal functions, POM, etc
	private:
		struct by_time();
		struct by_peer_id{};
		struct by_round{};
	};

	//Add other locking functions and peer manergial functions as needed. 
	//Add a randomizer for picking whitelist and greylist peers.
	//Define a protocol for how peers may get demoted from the whitelist to the greylist
	//Add in POM, maybe as a discredit based on sending incorrect messages, either upon the first connection or during exchange.
	//Define a pruning process (ie, only getting a certain portion of the blockchain to exchange with peers).
	//Define how an optimisitic push (ie altrustic nodes supplying data to light nodes) could work.
}
