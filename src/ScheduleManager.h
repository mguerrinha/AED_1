#ifndef PROJECT_1_SCHEDULE_SCHEDULEMANAGER_H
#define PROJECT_1_SCHEDULE_SCHEDULEMANAGER_H


#include <set>
#include <list>
#include <map>
#include <queue>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <stack>
#include "Student.h"
#include "Class.h"
#include "Requests.h"

/**
 * @brief Classe que permite obter informações dos horários (seja turma ou uc), dos pedidos e dos estudantes.
 */

class ScheduleManager {

public:
    ScheduleManager();

    void load_classes(const std::string &file);

    void load_students_classes(const std::string &file);

    unsigned int displayAllStudents();

    void displayStudentsPerYear(const std::string& year);

    void displayScheduleOfAStudent(unsigned int up);

    void displayStudentsWithNUcs(int n);

    void displayClassSchedule(const std::string &classCode);

    static std::string displaySomeUcs(const char &ano);

    std::string displaySomeClasses(const char &ano);

    void displayStudentsFromClass(const UCSpecificClass& ucClass);

    void displayStudentsFromUC(const std::string &ucCode);

    void displayCurriculumSchedule(const std::string &ucCode);

    std::string displayAllUcs();

    void displayMostFilledUc();

    static std::string normalizeHours(float horas);

    static std::string ucCodeToName(const std::string &ucCode);

    static std::vector<std::string> UcsOfAClasse(const char &ano);

    [[nodiscard]] Student* findStudent(unsigned int studentCode);

    [[nodiscard]] Class* findClass(const UCSpecificClass& ucSpecificClass);

    bool findUc(const std::string& ucCode);

    [[nodiscard]] int getNumOfPendingRequests() const;

    void printPendingRequests() const;

    void printRejectedRequests();

    void SubmitChangeClassRequest(Student* student);

    void addChangeClassRequest(const Student &student, const UCSpecificClass &ucSpecificClass);

    void SubmitChangeUcRequest(Student* student);

    void addChangeUcRequest(const Student &student, const UCSpecificClass &ucSpecificClass, const std::string &ucCurrent);

    void SubmitRemovalRequest(Student* student);

    void addRemovalRequest(const Student &student, const UCSpecificClass &ucSpecificClass);

    void SubmitEnrollmentRequest(Student* student);

    void addEnrollmentRequest(const Student &student, const UCSpecificClass &ucSpecificClass);

    bool overlapClasses(const UCSpecificClass &ucSpecificClass, const UCSpecificClass &ucSpecificClassDesired);

    bool exceedsCapacity(const Requests &request);

    static unsigned int maxCapacity(const UCSpecificClass &ucSpecificClass);

    bool balancedClasses(const UCSpecificClass &ucSpecificClass, const UCSpecificClass &ucSpecificClassDesired);

    double desvioClasses(const UCSpecificClass &ucSpecificClass);

    double desvioAfterChange(const UCSpecificClass &ucSpecificClass, const UCSpecificClass &ucSpecificClassDesired, const unsigned int &sizeClass, const unsigned int &sizeClassDesired);

    void processRemovalRequests(const Requests& request);

    void processEnrollmentRequests(const Requests& request);

    void processChangeClassRequests(const Requests& request);

    void processChangeUcRequests(const Requests& request, const std::string &ucCurrent);

    void processRequests();

    char displayClassesYears();

    void undoLastRequest();

private:
    /** @brief Permite obter informações de um aluno em específico usando o seu número UP que está associado ao objeto 'Student', tendo assim acesso aos seus atributos. */
    std::map<unsigned int, Student> _students;
    /** @brief Permite mapear uma turma específica (UCSpecificClass) a um objeto da classe 'Class', obtendo acesso aos seus atributos (horário e alunos matriculados). */
    std::map<UCSpecificClass, Class> _classes;
    /** @brief Armazena-se os pedidos de troca de turma. */
    std::queue<Requests> _changeClassRequests;
    /** @brief Armazena-s os pedidos de troca de UC. */
    std::queue<std::pair<Requests, std::string>> _changeUcRequests;
    /** @brief Armazena-se os pedidos de cancelamento de uma UC. */
    std::queue<Requests> _removalRequests;
    /** @brief Armazena-se os pedidos de inscrição numa UC. */
    std::queue<Requests> _enrollmentRequests;
    /** @brief Armazena-se os pedidos que foram rejectados após processamento. */
    std::vector<std::pair<Requests, std::string>> _rejectedRequests;
    /** @brief Armazena-se os pedidos que foram aceites após processamento. */
    std::stack<Requests> _acceptedRequests;
    /** @brief Permite escolher a forma de visualização da lista de estudantes (alfabética ou numérica). */
    static void displaySortedStudents(const std::set<Student>& students);
    /** @brief Atualiiza o ficheiro CSV com os pedidos de troca de turma. */
    void UpdateStudentsClassesCSV();

};


#endif //PROJECT_1_SCHEDULE_SCHEDULEMANAGER_H
