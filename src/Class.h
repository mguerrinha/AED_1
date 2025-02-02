#ifndef PROJECT_1_SCHEDULE_CLASS_H
#define PROJECT_1_SCHEDULE_CLASS_H


#include <list>
#include <set>
#include "UCSpecificClass.h"
#include "Lesson.h"

/**
 * @brief Classe que representa uma turma de uma unidade curricular específica.
 * Nesta, são armazenadas informações como a lista de aulas (horário) da turma e uma lista de estudantes que a compõe.
 */

class Class {
public:

    Class();

    Class(UCSpecificClass ucClass, const std::vector <Lesson> &lessons);

    [[nodiscard]] const UCSpecificClass &getUcClass() const;

    [[nodiscard]] const std::vector <Lesson> &getLessons() const;

    void addLesson(const Lesson &lesson);

    void addStudent(unsigned int studentID);

    void removeStudent(unsigned int studentID);

    [[nodiscard]] const std::set <unsigned int> &getStudentsIDs() const;

private:
    /** @brief Turma à qual as informações remetem. */
    UCSpecificClass _ucClass;
    /** @brief Conjunto de aulas da turma. */
    std::vector <Lesson> _lessons;
    /** @brief Lista de alunos da turma. */
    std::set <unsigned int> _studentsIDs;
};


#endif //PROJECT_1_SCHEDULE_CLASS_H