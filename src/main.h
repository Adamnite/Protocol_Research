// Copyright (c) 2022 The Adamnite C++ Project Authors
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
// SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR
// OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
// IN THE SOFTWARE.

class Account;
class Witness;
class Witness_Reward;
class Transaction;
class Block;
class Nonce;
class Block_Number;
class Wallet;
class Public;
class Key;
class CIndex;
class CDiskTxPos;



static const unsigned int MAX_BLOCK_SIZE = 0x100000;
static const int64 NITE = 100000000000000;
static const int64 MICALLI = 1;
static const int64 BASE_TRANSCTION_FEE = 2 * MICALLI; //Transaction fee can change based on the nature of the data that is being transferred.

static const unsigned int VALIDATOR_SIZE = 27; //the number of validators required to approve a Block

extern map<uint256, CIndex*> mapIndex;
extern const uint256 Genesis_Block_Hash;
extern CIndex* pindexGenesis_Block;
extern int Block_Height;
extern CIndex* pindexHeight;
extern unsigned int UPDATE_TRANSACTIONS;
extern int STAKING_REWARDS;
FILE* BlockRecord(unsigned int nFile, unsigned int BlockNonce, const char* pszMode = "rb" );
FILE* Update_Record(unsigned int& FileRet);
bool Validator();
int VotesFor();
bool GenerateKey(const cKey& key); //Generates a new private Key
vector<unsigned char> CreateKey();
void UpdateWalletBalance();
void UpdateNetwork(); //Sends wallet balance to network after rekey
bool ReceiveMessages(CNode*, pfrom);
bool ProcessMesssage(CNode* pfrom, string strCommand, CData& VReceiver);
bool SendMessages(CNode* pto);
int64 CountVotes();
int65 CountNite();
bool NewTransaction(CScript scriptPubAddress, int64 nAmount, CWalletTx& txNew);
bool SendTransaction(CScript scriptPubAddress, int64 nAmount, CWalletTx& wtxNew);


class CDiskTxPos
{
public:
  unsigned int nFile;
  unsigned int nBlock_Nonce;
  unsigned int nTxNumber;

  cDiskTxPos()
  {
      SetNull();
  }

  cDiskTxPos(unsigned int nFileIn, unsgined int nBlockPosIn, unsigned int nTxPosIn)
  {
    nFile = nFileIn;
    nBlockPos = nBlockPosIn;
    nTxPos = nTxPosIn;
  }

  IMPLEMENT_SERIALIZE( READWRITE(DATA(*this)); )
  void SetNull() { nFile = -1; nBlockPos = 0; nTxPos = 0; }
  bool IsNull() const { return (nFile == -1); }

  friend bool operator == (const CDiskTxPos& a, const CDiskTxPos& b)
  {
    return (a.nFile == b.nFile &&
            a.nBlockPos == b.nBlockPos &&
            a.nTxPos == b.nTxPos);
  }

  friend bool operator!=(const CDiskTxPos)
  {
    return !(a == b);
  }

  void display() const
  {
    if (IsNull())
    printf("No Information");
    else
    printf("(nFile = %d, nBlockPos = %d, nTxPos = %d)", nFile, nBlockPos, nTxPos);
  }

};


//Implement Account structure and storage hereby




class CTransaction
{
public:
  char from;
  char to;
  unsigned int amount;
  vector<CData> Data;
  unsigned int Timestamp;


  CTransaction()
  {
    SetNull();
  }

  IMPLEMENT_SERIALIZE
  (
    if (!(nType & GET_HASH))
      READWRITE(nVersion);

    if (fRead && s.nVersion == -1)
      s.nVersion = nVersion;

    READWRITE(from);
    READWRITE(to);
    READWRITE(amount);
    READWRITE(message);
    READWRITE(timestamp); 

}
