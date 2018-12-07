#pragma once

#include <iostream>
#include <fstream>
#include <list>
#include <string>
#include <stdexcept>
#include "Webpage.h"
using namespace std;

class BrowserHistory {
public:
	BrowserHistory();    // constructor
	BrowserHistory(const int&);  // constructor
	void visitSite(const Webpage & newSite);
	string back();
	string forward();

	void readHistory(string fileName);

	string getUrl();
	size_t getNavSize();

	list<Webpage> getSitesVisited();

private:
	list<Webpage> navHistory;
	list<Webpage>::iterator navPos;
	list<Webpage> sitesVisited;
	int numSites;

};

BrowserHistory::BrowserHistory()
{
	numSites = 0;

}

BrowserHistory::BrowserHistory(const int& numbsites)
{
	numSites = numbsites;
}


void BrowserHistory::visitSite(const Webpage & newSite)
{

    if (navHistory.empty())       // checks if empty
    {
        navHistory.push_back(newSite);
        sitesVisited.push_back(newSite);
        navPos = navHistory.begin();     // sets iterator to beginning of list
    }
    else
    {
        while(++navPos != navHistory.end())  // if not empty pop the urls in the list till the end
        {
            --navPos;
            navHistory.pop_back();     // pops end of list

        }
        --navPos;    // decrement iterator
        navHistory.push_back(newSite);
        sitesVisited.push_back(newSite);
        numSites++;
        navPos++;
    }
}




//decrements navPos and returns the function at that address
string BrowserHistory::back()
{

navPos--;
return navPos->getUrl();
}



//increments navPos and returns the function at that address
string BrowserHistory::forward()
{

navPos++;
return navPos->getUrl();
}


void BrowserHistory::readHistory(string fileName) {
	string temp;
	int newTime;
	Webpage newSite;
	ifstream inFile(fileName.c_str());

	while (inFile >> temp) {
		if (temp == "new") {
			inFile >> temp >> newTime;
			newSite = Webpage(temp, time_t(newTime));
			visitSite(newSite);
		}
		else if (temp == "back") {
			back();
		}
		else if (temp == "forward") {
			forward();
		}
		else {
			throw logic_error("invalid command");
		}
	}
}

//checks if list is empty and throws a logic error, if not returns geturl going backwards in list
//considering pushback
string BrowserHistory::getUrl()
{
    if(navHistory.empty())
    {
        throw logic_error("No URL");
    }
	return navPos->getUrl();
}

size_t BrowserHistory::getNavSize()
{

	return navHistory.size();   // returns number of sites visited
}

list <Webpage> BrowserHistory::getSitesVisited()
{
	return sitesVisited;
}
