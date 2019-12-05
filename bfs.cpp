/**
* Author: Christopher Mannes
* Student ID: 20743505
*
* ECE 650 - Methods and Tools for Software Engineering
* Assignment 2 - Determines the shortest path using the
* breadth-first-search algorithm for a given input using
* the commands from stdin as 
*
* V X
* E {<x1,y1>,<x2,y2>,<x3,y3>,...}
s A B
*
* where V X gives the number of nodes, E {} the set of 
* edges and s A B the initial starting node A and the 
* destination node B.
*/

/**
 * Import header files.
 */
#include <stdio.h>
#include <iostream>
#include <strings.h>
#include <sstream> 
#include <list>
#include <vector>
#include <iterator>

using namespace std;

/**
 * A class for constructing an undirected graph
 * and performing breadth first search.
 */ 
class Graph
{
    public:
        Graph(int numberOfNodes = 0)
        {
            this->numberOfNodes = numberOfNodes;

            adjList = new list<int>[numberOfNodes];
            // adjList.resize(numberOfNodes);

            parent = new int[numberOfNodes];
            
        }

        // Addes edges for an undirected graph.
        void addEdge(int & u, int & v)
        {
            adjList[u].push_back(v);
            adjList[v].push_back(u);
        }

        // Function for displaying the adjacency list.
        void displayAdjList()
        {
            // Method 1 for displaying adjList.
            // for (int i = 0; i < numberOfNodes; i++)
            // {
            //     cout << i << "-->";

            //     for (int ii = 0; ii < adjList[i].size(); ii++)
            //     {
            //         cout << adjList[i][ii] << " ";
            //     }
            //     cout << endl;
            // }

            // Method 2 for displaying adjList.
            for (int i = 0; i < numberOfNodes; i++)
            {
                cout << i << "-->";

                // vector<int> :: iterator it;
                list<int> :: iterator it;
                for (it = adjList[i].begin(); it != adjList[i].end(); it++)
                {
                    cout << *it << " ";
                }
                cout << endl;

            }

        }

        // Performs the breadth first search algorithm.
        void BFS(int s, int target)
        {
            // Generate a boolean array with all elements set to false.
            bool * visited = new bool[numberOfNodes];
            for (int i = 0; i < numberOfNodes; i++)
            {
                visited[i] = false;
            }

            list<int> queue;
            list<int> parentQueue;
            
            visited[s] = true;
            queue.push_back(s);

            // vector<int> :: iterator i;
            list<int> :: iterator i;

            bool firstIter = true;

            while (!queue.empty())
            {
                s = queue.front();
                queue.pop_front();

                if (firstIter)
                {
                    parent[s] = -1;
                    firstIter = false;
                }
                else
                {
                    parent[s] = parentQueue.front();
                    parentQueue.pop_front();
                }
                
                for ( i = adjList[s].begin(); i != adjList[s].end(); i++)
                {
                    if (!visited[*i])
                    {
                        visited[*i] = true;
                        queue.push_back(*i);
                        parentQueue.push_back(s);
                    }
                }
            }
            delete[] visited;

        }

        // Displays the shortest path.
        void displayPath(int & s, int & t)
        {
            for (int j = 0; j < numberOfNodes; j++)
            {
                // cout << parent[j] << endl;

                int counter = 0;
                list<int> :: iterator it;
                for (it = adjList[j].begin(); it != adjList[j].end(); it++)
                {
                    counter++;
                }

                if (counter == 0)
                {
                    parent[j] = -2;
                }
                counter = 0;
                // cout << parent[j] << endl;
                // cout << "------------" << endl;
                
            }
            
            // cout << t; 
            list<int> outputList;
            outputList.push_front(t);
            while (true)
            {
                t = pathReverse(t);

                if (t == -2)
                {
                    outputList.clear();
                    cout << "Error: No connected path exists for specified source and target." << endl;
                    break;
                }
                else if (t < 0)
                {
                    break;
                }
                outputList.push_front(t);
                // cout << "-" << t;

            }
            // cout << endl;
            if (!outputList.empty())
            {
                list<int> :: iterator i;
                for (i = outputList.begin(); i != prev(outputList.end()); i++)
                {
                    cout << *i << "-";
                }
                cout << outputList.back() << endl;
            }

        }

        int pathReverse(int currentNode)
        {
            int nextNode = parent[currentNode];
            // cout << currentNode << "-->" << nextNode << endl;

            return nextNode;
        }

        void resetGraph()
        {
            delete[] parent;

            delete[] adjList;

        }

        int getNumberOfNodes()
        {
            return numberOfNodes;
        }

    private:
        int numberOfNodes;
        int * parent;
        list<int> * adjList;
        // vector<vector<int> > adjList;

};

/**
 * Function for sending an error message to stderr.
 */
void error(string str)
{
    // Output error message.
    cerr << str << endl;
    
    exit(0);
}

/*
 * Enter main program.
 */
int main(int argc, char * argv[]) {

    string line;
    string inputFlag;
    string inputData;
    Graph * bfsGraph = nullptr;

    bool reset = false;

    while (true)
    {
        // cin >> inputFlag;

        getline(cin, line);
        // cout << line << endl;
        inputFlag = line[0];
        // cout << inputFlag << endl;
        // inputData = line.substr(2, line.size() - 2)

        if (inputFlag[0] == 'V')
        {
            if (reset)
            {
                // cin >> inputData;
                inputData = line.substr(2, line.size() - 2);
                // cout << inputData << endl;
                int numberOfNodes = stoi(inputData);

                bfsGraph->resetGraph();
                delete bfsGraph;
                bfsGraph = nullptr;

                bfsGraph = new Graph(numberOfNodes);
            }
            else
            {
                reset = true;
                // cin >> inputData;
                inputData = line.substr(2, line.size() - 2);
                int numberOfNodes = stoi(inputData);

                bfsGraph = new Graph(numberOfNodes);
            }

            // cin >> inputData;
            // int numberOfNodes = stoi(inputData);

            // bfsGraph = new Graph(numberOfNodes);

        }
        else if (inputFlag[0] == 'E')
        {
            // cin >> inputData;
            inputData = line.substr(2, line.size() - 2);
            inputData = inputData.substr(2, inputData.size() - 3);
            inputData.append(",<");

            string delim = ">,<";
            string delim2 = ",";

            int start = 0;
            int end = inputData.find(delim);

            while (end != string::npos)
            {
                string pair = inputData.substr(start, end - start);
                int comma = pair.find(delim2);

                int coord1 = stoi(pair.substr(0, comma));
                int coord2 = stoi(pair.substr(comma + 1, pair.length() - comma));

                // bfsGraph->addEdge(coord1, coord2);

                // int j = bfsGraph->getNumberOfNodes();

                // cout << "before " << j << endl;
                // cout << coord1 << " and " << coord2 << endl;
                // cout << "---------------------------------" << endl;

                if (coord1 < (bfsGraph->getNumberOfNodes()) && coord2 < (bfsGraph->getNumberOfNodes()))
                {
                    bfsGraph->addEdge(coord1, coord2);
                }
                else if (coord1 > (bfsGraph->getNumberOfNodes()) && coord2 > (bfsGraph->getNumberOfNodes()))
                {
                    int j = bfsGraph->getNumberOfNodes();
                    cout << j << endl;
                    cout 
                    << "Error: For specified edge (" 
                    << coord1 << "," << coord2 
                    << "), vertices " << coord1 << " and " << coord2 << " do not exist." << endl;
                }
                else if (coord1 > (bfsGraph->getNumberOfNodes()))
                {
                    cout 
                    << "Error: For specified edge (" 
                    << coord1 << "," << coord2 
                    << "), vertex " << coord1 << " does not exist." << endl;
                }
                else if (coord2 > (bfsGraph->getNumberOfNodes()))
                {
                    cout 
                    << "Error: For specified edge (" 
                    << coord1 << "," << coord2 
                    << "), vertex " << coord2 << " does not exist." << endl;
                }

                start = end + delim.length();
                end = inputData.find(delim, start);

            }
            bfsGraph->displayAdjList();

        }
        else if (inputFlag[0] == 's')
        {
            // string inputData2;
            // cin >> inputData >> inputData2;
            inputData = line.substr(2, line.size() - 2);

            vector<string> result;
            std::istringstream iss(inputData);
            for(string inputData; iss >> inputData; )
            {
                result.push_back(inputData);
            }

            int source = stoi(result[0]);
            int target = stoi(result[1]);

            // cout << source << " " << target << endl;
            // bfsGraph->BFS(source, target);

            // bfsGraph->displayPath(source, target);

            if (source > (bfsGraph->getNumberOfNodes()) && target > (bfsGraph->getNumberOfNodes()))
            {
                cout << "Error: vertex " << source << " and vertex " << target << " do not exist" << endl;
            }
            else if (source > (bfsGraph->getNumberOfNodes()))
            {
                cout << "Error: vertex " << source << " does not exist" << endl;
            }
            else if (target > (bfsGraph->getNumberOfNodes()))
            {
                cout << "Error: vertex " << target << " does not exist" << endl;
            }
            else 
            {
                // cout << source << " " << target << endl;
                bfsGraph->BFS(source, target);
                bfsGraph->displayPath(source, target);
            }

        }
        else if (cin.eof())
        {
            bfsGraph-> resetGraph();
            delete bfsGraph;
            bfsGraph = nullptr;

            return 0;
        }
        else if (inputFlag[0] == 'q')
        {
            bfsGraph->resetGraph();
            delete bfsGraph;
            bfsGraph = nullptr;

            return 0;

        }

    }

    return 0;
}

// V 15
// E {<2,6>,<2,8>,<2,5>,<6,5>,<5,8>,<6,10>,<10,8>}
// E {<2,6>,<2,8>,<2,5>,<16,17>,<6,20>,<30,8>,<6,5>,<5,8>,<6,10>,<10,8>}
// s 2 10
//
// V 5
// E {<0,2>,<2,1>,<2,3>,<3,4>,<4,1>}
// E {<0,2>,<6,1>,<2,3>,<3,4>,<4,1>}
// s 4 0
//
// V 10
// E {<3,0>,<0,2>,<7,1>,<1,6>,<5,0>,<0,1>,<1,4>,<9,1>,<1,8>}
// s 8 3