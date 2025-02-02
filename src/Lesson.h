#ifndef PROJECT_1_SCHEDULE_LESSON_H
#define PROJECT_1_SCHEDULE_LESSON_H

#include <vector>
#include <string>
#include <map>
#include "UCSpecificClass.h"

/**
 * @brief Classe que representa uma aula em específico dentro de um horário.
 */

class Lesson {
public:

    Lesson(std::string weekDay, float startTime, float duration, std::string ucType,
           UCSpecificClass ucSpecificClass);

    [[nodiscard]] float getStartTime() const;

    [[nodiscard]] float getDuration() const;

    [[nodiscard]] const std::string &getUcType() const;

    [[nodiscard]] const std::string &getWeekDay() const;

    [[nodiscard]] int getDayValue() const;

    [[nodiscard]] const UCSpecificClass &getUcSpecificClass() const;

    [[nodiscard]] bool isOverlapping(const Lesson &other) const;

    bool operator<(const Lesson &rhs) const;

private:
    /** @brief Dia da semana. */
    std::string _weekDay;
    /** @brief Início da aula. */
    float _startTime;
    /** @brief Duração. */
    float _duration;
    /** @brief Tipo ( "T" / "TP" / "PL" ). */
    std::string _ucType;
    /** @brief Turma à qual a aula está associada. */
    UCSpecificClass _ucSpecificClass;

};


#endif //PROJECT_1_SCHEDULE_LESSON_H
