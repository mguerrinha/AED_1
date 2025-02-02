#ifndef PROJECT_1_SCHEDULE_REQUESTS_H
#define PROJECT_1_SCHEDULE_REQUESTS_H

#include "Student.h"
#include <iostream>

/**
 * @brief Classe que permite armazenar as informações sobre um pedido.
 */

class Requests {
public:
    Requests(const Student &student, const UCSpecificClass &desiredClass, const std::string &typeRequest);

    [[nodiscard]] Student getStudent() const;

    [[nodiscard]] UCSpecificClass getDesiredClass() const;

    std::string gettypeRequest();
private:
    /** @brief Aluno associado ao pedido. */
    Student _student;
    /** @brief Turma desejada. */
    UCSpecificClass _desiredClass;
    /** @brief Tipo de pedido ( "Change" / "Enrollment" / "Removal" ). */
    std::string _typeRequest;
};


#endif //PROJECT_1_SCHEDULE_REQUESTS_H
