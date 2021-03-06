// Implementation of the Draft header file
// The methods are labeled as 'method x' as denoted in the assignment instructions

#include "Draft.h"

//-------------------------------------------------------------------------
// Name:        Draft (method a)
// Parameters:  none
// Returns:     nothing
// Purpose:     Default constructor of the Draft class; it initalizes the 
//              two instance variables of the class to zero 
//      THIS CODE IS GIVEN TO YOU AND SHOULD NOT NEED TO BE EDITED!
//-------------------------------------------------------------------------
Draft::Draft()
{
	numPlayers = 0;
    numAvailable = 0;
}

//-------------------------------------------------------------------------
// Name:        Draft (method b)
// Parameters:  Draft object 
// Returns:     nothing
// Purpose:     Copy constructor of the Draft class; it copies the instance
//              variables from copyMe to this object.
//              Be sure to also copy each element of the copyMe.allPlayers[]
//              array into this class's allPlayers[] array (you'll need a loop!)
//-------------------------------------------------------------------------
Draft::Draft(const Draft &copyMe)
{
    //Copying both of the variables from the old object to the new object
    numPlayers = copyMe.numPlayers;
    numAvailable = copyMe.numAvailable;
    for (int i = 0; i < MAX_PLAYERS; i++){ //Looping through the array to copy all of the values to the new object
        allPlayers[i] = copyMe.allPlayers[i];
    }
}

//-------------------------------------------------------------------------
// Name:        ~Draft (method c)
// Parameters:  none
// Returns:     nothing
// Purpose:     Destructor. There is no memory to deallocate, so nothing
//              is implemented here
//      THIS CODE IS GIVEN TO YOU AND SHOULD NOT NEED TO BE EDITED!
//-------------------------------------------------------------------------
Draft::~Draft()
{
    
}

//-------------------------------------------------------------------------
// Name:        draftPlayer (method k)
// Parameters:  string: teamName, the name of the drafting team (pass-by-value)
//				int: playerIndex, the index of the player who is being drafted (pass-by-value)
// Returns:     nothing
// Purpose:     Private helper function. Sets the Player's (in the array at index
//              PlayerIndex) status to taken, changes their team name to the
//              team to which they were drafted.  Once a Player is drafted,
//              the number of available Players should decrease
//-------------------------------------------------------------------------
void Draft::draftPlayer(const string teamName, const int playerIndex)
{
    // Set the Player (at the provided index) as taken and set the team name to the drafting team
    allPlayers[playerIndex - 1].setTeamName(teamName);
    allPlayers[playerIndex - 1].setTaken();

    // Print out a message letting the user know that the Player has been drafted
    cout << teamName << " has drafted " << allPlayers[playerIndex - 1].getFirstName() << " " << allPlayers[playerIndex - 1].getLastName();
    // decrease the number of available Players
    numAvailable = numAvailable - 1;
}

//-------------------------------------------------------------------------
// Name:        getNumPlayers (method f)
// Parameters:  none
// Returns:     int, the number of total players in the class
// Purpose:     accessor (getter) for our private instance variable
//-------------------------------------------------------------------------
int Draft::getNumPlayers() const
{
    return numPlayers;
}

//-------------------------------------------------------------------------
// Name:        getNumAvailable (method g)
// Parameters:  none
// Returns:     int, the number of available players in the class
// Purpose:     accessor (getter) for our private instance variable
//-------------------------------------------------------------------------
int Draft::getNumAvailable() const
{
    return numAvailable;
}

//-------------------------------------------------------------------------
// Name:        readFile (method e)
// Parameters:  string, fileName, the name of the file we're opening (pass-by-value)
// Returns:     nothing
// Purpose:     Get the Player information from a text file of the Players
//              who have entered the draft.
//              There are FIVE pieces of data per line: firstName (string), 
//              lastName (string), position (string), overallRank (integer), 
//              and positionalRank (integer)
//              When you have retrieved one line of the text file, use the
//              Player class setters to set information in the allPlayers[] array 
//-------------------------------------------------------------------------
void Draft::readFile(const string filename)
{
    // open the file
    ifstream infile;
    infile.open(filename);

    // create temporary variables to read information into
    string tempfname, templname, tempposition;
    int tempoverallrank, temppositionrank;
    numPlayers = 0;
    // Read the file (in a loop), reading each line into the temporary variables
        while (infile >> tempfname >> templname >> tempposition >> tempoverallrank >> temppositionrank){
            //Setting each players respective values
            allPlayers[numPlayers].setName(tempfname, templname);
            allPlayers[numPlayers].setPosition(tempposition);
            allPlayers[numPlayers].setOverallRank(tempoverallrank);
            allPlayers[numPlayers].setPositionRank(temppositionrank);
            allPlayers[numPlayers].setUntaken(); //Allowing them to be drafted
            numPlayers++; //Counting the number of players read in
        }


    // Set the number of Players available to draft equal to the total number of Players
    numAvailable = numPlayers;

    // Close the file
    infile.close();
}

//-------------------------------------------------------------------------
// Name:        isValidPosition (method i)
// Parameters:  string: position, the position we are validating (pass-by-value)
// Returns:     boolean, if the user input is valid
// Purpose:     Goes through allPlayers[] array and checks if the given
//			    position is valid - checking both that the user input is a valid
//              position name, AND that there exists at least one undrafted player
//              still available in that position
//-------------------------------------------------------------------------
bool Draft::isValidPosition(const string position) const
{
	// Go through the all_players array and if there's a position name match of an
	// undrafted player, return true.  Else, return false since either the position 
	// doesn't exist or all available players in that position have already been drafted
    for (int i = 0; i < numPlayers; i++){
        if (allPlayers[i].isTaken() == false && allPlayers[i].getPosition() == position){
            return true;
        }
    }
    return false;
}

//-------------------------------------------------------------------------
// Name:        isValidName (method l)
// Parameters:  string: lastName, the Player's last name (pass-by-value)
// Returns:     boolean, whether the name passed in matches a name in our array
// Purpose:     Checks whether a given name is valid.
// 		        Returns true if the name is found in the allPlayers array
//		        Returns false if it is not found
//-------------------------------------------------------------------------
bool Draft::isValidName(const string lastName) const
{
    // Create a variable to keep track of whether we have a valid name (start at false)
    bool t_or_f = false;
    // loop through the allPlayers[] array
    for (int i = 0; i < numPlayers; i++){
        if (allPlayers[i].getLastName() == lastName){ //Checks to see if the input is equal to players last name
            t_or_f = true;
        }
    }
    return t_or_f;
}

//-------------------------------------------------------------------------
// Name:        pickByName (method m)
// Parameters:  string: teamName, the team that is drafting (pass-by-value)
// Returns:     nothing
// Purpose:     Chooses Player based on given name
//-------------------------------------------------------------------------
void Draft::pickByName(const string teamName)
{
    // Make sure there are still players available to draft.  If not, print a message
    // and don't try to get a player name
    if (numAvailable == 0){
        cout << "I'm sorry, there are no more players available." << endl;
    }
    else{
        string lname; //Creating a user input variable to allow them to select a player
        int index = 0;
        bool name_v_or_inv = false; //Bool to check whether or not the input from the user is valid or invalid
        bool taken = true;
        
        do { //Using a do while because I want this to execute at least once
            cout << "Please enter the last name of the player you want for your team." << endl;
            cin >> lname;
            for (int i = 0; i < numPlayers; i++){
                if (lname == allPlayers[i].getLastName()){ //Runs if name is valid
                    name_v_or_inv = true; //Satisfies first condition to break the loop
                    if (allPlayers[i].isTaken() == false){
                        index = i; //Gets player index
                        taken = false;//Breaks loop because player name matches and they are not taken.
                    }
                }
            }
            if (name_v_or_inv == false){ //If inputted name didn't match
                cout << "Invalid last name. Please try again." << endl;
            }
            else if (taken == true){ //If the player had already been drafted.
                cout << "Player has already been drafted. Please try again." << endl;
            }
        } while (name_v_or_inv == false || taken == true);
        
        //Drafting player to team
        cout << allPlayers[index].getFirstName() << " " << allPlayers[index].getLastName() << " has been drafted to the " << teamName << "." << endl;
        allPlayers[index].setTeamName(teamName);
        allPlayers[index].setTaken();
    }

}

//-------------------------------------------------------------------------
// Name:        pickBestOverall (method o)
// Parameters:  string: teamName, the team that is drafting (pass-by-value)
// Returns:     nothing
// Purpose:     Drafts the best Player based on overallRank value to the team
//              whose name is passed in
//          Note: a smaller value is better (i.e. an overallRank of 1 is best)
//-------------------------------------------------------------------------
void Draft::pickBestOverall(const string teamName) 
{
    // Create some variables to keep track of the best index and best rank found so far
    int bestIndex = numPlayers;
    int bestRank = numPlayers;
	// loop over all players to find the lowest overall rank
    for (int i = 0; i < numPlayers; i++){
        if (allPlayers[i].getOverallRank() < bestRank && allPlayers[i].isTaken() == false){ //Checks to see if the players rank is the lowest and if they are available.
            bestRank = allPlayers[i].getOverallRank();
            bestIndex = i;
        }
    }
	allPlayers[bestIndex].setTeamName(teamName);
    allPlayers[bestIndex].setTaken();
    cout << allPlayers[bestIndex].getFirstName() << " " << allPlayers[bestIndex].getLastName() << " has been drafted to the " << teamName << "." << endl; 
    numAvailable = numAvailable - 1;
}

//-------------------------------------------------------------------------
// Name:        pickBestByPosition (method p)
// Parameters:  string: position (pass-by-value)
//				string: teamName, the team that is drafting (pass-by-value)
// Returns:     nothing
// Purpose:     Drafts the best Player in a specified position based on 
//              positionRank value to the team whose name is passed in
//          Note: a smaller value is better (i.e. a positionRank of 1 is best)
//-------------------------------------------------------------------------
void Draft::pickBestByPosition(const string position, const string teamName) 
{
    // Create some variables to keep track of the position rank and position index
    int posrank = numPlayers;
    int posindex = numPlayers;
	// loop over all players to find the lowest position rank
    for (int i = 0; i < numPlayers; i++){
        if (allPlayers[i].getPositionRank() < posrank && allPlayers[i].getPosition() == position && allPlayers[i].isTaken() == false){ //Checks to see if players rank is lower, and if the position matches, and that they are not taken
            posrank = allPlayers[i].getPositionRank(); //If conditions are met the lowest rank so far is set
            posindex = i; //If conditions are met the index is stored
        }
    }
    // Drafting player using logged index and teamName parameter
    allPlayers[posindex].setTaken();
    allPlayers[posindex].setTeamName(teamName);

    cout << allPlayers[posindex].getFirstName() << " " << allPlayers[posindex].getLastName() << " has been drafted to " << teamName << "." << endl;
}

//-------------------------------------------------------------------------
// Name:        printAllPlayers (method d)
// Parameters:  none
// Returns:     nothing
// Purpose:     Prints all Players in the draft, regardless of whether or 
//              not they've been drafted
//      THIS CODE IS GIVEN TO YOU AND SHOULD NOT NEED TO BE EDITED!
//-------------------------------------------------------------------------
void Draft::printAllPlayers() const
{
    cout << "Here are all the players in the draft: \n";
    // Loop through the allPlayers[] array
	for(int i=0; i<numPlayers; i++)
	{
	    // Print each Player
		allPlayers[i].print();
	}
}

//-------------------------------------------------------------------------
// Name:        printAvailablePlayers (method h)
// Parameters:  none
// Returns:     nothing
// Purpose:     Prints all available Players (if they are not drafted/taken)
//-------------------------------------------------------------------------
void Draft::printAvailablePlayers() const
{
    // Print a message indicating the number of available players to the screen
    cout << "There are " << numAvailable << " available players to draft." << endl;
    // Loop through the allPlayers[] array
    for (int i = 0; i < numPlayers; i++){
        if (allPlayers[i].isTaken() == false){ // If the Player is not taken, print them
            allPlayers[i].print();
        }
    }
}
//-------------------------------------------------------------------------
// Name:        printAvailablePositionPlayers (method j)
// Parameters:  string: position (pass-by-value)
// Returns:     nothing
// Purpose:     Prints all available Players who play a certain Position
//-------------------------------------------------------------------------
void Draft::printAvailablePositionPlayers(const string position) const
{
    // Loop through the allPlayers[] array
    for (int i = 0; i < numPlayers; i++){
        if(!allPlayers[i].isTaken() && allPlayers[i].getPosition() == position){ //Checks to see if the position is valid or if the player is taken
            allPlayers[i].print(); // Prints the player if the conditions check out.
        }
    }
}


//-------------------------------------------------------------------------
// Name:        printTeamPlayers (method n)
// Parameters:  string: teamName, name of the team of whom to print the roster (pass-by-value)
// Returns:     nothing
// Purpose:     Prints the roster of Players in a given teamName.
//-------------------------------------------------------------------------
void Draft::printTeamPlayers(const string teamName) const
{
    // Loop through the allPlayers[] array
    for (int i = 0; i < numPlayers; i++){
        if (allPlayers[i].getTeamName() == teamName){ //Checks to see if they are on the given teamName
            allPlayers[i].print(); //Prints player names if they are on our team.
        }
    }
}
