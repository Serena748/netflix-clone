#ifndef USERDATABASE_INCLUDED
#define USERDATABASE_INCLUDED

#include <string>
#include <vector>
#include "treemm.h"

class User;

class UserDatabase
{
  public:
    UserDatabase() : m_loaded(false), m_data() {};
    bool load(const std::string& filename);
    User* get_user_from_email(const std::string& email) const;

  private:
    TreeMultimap<std::string, User> m_data;
    bool m_loaded;
    
};

#endif // USERDATABASE_INCLUDED
