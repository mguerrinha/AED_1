#include "Class.h"

/**
 * @brief Construtor da classe Class.
 * Complexidade: O(1).
 * @param ucClass - Turma à qual as informações remetem.
 * @param lessons - Conjunto de aulas da turma.
 */
Class::Class(UCSpecificClass ucClass, const std::vector<Lesson> &lessons) : _ucClass(std::move(ucClass)), _lessons(lessons) {}

/**
 * @brief Permite obter a turma à qual as informações remetem.
 * Complexidade: O(1).
 * @return Turma desejada.
 */
const UCSpecificClass &Class::getUcClass() const {
    return _ucClass;
}

/**
 * @brief Permite obter o conjunto de aulas da turma.
 * Complexidade: O(1).
 * @return Vetor que representa o conjunto de aulas da turma.
 */
const std::vector<Lesson> &Class::getLessons() const {
    return _lessons;
}

/**
 * @brief Permite adicionar uma aula ao conjunto de aulas da turma.
 * Complexidade: O(1).
 * @param lesson - Aula a adicionar.
 */
void Class::addLesson(const Lesson &lesson) {
    _lessons.push_back(lesson);
}

/**
 * @brief Permite adicionar um aluno à turma.
 * Complexidade: O(1).
 * @param studentID - Id do aluno a adicionar.
 */
void Class::addStudent(unsigned int studentID) {
    _studentsIDs.insert(studentID);
}

/**
 * @brief Permite remover um aluno da turma.
 * Complexidade: O(1).
 * @param studentID - Id do aluno a remover.
 */
void Class::removeStudent(unsigned int studentID) {
    _studentsIDs.erase(studentID);
}

/**
 * @brief Permite obter o conjunto de alunos da turma.
 * Complexidade: O(1).
 * @return Conjunto de alunos da turma, tendo em conta os seus ids.
 */
const std::set<unsigned int> &Class::getStudentsIDs() const {
    return _studentsIDs;
}

/**
 * @brief Construtor default da classe Class.
 * Complexidade: O(1).
 */
Class::Class() = default;
