#include <iostream>
#include <vector>
#include "StateNode.h"
#include "PuzzleSolver.h"
#include <map>
////#include "nvwa/debug_new.h"
//using namespace std;
////TestCase 1 method paramter specifies which method to use
////BFS - Breadth First Search
////DFS - Depth First Search
////IDFS - Iteravtive Depth First st Searchst Search
void Test1(int method){

    std::string intial= " 1 10 3 8 "
                        " 100 14 9 4 "
                         "6 5 13 7  "
                        "11 15 2 12 ";

   std::string goal= "1 2 3 4 "
                     "5 6 7 8 "
                     "9 10 11 12 "
                     "13 14 15 100";
    PuzzleSolver puzz_solver(goal);

    auto SolNode = std::move(puzz_solver.solve(intial,method));
    std::cout << std::endl;
    auto  solutionAction = puzz_solver.traceSolution(SolNode);
    std::cout << solutionAction << std::endl;

}



bool getSolvable(char* puzzle);
std::string solve(char* puzzle, char* goal, unsigned int method);

int main()
{

    //Specify Which Method To Use For Various Puzzle Instance
    //Read OutPut From Bottom To Top
    {
    Test1(BSearchFirstSET);

    }



}






