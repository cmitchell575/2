/***************************************
Round 1 Voting
Author: Chase Mitchell
Date Completed: 11/11/25
Description: This is an example assignment letting us work on the code that will be used in the upcoming assignment.
***************************************/
#include <iostream>
#include "HashTable.hpp"
using namespace std;
// Implement definition of Candidate data type here
class Candidate {
    private:
        string id_;
        string name_;
    public:
        Candidate(string id, string name)
        : id_(id), name_(name){}

        string getId();
        {
            return id_;
        }
        
        string getName();
        {
            return name_;
        }
}

// Implement definition of Ballot data type here
class Ballot {
    private:
        string choiceOne_;
        string choiceTwo_;
        string choiceThree_;
    public:
        Ballot(string c1,string c2,string c3)
        : choiceOne_(c1),choiceTwo_(c2,),choiceThree(c3){}
        string getHighestRankedCandidate() {
            return choiceOne_;
        }
}

// Implement body of "tallyRound1Votes" non-member function
HashTable<int> tallyRound1Votes(LinkedList<Ballot> &ballots, HashTable<Candidate> &candidates)
{
    HashTable<int> talliedVotes;
     for (HashTable<Candidate>::Iterator iter = candidates.generateIterator(); iter.hasNext(); iter.next()) {
        string cid = iter.current()->first;
        talliedVotes.add(cid,0);
     }
     for (LinkedList<Ballot>::Iterator iterBall = ballots.generateIterator(); iterBall.hasNext(); iterBall.next()){
        Ballot b = iterBall.current();
        string cid = b.getHighestRankedCandidate();
        int current = talliedVotes.getValue(cid);
        talliedVotes.update(cid, current + 1);
     }
     return talliedVotes;
}
// Implement body of "processRound1Results" non-member function
void processRound1Results(HashTable<int> &talliedVotes, HashTable<Candidate> &candidates, float halfOfVotes)
{
    cout << "Round 1 Results:" << endl;

    // initialize directly from the first entry
    HashTable<int>::Iterator iter = talliedVotes.generateIterator();
    if (!iter.hasNext()) { 
        cout << endl << "No candidate had more than 50% of the votes" << endl;
        return;
    }

    string highestId = iter.current()->first;
    int    highestVotes = iter.current()->second;
    string lowestId  = highestId;
    int    lowestVotes = highestVotes;

    // print first
    {
        Candidate c = candidates.getValue(highestId);
        cout << c.getName() << ": " << highestVotes << " vote(s)" << endl;
    }

    // process the rest
    for (iter.next(); iter.hasNext(); iter.next()) {
        string cid = iter.current()->first;
        int    votes = iter.current()->second;
        Candidate c = candidates.getValue(cid);

        cout << c.getName() << ": " << votes << " vote(s)" << endl;

        if (votes > highestVotes) { highestVotes = votes; highestId = cid; }
        if (votes < lowestVotes)  { lowestVotes  = votes;  lowestId  = cid; }
    }

    cout << endl;

    if (highestVotes > halfOfVotes) {
        cout << candidates.getValue(highestId).getName() << " is the winner!" << endl;
    } else {
        cout << "No candidate had more than 50% of the votes" << endl;
        cout << candidates.getValue(lowestId).getName()<< " had the least number of votes and will be eliminated" << endl;
    }
}
// This function is used to test implementation of the "tallyRound1Votes"
// and "processRound1Results" non-member functions.
void test1()
{
LinkedList<Ballot> ballots;
ballots.pushFront(Ballot("CC", "CB", "CA"));
ballots.pushFront(Ballot("CB", "CA", "CC"));
ballots.pushFront(Ballot("CC", "CB", "CA"));
ballots.pushFront(Ballot("CC", "CA", "CB"));
ballots.pushFront(Ballot("CA", "CB", "CC"));
ballots.pushFront(Ballot("CC", "CA", "CB"));
ballots.pushFront(Ballot("CB", "CA", "CC"));
ballots.pushFront(Ballot("CA", "CB", "CC"));
ballots.pushFront(Ballot("CB", "CC", "CA"));
ballots.pushFront(Ballot("CA", "CB", "CC"));
ballots.pushFront(Ballot("CC", "CB", "CA"));
ballots.pushFront(Ballot("CC", "CA", "CB"));
ballots.pushFront(Ballot("CB", "CA", "CC"));
HashTable<Candidate> candidates;
candidates.add("CA", Candidate("CA", "Candidate A"));
candidates.add("CB", Candidate("CB", "Candidate B"));
candidates.add("CC", Candidate("CC", "Candidate C"));
int totalVotes(ballots.size());
float halfOfVotes = float(totalVotes)/2;
cout<<"Total Votes: "<<totalVotes<<endl<<endl;
HashTable<int> talliedVotes = tallyRound1Votes(ballots, candidates);
processRound1Results(talliedVotes, candidates, halfOfVotes);
}
// This function is used to test implementation of the "tallyRound1Votes"
// and "processRound1Results" non-member functions.
void test2()
{
LinkedList<Ballot> ballots;
ballots.pushFront(Ballot("3", "4", "2"));
ballots.pushFront(Ballot("2", "1", "4"));
ballots.pushFront(Ballot("4", "2", "3"));
ballots.pushFront(Ballot("3", "1", "2"));
ballots.pushFront(Ballot("1", "4", "2"));
ballots.pushFront(Ballot("3", "1", "2"));
ballots.pushFront(Ballot("3", "2", "1"));
ballots.pushFront(Ballot("1", "2", "3"));
ballots.pushFront(Ballot("3", "1", "4"));
ballots.pushFront(Ballot("4", "2", "3"));
ballots.pushFront(Ballot("3", "1", "2"));
HashTable<Candidate> candidates;
candidates.add("1", Candidate("1", "Candidate A"));
candidates.add("2", Candidate("2", "Candidate B"));
candidates.add("3", Candidate("3", "Candidate C"));
candidates.add("4", Candidate("4", "Candidate D"));
int totalVotes(ballots.size());
float halfOfVotes = float(totalVotes)/2;
cout<<"Total Votes: "<<totalVotes<<endl<<endl;
HashTable<int> talliedVotes = tallyRound1Votes(ballots, candidates);
processRound1Results(talliedVotes, candidates, halfOfVotes);
}
// Driver code calls both tests
int main()
{
cout<<"Test 1:\n\n";
test1();
cout<<"\n\nTest 2:\n\n";
test2();
return 0;
}
