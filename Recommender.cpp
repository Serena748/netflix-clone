#include "Recommender.h"
#include "UserDatabase.h"
#include "MovieDatabase.h"
#include "User.h"
#include "Movie.h"

#include <string>
#include <vector>
#include <unordered_map>
using namespace std;

vector<MovieAndRank> Recommender::recommend_movies(const string& user_email, int movie_count) const
{
    User* user = m_user_database.get_user_from_email(user_email);
    vector<string> watchHistory = user->get_watch_history();
    unordered_map<string, int> movies;
    
    for (auto movieID : watchHistory) {
        Movie* movie = m_movie_database.get_movie_from_id(movieID);
        
        // update movies that contain director
        for (auto d : movie->get_directors())
            for (auto m : m_movie_database.get_movies_with_director(d))
                movies[m->get_id()] += 20;
        
        // update movies that contain actor
        for (auto a : movie->get_actors())
            for (auto m : m_movie_database.get_movies_with_actor(a))
                movies[m->get_id()] += 30;
        
        // update movies that contain genre
        for (auto g : movie->get_genres())
            for (auto m : m_movie_database.get_movies_with_genre(g))
                movies[m->get_id()] += 1;
    }
    
    vector<MovieAndRank> recs;
    
    for (auto m : movies) {
        MovieAndRank curr(m.first, m.second);
        
        // fill up array first in sorted order
        if (recs.size() < movie_count) {
            
            // don't add to recs if already in watch history
            if (find(watchHistory.begin(), watchHistory.end(), curr.movie_id) != watchHistory.end())
                continue;
            
            // place into correct place in vector
            auto i = recs.begin();
            for (; i != recs.end() && !isRankedHigherThan(curr, *i); i++);
            recs.insert(i, curr);
        }
        
        
        // if movie is greater than the smallest movie currently in recs, it belongs in the ranking.
        else if (isRankedHigherThan(curr, recs[movie_count-1])) {
            
            // don't add to recs if already in watch history
            if (find(watchHistory.begin(), watchHistory.end(), curr.movie_id) != watchHistory.end())
                continue;
            
            // iterate until we find the first movie less than curr, then insert
            for (auto i = recs.begin(); i != recs.end(); i++)
                if (isRankedHigherThan(curr, *i)) {
                    recs.insert(i, curr); // insert new movie
                    recs.pop_back(); // pop last element to remain at correct num of movies
                    break;
                }
        }
    }
    
    return recs;  // Replace this line with correct code.
}

bool Recommender::isRankedHigherThan(const MovieAndRank &m1, const MovieAndRank &m2) const {
    
    // compare compatibility scores
    if (m1.compatibility_score > m2.compatibility_score)
        return true;
    else if (m1.compatibility_score < m2.compatibility_score)
        return false;
    
    // get movie objects
    Movie* m1Object = m_movie_database.get_movie_from_id(m1.movie_id);
    Movie* m2Object = m_movie_database.get_movie_from_id(m2.movie_id);
    
    // tie breaker: rating
    if (m1Object->get_rating() > m2Object->get_rating())
        return true;
    else if (m1Object->get_rating() < m2Object->get_rating())
        return false;
    
    // final tie breaker: title
    if (m1Object->get_title() < m2Object->get_title())
        return true;
    return false;
}
