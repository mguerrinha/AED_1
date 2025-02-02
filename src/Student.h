#ifndef PROJECT_1_SCHEDULE_STUDENT_H
#define PROJECT_1_SCHEDULE_STUDENT_H


#include <string>
#include <vector>
#include "UCSpecificClass.h"

/**
 * @brief Classe que representa um aluno, armazenando informações essenciais sobre o mesmo.
 */

class Student {
public:

    Student(unsigned int studentCode, std::string name);

    Student();

    [[nodiscard]] unsigned int getStudentCode() const;

    [[nodiscard]] const std::string &getName() const;

    [[nodiscard]] const std::vector <UCSpecificClass> &getTurmas() const;

    void addTurma(const UCSpecificClass &ucSpecificClass);

    UCSpecificClass changeTurma(const UCSpecificClass &newTurma);

    void removeTurma(const std::string &ucCode);

    [[nodiscard]] bool isEnrolledUc(const std::string &ucCode) const;

    [[nodiscard]] UCSpecificClass findUCSpecificClass(const std::string &ucCode) const;

    bool operator == (const Student &rhs) const;

    bool operator < (const Student &rhs) const;

    bool operator > (const Student &rhs) const;

private:
    /** @brief Id do estudante. */
    unsigned int _studentCode{};
    /** @brief Nome do estudante. */
    std::string _name;
    /** @brief Turmas às quais pertence. */
    std::vector <UCSpecificClass> _turmas;
};


#endif //PROJECT_1_SCHEDULE_STUDENT_H
