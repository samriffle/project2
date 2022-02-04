// Bible class function definitions
// Computer Science, MVNU

#include "Ref.h"
#include "Verse.h"
#include "Bible.h" 
#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

Bible::Bible() { // Default constructor
	infile = "/home/class/csc3004/Bibles/web-complete";
}

// Constructor – pass bible filename
Bible::Bible(const string s) { infile = s; }

// REQUIRED: lookup finds a given verse in this Bible
Verse Bible::lookup(Ref ref, LookupResult& status) { 
    // TODO: scan the file to retrieve the line that holds ref ...
	if (ref.getBook() < 1 || ref.getBook() > 66) {
		status = NO_BOOK;
		cout << error(status) << ref.getBook() << endl;
		Verse aVerse;
		return aVerse;
	}
	// use getline to get a line of bible
	// turn line into ref by parsing front
	// compare refs, get next line if not ==
	// make verse object with the OG line and return
	instream.open(infile.c_str(), ios::in);
	if (!instream) {
		cerr << "Error - can't open input file: " << infile << endl;
		exit(2);
	}
	instream.unsetf(ios::skipws); // include white space in reads
	string line;
	status = OTHER;

	//cout << "Setup Done" << endl;
	string books[66] = { "Genesis", "Exodus", "Leviticus", "Numbers", "Deuteronomy", "Joshua", "Judges", "Ruth", "1 Samuel", "2 Samuel", "1 Kings", "2 Kings", "1 Chronicles", "2 Chronicles", "Ezra", "Nehimiah", "Esther", "Job", "Psalms", "Proverbs", "Ecclesiastes", "Song of Songs", "Isaiah", "Jeremiah", "Lamentations", "Ezekiel", "Daniel", "Hosea", "Joel", "Amos", "Obadiah", "Jonah", "Micha", "Nahum", "Habakkuk", "Zephaniah", "Haggai", "Zechariah", "Malachi", "Matthew", "Mark", "Luke", "John", "Acts", "Romans", "1 Corinthians", "2 Corinthians", "Galatians", "Ephesians", "Philippians", "Colossians", "1 Thessalonians", "2 Thessalonians", "1 Timothy", "2 Timothy", "Titus", "Philemon", "Hebrews", "James", "1 Peter", "2 Peter", "1 John", "2 John", "3 John", "Jude", "Revelation" };
	int bookTrack = 1; int chapTrack = 1; int verseTrack = 1; int bt2 = 1; int ct2 = 1; int vt2 = 1;

	do {
		bt2 = bookTrack;
		ct2 = chapTrack;
		vt2 = verseTrack;
		getline(instream, line); // parse the reference
		if (instream.eof()) {
			status = OTHER;
			Verse aVerse;
			return aVerse;
		}
		Ref thisVerse(line);
		bookTrack = thisVerse.getBook();
		chapTrack = thisVerse.getChap();
		verseTrack = thisVerse.getVerse();
		if (thisVerse.getBook() > ref.getBook() && thisVerse.getChap() < ref.getChap() && vt2 < ref.getVerse()) {
			status = NO_VERSE;
			cout << error(status) << ref.getVerse() << " in " << books[ref.getBook() - 1] << " " << ref.getChap() << endl;
			Verse aVerse;
			return aVerse;
		}
		if (thisVerse == ref) {
			status = SUCCESS;
		}
		else if (ref.getChap() < 1 || thisVerse.getBook() > ref.getBook() && thisVerse.getChap() == 1) {
			status = NO_CHAPTER;
			cout << error(status) << ref.getChap() << " in " << books[ref.getBook() - 1] << endl;
			Verse aVerse;
			return aVerse;
		}
		else if (ref.getVerse() < 1 || thisVerse.getBook() == ref.getBook() && thisVerse.getChap() - 1 == ref.getChap() && thisVerse.getVerse() < ref.getVerse() || thisVerse.getBook() > ref.getBook() && thisVerse.getChap() == 1 && thisVerse.getVerse() == 1) {
			status = NO_VERSE;
			cout << error(status) << ref.getVerse() << " in " << books[ref.getBook() - 1] << " " << ref.getChap() << endl;
			Verse aVerse;
			return aVerse;
		}
	} while (status == OTHER);

	//cout << "Search loop done" << endl;

	if (status == SUCCESS) {
		Verse pVerse(line);
		return pVerse;
	}

    // update the status variable
	//status = OTHER; // placeholder until retrieval is attempted
	// create and return the verse object
	//Verse aVerse;   // default verse, to be replaced by a Verse object
	                // that is constructed from a line in the file.
	Verse defaultV;
    return defaultV;
}

// REQUIRED: Return the next verse from the Bible file stream if the file is open.
// If the file is not open, open the file and return the first verse.
Verse Bible::nextVerse(LookupResult& status) {
	if (!instream) {
		instream.open(infile.c_str(), ios::in);
		Verse aVerse("1 1 1");
		return aVerse;
	}
	else {
		string line;
		getline(instream, line); // parse the reference
		if (instream.eof()) {
			status = OTHER;
			Verse aVerse;
			return aVerse;
		}
		else {
			status = SUCCESS;
			 Verse pVerse(line);
			 return pVerse;
		}
	}

}

// REQUIRED: Return an error message string to describe status
string Bible::error(LookupResult status) {
	if (status == 1) {
		return "Error: no such book ";
	}
	else if (status == 2) {
		return "Error: no such chapter ";
	}
	else if (status == 3) {
		return "Error: no such verse ";
	}
	else {
		return "";
	}
}

void Bible::display() {
	cout << "Bible file: " << infile << endl;
}
	
// OPTIONAL access functions
// OPTIONAL: Return the reference after the given ref
Ref Bible::next(const Ref ref, LookupResult& status) {}

// OPTIONAL: Return the reference before the given ref
Ref Bible::prev(const Ref ref, LookupResult& status) {}
