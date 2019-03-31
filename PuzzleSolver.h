#ifndef PUZZLESOLVER_H
#define PUZZLESOLVER_H
#include <stack>
#include <queue>
#include <vector>
#include "StateNode.h"
#include <map>
#define BREADTH_FS 100
#define BFS  1
#define DFS  2
#define IDFS 3
#define BSearchFirst 4
#define BSearchFirstSET 5
#include <iterator>
#include <algorithm>
#include <string>
#include <sstream>
#include <math.h>
class Compare
{
public:
    bool operator() (const std::unique_ptr<StateNode>& lhs,const std::unique_ptr<StateNode>& rhs)
    {
        return (*lhs < *rhs);
    }
};

class CompareSET
{
public:
    bool operator() (const std::unique_ptr<StateNode>& lhs,const std::unique_ptr<StateNode>& rhs)
    {
        return (*lhs > *rhs);
    }
};
class PuzzleSolver
{
    public:
        PuzzleSolver(const std::string & goal); //Conctructor
        void setGoalState(const std::string &intialState); //Set the internel goal state
        //Specify which method to use, method
        StateNode solve(const std::string& intialStateString, unsigned int method); //Solve the puzzle problem
        std::string solveString(const unsigned int &intialStateStringPtr, unsigned int method); //Solve the puzzle problem
        std::string traceSolution(const StateNode& node); //trace the solution to the problem
        //Web Assembling Interface
        ~PuzzleSolver();



    private:
        std::vector<std::vector<int> > convertVectorArray(const std::string& puzzleString);
        bool checkSolvable(const std::vector<std::vector<int> > &intialState); //check if the current puzzle is solvable 
        std::vector<std::unique_ptr<StateNode>> discoveredNodes; // set of already expanded node including the original problem 
        std::map<std::string, std::unique_ptr<StateNode>> discoveredmap; //set of already expanded node including the original problem using map for
        //faster search and inserts
        std::stack<std::unique_ptr<StateNode>>  DFSstack; //Depth First Search Stack 
        std::queue<std::unique_ptr<StateNode>>  BFSqueue; //Breadth First Search Stack 
        std::priority_queue<std::unique_ptr<StateNode>,std::vector<std::unique_ptr<StateNode>>,Compare> pQueue;
        StateNode intialState; //The intial problem node
        StateNode goalState; //The goal state set bu setGoalState method
        bool isDiscovered(StateNode &node);
        bool isGoal(const StateNode& node);//check if the goal is reached by the passed in node
        //Search Algorithiums
        StateNode DFSearch(const std::vector<std::vector<int>>& intialState); //BFS helper function
        StateNode BestFirstSearch(const std::vector<std::vector<int>>& intialState); //BFS helper function
        StateNode BFSearch(const std::vector<std::vector<int>>& intialState);//DFS helper funciton 
        StateNode InterativeDFSearch(const std::vector<std::vector<int>>& intialState, unsigned int maxLevel);////IDFS helper funciton 
        bool insertDiscovered(std::unique_ptr<StateNode>& node);//insert node into the discovered map or vector
        std::multiset<std::unique_ptr<StateNode>,CompareSET> pQueueSet;
        StateNode BestFirstSearchSet(const std::vector<std::vector<int>>& intialState); //BFS helper function
        //clear internel datasctucture
        //Deconstructor
        bool checkValidPuzzle(long double x);
        void clear();
        
        
};



#endif // PUZZLESOLVER_H
