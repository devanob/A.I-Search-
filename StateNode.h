#ifndef STATENODE_H
#define STATENODE_H
#include <vector>
#include <memory>
#include <algorithm>
#include <iostream>
#include <iomanip>
//Transistions
#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4
#define NOACTION 5
//BLANK
#define BLANK 100
#define ACTION unsigned int
#include <cstring>
#include <string>
#include <set>
class StateNode
{
    public:
        void print() const;
        void clear();
        StateNode();
        StateNode(const std::vector<std::vector<int>>& setState);
        StateNode(const StateNode& parentNode, const unsigned int& action);
        StateNode(const StateNode& parentNode);
        StateNode(StateNode&& parentNode);
        //
        StateNode& operator=(const StateNode& parentNode);
        StateNode& operator=(StateNode&& parentNode);
        //
         std::vector<std::unique_ptr<StateNode>> generatePath();
        bool operator==(const StateNode& node);

        bool operator< (const StateNode& node);
        bool operator> (const StateNode& node);
        //Getter Member Methods
        unsigned int getAction() const; //Get Action

        unsigned int getPathlevel() const; //Get Pathlevel

        unsigned int getPathcost() const; //Get pathCost

        unsigned int getBlackPostionRow() const;
        void setBlackPostionRow(unsigned int value);

        unsigned int getBlackPostionCol() const;
        void setBlackPostionCol(unsigned int value);
        std::vector<std::vector<int> > getInternelState() const;
        void setInternelState(const std::vector<std::vector<int> > &value);

        const StateNode *getParentNode() const;
        void setParentNode(const StateNode *value);

        unsigned int getHeuristiccost() const;
        void setHeuristiccost(unsigned int value);
        //static goal
        
        std::string& getStringID();

        unsigned int getTotalCost() const;

        //Get internel Memory Allocation in bytes//
        long getMemAllocation();
        ~StateNode();

private:
        unsigned int totalCost;
        std::string stringID; //The string is of the State
        void generateID();
        std::vector<std::vector<int>> internelState; //The Internel State
        const StateNode *parentNode; //The Parent Node
        unsigned int action; //The action that lead t this  state
        unsigned int  Pathlevel; //the path depth of this state
        unsigned int Pathcost ; //path cost not needed
        unsigned int heuristiccost ; //the cost
        void heuristicCostcalcalculator();
        //Gives Up The Blank Position
        unsigned int blackPostionRow; //position of the blank
        unsigned int blackPostionCol; //position of the blank
        //Private Methods
        void generateNewState(const unsigned int& row,const unsigned int& col); //generate new statess return a vector of the states

};

#endif // STATENODE_H
