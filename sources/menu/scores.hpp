#pragma once

class Scores
{

  public:

    Scores();

    void parseFile(const std::string &filename);
    const std::map<std::string, std::string> &getScores() const;

  private:
    std::map<std::string, std::string> scores;
    bool isParsedFile;
};
