#include "Note.h"

Note::Note(std::string discipline, std::string theme, std::string number):
    discipline(discipline), theme(theme), number(number){}

bool Note::operator<(const Note& other) const
{
    if(this->discipline != other.discipline)
    {
        return this->discipline < other.discipline;
    }
    else if(this->theme != other.theme)
    {
        return this->theme < other.theme;
    }
    return false;
}
bool Note::operator>(const Note& other) const
{
    return other < *this;
}
bool Note::operator>=(const Note& other) const
{
    return !(*this < other);
}
bool Note::operator==(const Note& other) const
{
    return (this->discipline == other.discipline && this->theme == other.theme && this->number == other.number);
}

std::string Note::getDiscipline() const
{
    return discipline;
}
std::string Note::getTheme() const
{
    return theme;
}
std::string Note::getNumber() const
{
    return number;
}

std::string note_to_string(const Note& n)
{
    return (n.getDiscipline() + ' ' + n.getTheme() + ' ' + n.getNumber());
}

std::ostream& operator<<(std::ostream& os, const Note& n)
{
    os << note_to_string(n);
    return os;
}
