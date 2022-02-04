// Verse class function definitions
// Computer Science, MVNU

#include "Verse.h"
#include <iostream>
using namespace std;

Verse::Verse() {  	// Default constructor
    verseText = "Uninitialized Verse!";
    verseRef = Ref();
} 

// REQUIRED: Parse constructor - pass verse string from file
Verse::Verse(const string s) {
	// use Ref constructor to create verseRef
	// store the remainder of the string in verseText

    string rtext = s; // make local copy of string to avoid modifying parameter //// Verse parser
    // parse the reference - notice, currently there is no error checking!
    // Get book number
    string strbook = GetNextToken(rtext, ":");
    int bookV = atoi(strbook.c_str());
    // Get the chapter number
    string strchap = GetNextToken(rtext, ":");
    int chapV = atoi(strchap.c_str());
    // Get the verse number
    string strverse = GetNextToken(rtext, " ");
    int verseV = atoi(strverse.c_str());                                        //// End of Verse Parser
    
    verseRef = Ref(bookV, chapV, verseV);
    verseText = rtext;
}  	

// REQUIRED: Accessors
string Verse::getVerse() {
    return verseText;
}

Ref Verse::getRef() {
    return verseRef;
}

// display reference and verse
void Verse::display(const int vNum) {
    verseRef.display(vNum);
    cout << " " << "<sub>" << getRef().getVerse() << "</sub>" << verseText;
 }

////////////////////////////////////////////////////////// New for project 2 formatting
// display only the verse
void Verse::displaySans() {
    cout << " " << "<sub>" << getRef().getVerse() << "</sub>" << verseText;
}
