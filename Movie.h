#ifndef MOVIE_INCLUDED
#define MOVIE_INCLUDED

#include <string>
#include <vector>
#include <iostream>

class Movie
{
  public:
    Movie(const std::string& id,
          const std::string& title,
          const std::string& release_year,
          const std::vector<std::string>& directors,
          const std::vector<std::string>& actors,
          const std::vector<std::string>& genres,
          float rating)
        : m_id(id), m_title(title), m_release_year(release_year),
          m_directors(directors), m_actors(actors),
          m_genres(genres), m_rating(rating) {}
    std::string get_id() const { return m_id; };
    std::string get_title() const { return m_title; };
    std::string get_release_year() const { return m_release_year; };
    float get_rating() const { return m_rating; };
    std::vector<std::string> get_directors() const { return m_directors; };
    std::vector<std::string> get_actors() const { return m_actors; };
    std::vector<std::string> get_genres() const { return m_genres; };
    void dump() {
        std::cout << "ID: " << m_id << std::endl;
        std::cout << "TITLE: " << m_title << std::endl;
        std::cout << "RELEASE YEAR: " << m_release_year << std::endl;
        std::cout << "DIRECTORS: " << std::endl;
        for (auto d : m_directors)
            std::cout << "    " << d << std::endl;
        std::cout << "ACTORS: " << std::endl;
        for (auto a : m_actors)
            std::cout << "    " << a << std::endl;
        std::cout << "GENRES: " << std::endl;
        for (auto g : m_genres)
            std::cout << "    " << g << std::endl;
        std::cout << "RATING: " << m_rating << std::endl << std::endl;
    }

  private:
    std::string m_id;
    std::string m_title;
    std::string m_release_year;
    std::vector<std::string> m_directors;
    std::vector<std::string> m_actors;
    std::vector<std::string> m_genres;
    float m_rating;

};

#endif // MOVIE_INCLUDED
