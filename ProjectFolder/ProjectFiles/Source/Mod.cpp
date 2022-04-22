#include "GameAPI.h"
#include "QuarryBlock.h"
#include <fstream>
#include <iostream>

/************************************************************
	Custom Variables for the mod
*************************************************************/

// Stores all Quarry blocks currently in the world
std::vector<QuarryBlock*> quarryBlocks;

// All blocks with possible interactions
const int quarryBlockID = 1473066952;
//const int markBlockID = 1473066953; // Purely for decoration
const int outBlockID = 1473066954;
const int downBlockID = 1473066955;
const int upBlockID = 1473066956;
const int inBlockID = 1473066957;
const int setBlockID = 1473066958;
//const int exclBlockID = 1473066959; // Purely for decoration
const int checkBlockID = 1473066960;
const int crossBlockID = 1473066961;


/************************************************************
	Config Variables (Set these to whatever you need. They are automatically read by the game.)
*************************************************************/

UniqueID ThisModUniqueIDs[] = { quarryBlockID, outBlockID, downBlockID, upBlockID, inBlockID, setBlockID, checkBlockID, crossBlockID }; // All the UniqueIDs this mod manages. Functions like Event_BlockPlaced are only called for blocks of IDs mentioned here. 

float TickRate = 5;							 // Set how many times per second Event_Tick() is called. 0 means the Event_Tick() function is never called.

/************************************************************* 
	Functions (Run automatically by the game, you can put any code you want into them)
*************************************************************/


// Run every time a block is placed
void Event_BlockPlaced(CoordinateInBlocks At, UniqueID CustomBlockID, bool Moved)
{
	if (CustomBlockID == quarryBlockID) {

		// Adds the newly placed Quarry block to the list of Quarry blocks (if it doesn't already exist).
		bool newBlock = true;
		for (auto it = quarryBlocks.begin(); it != quarryBlocks.end(); it++) {
			if ((*it)->getBlockPosition() == At) {
				newBlock = false;
				break;
			}
		}
		if (newBlock) {
			quarryBlocks.push_back(new QuarryBlock(At));
		}
	}
}


// Run every time a block is destroyed
void Event_BlockDestroyed(CoordinateInBlocks At, UniqueID CustomBlockID, bool Moved)
{
	if (CustomBlockID == quarryBlockID) {

		// Goes through all Quarry blocks, deletes the one that was destroyed.
		for (auto it = quarryBlocks.begin(); it != quarryBlocks.end(); it++) {
			if ((*it)->getBlockPosition() == At) {
				(*it)->destroy();
				quarryBlocks.erase(it);
				break;
			}
		}
	}
}


// Run every time a block is hit by a tool
void Event_BlockHitByTool(CoordinateInBlocks At, UniqueID CustomBlockID, std::wstring ToolName)
{
	if (CustomBlockID == checkBlockID || CustomBlockID == crossBlockID) {

		// Goes through all Quarry blocks, toggles the digging of the one the Check/Cross Mark block belongs to.
		for (auto it = quarryBlocks.begin(); it != quarryBlocks.end(); it++) {
			if ((*it)->getBlockPosition() == (At - CoordinateInBlocks(0, 0, 6))) {
				(*it)->toggleDigging();
				break;
			}
		}
	}
	else if (CustomBlockID == setBlockID) {

		// Goes through all Quarry blocks, toggles the settings of the one the Settings block belongs to.
		for (auto it = quarryBlocks.begin(); it != quarryBlocks.end(); it++) {
			if ((*it)->getBlockPosition() == (At - CoordinateInBlocks(0, 0, 4))) {
				(*it)->toggleSettings();
				break;
			}
		}
	}
	else if (CustomBlockID == outBlockID) {
		
		// Goes through all Quarry blocks, increments the size of the one the Outwards block belongs to.
		for (auto it = quarryBlocks.begin(); it != quarryBlocks.end(); it++) {
			if ((*it)->getBlockPosition() == (At - CoordinateInBlocks(-1, 0, 0))) {
				(*it)->incrementSize();
				(*it)->printSize();
				break;
			}
		}
	}
	else if (CustomBlockID == inBlockID) {

		// Goes through all Quarry blocks, decrements the size of the one the Inwards block belongs to.
		for (auto it = quarryBlocks.begin(); it != quarryBlocks.end(); it++) {
			if ((*it)->getBlockPosition() == (At - CoordinateInBlocks(1, 0, 0))) {
				(*it)->decrementSize();
				(*it)->printSize();
				break;
			}
		}
	}
	else if (CustomBlockID == upBlockID) {

		// Goes through all Quarry blocks, decrements the depth of the one the Up block belongs to.
		for (auto it = quarryBlocks.begin(); it != quarryBlocks.end(); it++) {
			if ((*it)->getBlockPosition() == (At - CoordinateInBlocks(0, 0, 2))) {
				(*it)->decrementDepth();
				(*it)->printDepth();
				break;
			}
		}
	}
	else if (CustomBlockID == downBlockID) {

		// Goes through all Quarry blocks, increments the depth of the one the Down block belongs to.
		for (auto it = quarryBlocks.begin(); it != quarryBlocks.end(); it++) {
			if ((*it)->getBlockPosition() == (At - CoordinateInBlocks(0, 0, 1))) {
				(*it)->incrementDepth();
				(*it)->printDepth();
				break;
			}
		}
	}
}


// Run X times per second, as specified in the TickRate variable at the top
void Event_Tick()
{

	// Goes through all Quarry blocks and runs the dig method.
	for (auto it = quarryBlocks.begin(); it != quarryBlocks.end(); it++) {
		(*it)->dig();
	}
}


// Run once when the world is loaded
void Event_OnLoad()
{

	// Loads all Quarry blocks previously placed in the world into the quarryBlocks vector.
	quarryBlocks = QuarryBlock::readQuarryBlocks(std::ifstream{ "QuarryBlocks.txt" });
}

// Run once when the world is exited
void Event_OnExit()
{

	// Saves all Quarry blocks to a file for later loading.
	QuarryBlock::writeQuarryBlocks(std::ofstream{ "QuarryBlocks.txt" }, quarryBlocks);
}

/*******************************************************

	For all the available game functions you can call, look at the GameAPI.h file

*******************************************************/
