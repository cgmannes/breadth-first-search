/**
 * Author: Christopher Mannes
 * Student ID: 20743505
 * 
 * ECE 650 - Methods and Tools for Software Engineering
 * Assignment 3 - rgen.cpp is a random generator program that generates 
 * a series of street names with a corresponding set of steet coordinates
 * that are subsequently output using standart out. The program will then
 * sleep for a set amount of seconds and repeat the given process.
 */ 

/**
 * Import header files.
 */ 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <strings.h>

/**
 * Import libraries.
 */ 
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

/**
 * Function for sending an error message to stderr.
 */ 
void error(string str)
{
    // Output error message.
    cerr << str << endl;

    exit(0);
}

vector<int> vectorGen(vector<int> & vec, int & maxVal, int & minVal)
{
    for (int i = minVal; i < maxVal + 1; i++)
    {
        vec.push_back(i);
    }
    return vec;

}

void printVector(vector< pair<int,int> > & vec)
{
    vector< pair<int,int> > :: iterator i;
    for (i = vec.begin(); i != vec.end(); i++)
    {
        cout << "  first  " << i->first << "  sec  " << i->second << endl;
    }

}

// https://www.geeksforgeeks.org/program-for-point-of-intersection-of-two-lines/
pair<int,int> lineLineIntersection(pair<int,int> A, pair<int,int> B, pair<int,int> C, pair<int,int> D) 
{
    // Line AB represented as a1x + b1y = c1 
    double a1 = B.second - A.second; 
    double b1 = A.first - B.first; 
    double c1 = (A.first*B.second) - (B.first*A.second);
  
    // Line CD represented as a2x + b2y = c2 
    double a2 = D.second - C.second; 
    double b2 = C.first - D.first; 
    double c2 = (C.first*D.second) - (D.first*C.second);
  
    double determinant = a1*b2 - a2*b1; 
    // cout << "det: " << determinant << endl; 
  
    if (determinant == 0) 
    { 
        // The lines are parallel.
        return make_pair(0, 0); 
    } 
    else
    { 
        double X = (b2*c1 - b1*c2)/determinant; 
        double Y = (a1*c2 - a2*c1)/determinant;
        // cout << "**********" << endl;
        // cout << "intersection points " << X << " and " << Y << endl;
        double minX = max(min(A.first, B.first), min(C.first, D.first));
        double maxX = min(max(A.first, B.first), max(C.first, D.first));

        double minY = max(min(A.second, B.second), min(C.second, D.second));
        double maxY = min(max(A.second, B.second), max(C.second, D.second));
        // cout << "X min and max" << minX << " and " << maxX << endl;
        // cout << "Y min and max" << minY << " and " << maxY << endl;
        // cout << "**********" << endl;
        if (X > minX && X < maxX && Y > minY && Y < maxY)
        {
            // cout << "det != 0 " << X << " and " << Y << endl; 
            return make_pair(X, Y); 
        }
        else
        {
            return make_pair(0, 0);
        }
    } 
} 

/**
 * Enter main program.
 */ 
int main(int argc, char * argv[]) {

    /* Default parameter values. */
    //
    // Default parameters for number of steets.
    int minNumOfStreets = 2; int maxNumOfStreets = 10;
    vector<int> numPossStreets;
    vectorGen(numPossStreets, maxNumOfStreets, minNumOfStreets);
    // printVector(numPossStreets, maxNumOfStreets, minNumOfStreets);

    // Default parameters for number of line segments per street.
    int minNumOfLineSeg = 1; int maxNumOfLineSeg = 5;
    vector<int> numPossStreetSeg;
    vectorGen(numPossStreetSeg, maxNumOfLineSeg, minNumOfLineSeg);
    // printVector(numPossStreetSeg, maxNumOfLineSeg, minNumOfLineSeg);

    // Default parameters for number of seconds to wait before generating new graph.
    int minWaitSecs = 5; int maxWaitSecs = 5;
    vector<int> numPossWaitSec;
    vectorGen(numPossWaitSec, maxWaitSecs, minWaitSecs);
    // printVector(numPossWaitSec, maxWaitSecs, minWaitSecs);

    // Default parameters for range of coordinates.
    int minCoordRange = 1; int maxCoordRange = 20;
    vector<int> numPossCoordRange;
    vectorGen(numPossCoordRange, maxCoordRange, minCoordRange);
    // printVector(numPossCoordRange, maxCoordRange, minCoordRange);


    string rgenInput;
    getline(cin, rgenInput);

    string delim = "-";

    int start = 0;
    int end = rgenInput.find(delim);

    if (end > 0)
    {
        rgenInput = rgenInput.substr(end + 1, rgenInput.length() + 1  - end);
        rgenInput.append("-");
        end = rgenInput.find(delim);
    }

    while (end != string::npos)
    {
        string flag = rgenInput.substr(start, end - start);

        if (flag[0] == 's')
        {
            string flagVal = flag.substr(1,flag.length() - 1);
            maxNumOfStreets = stoi(flagVal);
            vectorGen(numPossStreets, maxNumOfStreets, minNumOfStreets);
        }
        else if (flag[0] == 'n')
        {
            string flagVal = flag.substr(1,flag.length() - 1);
            maxNumOfLineSeg = stoi(flagVal);
            vectorGen(numPossStreetSeg, maxNumOfLineSeg, minNumOfLineSeg);
        }
        else if (flag[0] == 'l')
        {
            string flagVal = flag.substr(1,flag.length() - 1);
            maxWaitSecs = stoi(flagVal);
            vectorGen(numPossWaitSec, maxWaitSecs, minWaitSecs);
            
        }
        else if (flag[0] == 'c')
        {
            string flagVal = flag.substr(1,flag.length() - 1);
            maxCoordRange = stoi(flagVal);
            vectorGen(numPossCoordRange, maxCoordRange, minCoordRange);
        }

        start = end + delim.length();
        end = rgenInput.find(delim, start);

    }

    // Open stream.
    ifstream urandom("/dev/urandom");

    // Check if urandom failed to open stream.
    if (urandom.fail()) {

        error("Error: Open /dev/urandom failed.");

    }

    unsigned int numOfStreets = 0;
    unsigned int numOfLineSeg = 0;
    unsigned int numOfSec = 0;
    unsigned int numRangeCoord = 0;

    urandom.read((char *)&numOfStreets, sizeof(numOfStreets));
    urandom.read((char *)&numOfLineSeg, sizeof(numOfLineSeg));
    urandom.read((char *)&numOfSec, sizeof(numOfSec));
    urandom.read((char *)&numRangeCoord, sizeof(numRangeCoord));

    numOfStreets = numOfStreets % (maxNumOfStreets + 1 - minNumOfStreets);
    numOfStreets = numPossStreets[numOfStreets];
    // cout << numOfStreets << endl;

    numOfLineSeg = numOfLineSeg % (maxNumOfLineSeg + 1 - minNumOfLineSeg);
    numOfLineSeg = numPossStreetSeg[numOfLineSeg];
    // cout << numOfLineSeg << endl;

    numOfSec = numOfSec % (maxWaitSecs + 1 - minWaitSecs);
    numOfSec = numPossWaitSec[numOfSec];
    // cout << numOfSec << endl;

    numRangeCoord = numRangeCoord % (maxCoordRange + 1 - minCoordRange);
    numRangeCoord = numPossCoordRange[numRangeCoord];
    // cout << numRangeCoord << endl;

    urandom.close();

    string outputStreet = "a ";
    int attemptsCounter = 1;
    int maxAttempts = 25;
    int x, y;

    vector< pair<int,int> > prevGenCoords;
    vector< pair<int,int> >::iterator it;
    pair<int,int> P;
    pair<int,int> Q;
    pair<int,int> lastPair;
    pair<int,int> currentPair;
    
    // cout << numOfStreets << endl;
    // cout << numOfLineSeg << endl;
    // cout << numRangeCoord << endl;


    while (1)
    {
        for (int i = 0; i < numOfStreets; i++)
        {
            // cout << "-----------" << endl;
            outputStreet.append("\"");
            outputStreet.append(to_string(i + 1));
            outputStreet.append("\"");
            
            for (int j = 0; j < numOfLineSeg + 1; j++)
            {
                x = (rand() % (numRangeCoord + 1 + numRangeCoord)) - numRangeCoord;
                y = (rand() % (numRangeCoord + 1 + numRangeCoord)) - numRangeCoord;
                // cout << " rand " << x << " and " << y << endl;

                pair<int,int> firstPair;
                pair<int,int> secondPair;
                if (prevGenCoords.empty())
                {
                    prevGenCoords.push_back(make_pair(x,y));
                    firstPair = make_pair(x,y);
                }
                else if (prevGenCoords.size() == 1)
                {
                    secondPair = make_pair(x,y);

                    if ( x == firstPair.first && y == firstPair.second )
                    {
                        int firstCounter = 0;
                        do
                        {
                            if (firstCounter > maxAttempts)
                            {
                                error("Error: 25 attempts were executed to generate a valid street.");
                            }
                            x = (rand() % (numRangeCoord + 1 + numRangeCoord)) - numRangeCoord;
                            y = (rand() % (numRangeCoord + 1 + numRangeCoord)) - numRangeCoord; 
                            secondPair = make_pair(x,y);
                            firstCounter++;

                        } while (x == firstPair.first && y == firstPair.second);
                    }
                    prevGenCoords.push_back(secondPair);

                }
                else if (prevGenCoords.size() == 2)
                {
                    lastPair = make_pair(x,y);

                    if ( x == secondPair.first && y == secondPair.second )
                    {
                        int secondCounter = 0;
                        do
                        {
                            if (secondCounter > maxAttempts)
                            {
                                error("Error: 25 attempts were executed to generate a valid street.");
                            }
                            x = (rand() % (numRangeCoord + 1 + numRangeCoord)) - numRangeCoord;
                            y = (rand() % (numRangeCoord + 1 + numRangeCoord)) - numRangeCoord; 
                            lastPair = make_pair(x,y);
                            secondCounter++;

                        } while (x == secondPair.first && y == secondPair.second);
                    }
                    prevGenCoords.push_back(lastPair);
                    
                }
                else if (prevGenCoords.size() >= 3)
                {
                    currentPair = make_pair(x,y);

                    for (it = prevGenCoords.begin(); it != prev(prevGenCoords.end()); it++)
                    {                    
                        P = make_pair(it->first,it->second);
                        it++;
                        Q = make_pair(it->first,it->second);
                        it--;
                    
                        pair<int,int> intersection = lineLineIntersection(P, Q, lastPair, currentPair);

                        // cout << intersection.first << " and " << intersection.second << endl;

                        if ( (intersection.first != 0) || (intersection.second != 0) || (currentPair.first == lastPair.first && currentPair.second == lastPair.second) )
                        {
                            // cout << "intersection detected" << endl;
                            // cout << "original " << x << " and " << y << endl;

                            pair<int,int> intersect;
                            do
                            {
                                if (attemptsCounter > 25)
                                {
                                    error("Error: 25 attempts were executed to generate a valid street.");
                                }

                                attemptsCounter++;
                                x = (rand() % (numRangeCoord + 1 + numRangeCoord)) - numRangeCoord;
                                y = (rand() % (numRangeCoord + 1 + numRangeCoord)) - numRangeCoord; 
                                currentPair = make_pair(x,y);

                                intersect = lineLineIntersection(P, Q, lastPair, currentPair);

                                if ((intersect.first == 0 && intersect.second == 0))
                                {
                                    // cout << "found" << endl;
                                    // cout << "new " << x << " and " << y << endl;
                                    break;
                                }

                            } while (intersect.first != 0 && intersect.second != 0);
                        }
                    }
                    prevGenCoords.push_back(make_pair(x,y));
                }

                lastPair = currentPair;
                outputStreet.append(" (");
                outputStreet.append(to_string(x));
                outputStreet.append(",");
                outputStreet.append(to_string(y));
                outputStreet.append(")");
            }
            // printVector(prevGenCoords);
            prevGenCoords.clear();
            cout << outputStreet << endl;
            outputStreet.clear();
            outputStreet = "a ";
        }

        cout << "g" << endl;
        sleep(numOfSec);
    }


    // cout << "a \"1\" (3,-6) (-3,-4)" << endl;
    // cout << "a \"2\" (-3,2) (4,-8)" << endl;
    // -s 5 -n 4 -l 5
    // pair<int,int> W = make_pair(5,6);
    // pair<int,int> E = make_pair(3,8); 
    // pair<int,int> R = make_pair(1,4);
    // pair<int,int> T = make_pair(5,8);
    // pair<int,int> intersection = lineLineIntersection(W, E, R, T);
    // cout << intersection.first << intersection.second << endl;
    // cout << "a \"Weber Street\" (2,-1) (2,2) (5,5) (5,6) (3,8)" << endl; //(3,0)" << endl;
    // cout << "a \"King Street S\" (4,2) (4,8)" << endl;
    // cout << "a \"Davenport Road\" (1,4) (5,8)" << endl;
    // cout << "g" << endl;

    return 0;

}