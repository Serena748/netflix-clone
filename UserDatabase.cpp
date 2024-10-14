#include "UserDatabase.h"
#include "User.h"

#include <string>
#include <vector>
#include <fstream>
using namespace std;

bool UserDatabase::load(const string& filename)
{
    // don't open file if we already loaded users
    if (m_loaded)
        return false;
    
    // open file
    ifstream infile(filename);
    if ( !infile ) {
        cerr << "Error: could not open file!" << endl;
        return false;
    }
    
    // variables to store data
    string name, email, temp;
    int numMovies;
    vector<std::string> movies;
    
    
    while (getline(infile, name)) {
        
        // read user data
        getline(infile, email);
        infile >> numMovies;
        infile.ignore(10000, '\n');
        for (int i=0; i<numMovies; i++) {
            string movie;
            getline(infile, movie);
            movies.push_back(movie);
        }
        // skip empty line
        getline(infile, temp);
        
        // add user to tree multimap
        m_data.insert(email, User(name, email, movies));
        
        // clear movies vector for reuse
        movies.clear();
    }
    
    m_loaded = true;
    return true;
}

User* UserDatabase::get_user_from_email(const string& email) const
{
    auto i = m_data.find(email);
    if (!i.is_valid()) return nullptr;
    return &(i.get_value()); 
}
