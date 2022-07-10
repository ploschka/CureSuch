    #pragma once
#include <string>

class Note
{
private:
    std::string discipline;
    std::string theme;
    std::string number;
public:
    Note(std::string discipline, std::string theme, std::string number);
    Note() = default;

    bool operator<(const Note& other) const;
    bool operator>(const Note& other) const;
    bool operator>=(const Note& other) const;
    bool operator==(const Note& other) const;

    std::string getDiscipline() const;
    std::string getTheme() const;
    std::string getNumber() const;
};

std::string note_to_string(const Note& n);
std::ostream& operator<<(std::ostream& os, const Note& n);
