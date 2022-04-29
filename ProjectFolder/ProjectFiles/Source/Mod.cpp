#include "GameAPI.h"
#include "QuarryBlock.h"
#include <fstream>
#include <iostream>

/************************************************************
	Custom Variables for the mod
*************************************************************/

// Stores all Quarry blocks currently in the world
std::vector<QuarryBlock> quarryBlocks;

// The name of the world
std::wstring worldName;

// All blocks with possible interactions
const int quarryBlockID = 1473066952;
const int mark1BlockID = 430459851;
const int mark2BlockID = 430459852;
const int mark3BlockID = 430459853;
const int mark4BlockID = 430459854;
const int outBlockID = 1473066954;
const int downBlockID = 1473066955;
const int upBlockID = 1473066956;
const int inBlockID = 1473066957;
const int setBlockID = 1473066958;
const int exclBlockID = 1473066959;
const int checkBlockID = 1473066960;
const int crossBlockID = 1473066961;
const int leftBlockID = 577305854;
const int rightBlockID = 577305855;
const int backBlockID = 577305856;
const int frontBlockID = 577305857;
const int nextBlockID = 527579106;
const int prevBlockID = 527579107;
const int oresBlockID = 527579108;

/************************************************************
	Config Variables (Set these to whatever you need. They are automatically read by the game.)
*************************************************************/

UniqueID ThisModUniqueIDs[] = { quarryBlockID, outBlockID, downBlockID, upBlockID, inBlockID, setBlockID, exclBlockID, checkBlockID, 
								crossBlockID, leftBlockID, rightBlockID, backBlockID, frontBlockID, nextBlockID, prevBlockID,
								mark1BlockID, mark2BlockID, mark3BlockID, mark4BlockID, oresBlockID }; // All the UniqueIDs this mod manages. Functions like Event_BlockPlaced are only called for blocks of IDs mentioned here. 

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
			if (it->blockPosition == At) {
				newBlock = false;
				break;
			}
		}
		if (newBlock) {
			quarryBlocks.push_back(QuarryBlock(At));
		}
	}
}


// Run every time a block is destroyed
void Event_BlockDestroyed(CoordinateInBlocks At, UniqueID CustomBlockID, bool Moved)
{
	if (CustomBlockID == quarryBlockID) {

		// Goes through all Quarry blocks, deletes the one that was destroyed.
		for (auto it = quarryBlocks.begin(); it != quarryBlocks.end(); it++) {
			if (it->blockPosition == At) {
				it->destroy();
				quarryBlocks.erase(it);
				break;
			}
		}
	}
}


// Run every time a block is hit by a tool
void Event_BlockHitByTool(CoordinateInBlocks At, UniqueID CustomBlockID, wString ToolName)
{
	bool isLeftover = true; // Keeps track of whether the block is leftover (from bug or something else), i.e., it doesn't belong to a Digging Block.

	if (CustomBlockID == quarryBlockID) {
		isLeftover = false;
	}
	else if (CustomBlockID == checkBlockID || CustomBlockID == crossBlockID) {

		// Goes through all Quarry blocks, toggles the digging of the one the Check/Cross Mark block belongs to.
		for (auto it = quarryBlocks.begin(); it != quarryBlocks.end(); it++) {
			if (it->blockPosition == (At - it->buttonBlocks[6].position)) { // Specifically checks the Check Mark block (should always be the same as Cross Mark).
				it->toggleDigging();
				isLeftover = false;
				break;
			}
		}
	}
	else if (CustomBlockID == setBlockID) {

		// Goes through all Quarry blocks, toggles the settings of the one the Settings block belongs to.
		for (auto it = quarryBlocks.begin(); it != quarryBlocks.end(); it++) {
			if (it->blockPosition == (At - it->buttonBlocks[0].position)) {
				it->toggleSettings();
				isLeftover = false;
				break;
			}
		}
	}
	else if (CustomBlockID == outBlockID) {
		
		// Goes through all Quarry blocks, increments the size of the one the Outwards block belongs to.
		for (auto it = quarryBlocks.begin(); it != quarryBlocks.end(); it++) {
			if (it->blockPosition == (At - it->buttonBlocks[4].position)) {
				it->incrementSize();
				it->printSize();
				isLeftover = false;
				break;
			}
		}
	}
	else if (CustomBlockID == inBlockID) {

		// Goes through all Quarry blocks, decrements the size of the one the Inwards block belongs to.
		for (auto it = quarryBlocks.begin(); it != quarryBlocks.end(); it++) {
			if (it->blockPosition == (At - it->buttonBlocks[3].position)) {
				it->decrementSize();
				it->printSize();
				isLeftover = false;
				break;
			}
		}
	}
	else if (CustomBlockID == upBlockID) {

		// Goes through all Quarry blocks, decrements the depth of the one the Up block belongs to.
		for (auto it = quarryBlocks.begin(); it != quarryBlocks.end(); it++) {
			if (it->blockPosition == (At - it->buttonBlocks[1].position)) {
				it->decrementDepth();
				it->printDepth();
				isLeftover = false;
				break;
			}
		}
	}
	else if (CustomBlockID == downBlockID) {

		// Goes through all Quarry blocks, increments the depth of the one the Down block belongs to.
		for (auto it = quarryBlocks.begin(); it != quarryBlocks.end(); it++) {
			if (it->blockPosition == (At - it->buttonBlocks[2].position)) {
				it->incrementDepth();
				it->printDepth();
				isLeftover = false;
				break;
			}
		}
	}
	else if (CustomBlockID == mark1BlockID) {
		for (auto it = quarryBlocks.begin(); it != quarryBlocks.end(); it++) {
			if (it->blockPosition == (At - it->cornerBlocks[0].position)) {
				isLeftover = false;
				break;
			}
		}
	}
	else if (CustomBlockID == mark2BlockID) {
		for (auto it = quarryBlocks.begin(); it != quarryBlocks.end(); it++) {
			if (it->blockPosition == (At - it->cornerBlocks[1].position)) {
				isLeftover = false;
				break;
			}
		}
	}
	else if (CustomBlockID == mark3BlockID) {
		for (auto it = quarryBlocks.begin(); it != quarryBlocks.end(); it++) {
			if (it->blockPosition == (At - it->cornerBlocks[2].position)) {
				isLeftover = false;
				break;
			}
		}
	}
	else if (CustomBlockID == mark4BlockID) {
		for (auto it = quarryBlocks.begin(); it != quarryBlocks.end(); it++) {
			if (it->blockPosition == (At - it->cornerBlocks[3].position)) {
				isLeftover = false;
				break;
			}
		}
	}
	else if (CustomBlockID == nextBlockID) {

		// Goes through all Quarry blocks, goes to the next page of the settings of the one the Next block belongs to.
		for (auto it = quarryBlocks.begin(); it != quarryBlocks.end(); it++) {
			if (it->blockPosition == (At - it->buttonBlocks[12].position)) {
				it->nextSettingsPage();
				isLeftover = false;
				break;
			}
		}
	}
	else if (CustomBlockID == prevBlockID) {

		// Goes through all Quarry blocks, goes to the previous page of the settings of the one the Previous block belongs to.
		for (auto it = quarryBlocks.begin(); it != quarryBlocks.end(); it++) {
			if (it->blockPosition == (At - it->buttonBlocks[13].position)) {
				it->prevSettingsPage();
				isLeftover = false;
				break;
			}
		}
	}
	else if (CustomBlockID == leftBlockID) {

		// Goes through all Quarry blocks, increments or decrements width of the one the Left block belongs to.
		for (auto it = quarryBlocks.begin(); it != quarryBlocks.end(); it++) {
			if (it->blockPosition == (At - it->buttonBlocks[8].position)) {
				it->incrementWidth('l');
				isLeftover = false;
				break;
			}
			else if (it->blockPosition == (At - it->buttonBlocks[14].position)) {
				it->decrementWidth('l');
				isLeftover = false;
				break;
			}
		}
	}
	else if (CustomBlockID == rightBlockID) {

		// Goes through all Quarry blocks, increments or decrements width of the one the Right block belongs to.
		for (auto it = quarryBlocks.begin(); it != quarryBlocks.end(); it++) {
			if (it->blockPosition == (At - it->buttonBlocks[9].position)) {
				it->incrementWidth('r');
				isLeftover = false;
				break;
			}
			else if (it->blockPosition == (At - it->buttonBlocks[15].position)) {
				it->decrementWidth('r');
				isLeftover = false;
				break;
			}
		}
	}
	else if (CustomBlockID == backBlockID) {

		// Goes through all Quarry blocks, increments back or decrements front width of the one the Back block belongs to.
		for (auto it = quarryBlocks.begin(); it != quarryBlocks.end(); it++) {
			if (it->blockPosition == (At - it->buttonBlocks[10].position)) {
				it->incrementLength('b');
				isLeftover = false;
				break;
			}
			else if (it->blockPosition == (At - it->buttonBlocks[16].position)) {
				it->decrementLength('b');
				isLeftover = false;
				break;
			}
		}
	}
	else if (CustomBlockID == frontBlockID) {

		// Goes through all Quarry blocks, increments front or decrements back width of the one the Front block belongs to.
		for (auto it = quarryBlocks.begin(); it != quarryBlocks.end(); it++) {
			if (it->blockPosition == (At - it->buttonBlocks[11].position)) {
				it->incrementLength('f');
				isLeftover = false;
				break;
			}
			else if (it->blockPosition == (At - it->buttonBlocks[17].position)) {
				it->decrementLength('f');
				isLeftover = false;
				break;
			}
		}
	}
	else if (CustomBlockID == oresBlockID) {

		// Goes through all Quarry blocks, toggles whether to dig ores for the corresponding Quarry block.
		for (auto it = quarryBlocks.begin(); it != quarryBlocks.end(); it++) {
			if (it->blockPosition == (At - it->buttonBlocks[18].position)) {
				it->toggleDigOres();
				it->printDigOres();
				isLeftover = false;
				break;
			}
		}
	}

	if (isLeftover) {
		SetBlock(At, EBlockType::Air);
	}
}


// Run X times per second, as specified in the TickRate variable at the top
void Event_Tick()
{

	// Goes through all Quarry blocks and runs the dig method.
	for (auto it = quarryBlocks.begin(); it != quarryBlocks.end(); it++) {
		it->dig();
	}
}


// Run once when the world is loaded
void Event_OnLoad()
{
	worldName = GetWorldName();
	
	// Loads all Quarry blocks previously placed in the world into the quarryBlocks vector.
	quarryBlocks = readBlocks<QuarryBlock>(std::ifstream{worldName + L"-QuarryBlocks.txt"});

	auto it = quarryBlocks.begin();
	while (it != quarryBlocks.end()) {
		if (GetBlock(it->blockPosition).CustomBlockID != quarryBlockID) {
			it->destroy();
			it = quarryBlocks.erase(it);
		}
		else {
			it++;
		}
	}
}

// Run once when the world is exited
void Event_OnExit()
{

	// Saves all Quarry blocks to a file for later loading.
	writeBlocks<QuarryBlock>(std::ofstream{worldName + L"-QuarryBlocks.txt"}, quarryBlocks);
}



/*******************************************************

	Advanced functions

*******************************************************/

// Run every time any block is placed by the player
void Event_AnyBlockPlaced(CoordinateInBlocks At, BlockInfo Type, bool Moved)
{

}

// Run every time any block is destroyed by the player
void Event_AnyBlockDestroyed(CoordinateInBlocks At, BlockInfo Type, bool Moved)
{

}

// Run every time any block is hit by a tool
void Event_AnyBlockHitByTool(CoordinateInBlocks At, BlockInfo Type, wString ToolName)
{

}

/*******************************************************

	For all the available game functions you can call, look at the GameAPI.h file

*******************************************************/
