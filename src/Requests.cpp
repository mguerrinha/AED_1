#include "Requests.h"

/**
 * @brief Construtor da classe Requests.
 * Complexidade: O(1).
 * @param student Aluno associado ao pedido.
 * @param desiredClass Turma desejada.
 * @param typeRequest Tipo de pedido ( "Change" / "Enrollment" / "Removal" ).
 */
Requests::Requests(const Student &student, const UCSpecificClass &desiredClass, const std::string &typeRequest) {
    _student = student;
    _desiredClass = desiredClass;
    _typeRequest = typeRequest;
}

/**
 * @brief Permite obter o aluno associado ao pedido.
 * Complexidade: O(1).
 * @return Aluno associado ao pedido.
 */
Student Requests::getStudent() const {
    return _student;
}

/**
 * @brief Permite obter a turma desejada.
 * Complexidade: O(1).
 * @return Turma desejada.
 */
UCSpecificClass Requests::getDesiredClass() const {
    return _desiredClass;
}

/**
 * @brief Permite obter o tipo de pedido.
 * Complexidade: O(1).
 * @return Tipo de pedido.
 */
std::string Requests::gettypeRequest() {
    return _typeRequest;
}