#include "UCSpecificClass.h"

/**
 * @brief Construtor default da classe UCSpecificClass.
 * Complexidade: O(1).
 */
UCSpecificClass::UCSpecificClass() = default;

/**
 * @brief Construtor da classe UCSpecificClass que recebe o id de uma turma e o id de uma UC.
 * Complexidade: O(1).
 * @param classCode
 * @param ucCode
 */
UCSpecificClass::UCSpecificClass(std::string classCode, std::string ucCode) : _classCode(std::move(classCode)), _ucCode(std::move(ucCode)) {}

/**
 * @brief Permite obter o id de uma turma.
 * Complexidade: O(1).
 * @return Id da turma.
 */
const std::string &UCSpecificClass::getClassCode() const {
    return _classCode;
}

/**
 * @brief Permite obter o id de uma UC.
 * Complexidade: O(1).
 * @return Id da UC.
 */
const std::string &UCSpecificClass::getUcCode() const {
    return _ucCode;
}

/**
 * @brief Verifica se uma UCSpecificClass é menor que outra, tendo em conta o id da UC e o id da turma.
 * Complexidade: O(N).
 * @param rhs
 * @return
 */
bool UCSpecificClass::operator<(const UCSpecificClass &rhs) const {
    if (_ucCode < rhs._ucCode)
        return true;
    if (rhs._ucCode < _ucCode)
        return false;
    return _classCode < rhs._classCode;
}

/**
 * @brief Verifica se uma UCSpecificClass é igual a outra, tendo em conta o id da UC e o id da turma.
 * Complexidade: O(N).
 * @param rhs
 * @return
 */
bool UCSpecificClass::operator==(const UCSpecificClass &rhs) const {
    return _ucCode == rhs._ucCode &&
           _classCode == rhs._classCode;
}

/**
 * @brief Verifica se uma UCSpecificClass é diferente de outra, tendo em conta o id da UC e o id da turma.
 * Complexidade: O(N).
 * @param rhs
 * @return
 */
bool UCSpecificClass::operator!=(const UCSpecificClass &rhs) const {
    return !(rhs == *this);
}

/**
 * @brief Verifica se uma UCSpecificClass é maior que outra, tendo em conta o id da UC e o id da turma.
 * Complexidade: O(N).
 * @param rhs
 * @return
 */
bool UCSpecificClass::operator>(const UCSpecificClass &rhs) const {
    if (_ucCode == rhs._ucCode) return _classCode > rhs._classCode;
    return _ucCode > rhs._ucCode;
}


