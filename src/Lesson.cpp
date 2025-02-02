#include "Lesson.h"

#include <utility>

/**
 * @brief Construtor da classe Lesson.
 * Complexidade: O(1).
 * @param weekDay - Dia da semana.
 * @param startTime - Início da aula.
 * @param duration - Duração.
 * @param ucType - Tipo ( "T" / "TP" / "PL" ).
 * @param ucSpecificClass - Turma à qual a aula está associada.
 */
Lesson::Lesson(std::string weekDay, float startTime, float duration, std::string ucType,
               UCSpecificClass ucSpecificClass) : _weekDay(std::move(weekDay)), _startTime(startTime),
                                                  _duration(duration),
                                                  _ucType(std::move(ucType)),
                                                  _ucSpecificClass(std::move(ucSpecificClass)) {}

/**
 * @brief Permite obter o início da aula.
 * Complexidade: O(1).
 * @return Início da aula.
 */
float Lesson::getStartTime() const {
    return _startTime;
}

/**
 * @brief Permite obter a duração da aula.
 * Complexidade: O(1).
 * @return Duração da aula.
 */
float Lesson::getDuration() const {
    return _duration;
}

/**
 * @brief Permite obter o tipo da aula.
 * Complexidade: O(1).
 * @return Tipo da aula.
 */
const std::string &Lesson::getUcType() const {
    return _ucType;
}

/**
 * @brief Permite obter o dia da semana da aula, em formato numérico.
 * Complexidade: O(1).
 * @return Número correspondente ao dia da semana da aula.
 */
int Lesson::getDayValue() const {
    static std::map<std::string, int> dayToValue = {
            {"Monday", 0},
            {"Tuesday", 1},
            {"Wednesday", 2},
            {"Thursday", 3},
            {"Friday", 4},
            {"Saturday", 5},
            {"Sunday", 6}
    };
    return dayToValue[_weekDay];
}

/**
 * @brief Permite comparar o dia de duas aulas.
 * Complexidade: O(1).
 * @param other - Aula a comparar.
 * @return Verdadeiro se o dia da aula for menor que o da outra, falso caso contrário.
 */
bool Lesson::operator<(const Lesson &other) const {
    if (getDayValue() == other.getDayValue()) {
        return getStartTime() < other.getStartTime();
    }
    return getDayValue() < other.getDayValue();
}

/**
 * @brief Permite obter o dia da semana da aula.
 * Complexidade: O(1).
 * @return Dia da semana da aula.
 */
const std::string &Lesson::getWeekDay() const {
    return _weekDay;
}

/**
 * @brief Permite obter a turma à qual a aula está associada.
 * Complexidade: O(1).
 * @return Turma à qual a aula está associada.
 */
const UCSpecificClass &Lesson::getUcSpecificClass() const {
    return _ucSpecificClass;
}

/**
 * @brief Permite verificar se duas aulas se sobrepõem.
 * Complexidade: O(1).
 * @param other - Aula a comparar.
 * @return Verdadeiro se as aulas se sobrepõem, falso caso contrário.
 */
bool Lesson::isOverlapping(const Lesson &other) const {
    if (_weekDay != other.getWeekDay()) {
        return false;
    }
    else if (_ucType == "T" || other.getUcType() == "T") {
        return false;
    }
    else if (_startTime >= (other.getStartTime() + other.getDuration()) || (_startTime + _duration) <= other.getStartTime()) {
        return false;
    }
    return true;
}

