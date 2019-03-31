#include "PuzzleSolver.h"

PuzzleSolver::PuzzleSolver(const std::string& goal)
{

    goalState= std::move(StateNode(this->convertVectorArray(goal)));

}



void PuzzleSolver::setGoalState(const std::string &intialState)
{
    goalState = std::move(StateNode(this->convertVectorArray(intialState)));


}

StateNode PuzzleSolver::solve(const std::string &intialStateString, unsigned int method)
{
    std::cout << "Nope" << std::endl;
    auto intialMatrix = std::move(this->convertVectorArray(intialStateString));
    if (!checkSolvable(intialMatrix)){
          throw std::runtime_error("This State Is Not Solvable\n");
    }

    if (method == BFS){
        return std::move(BFSearch(intialMatrix));
    }
    else if (method == BSearchFirst){
        return std::move(BestFirstSearch(intialMatrix));
    }
    else if (method == DFS){
        return std::move(DFSearch(intialMatrix));
    }
    else if (method == IDFS){
        std::cout << "Iterative Depth First Search" << std::endl;
        for(unsigned int level = 0 ; ;level++){
            try {
                return std::move(InterativeDFSearch(intialMatrix,level));
            }
            catch (...) {

            }
        }
    }
    else if (method == BSearchFirstSET){
        return std::move(BestFirstSearchSet(intialMatrix));
    }

    return StateNode();
}

std::string PuzzleSolver::solveString(const unsigned int &intialStateStringPtr, unsigned int method)
{
    //Convert ptr char* string to c++ string
    char * stringPuzzle = (char*) intialStateStringPtr;
    std::cout << stringPuzzle << std::endl;
    std::string puzzleString(stringPuzzle);
    auto  solutionActions = traceSolution( solve(puzzleString,method));
    std::cout << solutionActions << std::endl;
    return solutionActions;
}

bool PuzzleSolver::isDiscovered(StateNode &node)
{
    auto resultsQuerie = discoveredmap.count(node.getStringID());
    if (resultsQuerie > 0)
        return true;
    else
        return false ;

}
std::string PuzzleSolver::traceSolution(const StateNode &node)
{
    std::string solution = "";
    StateNode *nodePtr = (StateNode*)&(node);
    while(nodePtr != nullptr){
            auto action = nodePtr->getAction();
            if (action ==LEFT)
                solution.append("L ");
            else if (action == RIGHT)
                solution.append("R ");
            else if (action == UP)
                solution.append("U ");
            else if (action == DOWN)
                solution.append("D ");

//         nodePtr->print();
         nodePtr = (StateNode*)nodePtr->getParentNode();

    }
    //clear();
    clear();
    return std::move(solution);


}

bool PuzzleSolver::checkSolvable(const std::vector<std::vector<int> > &intialState)
{
    std::cout << "--is Solvable--" << std::endl;
    //Gather The Matrix Elements
    std::vector<int> inversionVector;
    for (auto& row : intialState){
        for (auto& element : row){
            if (element != BLANK){
                inversionVector.push_back(element);
            }
        }
    }
    //
    unsigned int inversionCount = 0; //The number of inversions
    for (auto& i : inversionVector)
        std::cout << i << " ";
    //int test;
    for (unsigned int invers = 0 ; invers  < inversionVector.size() ; invers++){
        for (unsigned int i = invers+1 ; i < inversionVector.size() ; i++){
            if (inversionVector[i] < inversionVector[invers]){
                //test++;
                inversionCount++;
            }

        }
        // std::cout <<std::endl<< test << std::endl;
         //test = 0;


    }
    unsigned int blackPostionRow = 500;
    for (unsigned int i = 0 ; i < intialState.size(); i++)
        for (unsigned int y = 0 ; y < intialState.size() ; y++){
            if (intialState[i][y] == BLANK){
                blackPostionRow = i;
                i = intialState.size(); // break the loop after findnig the blank
                break;
            }
    }
    if (blackPostionRow >= intialState.size())
        throw std::runtime_error("No Blank Detected");
    //std::cout << test;
    std::cout << std::endl;
    unsigned int inversionTotal = inversionCount + (intialState.size() - blackPostionRow );
     std::cout << "Inversion + Row Blank:" << inversionTotal << std::endl;
   if (inversionTotal %2 != 0 ){
        return true;
   }
   else {
       return false;
   }

}

bool PuzzleSolver::isGoal(const StateNode &node)
{
    return goalState == node;
}
StateNode PuzzleSolver::DFSearch(const std::vector<std::vector<int> > &intialState)
{
    std::cout << "Depth First Search" << std::endl;
     std::cout << "Hello\n";
    //Clear DataStructures Before Use
    std::stack<std::unique_ptr<StateNode>> empty;
    std::swap(this->DFSstack, empty );
    discoveredNodes.clear();
    discoveredmap.clear();
    ///
    std::unique_ptr<StateNode> intialStatePtr(new StateNode(intialState));
    //intialStatePtr->print();
     DFSstack.push(std::move(intialStatePtr));
     while (!DFSstack.empty()){
         auto Parentnode = std::move(DFSstack.top()); //the top of the stack
         DFSstack.pop(); //pop the front elememnt
         //std::cout << "Here\n";
         if (isGoal(*Parentnode)){
             return std::move(*Parentnode);
         }
         auto nodeChildren = std::move(Parentnode->generatePath()); //generate new paths
         insertDiscovered(Parentnode);
          //std::cout << "SIZE DISCOVERED" << discoveredNodes.size() << std::endl;
         for (auto& node_children : nodeChildren){
             if (!isDiscovered(*node_children)){
                 DFSstack.push(std::move(node_children));
//                 if (isGoal(*node_children))
//                     return std::move(*node_children);
             }
         }
     }
     throw std::runtime_error("No Solution Found");
}

StateNode PuzzleSolver::BestFirstSearch(const std::vector<std::vector<int> > &intialState)
{
    std::cout << "Best First Search" << std::endl;
   //Clear DataStructure Before Use
   std::priority_queue<std::unique_ptr<StateNode>,std::vector<std::unique_ptr<StateNode>>,Compare> empty;
   std::swap(this->pQueue, empty );
   discoveredNodes.clear();
   discoveredmap.clear();   ///
   std::unique_ptr<StateNode> intialStatePtr(new StateNode(intialState));
   pQueue.push(std::move(intialStatePtr));
   while (!pQueue.empty()){
       //std::cout << "Open:" << this->pQueue.size() << " Discovered: " << this->discoveredmap.size() << std::endl;
       //std::cout << this->discoveredmap.size() << std::endl;
       auto Parentnode = std::move((std::unique_ptr<StateNode>&)pQueue.top()); //the the  front of the queue
       //std::cout << std::endl<<"Parent: "<< Parentnode->getTotalCost();
       pQueue.pop(); //pop the front elememnt
       if (isDiscovered(*Parentnode)){
            //This Node Has Already Been Expaned, Check As Goal Discovered
       }

       else {
           if (isGoal(*Parentnode)) {
               //traceSolution(*Parentnode);
               return std::move(*Parentnode);
           }
          //Parent Discovered Check
               //Check If The Parent Has Already Been Discovered else dont expand:Avoid Waisted Computation
               auto nodeChildren = std::move(Parentnode->generatePath()); //generate new paths
               insertDiscovered(Parentnode);
                //std::cout << "SIZE DISCOVERED" << discoveredNodes.size() << std::endl;
              // std::cout << " Children:";

               for (auto& node_children : nodeChildren){

                   if (!isDiscovered(*node_children)){
                      // std::cout << node_children->getTotalCost() << " ";
                       if (isGoal(*node_children))
                           return std::move(*node_children);
                       pQueue.push(std::move(node_children));


                   }
               }

       }
   }
   throw std::runtime_error("No Solution Found");
}


StateNode PuzzleSolver::BFSearch(const std::vector<std::vector<int> > &intialState)
{
    std::cout << "Breadth First Search" << std::endl;
   //Clear DataStructure Before Use
   std::queue<std::unique_ptr<StateNode>> empty;
   std::swap(this->BFSqueue, empty );
   discoveredNodes.clear();
   discoveredmap.clear();
   ///
   std::unique_ptr<StateNode> intialStatePtr(new StateNode(intialState));
   BFSqueue.push(std::move(intialStatePtr));
   while (!BFSqueue.empty()){
       //std::cout << this->discoveredmap.size() << std::endl;
       auto Parentnode = std::move(BFSqueue.front()); //the the  front of the queue
       BFSqueue.pop(); //pop the front elememnt
       if (isDiscovered(*Parentnode)){
            //This Node Has Already Been Expaned, Check As Goal Discovered
       }
       else {
           if (isGoal(*Parentnode)) {
               return std::move(*Parentnode);
           }
           auto nodeChildren = std::move(Parentnode->generatePath()); //generate new paths
           insertDiscovered(Parentnode);
            //std::cout << "SIZE DISCOVERED" << discoveredNodes.size() << std::endl;
           for (auto& node_children : nodeChildren){
               if (!isDiscovered(*node_children)){
                   BFSqueue.push(std::move(node_children));
                   //if (isGoal(node_children))
                      // return std::move(node_children);
               }
           }
       }
   }
   throw std::runtime_error("No Solution Found");
}

StateNode PuzzleSolver::InterativeDFSearch(const std::vector<std::vector<int> > &intialState, unsigned int maxLevel)
{

    std::stack<std::unique_ptr<StateNode>> empty;
    std::swap(this->DFSstack, empty );
    discoveredNodes.clear();
    discoveredmap.clear();
    ///
    std::unique_ptr<StateNode> intialStatePtr(new StateNode(intialState));
     DFSstack.push(std::move(intialStatePtr));
     while (!DFSstack.empty()){
         auto Parentnode = std::move(DFSstack.top()); //the top of the stack
         DFSstack.pop(); //pop the front elememnt
         if (isGoal(*Parentnode)){
             return std::move(*Parentnode);
         }
         auto nodeChildren = std::move(Parentnode->generatePath()); //generate new paths
         //insertDiscovered(Parentnode);
          //std::cout << "SIZE DISCOVERED" << discoveredNodes.size() << std::endl;
         for (auto& node_children : nodeChildren){
             if ( node_children->getPathlevel() <= maxLevel){
                 DFSstack.push(std::move(node_children));
                 if (isGoal(*node_children))
                     return std::move(*node_children);
             }
         }
     }
     throw std::runtime_error("No Solution Found");
}


bool PuzzleSolver::insertDiscovered(std::unique_ptr<StateNode> &childState)
{

    try {
        //inserts into map using the node Stringid as key 
        childState->clear();
        std::pair<std::string, std::unique_ptr<StateNode>> pair(std::move(childState->getStringID()), std::move(childState));
        this->discoveredmap.insert(std::move(pair));
        return true;

    }
    //handles just in case of exceptions such as memeory issues 
    catch(const std::exception& exception){
        std::cout << exception.what();
        return false;
    }

}

StateNode PuzzleSolver::BestFirstSearchSet(const std::vector<std::vector<int> > &intialState)
{
    std::cout << "Best First Search" << std::endl;
   //Clear DataStructure Before Use
   this->pQueueSet.clear();
   discoveredmap.clear();   ///
   std::unique_ptr<StateNode> intialStatePtr(new StateNode(intialState));
   pQueueSet.insert(std::move(intialStatePtr));
   while (!pQueueSet.empty()){
//       for (auto ms_iterator = pQueueSet.begin();  ms_iterator != pQueueSet.end(); ms_iterator++){
//           std::cout << (*(*ms_iterator)).getTotalCost() << " ";

//       }
      // std::cout << std::endl;
       //std::cout << "Open:" << pQueueSet.size() << " Discovered: " << this->discoveredmap.size() << std::endl;
       std::unique_ptr<StateNode>* ptrtoTop = ( std::unique_ptr<StateNode>*)&(*pQueueSet.begin());



        auto Parentnode(std::move(*ptrtoTop)); //the the  front of the queue
       //auto InteratorParentnode = pQueueSet.begin();
        pQueueSet.erase(pQueueSet.begin());;//pop the front elememnt
       if (isDiscovered(*Parentnode)){
            //This Node Has Already Been Expaned, Check As Goal Discovered
       }
       else {
           if (isGoal(*Parentnode)) {
               return std::move(*Parentnode);
           }
          //Parent Discovered Check
               //Check If The Parent Has Already Been Discovered else dont expand:Avoid Waisted Computation
               auto nodeChildren = std::move(Parentnode->generatePath()); //generate new paths
               insertDiscovered(Parentnode);
                //std::cout << "SIZE DISCOVERED" << discoveredNodes.size() << std::endl;
              // std::cout << " Children:";

               for (auto& node_children : nodeChildren){

                   if (!isDiscovered(*node_children)){
                      // std::cout << node_children->getTotalCost() << " ";
                       if (isGoal(*node_children))
                           return std::move(*node_children);
                       pQueueSet.insert(std::move(node_children));


                   }
               }

       }
   }
   throw std::runtime_error("No Solution Found");

}

bool PuzzleSolver::checkValidPuzzle(long double x)
{
    // Find floating point value of
     // square root of x.
     long double num =sqrt(x);

     // If square root is an integer
     return ((num - floor(num)) == 0);

}

PuzzleSolver::~PuzzleSolver()
{
    clear();

}

std::vector<std::vector<int>> PuzzleSolver::convertVectorArray(const std::string &puzzleString)
{

    std::vector<int> numVec ;
    std::stringstream stringStream(puzzleString);
    int num;
    while (stringStream >> num){
        numVec.push_back(num);
        //std::cout << num << std::endl;
    }
    //Convert To Multi-Dimen Vector

    if (this->checkValidPuzzle(numVec.size())){
        //std::cout << "Vlaif" << std::endl;
        int square = sqrt(numVec.size());
        std::vector<std::vector<int>> puzzleMatrix(square);
        for (auto& vec : puzzleMatrix)
            vec.resize(square);
        //std::cout << square << std::endl;
        int totalIndex =0;
        for (int row = 0 ; row < square ; row++){
            for (int column = 0 ; column < square ; column++){
                puzzleMatrix[row][column] =  numVec[totalIndex];
                totalIndex++;
            }
        }
        return puzzleMatrix;
    }
    else {
        throw std::runtime_error("Puzzle State Is Not Valid");
    }
    //Check If Valid



}

void PuzzleSolver::clear()
{
    std::stack<std::unique_ptr<StateNode>> stackClean;
    std::queue<std::unique_ptr<StateNode>> queueClean;
    std::priority_queue<std::unique_ptr<StateNode>,std::vector<std::unique_ptr<StateNode>>,Compare> priorityClean;
    std::vector<std::unique_ptr<StateNode>> vectorDiscoveredClean;
    stackClean.swap(DFSstack);
    queueClean.swap(BFSqueue);
    priorityClean.swap(pQueue);
    this->discoveredmap.clear();
    this->discoveredNodes.clear();
    this->pQueueSet.clear();
    this->discoveredNodes.swap(vectorDiscoveredClean);
}


