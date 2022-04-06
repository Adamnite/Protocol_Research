This file defines the overall layout of the Adamnite prototype, as defined in C++. This prototype will include: an implementation of the distributed ledger, DPOS consensus mechanism, and the virtual machine.

For the distributed ledger, the following requirements must be met:

* Wallets/Accounts must be defined. Each wallet must have an associated public key (corresponding to the public address that is used to identify the account) and a private key that is used to sign transactions.

* A peer to peer network that allows individual nodes to both send and receive various messages must be defined. Particular types of messages (a voting message) must also be defined.

* Blocks, Transactions, etc. Already defined.

* A consensus process (DPOS)

