#include "author.h"
#include <string>

std::string Author::getFavouriteGenre() const
{
    return favouriteGenre;
}

void Author::setFavouriteGenre(const std::string &value)
{
    favouriteGenre = value;
}

Author::Author(std::string realName, std::string favouriteGenre)
{
    this->realName = realName;
    this->favouriteGenre = favouriteGenre;
}

std::string Author::getRealName() const
{
    return realName;
}

void Author::setRealName(const std::string &value)
{
    realName = value;
}

