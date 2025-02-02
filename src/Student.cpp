#include "Student.h"

/**
 * @brief Construtor default da classe Student.
 * Complexidade: O(1).
 */
Student::Student() = default;

/**
 * @brief Construtor da classe Student.
 * Complexidade: O(1).
 * @param studentCode - Id do estudante.
 * @param name - Nome do estudante.
 */
Student::Student(unsigned int studentCode, std::string name) : _studentCode(studentCode), _name(std::move(name)) {}

/**
 * @brief Permite obter o id do estudante.
 * Complexidade: O(1).
 * @return Id do estudante.
 */
unsigned int Student::getStudentCode() const {
    return _studentCode;
}

/**
 * @brief Permite obter o nome do estudante.
 * Complexidade: O(1).
 * @return Nome do estudante.
 */
const std::string &Student::getName() const {
    return _name;
}

/**
 * @brief Permite obter as turmas às quais o estudante pertence.
 * Complexidade: O(1).
 * @return Vetor com as turmas às quais o estudante pertence.
 */
const std::vector<UCSpecificClass> &Student::getTurmas() const {
    return _turmas;
}

/**
 * @brief Permite adicionar uma turma ao vetor de turmas do estudante.
 * Complexidade: O(1).
 * @param ucSpecificClass - Turma a adicionar.
 */
void Student::addTurma(const UCSpecificClass &ucSpecificClass) {
    _turmas.push_back(ucSpecificClass);
}

/**
 * @brief Permite alterar a turma de um estudante.
 * Complexidade: O(N).
 * @param newTurma - Nova turma.
 * @return Turma antiga.
 */
UCSpecificClass Student::changeTurma(const UCSpecificClass &newTurma) {
    for (auto & turma : _turmas) {
        if (turma.getUcCode() == newTurma.getUcCode()) {
            UCSpecificClass oldTurma = turma;
            turma = newTurma;
            return oldTurma;
        }
    }
    return {};
}

/**
 * @brief Permite remover uma turma do vetor de turmas do estudante.
 * Complexidade: O(N).
 * @param ucCode - Id da turma a remover.
 */
void Student::removeTurma(const std::string &ucCode) {
    for (int i = 0; i < _turmas.size(); i++) {
        if (_turmas.at(i).getUcCode() == ucCode) {
            _turmas.erase(_turmas.begin() + i);
            return;
        }
    }
}

/**
 * @brief Permite verificar se um estudante está matriculado numa determinada UC.
 * Complexidade: O(N).
 * @param ucCode - Id da UC.
 * @return Verdadeiro se o estudante estiver matriculado na UC, falso caso contrário.
 */
bool Student::isEnrolledUc(const std::string &ucCode) const {
    for (const UCSpecificClass &turma: _turmas) {
        if (turma.getUcCode() == ucCode) {
            return true;
        }
    }
    return false;
}

/**
 * @brief Permite obter uma turma específica de um estudante.
 * Complexidade: O(N).
 * @param ucCode - Id da UC.
 * @return Turma específica.
 */
UCSpecificClass Student::findUCSpecificClass(const std::string &ucCode) const {
    for (const UCSpecificClass &turma: _turmas) {
        if (turma.getUcCode() == ucCode) {
            return turma;
        }
    }
    return {};
}

/**
 * @brief Permite verificar se dois estudantes são iguais.
 * Complexidade: O(1).
 * @param rhs - Estudante a comparar.
 * @return Verdadeiro se os estudantes forem iguais, falso caso contrário.
 */
bool Student::operator==(const Student &rhs) const {
    return _studentCode == rhs._studentCode;
}

/**
 * @brief Permite verificar se um estudante é menor que outro.
 * Complexidade: O(1).
 * @param rhs - Estudante a comparar.
 * @return Verdadeiro se o estudante for menor que o outro, falso caso contrário.
 */
bool Student::operator<(const Student &rhs) const {
    return _studentCode < rhs._studentCode;
}

/**
 * @brief Permite verificar se um estudante é maior que outro.
 * Complexidade: O(1).
 * @param rhs - Estudante a comparar.
 * @return Verdadeiro se o estudante for maior que o outro, falso caso contrário.
 */
bool Student::operator>(const Student &rhs) const {
    return _studentCode > rhs._studentCode;
}






