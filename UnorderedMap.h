#pragma once
#include <vector>
#include <list>
#include <iostream>// Debugging only

// Key, Value, Hasher, Equalitor
template< typename K, typename V, typename H, typename E >
class UnorderedMap
{
	struct HashEntry
	{
		K mKey;
		V mValue;
	};
	struct HashNode
	{
		std::list<HashEntry> mEntries;
	};
	std::vector<HashNode> mData;
	// For the purposes of the "Optimize the hasher" homework, I'm going to mangle this official list of numbers.
	int GetNextSize()
	{
		return mData.size() + 13;
	}

	int mBucketsInUse = 0;// When this gets to half the vector size, we need to rehash.
	int mDebugData = 0;// Not part of our algorithm

public:
	UnorderedMap()
	{
		// A vector comes empty, so we need to force it to embiggen to allow us to access spot 90 immediately.
		mBucketsInUse = 0;
		mData.resize(17);// Fills the vector with default-constructed HashNodes.  NOT Reserve.
	}

	// No big three.  We never say "new".  stl vector and list can take care of themselves.

	void Clear()
	{
		//We want to end up just like we were when we were constructed.
		for( auto tIter = mData.begin(); tIter != mData.end(); ++tIter )// Foreach is darkside.  It copies.
			(*tIter).mEntries.clear();
		mBucketsInUse = 0;
		mDebugData = 0;
	}

	void SetWithKey(K tKey, const V &tValue)// Adding to an unordered-map in stl adds a copy, and returns a reference
	{
		H tHashor; // Movie::Hashor
		int tHash = tHashor(tKey);
		std::cout << " resulting in " << tHash << std::endl;
		tHash = abs(tHash);
		while (tHash > mData.size())
		{
			tHash /= mData.size();
		}

		HashEntry tNew;
		tNew.mKey = tKey;
		tNew.mValue = tValue;

		E tEqualitor;
		for (auto tIter = mData.begin(); tIter != mData.end(); ++tIter)
		{
			for (auto ttIter = (*tIter).mEntries.begin(); ttIter != (*tIter).mEntries.end(); ++ttIter)
			{
				if (tEqualitor(tKey, (*ttIter).mKey))
				{
					(*tIter).mEntries.erase(ttIter);
					if ((*tIter).mEntries.size() == 0)
						mBucketsInUse--;
					break;
				}
			}
		}


		// Shoot, I forgot to handle adding a duplicate using the Equalitor.  I need to remove an existing perfect match by searching everything.
		// Ah well, I'll get that new intern to do it while I'm on my trip.  Sucker!
		mData[tHash].mEntries.push_back(tNew);
		if (mData[tHash].mEntries.size() == 0)
			mBucketsInUse++;
		if( mBucketsInUse > (mData.size() / 2) )
			Rehash();// This just changed the size so do it last

		mDebugData++;
	}

	//V GetWithKey(K tKey)
	//{
	//	return V&;
	//}

	std::string DebugDump()
	{
		// I'm leaving this pile because I got mad string doesn't have useful methods.  This is C.
		char buff[100];
		snprintf(buff, 100, "There are %d out of %d buckets in use holding %d items.\n", mBucketsInUse, mData.size(), mDebugData);
		std::string tOutput(buff);
		return tOutput;
	}

private:
	void Rehash()
	{
		std::cout << "Rehash!\n";

		// The real unordered_map probably resizes on data count, not used bucket count.  But we are testing spread here so we want bucket count.

		std::list<HashEntry> tAllEntries;
		// Gather all of the entries out of the nodes.  (remember with chaining there can be more than one in each node)
		for( int i = 0; i < mData.size(); i++ )
		{
			for( auto tIter = mData[i].mEntries.begin(); tIter != mData[i].mEntries.end(); ++tIter )
				tAllEntries.push_back(*tIter);
		}

		// Wait, what was the point of rehashing again?  Grab all the data, yadda yadda, put the data back in.  Intern will get this.

		mData.resize(GetNextSize());
		// Throw all the old entries back in to the hash.
		for( auto tIter = tAllEntries.begin(); tIter != tAllEntries.end(); ++tIter )
		{
			SetWithKey((*tIter).mKey, (*tIter).mValue);
		}
		std::cout << "Rehash done!\n";

	}

};