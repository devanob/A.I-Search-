#include "StateNode.h"



void StateNode::print() const
{
    std::cout <<std::endl<<"-----------------------" <<std::endl;
    for (unsigned int i = 0 ; i < this->internelState.size(); i++){
        for (unsigned int y = 0 ; y < this->internelState.size() ; y++){
            if (internelState[i][y] != BLANK){
                std::cout <<std::right << std::setw(7) << internelState[i][y] << "  ";
            }
            else {
                std::cout <<std::right << std::setw(7)<< "X" << "  ";
            }
        }
        std::cout << std::endl;
    }
    std::cout <<"--------------------------" <<std::endl;
    if (action == LEFT)
        std::cout << "LEFT" << std::endl;
    else if (action== RIGHT)
        std::cout << "RIGHT" << std::endl;
    else if (action == UP)
        std::cout << "UP" << std::endl;
    else if (action == DOWN)
        std::cout << "DOWN" << std::endl;
    else {
        //Do nothin
    }
     std::cout <<"-----------------------" <<std::endl;

}

void StateNode::clear()
{
    this->internelState.clear();
}

StateNode::StateNode()
{

}

StateNode::StateNode(const std::vector<std::vector<int> > &setState)
{
    this->internelState = setState;
    this->Pathcost = 0;
    this->Pathlevel =0;
    this->action = NOACTION;
    this->setParentNode(nullptr);
    //Find The Blank
    for (unsigned int i = 0 ; i < this->internelState.size(); i++)
        for (unsigned int y = 0 ; y < this->internelState.size() ; y++){
            if (internelState[i][y] == BLANK){
                this->blackPostionRow = i;
                this->blackPostionCol = y;
                generateID();
                heuristicCostcalcalculator();
                return;
            }


        }

    throw std::runtime_error("No Black Found In Table");


}

StateNode::StateNode(const StateNode &parentNode, const unsigned int &action)
{
    this->parentNode = (&parentNode);
    //Set Attribute Using The Parent Node Attribute
    this->Pathcost = parentNode.getPathcost() + 1;
    this->Pathlevel = parentNode.getPathlevel() +1;
    this->action = action;
    this->internelState = parentNode.getInternelState();
    generateNewState(parentNode.getBlackPostionRow(), parentNode.getBlackPostionCol()); //generate the new state form the parent state
    generateID();
    heuristicCostcalcalculator();

}

StateNode::StateNode(const StateNode &parentNode)
{
    this->internelState = parentNode.internelState;
    this->Pathcost = parentNode.Pathcost;
    this->Pathlevel = parentNode.Pathlevel;
    this->action = parentNode.action;
    this->blackPostionCol = parentNode.blackPostionCol;
    this->blackPostionRow = parentNode.blackPostionRow;
    this->parentNode = parentNode.parentNode;
    this->stringID = parentNode.stringID;
    this->totalCost = parentNode.totalCost;
}

StateNode::StateNode(StateNode &&parentNode)
{

    //std::cout << "MOVE" << std::endl;
    this->internelState = std::move(parentNode.internelState);
    this->Pathcost = std::move(parentNode.Pathcost);
    this->Pathlevel = std::move(parentNode.Pathlevel);
    this->action = std::move(parentNode.action);
    this->blackPostionCol = std::move(parentNode.blackPostionCol);
    this->blackPostionRow = std::move(parentNode.blackPostionRow);
    this->parentNode = std::move(parentNode.parentNode);
    this->stringID = std::move(parentNode.stringID);
    this->stringID = parentNode.stringID;
    this->totalCost = std::move(parentNode.totalCost);
}

StateNode & StateNode::operator=(const StateNode &parentNode)
{

    this->internelState = parentNode.internelState;
    this->Pathcost = parentNode.Pathcost;
    this->Pathlevel = parentNode.Pathlevel;
    this->action = parentNode.action;
    this->blackPostionCol = parentNode.blackPostionCol;
    this->blackPostionRow = parentNode.blackPostionRow;
    this->parentNode = parentNode.parentNode;
     this->totalCost = parentNode.totalCost;
    return *this;
}

StateNode &StateNode::operator=(StateNode &&parentNode)
{
    this->internelState = std::move(parentNode.internelState);
    this->Pathcost = std::move(parentNode.Pathcost);
    this->Pathlevel = std::move(parentNode.Pathlevel);
    this->action = std::move(parentNode.action);
    this->blackPostionCol = std::move(parentNode.blackPostionCol);
    this->blackPostionRow = std::move(parentNode.blackPostionRow);
    this->parentNode = std::move(parentNode.parentNode);
    this->stringID = std::move(parentNode.stringID);
    this->totalCost = std::move(parentNode.totalCost);
    return *this;

}

std::vector<std::unique_ptr<StateNode> > StateNode::generatePath()
{
    std::vector<std::unique_ptr<StateNode>> NextStates;
     int blankRow = this->getBlackPostionRow();
     int blankColumn = getBlackPostionCol();
     int size = internelState.size();
     if (blankColumn  + 1 < size ){
         NextStates.push_back(std::unique_ptr<StateNode>(new StateNode(*this,RIGHT)));
     }

    //Check Left


        if (blankColumn  - 1 >=  0 ){
            NextStates.push_back(std::unique_ptr<StateNode>(new StateNode(*this,LEFT)));
            //std::cout << "GOOD" << std::endl;
        }



        if (blankRow   + 1  <  size ){
            NextStates.push_back(std::unique_ptr<StateNode>(new StateNode(*this,DOWN)));
            //std::cout << "GOOD" << std::endl;
        }


         if (blankRow - 1  >= 0 ){
             //std::cout << "GOOD" << std::endl;
             NextStates.push_back(std::unique_ptr<StateNode>(new StateNode(*this,UP)));
         }


    return  std::move(NextStates);
}

bool StateNode::operator==(const StateNode& node)
{
    for (unsigned int i = 0 ; i < this->internelState.size(); i++)
        for (unsigned int y = 0 ; y < this->internelState.size() ; y++){
            if (internelState[i][y] != node.internelState[i][y])
                return false;
        }
    return true;
}

bool StateNode::operator<(const StateNode &node)
{
    return this->totalCost > node.totalCost;
}

bool StateNode::operator>(const StateNode &node)
{
     return this->totalCost < node.totalCost;
}

unsigned int StateNode::getAction() const
{
    return action;
}

unsigned int StateNode::getPathlevel() const
{
    return Pathlevel;
}

unsigned int StateNode::getPathcost() const
{
    return Pathcost;
}

unsigned int StateNode::getBlackPostionRow() const
{
    return blackPostionRow;
}

void StateNode::setBlackPostionRow(unsigned int value)
{
    blackPostionRow = value;
}

unsigned int StateNode::getBlackPostionCol() const
{
    return blackPostionCol;
}

void StateNode::setBlackPostionCol(unsigned int value)
{
    blackPostionCol = value;
}

std::vector<std::vector<int> > StateNode::getInternelState() const
{
    return internelState;
}

void StateNode::setInternelState(const std::vector<std::vector<int> > &value)
{
    internelState = value;
}

const StateNode *StateNode::getParentNode() const
{
    return parentNode;
}

void StateNode::setParentNode(const StateNode *value)
{
    parentNode = value;
}

unsigned int StateNode::getHeuristiccost() const
{
    return heuristiccost;
}

void StateNode::setHeuristiccost(unsigned int value)
{
    heuristiccost = value;
}

std::string &StateNode::getStringID()
{
    return stringID;
}

unsigned int StateNode::getTotalCost() const
{
    return totalCost;
}

long StateNode::getMemAllocation()
{

}

StateNode::~StateNode()
{
   //std::cout << "Decontructing" <<this->getStringID()<< std::endl;
}

void StateNode::generateID()
{
    for (auto& vec : this->internelState){
        for (auto& item : vec)
            this->stringID += std::to_string(item);
    }
}

void StateNode::heuristicCostcalcalculator()
{
    std::vector<int> inversionVector;
    for (auto& row : internelState){
        for (auto& element : row){
            if (true ){
                inversionVector.push_back(element);
            }
        }
    }
         unsigned int inversionCount = 0; //The number of inversions
         for (unsigned int invers = 0 ; invers  < inversionVector.size() ; invers++){
             for (unsigned int i = invers+1 ; i < inversionVector.size() ; i++){
                 if (inversionVector[i] < inversionVector[invers]){
                     //test++;
                     inversionCount++;
                 }

             }

      totalCost= inversionCount + (internelState.size() - blackPostionRow ) + Pathcost;

      }

}
void StateNode::generateNewState(const unsigned int &row, const unsigned int &col)
{
    switch (action) {
    case  LEFT :  {
        unsigned int newRowBlank = row;
            unsigned int newColBlank = col - 1;
            std::swap(internelState[row][col],internelState[newRowBlank][newColBlank]);
            this->blackPostionRow = newRowBlank;
            this->blackPostionCol = newColBlank;
            break;

        }
    case  RIGHT :  {
        unsigned int newRowBlank = row;
        unsigned int newColBlank = col + 1;
        std::swap(internelState[row][col],internelState[newRowBlank][newColBlank]);
        this->blackPostionRow = newRowBlank;
        this->blackPostionCol = newColBlank;
        break;

    }
    case  UP :  {
        unsigned int newRowBlank = row - 1;
        unsigned int newColBlank = col ;
        std::swap(internelState[row][col],internelState[newRowBlank][newColBlank]);
        this->blackPostionRow = newRowBlank;
        this->blackPostionCol = newColBlank;
        break;

    }
    case  DOWN :  {
        unsigned int newRowBlank = row + 1;
        unsigned int newColBlank = col ;
        std::swap(internelState[row][col],internelState[newRowBlank][newColBlank]);
        this->blackPostionRow = newRowBlank;
        this->blackPostionCol = newColBlank;
        break;
    }


    }
}






