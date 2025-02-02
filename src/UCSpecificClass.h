#ifndef PROJECT_1_SCHEDULE_UCSPECIFICCLASS_H
#define PROJECT_1_SCHEDULE_UCSPECIFICCLASS_H


#include <string>

/**
 * @brief Classe que representa uma identificação especĩfica de uma turma. Não representa uma turma em si, mas sim uma identificação para diferenciar as turmas entre si.
 */

class UCSpecificClass {
public:

    UCSpecificClass();

    UCSpecificClass(std::string classCode, std::string ucCode);

    [[nodiscard]] const std::string &getClassCode() const;

    [[nodiscard]] const std::string &getUcCode() const;

    bool operator<(const UCSpecificClass &rhs) const;

    bool operator==(const UCSpecificClass &rhs) const;

    bool operator!=(const UCSpecificClass &rhs) const;

    bool operator>(const UCSpecificClass &rhs) const;

private:
    /** @brief Id de uma UC. */
    std::string _ucCode;
    /** @brief Id de uma turma. */
    std::string _classCode;
};


#endif //PROJECT_1_SCHEDULE_UCSPECIFICCLASS_H
