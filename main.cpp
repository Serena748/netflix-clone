#include "UserDatabase.h"
#include "MovieDatabase.h"
#include "Movie.h"
#include "User.h"
#include "treemm.h"
#include "Recommender.h"
#include <iostream>
#include <string>
using namespace std;


  // If your program is having trouble finding these files. replace the
  // string literals with full path names to the files.  Also, for test
  // purposes, you may want to create some small, simple user and movie
  // data files to makde debuggiing easier, so you can replace the string
  // literals with the names of those smaller files.

const string USER_DATAFILE  = "INSERT YOUR FILE PATH HERE";
const string MOVIE_DATAFILE = "INSERT YOUR FILE PATH HERE";

void findMatches(const Recommender& r,
 const MovieDatabase& md,
 const string& user_email,
 int num_recommendations) {
 // get up to ten movie recommendations for the user
 vector<MovieAndRank> recommendations =
 r.recommend_movies(user_email, 10);
 if (recommendations.empty())
 cout << "We found no movies to recommend :(.\n";
 else {
for (int i = 0; i < recommendations.size(); i++) {
 const MovieAndRank& mr = recommendations[i];
 Movie* m = md.get_movie_from_id(mr.movie_id);
 cout << i << ". " << m->get_title() << " ("
 << m->get_release_year() << ")\n Rating: "
 << m->get_rating() << "\n Compatibility Score: "
 << mr.compatibility_score << "\n";
}
 }
}

int main()
{
    /// TREE MULTIMAP TESTING
//    TreeMultimap<int, std::string> tmm;
//    tmm.insert(1, "one");
//    tmm.insert(2, "two");
//    tmm.insert(3, "three");
//    auto it1 = tmm.find(1);
//    assert(it1.get_value() == "one");
//    auto it2 = tmm.find(2);
//    assert(it2.get_value() == "two");
//    auto it3 = tmm.find(3);
//    assert(it3.get_value() == "three");
//
//    TreeMultimap<int, std::string> tmm2;
//    tmm2.insert(1, "one");
//    tmm2.insert(2, "two");
//    tmm2.insert(1, "uno");
//    tmm2.insert(2, "dos");
//
//    auto it = tmm2.find(1);
//    assert(it.get_value() == "one");
//    it.advance();
//    assert(it.get_value() == "uno");
//    it.advance();
//    assert(!it.is_valid());
//    it = tmm2.find(2);
//    assert(it.get_value() == "two");
//    it.advance();
//    assert(it.get_value() == "dos");
//    it.advance();
//    assert(!it.is_valid());
//
//    cout << "all test cases passed! " << endl;
    
    /// USER DATABASE TESTING
    ///
	UserDatabase udb;
	if (!udb.load(USER_DATAFILE))  // In skeleton, load always return false
	{
		cout << "Failed to load user data file " << USER_DATAFILE << "!" << endl;
		return 1;
	}

    MovieDatabase mdb;
    if (!mdb.load(MOVIE_DATAFILE))
    {
        cout << "Failed to load user data file " << USER_DATAFILE << "!" << endl;
        return 1;
    }
    
    Recommender r(udb, mdb);

    findMatches(r, mdb, "AbFow2483@charter.net", 10);
    
}
